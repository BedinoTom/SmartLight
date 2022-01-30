package com.bedic.smartlightapp;

import androidx.activity.result.ActivityResult;
import androidx.activity.result.ActivityResultCallback;
import androidx.activity.result.ActivityResultLauncher;
import androidx.activity.result.contract.ActivityResultContracts;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import androidx.drawerlayout.widget.DrawerLayout;
import androidx.navigation.NavController;
import androidx.navigation.Navigation;
import androidx.navigation.fragment.NavHostFragment;
import androidx.navigation.ui.AppBarConfiguration;
import androidx.navigation.ui.NavigationUI;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Context;
import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.ArrayMap;
import android.view.Gravity;
import android.view.View;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.Toast;

import com.google.android.material.appbar.CollapsingToolbarLayout;

import java.util.Map;
import java.util.Set;

public class MainActivity extends AppCompatActivity implements View.OnClickListener, CompoundButton.OnCheckedChangeListener {

    private final static int REQUEST_CODE_ENABLE_BLUETOOTH = 0;

    public static BluetoothAdapter bluetoothAdapter = null;
    public static Peripherique mConnect_device = null;

    private Context mContext;
    private Button bt_connect, bt_send_time;
    private Switch switch_light, switch_detect;
    private TextView text_link, text_light, text_detect_switch, text_detect;
    private EditText date_stop, time_stop;

    private Handler handler = new Handler() {
        @Override
        public void handleMessage(Message msg) {
            MyMessage rmsg = (MyMessage)msg.obj;
            if(rmsg.code == Peripherique.CODE_RECEPTION) {
                String k[] = rmsg.message.split(";");
                ArrayMap<String, String> map_value = new ArrayMap<>();
                for (String i : k) {
                    String sv[] = i.split("=");
                    if(sv.length >= 2) {
                        map_value.put(sv[0], sv[1]);
                    }
                }

                for (Map.Entry<String, String> entry : map_value.entrySet()) {
                    switch (entry.getKey()) {
                        case "light":
                            if (entry.getValue().equals("on")) {
                                text_light.setTextColor(Color.GREEN);
                                text_light.setText("On");
                            } else {
                                text_light.setTextColor(Color.RED);
                                text_light.setText("Off");
                            }
                            break;
                        case "detect":
                            if (entry.getValue().equals("on")) {
                                text_detect_switch.setTextColor(Color.GREEN);
                                text_detect_switch.setText("On");
                            } else {
                                text_detect_switch.setTextColor(Color.RED);
                                text_detect_switch.setText("Off");
                            }
                            break;
                        case "collide":
                            if (entry.getValue().equals("on")) {
                                text_detect.setTextColor(Color.GREEN);
                                text_detect.setText("On");
                            } else {
                                text_detect.setTextColor(Color.RED);
                                text_detect.setText("Off");
                            }
                            break;
                    }
                }
            }
        }
    };

    ActivityResultLauncher<Intent> someActivityResultLauncher = registerForActivityResult(
            new ActivityResultContracts.StartActivityForResult(),
            new ActivityResultCallback<ActivityResult>() {
                @Override
                public void onActivityResult(ActivityResult result) {
                    if (result.getResultCode() == Activity.RESULT_OK) {
                        Intent data = result.getData();
                        Set<BluetoothDevice> devices = MainActivity.bluetoothAdapter.getBondedDevices();
                        String addr = data.getStringExtra("address_choose");

                        for (BluetoothDevice blueDevice : devices) {
                            if(blueDevice.getAddress().equals(addr))
                            {
                                if(mConnect_device != null)
                                {
                                    mConnect_device.deconnecter();
                                }
                                mConnect_device = new Peripherique(blueDevice,handler);
                                break;
                            }
                        }
                        mConnect_device.connecter();
                        try {
                            while (!mConnect_device.estConnecte()) ;
                            bt_connect.setText("Disconnect");
                            text_link.setTextColor(Color.GREEN);
                            text_link.setText("Connected");

                            text_light.setText("None");

                            text_detect.setText("None");

                            text_detect_switch.setText("None");
                        }
                        catch(PeripheriqueInternalError e)
                        {
                            mConnect_device=null;
                            e.printStackTrace();
                        }
                    }
                }
            });

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mContext = getBaseContext();

        bt_connect = (Button)findViewById(R.id.button2);
        bt_connect.setOnClickListener(this);
        bt_send_time = (Button)findViewById(R.id.button);
        bt_send_time.setOnClickListener(this);
        switch_light = (Switch)findViewById(R.id.switch1);
        switch_light.setOnCheckedChangeListener(this);
        switch_detect = (Switch)findViewById(R.id.switch2);
        switch_detect.setOnCheckedChangeListener(this);

        text_link = (TextView)findViewById(R.id.textView7);
        text_light = (TextView)findViewById(R.id.textView);
        text_detect = (TextView)findViewById(R.id.textView5);
        text_detect_switch = (TextView)findViewById(R.id.textView4);

        text_link.setTextColor(Color.RED);
        text_link.setText("Not Connected");

        text_light.setTextColor(Color.RED);
        text_light.setText("Not Connected");

        text_detect.setTextColor(Color.RED);
        text_detect.setText("Not Connected");

        text_detect_switch.setTextColor(Color.RED);
        text_detect_switch.setText("Not Connected");

        time_stop = (EditText)findViewById(R.id.editTextTime);
        date_stop = (EditText)findViewById(R.id.editTextDate);

        init_BLE();
    }

    public void init_BLE()
    {
        bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        if (bluetoothAdapter == null)
        {
            Toast.makeText(getApplicationContext(), "Bluetooth non détecté !", Toast.LENGTH_SHORT).show();
        }
        else
        {
            if (!bluetoothAdapter.isEnabled())
            {
                Toast.makeText(getApplicationContext(), "Bluetooth non activé !", Toast.LENGTH_SHORT).show();
                // Possibilité 1 :
                Intent activeBlueTooth = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
                startActivityForResult(activeBlueTooth, REQUEST_CODE_ENABLE_BLUETOOTH);
            }
            else
            {
                Toast.makeText(getApplicationContext(), "Bluetooth activé", Toast.LENGTH_SHORT).show();
            }
        }
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data)
    {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode != REQUEST_CODE_ENABLE_BLUETOOTH)
            return;
        if (resultCode == RESULT_OK)
        {
            Toast.makeText(getApplicationContext(), "Bluetooth activé", Toast.LENGTH_SHORT).show();
        }
        else
        {
            Toast.makeText(getApplicationContext(), "Bluetooth non activé !", Toast.LENGTH_SHORT).show();
        }
    }

    @Override
    public void onClick(View v) {
        switch (v.getId())
        {
            case R.id.button:
                try {
                    if(mConnect_device != null && mConnect_device.estConnecte())
                    {
                        mConnect_device.envoyer("cmd=time_stop;arg1="+time_stop.getText().toString()+";arg2="+date_stop.getText().toString()+";");
                    }
                } catch (PeripheriqueInternalError peripheriqueInternalError) {
                    peripheriqueInternalError.printStackTrace();
                }
                break;
            case R.id.button2:
                try {
                    if(mConnect_device != null && mConnect_device.estConnecte())
                    {
                        mConnect_device.deconnecter();
                        mConnect_device=null;

                        bt_connect.setText("Connect");

                        text_link.setTextColor(Color.RED);
                        text_link.setText("Not Connected");

                        text_light.setTextColor(Color.RED);
                        text_light.setText("Not Connected");

                        text_detect.setTextColor(Color.RED);
                        text_detect.setText("Not Connected");

                        text_detect_switch.setTextColor(Color.RED);
                        text_detect_switch.setText("Not Connected");
                    }
                    else
                    {
                        Intent intent=new Intent(mContext,BLEActivity.class);
                        someActivityResultLauncher.launch(intent);
                    }
                } catch (PeripheriqueInternalError peripheriqueInternalError) {
                    peripheriqueInternalError.printStackTrace();
                }
                break;
        }
    }

    @Override
    public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
        switch(buttonView.getId())
        {
            case R.id.switch1:
                try {
                    if(mConnect_device != null && mConnect_device.estConnecte())
                    {
                        mConnect_device.envoyer("cmd=light;arg1="+isChecked+";");
                    }
                } catch (PeripheriqueInternalError peripheriqueInternalError) {
                    peripheriqueInternalError.printStackTrace();
                }
                break;
            case R.id.switch2:
                try {
                    if(mConnect_device != null && mConnect_device.estConnecte())
                    {
                        mConnect_device.envoyer("cmd=detect;arg1="+isChecked+";");
                    }
                } catch (PeripheriqueInternalError peripheriqueInternalError) {
                    peripheriqueInternalError.printStackTrace();
                }
                break;
        }
    }
}