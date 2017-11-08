package com.execom.iot.wolksense.restService;

import com.execom.iot.wolksense.BuildConfig;
import com.execom.iot.wolksense.dto.SignInDto;

import org.androidannotations.rest.spring.annotations.Body;
import org.androidannotations.rest.spring.annotations.Get;
import org.androidannotations.rest.spring.annotations.Path;
import org.androidannotations.rest.spring.annotations.Post;
import org.androidannotations.rest.spring.annotations.RequiresHeader;
import org.androidannotations.rest.spring.annotations.Rest;
import org.androidannotations.rest.spring.api.RestClientErrorHandling;
import org.androidannotations.rest.spring.api.RestClientHeaders;
import org.springframework.http.HttpHeaders;
import org.springframework.http.converter.json.MappingJackson2HttpMessageConverter;

/**
 * Created by mlupurovic on 11.10.17..
 */

@Rest(rootUrl = BuildConfig.HOST, converters = MappingJackson2HttpMessageConverter.class)
public interface Service extends RestClientHeaders, RestClientErrorHandling {

    @Post("/emailSignIn")
    Object signIn(@Body SignInDto SignInDto);

    @Post("/points/{pointId}/actuators/{actuatorId}/actuations")
    @RequiresHeader(HttpHeaders.AUTHORIZATION)
    Object actuate(@Path String pointId, @Path String actuatorId, @Body String command);

    @Get("/points")
    @RequiresHeader(HttpHeaders.AUTHORIZATION)
    Object getPoints();

}
