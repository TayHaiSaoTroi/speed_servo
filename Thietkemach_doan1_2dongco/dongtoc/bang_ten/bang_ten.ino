#include <Ethernet.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define btn_Run 3
#define nutcong 4
#define nuttru 5
#define DIR 6
#define PULSE 7
#define ENABLE 8
Servo svo;
LiquidCrystal_I2C lcd(0x3F,20,4);
int s=0;
int T = 1;
bool flag_Run = 0, RUN = 0;
int Home = 0, xss;
const int s1 = 0, s2 = 1, s3 = 2, s4 = 3, s5 = 4, s6 = 5, s7 = 6, s8 = 7, s9 = 8, s10 = 9, s11 = 10, s12 = 11, s13 = 12, s14 = 13, s15 = 14, s16 = 15, s17 = 16;
int chuso[17] = {89,178,267,356,445,534,623,712,801,890,979,1068,1157,1246,1335,1424,1513};
char a[5]={};
void setup() {
lcd.init();

  lcd.backlight();
  
 Serial.begin(9600);
  pinMode(btn_Run, INPUT_PULLUP);
  pinMode(DIR, OUTPUT);
  pinMode(PULSE, OUTPUT);
  pinMode(ENABLE, OUTPUT);
  digitalWrite(ENABLE , HIGH); 
  pinMode(nutcong,INPUT_PULLUP);
  pinMode(nuttru,INPUT_PULLUP);
  svo.attach(9);
  svo.write(0);
  lcd.setCursor(1,0);
  lcd.print("TRUONG DH NONGLAM");
  lcd.setCursor(3,1);
  lcd.print("DO AN MON TKM");
  lcd.setCursor(7,2);
  lcd.print("NHOM 3");
  delay(2000);
  lcd.clear();
}

void loop() {
      if(Serial.available()>0)
  {
    delay(20);
    while(Serial.available())
    {
Serial.readBytes(a, 3);
 lcd.setCursor(0,3);
 lcd.print("Toc do :");
 lcd.setCursor(9,3);
 lcd.print(a);

  }
  }
  nut();
  scan_Btn_Run();
  if (RUN == 1) {
    digitalWrite(ENABLE , LOW);// Set Enable low  -  Enable mức thấp

 if(s==1)
{
  delay(500);
    goToPos(Home , chuso[s1]);
    delay(1500);
    svo.write(45);
    delay(700);
    svo.write(0);
    delay(1500);
    goToPos(chuso[s1],Home);
}
 if(s==2)
{
  delay(500);
    goToPos(Home , chuso[s2]);
    delay(1500);
    svo.write(45);
    delay(700);
    svo.write(0);
    delay(1500);
    goToPos(chuso[s2],Home);
}
 if(s==3)
{
  delay(500);
    goToPos(Home , chuso[s3]);
    delay(1500);
    svo.write(45);
    delay(700);
    svo.write(0);
    delay(1500);
    goToPos(chuso[s3],Home);
}
 if(s==4)
{
  delay(500);
    goToPos(Home , chuso[s4]);
    delay(1500);
    svo.write(45);
    delay(700);
    svo.write(0);
    delay(1500);
    goToPos(chuso[s4],Home);
}
 if(s==5)
{
  delay(500);
    goToPos(Home , chuso[s5]);
    delay(1500);
    svo.write(45);
    delay(700);
    svo.write(0);
    delay(1500);
    goToPos(chuso[s5],Home);
}
 if(s==6)
{
  delay(500);
    goToPos(Home , chuso[s6]);
    delay(1500);
    svo.write(45);
    delay(700);
    svo.write(0);
    delay(1500);
    goToPos(chuso[s6],Home);
}
 if(s==7)
{
  delay(500);
    goToPos(Home , chuso[s7]);
    delay(1500);
    svo.write(45);
    delay(700);
    svo.write(0);
    delay(1500);
    goToPos(chuso[s7],Home);
}
 if(s==8)
{
  delay(500);
    goToPos(Home , chuso[s8]);
    delay(1500);
    svo.write(45);
    delay(700);
    svo.write(0);
    delay(1500);
    goToPos(chuso[s8],Home);
}
 if(s==9)
{
  delay(500);
    goToPos(Home , chuso[s9]);
    delay(1500);
    svo.write(45);
    delay(700);
    svo.write(0);
    delay(1500);
    goToPos(chuso[s9],Home);
}
 if(s==10)
{
  delay(500);
    goToPos(Home , chuso[s10]);
    delay(1500);
    svo.write(45);
    delay(700);
    svo.write(0);
    delay(1500);
    goToPos(chuso[s10],Home);
}
 if(s==11)
{
  delay(500);
    goToPos(Home , chuso[s11]);
    delay(1500);
    svo.write(45);
    delay(700);
    svo.write(0);
    delay(1500);
    goToPos(chuso[s11],Home);
}
 if(s==12)
{
  delay(500);
    goToPos(Home , chuso[s12]);
    delay(1500);
    svo.write(45);
    delay(700);
    svo.write(0);
    delay(1500);
    goToPos(chuso[s12],Home);
}
 if(s==13)
{
  delay(500);
    goToPos(Home , chuso[s13]);
    delay(1500);
    svo.write(45);
    delay(700);
    svo.write(0);
    delay(1500);
    goToPos(chuso[s13],Home);
}
 if(s==14)
{
  delay(500);
    goToPos(Home , chuso[s14]);
    delay(1500);
    svo.write(45);
    delay(700);
    svo.write(0);
    delay(1500);
    goToPos(chuso[s14],Home);
}
 if(s==15)
{
  delay(500);
    goToPos(Home , chuso[s15]);
    delay(1500);
    svo.write(45);
    delay(700);
    svo.write(0);
    delay(1500);
    goToPos(chuso[s15],Home);
}
 if(s==16)
{
  delay(500);
    goToPos(Home , chuso[s16]);
    delay(1500);
    svo.write(45);
    delay(700);
    svo.write(0);
    delay(1500);
    goToPos(chuso[s16],Home);
}
 if(s==17)
{
  delay(500);
    goToPos(Home , chuso[s17]);
    delay(1500);
    svo.write(45);
    delay(700);
    svo.write(0);
    delay(1500);
    goToPos(chuso[s17],Home);
}
  }

Serial.println(s);
delay(20);
}
void nut()
{
  if(digitalRead(nutcong)==0)
{
delay(200);
  s++;
}
if(digitalRead(nuttru)==0)
{
delay(200);
  s--;
}
if(s>17)
{
  s=17;
}
if(s<0)
{
  s=0;
}

if(s==1)
{
lcd.setCursor(5,1);
lcd.print("VI TRI DAP");
lcd.setCursor(9,2);
lcd.print("S1");


}
 if(s==2)
{

lcd.setCursor(5,1);
lcd.print("VI TRI DAP");
lcd.setCursor(9,2);
lcd.print("S2");
}
 if(s==3)
{

lcd.setCursor(5,1);
lcd.print("VI TRI DAP");
lcd.setCursor(9,2);
lcd.print("S3");
}
 if(s==4)
{

lcd.setCursor(5,1);
lcd.print("VI TRI DAP");
lcd.setCursor(9,2);
lcd.print("S4");
}
 if(s==5)
{

lcd.setCursor(5,1);
lcd.print("VI TRI DAP");
lcd.setCursor(9,2);
lcd.print("S5");
}
 if(s==6)
{

lcd.setCursor(5,1);
lcd.print("VI TRI DAP");
lcd.setCursor(9,2);
lcd.print("S6");
}
 if(s==7)
{

lcd.setCursor(5,1);
lcd.print("VI TRI DAP");
lcd.setCursor(9,2);
lcd.print("S7");
}
 if(s==8)
{

lcd.setCursor(5,1);
lcd.print("VI TRI DAP");
lcd.setCursor(9,2);
lcd.print("S8");
}
 if(s==9)
{
lcd.clear();
lcd.setCursor(5,1);
lcd.print("VI TRI DAP");
lcd.setCursor(9,2);
lcd.print("S9");
}
 if(s==10)
{

lcd.setCursor(5,1);
lcd.print("VI TRI DAP");
lcd.setCursor(9,2);
lcd.print("S10");
}
 if(s==11)
{

lcd.setCursor(5,1);
lcd.print("VI TRI DAP");
lcd.setCursor(9,2);
lcd.print("S11");
}
 if(s==12)
{

lcd.setCursor(5,1);
lcd.print("VI TRI DAP");
lcd.setCursor(9,2);
lcd.print("S12");
}
 if(s==13)
{

lcd.setCursor(5,1);
lcd.print("VI TRI DAP");
lcd.setCursor(9,2);
lcd.print("S13");
}
 if(s==14)
{

lcd.setCursor(5,1);
lcd.print("VI TRI DAP");
lcd.setCursor(9,2);
lcd.print("S14");
}
 if(s==15)
{

lcd.setCursor(5,1);
lcd.print("VI TRI DAP");
lcd.setCursor(9,2);
lcd.print("S15");
}
 if(s==16)
{

lcd.setCursor(5,1);
lcd.print("VI TRI DAP");
lcd.setCursor(9,2);
lcd.print("S16");
}
 if(s==17)
{

lcd.setCursor(5,1);
lcd.print("VI TRI DAP");
lcd.setCursor(9,2);
lcd.print("S17");
}

}
void scan_Btn_Run() 
{
  if (!flag_Run && !digitalRead(btn_Run)) 
  {
    flag_Run = 1;
    delay(20);
    if (!digitalRead(btn_Run)) 
    {
      RUN = 1;
    }
  }
  else if (digitalRead(btn_Run)) {
    flag_Run = 0;
    RUN = 0;
  }
}
void StepMotorRun(int xung, int t) 
{

  for (int x = 0; x < xung; x++) 
  {
    digitalWrite(PULSE, HIGH); // Output high - xung mức cao
    delay(t);
    digitalWrite(PULSE, LOW);// Output low - xung mức thấp
    delay(t);
  }
}
void goToPos(int x, int y) 
{    
  xss = x - y;
  if (xss < 0) {
    digitalWrite(DIR, HIGH);//Set Dir high  - Set chiều quay mức cao

  }
  else if (xss > 0) 
  {
    digitalWrite(DIR, LOW); // Set Dir low - Set chiều quay mức thấp
  }
  StepMotorRun(abs(xss), T);
 
}
