package com.rgb0101.lsh_test;

import android.app.Activity;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends Activity {
    private static final String LIB_NAME = "lshtest";
    public native static final void lshstart();
    public native static final void shastart();
    static{
        System.loadLibrary(LIB_NAME);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        ((Button)findViewById(R.id.getresult)).setOnClickListener(click);
        ((Button)findViewById(R.id.shagetresult)).setOnClickListener(click);
    }

    View.OnClickListener click= new View.OnClickListener(){
        @Override
        public void onClick(View v){
            int id= v.getId();

            if(id == R.id.getresult){
                ((TextView)findViewById(R.id.result)).setText("lsh start");
                lshstart();
                ((TextView)findViewById(R.id.result)).setText("lsh finish");
                Toast.makeText(getApplicationContext(), "LSH call", Toast.LENGTH_SHORT).show();
            } else if(id == R.id.shagetresult){
                ((TextView)findViewById(R.id.result)).setText("sha start");
                shastart();
                ((TextView)findViewById(R.id.result)).setText("sha finish");
                Toast.makeText(getApplicationContext(), "SHA call", Toast.LENGTH_SHORT).show();
            }
        }
    };
}