package com.execom.iot.wolksense.activity;

import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

import com.execom.iot.wolksense.R;
import com.execom.iot.wolksense.dto.SignInDto;
import com.execom.iot.wolksense.restService.Service;

import org.androidannotations.annotations.Background;
import org.androidannotations.annotations.EActivity;
import org.androidannotations.annotations.ViewById;
import org.androidannotations.rest.spring.annotations.RestService;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

@EActivity
public class SignInActivity extends AppCompatActivity {

    @ViewById(R.id.btn_sign_in)
    Button btnSignIn;
    @ViewById(R.id.et_email)
    EditText etEmail;
    @ViewById(R.id.et_pass)
    EditText etPass;

    Context context;
    SharedPreferences sharedPref;

    static final String LOG_TAG = "Wolksense";

    @RestService
    static Service restService;

    public static final String SH_PREFS_USER = "signInData";
    public static final String KEY_TOKEN = "token";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_sign_in);

        context = this;
        sharedPref = context.getSharedPreferences(SH_PREFS_USER, MODE_PRIVATE);

        //final Button btnSignIn = (Button) findViewById(R.id.btn_sign_in);
        //final EditText etEmail = (EditText) findViewById(R.id.et_email);
        //final EditText etPass = (EditText) findViewById(R.id.et_pass);

        btnSignIn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String email = etEmail.getText().toString();
                String pass = etPass.getText().toString();

                backgroundSignIn(email, pass);

                //String response = restService.signIn(new SignInDto(email, pass)).toString();
                //Log.d(LOG_TAG, response);
            }
        });

//        if(sharedPref.getString("accessToken", null) != null){
//            Intent intent = new Intent(context, MainActivity.class);
//            startActivity(intent);
//            finish();
//        }
    }

    @Background
    public void backgroundSignIn(String email, String pass){

        try {
            String response = restService.signIn(new SignInDto(email, pass)).toString();
            Log.d(LOG_TAG, response);

            /*JSONObject json = new JSONObject(response);

            JSONArray accessList = json.getJSONArray("accessList");
            JSONObject tokenJson = new JSONObject(accessList.get(0).toString());

            String token = tokenJson.getString("accessToken");
            String refreshToken = json.getString("refreshToken");
            */

            Pattern pattern = Pattern.compile("accessToken=([0-9a-zA-Z.\\-_]+)");
            Matcher matcher = pattern.matcher(response);

            String token = "";

            if(matcher.find()){

                token = matcher.group(1);
                Log.d(LOG_TAG, token);
            }


            sharedPref.edit().putString(KEY_TOKEN, token).apply();
            //sharedPref.edit().putString("refreshToken", refreshToken).apply();

            Intent intent = new Intent(context, MainActivity_.class);
            startActivity(intent);
            finish();

        } catch (Exception e){
            Log.d(LOG_TAG, "ERROR ON NETWORK: ", e);
        }
    }
/*
    public static void signIn(Context context)
    {
        try {
            String response = restService.signIn(new SignInDto(username, password)).toString();
            JSONObject json = new JSONObject(response);
            JSONArray accessList = json.getJSONArray("accessList");
            json = new JSONObject(accessList.get(0).toString());
            String token = json.getString("accessToken");

            Context appContext = context.getApplicationContext();

            SharedPreferences sharedPref = PreferenceManager.getDefaultSharedPreferences(appContext);
            SharedPreferences.Editor editor = sharedPref.edit();
            editor.putString("token", token);
            editor.commit();
            Log.i("RESPONSE", response.toString());

        } catch (Exception e)
        {
            Log.e("EXCEPTION", e.getMessage());
        }
    }
*/

}
