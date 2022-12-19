
#include <SimpleKalmanFilter.h>
SimpleKalmanFilter simpleKalmanFilter(2, 2, 0.01);
#include <Wire.h>
int en = 8 ;
int dirPinX = 7 ;
int stepPinX = 4 ;


int bientro = A0; int gt_bientro; int gt_quydoi; int gt_locnhieu; int gt_quydoi1;
int vitri = 0;
#define IN1 9
#define IN2 10
#define eda 2
#define edb 3
int a;
int b;
int s = 0;
int rpm = 0;
int timecho = 1000;
int xung;
int giatri;
int TOCDO;
unsigned long thoigian;
unsigned long hientai;

const int CTHT1 = 5;
const int CTHT2 = 6;


long pulsePerRound = 200; // so xung/vong
long period ; // time bettween 2 pulse - us

// ============== defaut value ===================
float speedScroll  ; // vong/phut
bool dirXDefaut = LOW;
//================================================
void chay()
{

  TOCDO++;





}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
   Serial1.begin(9600);
  Wire.begin();

  pinMode(bientro, INPUT);
  pinMode(en, OUTPUT); // Enable
  pinMode(stepPinX, OUTPUT); // Step
  pinMode(dirPinX, OUTPUT); // Dir

  pinMode(CTHT1, INPUT_PULLUP);
  pinMode(CTHT2, INPUT_PULLUP);
  pinMode(eda, INPUT);
  // put your setup code here, to run once:
  attachInterrupt(0, chay, RISING);
  digitalWrite(en, LOW); // Set Enable low



}

void loop() {
  
  gt_bientro = analogRead(bientro);
  gt_locnhieu = simpleKalmanFilter.updateEstimate(gt_bientro);
  gt_quydoi = map(gt_locnhieu, 0, 1023, 0, 255);
  thoigian = millis();
  //  Serial.print("Time: "); Serial.print(thoigian); Serial.print("   ");
  //  Serial.print("Hiện tại: "); Serial.println(hientai);

  if (thoigian - hientai >= timecho) //millis thay delay
  {
    hientai = thoigian;
    rpm = ((TOCDO / 12.5) * 60) / 25;
    String h = String(rpm);
    Serial.print(h);
   

    TOCDO = 0;

  }
  speedScroll = rpm; //vong/phut
  period = 1000000 / (speedScroll / 60 * pulsePerRound);
  if (gt_locnhieu > 3)
  {

    if (digitalRead(CTHT1) == 0) {
      analogWrite(IN1, 0);
      analogWrite(IN2, gt_quydoi);

      digitalWrite(dirPinX, dirXDefaut);
    }
    if (digitalRead(CTHT2) == 0) {
      analogWrite(IN2, 0);
      analogWrite(IN1, gt_quydoi);

      digitalWrite(dirPinX, !dirXDefaut);
    }

    digitalWrite(stepPinX, HIGH);
    delayMicroseconds(0.5 * period);

    digitalWrite(stepPinX, LOW);
    delayMicroseconds(0.5 * period);

  }






}
void truyen()
{
Serial.println(rpm);
  
}

//------------------------------------------------------------------------------------





// ----------------------------------------------

// -----------------------------------------------
