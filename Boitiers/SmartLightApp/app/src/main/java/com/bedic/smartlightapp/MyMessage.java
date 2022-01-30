package com.bedic.smartlightapp;

public class MyMessage {
    public int code;
    public String message;

    public MyMessage(int code, String content)
    {
        this.code=code;
        this.message=content;
    }

    public MyMessage(int code, int content)
    {
        this(code,Integer.toString(content));
    }

    public MyMessage(int code , char[] content, int length)
    {
        this(code,new String(content,0,length));
    }
}
