package com.execom.iot.wolksense.activity;

import android.content.Context;
import android.content.SharedPreferences;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.Button;
import android.widget.EditText;

import com.execom.iot.wolksense.R;
import com.execom.iot.wolksense.restService.Service;
import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.JsonElement;

import org.androidannotations.annotations.Background;
import org.androidannotations.annotations.Click;
import org.androidannotations.annotations.EActivity;
import org.androidannotations.annotations.ViewById;
import org.androidannotations.rest.spring.annotations.RestService;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

@EActivity
public class MainActivity extends AppCompatActivity {


    @RestService
    static Service restService;

    SharedPreferences prefs;
    Context context;

    @ViewById(R.id.btn_actuate)
    Button btnActuate;

    @ViewById(R.id.et_point_name)
    EditText etPointName;
    @ViewById(R.id.et_actuator_reference)
    EditText etActuatorReference;
    @ViewById(R.id.et_actuator_data)
    EditText etActuatorData;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        context = this;
        prefs = getSharedPreferences(SignInActivity.SH_PREFS_USER, MODE_PRIVATE);
    }

    @Click(R.id.btn_actuate)
    public void actuateBtn(){
        String pointName = etPointName.getText().toString();
        String actuatorReference = etActuatorReference.getText().toString();
        String actuatorData = etActuatorData.getText().toString();
        actuate(pointName, actuatorReference, actuatorData);
    }

    @Background
    public void actuate(String pointName, String actReference, String data){
        try {
            String token = prefs.getString(SignInActivity.KEY_TOKEN, null);
            restService.setHeader("Authorization", "Bearer "+token);
            Log.d(SignInActivity.LOG_TAG, restService.getHeader("Authorization"));
            String pointsSerialised = restService.getPoints().toString();
            //JSONArray points = new JSONArray(pointsSerialised);
            GsonBuilder gsonBuilder = new GsonBuilder();
            JSONObject[] gsonPoints = gsonBuilder.create().fromJson(pointsSerialised, JSONObject[].class);

            for(int i = 0; i < gsonPoints.length; i++){

                //JSONObject point = new JSONObject(points.get(i).toString());
                JSONObject point = gsonPoints[i];

                //gsonPoints[i].fromJson("")
                String name = point.getString("name");
                if (name.equals(pointName)){

                    String pointId = point.getString("id");
                    String actsSerialised = point.getJSONArray("actuators").toString();
                    JSONArray actuators = new JSONArray(actsSerialised);
                    for(int j=0; j < actuators.length(); j++){

                        String actSerialised = actuators.get(j).toString();
                        JSONObject actuator = new JSONObject(actSerialised);
                        if(actuator.getString("reference").equals(actReference)){

                            String actId = actuator.getString("id");
                            String actuateRes = restService.actuate(pointId, actId, data).toString();
                            Log.d(SignInActivity.LOG_TAG, actuateRes);
                        }
                    }
                }
            }

        } catch (Exception e) {
            Log.d(SignInActivity.LOG_TAG, "Exception:", e);
        }
    }
}
