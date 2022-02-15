package com.bedic.smartlightapp;

import android.graphics.Color;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.Switch;
import android.widget.TextView;

import java.util.ArrayList;

import androidx.appcompat.app.AppCompatActivity;

public class PilotActivity extends AppCompatActivity implements View.OnClickListener, CompoundButton.OnCheckedChangeListener {
    private Button bt_brake, bt_up, bt_down, bt_left, bt_right, bt_upa;
    private TextView text_connect;
    private Switch switch_armed;
    private boolean armed=false;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_pilot);
        
        bt_brake = (Button)findViewById(R.id.button8);
        bt_up = (Button)findViewById(R.id.button4);
        bt_down = (Button)findViewById(R.id.button7);
        bt_left = (Button)findViewById(R.id.button5);
        bt_right = (Button)findViewById(R.id.button6);
        bt_upa = (Button)findViewById(R.id.button9);

        bt_brake.setOnClickListener(this);
        bt_up.setOnClickListener(this);
        bt_down.setOnClickListener(this);
        bt_left.setOnClickListener(this);
        bt_right.setOnClickListener(this);
        bt_upa.setOnClickListener(this);

        switch_armed = (Switch)findViewById(R.id.switch3);
        switch_armed.setOnCheckedChangeListener(this);

        text_connect = (TextView)findViewById(R.id.textView8);

        try {
            if(MainActivity.mConnect_device != null && MainActivity.mConnect_device.estConnecte())
            {
                text_connect.setTextColor(Color.GREEN);
                text_connect.setText("Connected");
            }
            else
            {
                text_connect.setTextColor(Color.RED);
                text_connect.setText("Not Connected");

                bt_brake.setEnabled(false);
                bt_up.setEnabled(false);
                bt_down.setEnabled(false);
                bt_left.setEnabled(false);
                bt_right.setEnabled(false);
                bt_upa.setEnabled(false);
                switch_armed.setEnabled(false);
            }
        }
        catch(PeripheriqueInternalError e)
        {
            e.printStackTrace();
            finish();
        }
    }

    @Override
    public void onClick(View v) {
        if(!armed)
        {
            MainActivity.mConnect_device.envoyer("dir=narmed;");
            return;
        }
        switch(v.getId())
        {
            case R.id.button4:
                MainActivity.mConnect_device.envoyer("dir=up;");
                break;
            case R.id.button5:
                MainActivity.mConnect_device.envoyer("dir=left;");
                break;
            case R.id.button6:
                MainActivity.mConnect_device.envoyer("dir=right;");
                break;
            case R.id.button7:
                MainActivity.mConnect_device.envoyer("dir=down;");
                break;
            case R.id.button8:
                MainActivity.mConnect_device.envoyer("dir=brake;");
                break;
            case R.id.button9:
                MainActivity.mConnect_device.envoyer("dir=climb;");
                break;
        }
    }

    @Override
    public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
        armed = isChecked;
    }
}
