package com.bedic.smartlightapp;

import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.os.Handler;
import android.os.Message;
import android.util.Log;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.Serializable;
import java.util.UUID;

public class Peripherique implements Serializable {
    private String nom;
    private String adresse;
    private Handler handler = null;
    private BluetoothDevice device = null;
    private BluetoothSocket socket = null;
    private InputStream receiveStream = null;
    private OutputStream sendStream = null;
    private TReception tReception;
    public final static int CODE_CONNEXION = 0;
    public final static int CODE_RECEPTION = 1;
    public final static int CODE_DECONNEXION = 2;

    public Peripherique(BluetoothDevice device, Handler handler)
    {
        if(device != null)
        {
            this.device = device;
            this.nom = device.getName();
            this.adresse = device.getAddress();
            this.handler = handler;
        }
        else
        {
            this.device = device;
            this.nom = "Aucun";
            this.adresse = "";
            this.handler = handler;
        }

        try
        {
            socket = device.createRfcommSocketToServiceRecord(UUID.fromString("00001101-0000-1000-8000-00805F9B34FB"));
            receiveStream = socket.getInputStream();
            sendStream = socket.getOutputStream();
        }
        catch (IOException e)
        {
            e.printStackTrace();
            socket = null;
        }

        if(socket != null)
            tReception = new TReception(handler, receiveStream);
    }

    public String getNom()
    {
        return nom;
    }

    public String getAdresse()
    {
        return adresse;
    }

    public boolean estConnecte()
    {
       return socket.isConnected();
    }

    public void setNom(String nom)
    {
        this.nom = nom;
    }

    public String toString()
    {
        return "\nNom : " + nom + "\nAdresse : " + adresse;
    }

    public void connecter()
    {
        new Thread()
        {
            @Override public void run()
            {
                try
                {
                    socket.connect();

                    Message msg = Message.obtain();
                    msg.arg1 = CODE_CONNEXION;
                    msg.obj = (Object)"Connect Ok";
                    handler.sendMessage(msg);

                    tReception.start();

                }
                catch (IOException e)
                {
                    System.out.println("<Socket> error connect");
                    e.printStackTrace();
                }
            }
        }.start();
    }

    public boolean deconnecter()
    {
        try
        {
            tReception.arreter();

            socket.close();
            return true;
        }
        catch (IOException e)
        {
            System.out.println("<Socket> error close");
            e.printStackTrace();
            return false;
        }
    }

    public void envoyer(final String data)
    {
        if(socket == null)
            return;

        new Thread()
        {
            @Override public void run()
            {
                try
                {
                    if(socket.isConnected())
                    {
                        sendStream.write(data.getBytes());
                        sendStream.flush();
                        System.out.println("<Socket> Message Send");
                    }
                    else
                    {
                        System.out.println("<Socket> Message Send Error");
                    }
                }
                catch (IOException e)
                {
                    System.out.println("<Socket> error send");
                    e.printStackTrace();
                }
            }
        }.start();
    }

    private class TReception extends Thread {
        Handler handlerUI;
        InputStream _receiveStream;
        private boolean fini;

        TReception(Handler h, InputStream _in) {
            handlerUI = h;
            _receiveStream = _in;
            fini = false;
        }

        @Override
        public void run() {
            BufferedReader reception = new BufferedReader(new InputStreamReader(_receiveStream));
            while (!fini) {
                try {
                    String trame = "";
                    if (reception.ready()) {
                        trame = reception.readLine();
                        System.out.println("<Socket>"+trame);
                    }
                    if (trame.length() > 0) {
                        //Log.d(TAG, "run() trame : " + trame);
                        Message msg = Message.obtain();
                        msg.what = Peripherique.CODE_RECEPTION;
                        msg.obj = trame;
                        handlerUI.sendMessage(msg);
                    }
                } catch (IOException e) {
                    System.out.println("<Socket> error read");
                    e.printStackTrace();
                }
                try {
                    Thread.sleep(250);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }

        public void arreter() {
            if (fini == false) {
                fini = true;
            }
            try {
                Thread.sleep(250);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
