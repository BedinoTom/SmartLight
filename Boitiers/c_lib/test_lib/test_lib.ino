void getValueFromKeyMap(char *_map, char* key, char*buf);

void setup() {
  char buf[500];
  
  buf[0]='i';
  buf[1]='=';
  buf[2]='9';
  buf[3]=';';
  buf[4]='\0';
  buf[5] = 't';
  buf[6] = 'g';

  Serial.begin(9600);
  
  Serial.println(strlen(buf));
  

  char b[50];
  getValueFromKeyMap(buf,"i",b);
  Serial.println(b);
  if(strcmp(b,"9")==0)
  {
    Serial.println("test");
  }
  Serial.println("test2");
  //printf("%s\n",getValueFromKeyMap(&mymap,"bedino"));

}

void loop() {


}

void getValueFromKeyMap(char *_map, char* key, char*buf)
{
  String _str = String(_map);
  String m_key = String(key);
  String temp="";
  int offset_search=0, offset_find=0;
  while((offset_find=_str.indexOf(";",offset_search)) != -1){
        temp=_str.substring(offset_search,offset_find);
        int offset_equal=temp.indexOf("=");
        String _key=temp.substring(0,offset_equal);
        String _value=temp.substring(offset_equal+1);
        if(_key==m_key)
        {
          //return _value.c_str();
          Serial.println(_value.length());
          memcpy(buf,_value.c_str(),_value.length());
          buf[_value.length()]='\0';
         return;
        }

        offset_search=offset_find+1;
        if(offset_search>=_str.length())
        {
          break;
        }
  }
  memcpy(buf,'\0',1);
}
