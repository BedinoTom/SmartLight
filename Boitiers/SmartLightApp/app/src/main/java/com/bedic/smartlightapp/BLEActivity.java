package com.bedic.smartlightapp;

import android.bluetooth.BluetoothDevice;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.Toast;

import java.util.Set;

import androidx.appcompat.app.AppCompatActivity;

public class BLEActivity extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_ble);

        final ListView listView = (ListView)findViewById(R.id.listView);

        Set<BluetoothDevice> devices = MainActivity.bluetoothAdapter.getBondedDevices();
        Peripherique users[] = new Peripherique[devices.toArray().length];
        int i=0;
        for (BluetoothDevice blueDevice : devices)
        {
            users[i] = new Peripherique(blueDevice,null);
            i++;
        }

        ArrayAdapter<Peripherique> arrayAdapter
                = new ArrayAdapter<>(this, android.R.layout.simple_list_item_1 , users);

        listView.setAdapter(arrayAdapter);
        listView.setOnItemClickListener(new AdapterView.OnItemClickListener() {

            @Override
            public void onItemClick(AdapterView<?> a, View v, int position, long id) {
                Object o = listView.getItemAtPosition(position);
                Peripherique p = (Peripherique)o;
                Intent returnIntent = new Intent();
                returnIntent.putExtra("address_choose",p.getAdresse());
                setResult(MainActivity.RESULT_OK,returnIntent);
                finish();
            }
        });
    }
}
