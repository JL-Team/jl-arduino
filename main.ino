#include <dht11.h>
#include <Wire.h> 
#include <RSCG12864B.h>

dht11 DHT11;
#define DHT11PIN A0
int nzx = 90,nzy = 40;
int nzhi = 0;
int nzmi = 0;
int xh=7,xm=30;
int tpressed=0;
char nzm[61][3]={"00","01","02","03","04","05","06","07","08","09","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49","50","51","52","53","54","55","56","57","58","59","60",};
char nzh[25][3]={"00","01","02","03","04","05","06","07","08","09","10","11","12","13","14","15","16","17","18","19","20","21","22","23"};
char humh[100][3]={"01","02","03","04","05","06","07","08","09","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49","50","51","52","53","54","55","56","57","58","59","60","61","62","63","64","65","66","67","68","69","70","71","72","73","74","75","76","77","78","79","80","81","82","83","84","85","86","87","88","89","90","91","92","93","94","95","96","97","98","99","100"};
char temph[100][3]={"01","02","03","04","05","06","07","08","09","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49","50","51","52","53","54","55","56","57","58","59","60","61","62","63","64","65","66","67","68","69","70","71","72","73","74","75","76","77","78","79","80","81","82","83","84","85","86","87","88","89","90","91","92","93","94","95","96","97","98","99","100"};

void setup()
{
  Serial.begin(9600);
  RSCG12864B.begin();
  RSCG12864B.clear();
  RSCG12864B.brightness(100);
  //Serial.println("AT+ROLE0");
  //delay(5000);
  //Serial.println("AT+ADDR");
  pinMode(11,INPUT);//
  pinMode(12,OUTPUT);//
  pinMode(8,INPUT);//按钮1
  pinMode(9,INPUT);//按钮2p
  pinMode(10,INPUT);//按钮3
  pinMode(13,OUTPUT);//
  JL_ScreenSetup();
}
void JL_ScreenSetup()
{
  RSCG12864B.print_string_16_xy(2,16,"JL-Clock.");
  RSCG12864B.print_string_16_xy(30,32,"By-JL-Team");
  delay(2000);
  RSCG12864B.clear();
  RSCG12864B.print_string_16_xy(5,30,"Welcome!");
  delay(1000);
  RSCG12864B.clear();
}
int JL_ULT()
{
  digitalWrite(12,LOW);
  delayMicroseconds(3);
  digitalWrite(12,HIGH);
  delayMicroseconds(11);
  digitalWrite(12,LOW);
  return (pulseIn(11,1,10000L) / 59);
}
void JL_Set_Time()//设置时钟
{
  while(digitalRead(8)==0){}
  RSCG12864B.clear();
  Serial.println("GO");
  int hpressed=0,mpressed=0;
  int chk = DHT11.read(DHT11PIN);
  int temp=float(DHT11.temperature);
  int hum =float(DHT11.humidity);
  RSCG12864B.print_string_16_xy(nzx-50,nzy-35,"Temp:");
  RSCG12864B.print_string_12_xy(nzx,nzy-31,temph[temp]);//显示
  RSCG12864B.print_string_16_xy(nzx-50,nzy-18,"Hum:");
  RSCG12864B.print_string_12_xy(nzx,nzy-14,humh[hum]);//显示
  RSCG12864B.print_string_16_xy(nzx-50,nzy-3,"Alarm:");
  RSCG12864B.print_string_12_xy(nzx,nzy+1,nzh[xh]);//显示
  RSCG12864B.print_string_12_xy(nzx+15,nzy+1,nzm[xm]);

  while(1)
  { 
    if(hpressed==0 && digitalRead(9)==0)//设置小时
    {
       hpressed = 1;
       xh++;
       if(xh==24) xh=0;
       RSCG12864B.clear();
       RSCG12864B.print_string_16_xy(nzx-50,nzy-3,"Alarm:");
       RSCG12864B.print_string_12_xy(nzx,nzy+1,nzh[xh]);
       RSCG12864B.print_string_12_xy(nzx+15,nzy+1,nzm[xm]);
       int chk = DHT11.read(DHT11PIN);
       int temp=float(DHT11.temperature);
       int hum =float(DHT11.humidity);
       RSCG12864B.print_string_16_xy(nzx-50,nzy-35,"Temp:");
       RSCG12864B.print_string_12_xy(nzx,nzy-31,temph[temp]);//显示
       RSCG12864B.print_string_16_xy(nzx-50,nzy-18,"Hum:");
       RSCG12864B.print_string_12_xy(nzx,nzy-14,humh[hum]);//显示
    }      
    else if(hpressed==1 && digitalRead(9)==1)      hpressed = 0;
    if(mpressed==0 && digitalRead(10)==0)//设置时间
    {
       mpressed = 1;
       xm+=5;
       if(xm==60) xm=0;
       RSCG12864B.clear();
       RSCG12864B.print_string_16_xy(nzx-50,nzy-3,"Alarm:");
       RSCG12864B.print_string_12_xy(nzx,nzy+1,nzh[xh]);
       RSCG12864B.print_string_12_xy(nzx+15,nzy+1,nzm[xm]);
       int chk = DHT11.read(DHT11PIN);
       int temp=float(DHT11.temperature);
       int hum =float(DHT11.humidity);
       RSCG12864B.print_string_16_xy(nzx-50,nzy-35,"Temp:");
       RSCG12864B.print_string_12_xy(nzx,nzy-31,temph[temp]);//显示
       RSCG12864B.print_string_16_xy(nzx-50,nzy-18,"Hum:");
       RSCG12864B.print_string_12_xy(nzx,nzy-14,humh[hum]);//显示
    }      
    else if(mpressed==1 && digitalRead(10)==1)      mpressed = 0;

    if(digitalRead(8)==0)//推出
    {
        RSCG12864B.clear();
        while(digitalRead(8)==0){}
        return; 
    }      
    else if(tpressed==1 && digitalRead(8)==1)      tpressed = 0;
  }
}
char StrtoChar(String(p))
{
  char charBuf[1001];
  p.toCharArray(charBuf, 1001);
  return charBuf;
}
char n;//从这开始为重要程序
int id = 1;
String T = "";
String C = "";
String Q = "";
void loop()
{
  delay(100);
  Serial.println(analogRead(A0)/1020);
  if(tpressed==0 && digitalRead(8)==0)//进入闹钟
  {
       tpressed = 1;
       delay(100);
       JL_Set_Time();
  }      
  else if(tpressed==1 && digitalRead(8)==1)      tpressed = 0;
  while(Serial.available() > 0)//检测是否有输入
  {
    n = int(Serial.read());
    if(n == '$')
    {
      delay(10);
      Serial.println(T);//感染人数
      RSCG12864B.print_string_12_xy(1,1,StrtoChar(T));
      Serial.println(C);//年月日
      RSCG12864B.print_string_12_xy(1,1,StrtoChar(C));
      Serial.println(Q);//天气
      RSCG12864B.print_string_12_xy(1,1,StrtoChar(Q));
      id = 1;
      T = "";
      C = "";
      Q = "";
    }
    else if(n == ';')
    {
      id++;
      //Serial.println(id);
    }
    else
    {
      switch(id)
      {
        case 1:T = T+String(n);break;
        case 2:C = C+String(n);break;
        case 3:Q = Q+String(n);break;
        default:break;
      }
    }
  }
}



/*
*————————————————————————————————————————————————*
a = ["晴","多云","阴天","雾","小雨","中雨","大雨","暴雨","雷阵雨","冰雹","冻雨","雨夹雪","小雪","中雪","暴雪","大雪","霜冻","大风","台风"]
a = ["Sunny","Partly Cloudy","Cloudy","Foggy","Light Rain","Rain","Heavy Rain","Thunderstorm","Thundershower","Hail","Freezing Rain","Sleet","Light Snow","Moderate Snow","SnowStorm","Heavy Snow","Frost","Gale","Typhoon"]
*————————————————————————————————————————————————*
String StrtoChar(String(p))
{
  char charBuf[1001];
  p.toCharArray(charBuf, 1001);
  return p;
}
*————————————————————————————————————————————————*
String address = "0x001583129EE4";
String bluetooth = "";
void linkBluetooth()
{
  char number;
  Serial.println("AT+INQ");
  delay(2000);
  for(int i = 0; i < 3; i++)
  {
    while(Serial.available() > 0)
    {
      bluetooth += char(Serial.read());
      delay(2);
    }
    delay(20);
  }
  number = bluetooth.indexOf(address) - 2;
  if(number)
  {
    Serial.print("AT+CONN");
    Serial.println(bluetooth[number]);
  }
}
*————————————————————————————————————————————————*
char n;//从这开始为重要程序
int id = 1;
String T = "";
String C = "";
String Q = "";
void loop()
{
  while(Serial.available() > 0)//检测是否有输入
  {
    n = int(Serial.read());
    if(n == '$')
    {
      delay(10);
      Serial.println(T);//感染人数
      Serial.println(C);//年月日
      Serial.println(Q);//天气
      id = 1;
      T = "";
      C = "";
      Q = "";
    }
    else if(n == ';')
    {
      id++;
      //Serial.println(id);
    }
    else
    {
      switch(id)
      {
        case 1:T = T+String(n);break;
        case 2:C = C+String(n);break;
        case 3:Q = Q+String(n);break;
        default:break;
      }
    }
  }
}
      //int id3 = (int(id1)-48)*(int(id2)-48);
      //Serial.println(nzh[id3]);//nzh[id3] 打印天气
      }
*————————————————————————————————————————————————*
*/
