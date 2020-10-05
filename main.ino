void setup()
{
  Serial.begin(9600);
  pinMode(11,INPUT);
  pinMode(12,OUTPUT);
  pinMode(8,INPUT);
  pinMode(9,INPUT);
  pinMode(10,INPUT);
  pinMode(13,OUTPUT);
}
int JL_BUTT()
{
  switch(not(digitalRead(8))+not(digitalRead(9))*2+not(digitalRead(10))*4)
  {
    case 1:return 1;
    case 2:return 2;
    case 4:return 3;
    default:return 0;
  }
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
void loop()
{
  
}
