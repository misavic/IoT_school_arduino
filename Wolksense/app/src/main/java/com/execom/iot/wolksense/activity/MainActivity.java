package com.execom.iot.wolksense.activity;

import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

import com.execom.iot.wolksense.R;
import com.execom.iot.wolksense.restService.Service;
import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.JsonElement;

import org.adw.library.widgets.discreteseekbar.DiscreteSeekBar;
import org.androidannotations.annotations.Background;
import org.androidannotations.annotations.Click;
import org.androidannotations.annotations.EActivity;
import org.androidannotations.annotations.ViewById;
import org.androidannotations.rest.spring.annotations.RestService;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import org.springframework.http.HttpHeaders;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

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

    DiscreteSeekBar seekBar;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        context = this;
        prefs = getSharedPreferences(SignInActivity.SH_PREFS_USER, MODE_PRIVATE);

        seekBar = (DiscreteSeekBar) findViewById(R.id.seekData);

        etActuatorData.setVisibility(View.INVISIBLE);
    }

    @Click(R.id.btn_actuate)
    public void actuateBtn(){
        String pointName = etPointName.getText().toString();
        String actuatorReference = etActuatorReference.getText().toString();
        String actuatorData = etActuatorData.getText().toString();
        actuate(pointName, actuatorReference, seekBar.getProgress()); //Integer.parseInt(actuatorData));
    }

    @Background
    public void actuate(String pointName, String actReference, int data){
        try {
            String token = prefs.getString(SignInActivity.KEY_TOKEN, null);
            restService.setHeader("Authorization", "Bearer "+token);
            Log.d(SignInActivity.LOG_TAG, restService.getHeader("Authorization"));
            String pointsSerialised = restService.getPoints().toString();
            Log.d(SignInActivity.LOG_TAG, pointsSerialised);
            String noSpace = pointsSerialised.replaceAll(" ", "");
            noSpace = noSpace.replaceAll("/", "");
            noSpace = noSpace.replaceAll("unit=,", "");
            //JSONObject



            //Pattern pattern = Pattern.compile("(Temp)(Android)");
                    //("\\\"id\\\":\\s*([0-9]*),\\s*\\\"name\\\":\\s*\\\"TempAndroid\\\"[\\s\\S]*\\\"actuators\\\"[\\s\\S]*\\\"id\\\":\\s*([0-9]*),\\s*\\\"name\\\":\\s*\\\"[0-9a-zA-Z ]*\\\",\\s*\\\"reference\\\":\\s*\\\"TAA\\\"");
            //Matcher matcher = pattern.matcher(pointsSerialised);

            //String pointId = "";
            //String actuatorId = "";
/*
            //if(matcher.find()){
            if(true){
                //pointId = matcher.group(1);
                //Log.d(SignInActivity.LOG_TAG, "PointId: " + pointId);
                //actuatorId = matcher.group(2);
                //Log.d(SignInActivity.LOG_TAG, "actuatorId: " + actuatorId);

                try {
                    restService.actuate(pointId, actuatorId, "43");
                    Snackbar.make(btnActuate, "Successful actuation", Snackbar.LENGTH_LONG).show();
                } catch (Exception e) {
                    Log.e(SignInActivity.LOG_TAG, "Exception: ", e);
                    Snackbar.make(btnActuate, "Something went wrong", Snackbar.LENGTH_LONG).show();
                }
            }
*/
            //JSONArray points = new JSONArray(pointsSerialised);
            //GsonBuilder gsonBuilder = new GsonBuilder();
            //JSONObject[] gsonPoints = gsonBuilder.create().fromJson(pointsSerialised, JSONObject[].class);

            JSONArray points = new JSONArray(noSpace);

            for(int i = 0; i < points.length(); i++){

                //JSONObject point = new JSONObject(points.get(i).toString());
                JSONObject point = new JSONObject(points.get(i).toString());

                //gsonPoints[i].fromJson("")
                String name = point.getString("name");
                if (name.equals(pointName)){

                    String pointIdF = point.getString("id");
                    Log.d(SignInActivity.LOG_TAG, "PointId: " + pointIdF);
                    String actsSerialised = point.getJSONArray("actuators").toString();
                    JSONArray actuators = new JSONArray(actsSerialised);
                    for(int j=0; j < actuators.length(); j++){

                        String actSerialised = actuators.get(j).toString();
                        JSONObject actuator = new JSONObject(actSerialised);
                        if(actuator.getString("reference").equals(actReference)){

                            String actId = actuator.getString("id");
                            Log.d(SignInActivity.LOG_TAG, "actId: " + actId);
                            //restService.setHeader(HttpHeaders.CONTENT_TYPE, "application/json");
                            //restService.actuate(pointId, actId, data);
                            restService.actuate(pointIdF, actId, data);
                            //Log.d(SignInActivity.LOG_TAG, actuateRes);
                        }
                    }
                }
            }

        } catch (Exception e) {
            Log.d(SignInActivity.LOG_TAG, "ExceptionDIS:", e);
        }
    }
}
