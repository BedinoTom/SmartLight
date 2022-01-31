#include <SoftwareSerial.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RX 10
#define TX 11

typedef struct {
  char **array;
  int size;
  int current_pointer;
}my_splitarray;

typedef struct {
  my_splitarray *_map;
  int size;
  int current_pointer;
}my_map;

void split_char(my_splitarray *sta, char *string, char *delimit);
void free_splitchar(my_splitarray *sta);
char* get_splitchar_element(my_splitarray *sta, int index);
void parse_map_string(my_map *_map,char *string, char *delimit_element, char *delimit_map);
char* getValueFromKeyMap(my_map *_map, char* key);
void free_map(my_map *_map);

SoftwareSerial BlueT(RX,TX);

void setup() {
 Serial.begin(9600);
 delay(500);
 Serial.println("Pret pour commande AT");
 BlueT.begin(9600);
 delay(500);
 Serial.println("BLE OK");
}

char buf[500];
int i=0,valid=0;

void loop() {
  while(BlueT.available())
  {
    if(i>=499)
     {
        break;
     }
     char c = char(BlueT.read());
     if(c == ';')
     {
      valid++.
     }
     //Serial.write(c);
     buf[i] = c;
     i++;
  }

  if(valid == 2)
  {
    
  }
  
  while(Serial.available())
  {
    BlueT.write(char(Serial.read()));
  }
}

void parse_map_string(my_map *_map,char *string, char *delimit_element, char *delimit_map)
{
  my_splitarray element;
  split_char(&element,string,delimit_element);
  if(element.array != NULL)
  {
    _map->size = element.size;
    _map->_map = (my_splitarray*)malloc(_map->size * sizeof(my_splitarray));
    if(_map->_map==NULL)
    {
      return;
    }
    for(int i=0;i<element.size;i++)
    {
      char *el = get_splitchar_element(&element,i);
      split_char(&_map->_map[i],el,delimit_map);
    }
  }
  free_splitchar(&element);
}

char* getValueFromKeyMap(my_map *_map, char* key)
{
  for(int i=0;i<_map->size;i++)
  {
    if(strcmp(_map->_map[i].array[0],key)==0)
    {
      return _map->_map[i].array[1];
    }
  }
  return "";
}

void split_char(my_splitarray *sta,char *string, char *delimit)
{
  int i;
  int count=0;
  for(i=0;i<strlen(string);i++)
  {
    if(string[i] == delimit[0])
    {
      count++;
    }
  }
  
  if(count == 0)
  {
    return;
  }
  
  sta->current_pointer=0;
  sta->size = count+1;
  sta->array = (char**)malloc((count+1) * sizeof(char*));
  
  int start=0;
  count=0;
  for(i=0;i<strlen(string);i++)
  {
    if(string[i] == delimit[0])
    {
      sta->array[count] = (char*)malloc((i-start)+1 * sizeof(char));
      memcpy(sta->array[count],&string[start],(i-start));
      sta->array[count][(i-start)]='\0';
      count++;
      start=i+1;
    }
  }
  
  sta->array[count] = (char*)malloc((strlen(string)-start)+1 * sizeof(char));
  memcpy(sta->array[count],&string[start],(strlen(string)-start));
}

char* get_splitchar_element(my_splitarray *sta, int index)
{
  if(index >= 0 && index < sta->size)
  {
    return sta->array[index];
  }
  
  return NULL;
}

void free_map(my_map *_map)
{
  for(int i=0;i<_map->size;i++)
  {
    free_splitchar(&_map->_map[i]);
  }
}

void free_splitchar(my_splitarray *sta)
{
  for(int i=0;i<sta->size;i++)
  {
    if(sta->array[i] != NULL)
    {
      free(sta->array[i]);
    }
  }
  
  if(sta->array != NULL)
  {
    free(sta->array);
  }
}
