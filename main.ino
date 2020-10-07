#include <Wire.h> 
#include <RSCG12864B.h>
int nzhi = 0;
int nzmi = 0;
int xh=1,xm=0;
int tpressed=0;
char nzm[61][3]={"00","01","02","03","04","05","06","07","08","09","10","11","12","13","14","15","16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31","32","33","34","35","36","37","38","39","40","41","42","43","44","45","46","47","48","49","50","51","52","53","54","55","56","57","58","59","60",};
char nzh[25][3]={"00","01","02","03","04","05","06","07","08","09","10","11","12","13","14","15","16","17","18","19","20","21","22","23"};
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
  pinMode(9,INPUT);//按钮2
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
  RSCG12864B.print_string_16_xy(5,16,"WelCome!");
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
    int xh=1,xm=0;
    RSCG12864B.clear();
    Serial.println("GO");
    int hpressed=0,mpressed=0;
    RSCG12864B.print_string_12_xy(40,25,nzh[xh]);//显示
    RSCG12864B.print_string_12_xy(55,25,nzm[xm]);
    while(1)
    { 
      if(hpressed==0 && digitalRead(9)==0)//设置小时
      {
         hpressed = 1;
         xh++;
         if(xh==24) xh=0;
         RSCG12864B.clear();
         RSCG12864B.print_string_12_xy(40,25,nzh[xh]);
         RSCG12864B.print_string_12_xy(55,25,nzm[xm]);
      }      
      else if(hpressed==1 && digitalRead(9)==1)      hpressed = 0;
      if(mpressed==0 && digitalRead(10)==0)//设置时间
      {
         mpressed = 1;
         xm+=5;
         if(xm==60) xm=0;
         RSCG12864B.clear();
         RSCG12864B.print_string_12_xy(40,25,nzh[xh]);
         RSCG12864B.print_string_12_xy(55,25,nzm[xm]);
      }      
      else if(mpressed==1 && digitalRead(10)==1)      tpressed = 0;
      if(tpressed==0 && digitalRead(8)==0)//推出
      {
          tpressed = 1;
          delay(50);
          return; 
      }      
      else if(tpressed==1 && digitalRead(8)==1)      tpressed = 0;
    }
    
}
void loop()
{
    if(tpressed==0 && digitalRead(8)==0)//进入闹钟
    {
         tpressed = 1;
         JL_Set_Time();
    }      
    else if(tpressed==1 && digitalRead(8)==1)      tpressed = 0;

}








/*
void setup()
{
  Serial.begin(9600);
}
char n;
void loop()
{
  while(Serial.available() > 0)
  {
    n = int(Serial.read());
    if(n == ';')
    {
      Serial.println("");
    }
    else
    {
      Serial.print(n);
    }
  }
}
*/
