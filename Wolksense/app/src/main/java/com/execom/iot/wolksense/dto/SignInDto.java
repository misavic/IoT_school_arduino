package com.execom.iot.wolksense.dto;

/**
 * Created by mlupurovic on 10.10.17..
 */

public class SignInDto {

    private String username;
    private String password;

    public SignInDto()
    {

    }

    public SignInDto(String username, String password)
    {
        this.username = username;
        this.password = password;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    @Override
    public String toString() {
        return "SignUpDto{" +
                "username='" + username + '\'' +
                ", password='" + password + '\'' +
                '}';
    }
}
