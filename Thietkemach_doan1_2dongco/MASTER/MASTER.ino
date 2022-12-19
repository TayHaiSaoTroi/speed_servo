#include <Wire.h>
#include <Servo.h>
#include <MCUFRIEND_kbv.h>
#include <AccelStepper.h>
#include <TouchScreen.h>

#if defined(__SAM3X8E__)
#undef __FlashStringHelper::F(string_literal)
#define F(string_literal) string_literal
#endif

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4


#define BLACK 0x0000
#define NAVY 0x000F
#define DARKGREEN 0x0404
#define DARKCYAN 0x03EF
#define MAROON 0x7800
#define PURPLE 0x7878
#define OLIVE 0x7BE0
#define LIGHTGREY 0xDEDE
#define DARKGREY 0x7BEF
#define BLUE 0x0202
#define GREEN 0x07E0
#define CYAN 0x3A3A
#define RED 0xF800
#define MAGENTA 0xF81F
#define YELLOW 0xE7E7
#define WHITE 0xFFFF
#define ORANGE 0x5959
#define GREENYELLOW 0xAFE5
#define PINK 0xF8F8
#define BLACKM  0x18E3
#define CYANS 0x0909
#define P 0x0C0C
#define S 0xE8E8
#define L 0xBFBF
#define B 0xA1A1
#define Z 0xFEFE
#define T 0x4242
#define STY 0xE7E7
#define  CS 0X3636
#define  CX 0XCBCB
#define  CA 0XAEAE
#define  CD 0X4B4B
#define  CE 0X2A2A
#define  CV 0XDEDE
#define  BP 0X2A2A
#define  CLR 0XCDCD
#define  X 0XEAEA
#define  BPL 0XCACA
#define  STP 0XEAEA


#define YP A3
#define XM A2
#define YM 9
#define XP 8

#define TS_MINX 118
#define TS_MAXX 906
#define TS_MINY 92
#define TS_MAXY 951
#define MINPRESSURE 10
#define MAXPRESSURE 1000

Servo myServo1;
const int dirPin =31;
const int stepPin = 33;
int servo1 = 35;
int CB = 37;
int giatri;

int sll = 0;

int goc1;
char o;
int stp = 0;
int pwm = 0;
int show_keyboard = 0;
int bp = 0;
int quay = 0;
int homee =0;
int block_key = 0;
int block2 = 0;
int bp1 = 0;
int bp2 = 0;
int rp = 0;
int st = 0 ;
int x = 0;
int x1 = 0;
int ss = 0;
int s = 0;
int z = 0;
int sbp = 0;
int show_keyboard1 = 0 ;
int gui1 = 0;
int gui2 = 0;
int sps = 0;
int slr = 0;
int speeds = 0;
int a = 0;
int vi_tri = 0;

int start_X = 308;
int start_Y = 165;

int stop_X = 398;
int stop_Y = 165;

int home_X = 308;
int home_Y = 248;

int ck_speed_X = 300;
int ck_speed_Y = 0;

int line1_X = 0;
int line1_Y = 160;

int line2_X = 150;
int line2_Y = 160;

int line3_X = 0;
int line3_Y = 0;

int line4_X = 150;
int line4_Y = 0;

int speed_X = 20;
int speed_Y = 240;

int select_X = 20;
int select_Y = 80;

int repeat_X = 170;
int repeat_Y = 80;

int keyboard_X = -5;
int keyboard_Y = -65;

int outbp_X = -5;
int outbp_Y = -65;

int ss1_X = -5;
int ss1_Y = -65;

char SL2;

MCUFRIEND_kbv tft;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

void setup()
{
  
  Serial.begin(9600);
  pinMode(stepPin, OUTPUT);
  pinMode(CB, INPUT);
  pinMode(dirPin, OUTPUT);
  Wire.begin(); // Khởi tạo thư viện i2c
  tft.reset();
  uint16_t identifier = tft.readID();
  Wire.setClock(16000000);
  tft.begin(identifier);
  myServo1.attach(servo1);
  tft.setRotation(305);

  tft.fillRoundRect(300, 160, 180, 160, 0, Z);
  pinMode(13, OUTPUT);

 
  
  start_btn(start_X, start_Y);
  stop_btn(stop_X, stop_Y);
  home_btn(home_X, home_Y);
  speed_btn( speed_X , speed_Y);
  select_btn ( select_X , select_Y);
  repeat_btn ( repeat_X , repeat_Y);
  key_board( keyboard_X , keyboard_Y);

  ck_speed(ck_speed_X, ck_speed_Y);
  ngang1( line1_X , line1_Y);
  ngang2( line2_X , line2_Y);
  doc1( line3_X , line3_Y);
  doc2( line4_X , line4_Y);
  outbp(outbp_X, outbp_Y);
  
}





void loop()
{
  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.height());
  p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.width());
  int y_set_rotatoon_305 = map(tft.height() - p.x, 0, 320, 0, tft.height());
  int x_set_rotatoon_305 = map(tft.width() - p.y, 0, 480, 0, tft.width());
   myServo1.write(18);
    goc1 = myServo1.read();
    giatri =digitalRead(CB);
  vi_tri =( bp * 10 ) + 1990;
    
if ( a == 0)
  {
    Wire.requestFrom(6, 1);
    while ( Wire.available())
    {
     
      speeds = Wire.read();
      tft.setCursor( 351, 50);
      tft.setTextSize(6);
      tft.setTextColor(YELLOW);
      tft.print(speeds);
      tft.fillRoundRect(334, 32, 135, 73, 0, CE);



    }
  }
   




  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {

    if (show_keyboard == 0 && show_keyboard1 == 0 )// mở khóa các phím ở home
    {

      if (x_set_rotatoon_305 > start_X && x_set_rotatoon_305 < (start_X + 75) && y_set_rotatoon_305 > start_Y && y_set_rotatoon_305 < (start_Y + 75)) {



        Wire.beginTransmission(6);
        Wire.write(bp2);
        Wire.endTransmission();

       quay = quay +1;
        start_btn_press(start_X, start_Y);
        delay(25);
        start_btn(start_X, start_Y);
        stp = 0;
        tft.fillRoundRect(152, 235, 145, 25, 0, CD);
        tft.setCursor(160,240);
        tft.setTextSize(2.5);
        tft.setTextColor(GREEN);
        tft.println("RUNNING ^_^");
        


      }

      if (x_set_rotatoon_305 > stop_X && x_set_rotatoon_305 < (stop_X + 75) && y_set_rotatoon_305 > stop_Y && y_set_rotatoon_305 < (stop_Y + 75)) {


        Wire.beginTransmission(6);
        Wire.write(0);
        Wire.endTransmission();
        stop_btn_press(stop_X, stop_Y);
        delay(25);
        stop_btn(stop_X, stop_Y);
        quay = 0;
        stp = stp + 1;
        tft.fillRoundRect(152, 235, 145, 25, 0, CD);
        tft.setCursor(163,240);
        tft.setTextSize(2.5);
        tft.setTextColor(RED);
        tft.println("STOPPED @_@");
      }

      if (x_set_rotatoon_305 > home_X && x_set_rotatoon_305 < ( home_X + 164) && y_set_rotatoon_305 > home_Y && y_set_rotatoon_305 < ( home_Y + 68)) {


        Wire.beginTransmission(6);
        Wire.write(2);
        Wire.endTransmission();
        bp  = 0;
        bp1 = 0;
        bp2 = 0;
        homee = homee + 1;
        home_btn_press( home_X,  home_Y);
        delay(10);
        home_btn( home_X,  home_Y);
        tft.fillRoundRect(152, 235, 145, 25, 0, CD);
        tft.setCursor(160,240);
        tft.setTextSize(2.5);
        tft.setTextColor(Z);
        tft.println("Going Home");
         
        

         


      }


      if (x_set_rotatoon_305 >  select_X && x_set_rotatoon_305 < (  select_X + 110) && y_set_rotatoon_305 >  select_Y && y_set_rotatoon_305 < (  select_Y + 75)) {


        show_keyboard = 1  ;
        st = 1;
        rp = 0;
        slr = 1;
        a = 1;
        key_board(keyboard_X, keyboard_Y);
        block_key = 1;
        sbp = 0;



      }

      if (x_set_rotatoon_305 > speed_X && x_set_rotatoon_305 < ( speed_X + 110) && y_set_rotatoon_305 > speed_Y && y_set_rotatoon_305 < ( speed_Y + 75)) {


        sbp = 1;
        a = 1;
        show_keyboard1 = 1 ;
        block_key = 0;
        tft.fillScreen(CD);
        //30
        tft.fillRoundRect(ss1_X + 100, ss1_Y + 157, 65, 65, 15, BP);
        tft.drawRoundRect(ss1_X + 100, ss1_Y + 157, 65, 65, 15, WHITE);
        tft.setCursor(ss1_X + 117, ss1_Y + 177);
        tft.setTextSize(3);
        tft.setTextColor(WHITE);
        tft.println("30");
        //60
        tft.fillRoundRect(ss1_X + 190, ss1_Y + 157, 65, 65, 15, BP);
        tft.drawRoundRect(ss1_X + 190, ss1_Y + 157, 65, 65, 15, WHITE);
        tft.setCursor(ss1_X + 207, ss1_Y + 177);
        tft.setTextSize(3);
        tft.setTextColor(WHITE);
        tft.println("60");
        //90
        tft.fillRoundRect(ss1_X + 282, ss1_Y + 157, 65, 65, 15, BP);
        tft.drawRoundRect(ss1_X + 282, ss1_Y + 157, 65, 65, 15, WHITE);
        tft.setCursor(ss1_X + 299, ss1_Y + 177);
        tft.setTextSize(3);
        tft.setTextColor(WHITE);
        tft.println("90");
        //120
        tft.fillRoundRect(ss1_X + 100, ss1_Y + 242, 65, 65, 15, BP);
        tft.drawRoundRect(ss1_X + 100, ss1_Y + 242, 65, 65, 15, WHITE);
        tft.setCursor(ss1_X + 106, ss1_Y + 260);
        tft.setTextSize(3);
        tft.setTextColor(WHITE);
        tft.println("120");
        //150
        tft.fillRoundRect(ss1_X + 190, ss1_Y + 242, 65, 65, 15, BP);
        tft.drawRoundRect(ss1_X + 190, ss1_Y + 242, 65, 65, 15, WHITE);
        tft.setCursor(ss1_X + 195, ss1_Y + 260);
        tft.setTextSize(3);
        tft.setTextColor(WHITE);
        tft.println("150");
        //180
        tft.fillRoundRect(ss1_X + 282, ss1_Y + 242, 65, 65, 15, BP);
        tft.drawRoundRect(ss1_X + 282, ss1_Y + 242, 65, 65, 15, WHITE);
        tft.setCursor(ss1_X + 288, ss1_Y + 260);
        tft.setTextSize(3);
        tft.setTextColor(WHITE);
        tft.println("180");

        //ok
        tft.fillRoundRect(ss1_X + 420, ss1_Y + 200, 72, 65, 15, DARKGREEN);
        tft.drawRoundRect(ss1_X + 420, ss1_Y + 200, 72, 65, 15, WHITE);


      }


      if (x_set_rotatoon_305 > repeat_X && x_set_rotatoon_305 < ( repeat_X + 110) && y_set_rotatoon_305 > repeat_Y && y_set_rotatoon_305 < ( repeat_Y + 75)) {

        a = 1;
        show_keyboard = 1  ;
        rp = 1;
        st = 0;
        sbp = 0;

        key_board(keyboard_X, keyboard_Y);
        block_key = 1;

      }

    }

    if ( sbp == 1) // mở khóa speed
    {

      if (x_set_rotatoon_305 > (ss1_X + 100) && x_set_rotatoon_305 < (ss1_X + 100 + 65) && y_set_rotatoon_305 > (ss1_Y + 157) && y_set_rotatoon_305 < ( ss1_Y + 157 + 65)) {

        bp2 = 30;
        if (  bp2 > 1 ) {
          tft.fillRoundRect(ss1_X + 420, ss1_Y + 200, 72, 65, 15, DARKGREEN);
          tft.drawRoundRect(ss1_X + 420, ss1_Y + 200, 72, 65, 15, WHITE);
          tft.setCursor(ss1_X + 429, ss1_Y + 222);
          tft.setTextSize(3);
          tft.setTextColor(WHITE);
          tft.println(bp2);



        }

      }


      if (x_set_rotatoon_305 > (ss1_X + 190) && x_set_rotatoon_305 < (ss1_X + 190 + 65) && y_set_rotatoon_305 > (ss1_Y + 157) && y_set_rotatoon_305 < ( ss1_Y + 157 + 65)) {
        bp2 = 60;

        tft.fillRoundRect(ss1_X + 420, ss1_Y + 200, 72, 65, 15, DARKGREEN);
        tft.drawRoundRect(ss1_X + 420, ss1_Y + 200, 72, 65, 15, WHITE);
        tft.setCursor(ss1_X + 429, ss1_Y + 222);
        tft.setTextSize(3);
        tft.setTextColor(WHITE);
        tft.println(bp2);





      }

      if (x_set_rotatoon_305 > (ss1_X + 282) && x_set_rotatoon_305 < (ss1_X + 282 + 65) && y_set_rotatoon_305 > (ss1_Y + 157) && y_set_rotatoon_305 < ( ss1_Y + 157 + 65)) {

        bp2 = 90;

        tft.fillRoundRect(ss1_X + 420, ss1_Y + 200, 72, 65, 15, DARKGREEN);
        tft.drawRoundRect(ss1_X + 420, ss1_Y + 200, 72, 65, 15, WHITE);
        tft.setCursor(ss1_X + 429, ss1_Y + 222);
        tft.setTextSize(3);
        tft.setTextColor(WHITE);
        tft.println(bp2);






      }

      if (x_set_rotatoon_305 > (ss1_X + 100) && x_set_rotatoon_305 < (ss1_X + 100 + 65) && y_set_rotatoon_305 > (ss1_Y + 242) && y_set_rotatoon_305 < ( ss1_Y + 242 + 65)) {

        bp2 = 120;

        tft.fillRoundRect(ss1_X + 420, ss1_Y + 200, 72, 65, 15, DARKGREEN);
        tft.drawRoundRect(ss1_X + 420, ss1_Y + 200, 72, 65, 15, WHITE);
        tft.setCursor(ss1_X + 429, ss1_Y + 222);
        tft.setTextSize(3);
        tft.setTextColor(WHITE);
        tft.println(bp2);





      }

      if (x_set_rotatoon_305 > (ss1_X + 190) && x_set_rotatoon_305 < (ss1_X + 190 + 65) && y_set_rotatoon_305 > (ss1_Y + 242) && y_set_rotatoon_305 < ( ss1_Y + 242 + 65)) {
        bp2 = 150;
        tft.fillRoundRect(ss1_X + 420, ss1_Y + 200, 72, 65, 15, DARKGREEN);
        tft.drawRoundRect(ss1_X + 420, ss1_Y + 200, 72, 65, 15, WHITE);
        tft.setCursor(ss1_X + 429, ss1_Y + 222);
        tft.setTextSize(3);
        tft.setTextColor(WHITE);
        tft.println(bp2);

      }

      if (x_set_rotatoon_305 > (ss1_X + 282) && x_set_rotatoon_305 < (ss1_X + 282 + 65) && y_set_rotatoon_305 > (ss1_Y + 242) && y_set_rotatoon_305 < ( ss1_Y + 242 + 65)) {
        bp2 = 180;
        tft.fillRoundRect(ss1_X + 420, ss1_Y + 200, 72, 65, 15, DARKGREEN);
        tft.drawRoundRect(ss1_X + 420, ss1_Y + 200, 72, 65, 15, WHITE);
        tft.setCursor(ss1_X + 429, ss1_Y + 222);
        tft.setTextSize(3);
        tft.setTextColor(WHITE);
        tft.println(bp2);

      }

      if (x_set_rotatoon_305 > (ss1_X + 443) && x_set_rotatoon_305 < (ss1_X + 443 + 72) && y_set_rotatoon_305 > (ss1_Y + 200) && y_set_rotatoon_305 < ( ss1_Y + 200 + 65)) {

        sbp = 0;
        a = 0;
        block_key = 0;
        show_keyboard = 0;
        show_keyboard1 = 0;
        tft.fillRoundRect(300, 160, 480, 320, 0, Z);
        start_btn(start_X, start_Y);
        stop_btn(stop_X, stop_Y);
        home_btn(home_X, home_Y);
        speed_btn( speed_X , speed_Y);
        select_btn ( select_X , select_Y);
        repeat_btn ( repeat_X , repeat_Y);
        ck_speed(ck_speed_X, ck_speed_Y);
        ngang1( line1_X , line1_Y);
        ngang2( line2_X , line2_Y);
        doc1( line3_X , line3_Y);
        doc2( line4_X , line4_Y);


      }


    }
    if ( block_key == 1) // mở khóa bàn phím
    {
      //1
      if (x_set_rotatoon_305 > (keyboard_X + 14) && x_set_rotatoon_305 < (keyboard_X + 14  + 65) && y_set_rotatoon_305 > (keyboard_Y + 70) && y_set_rotatoon_305 < ( keyboard_Y + 70 + 65)) {
        if (st == 1) {


          bp = 1;
        }

        if ( rp == 1) {
          bp1 = 1 ;
          
        }
        outbp(outbp_X, outbp_Y);
      }
      //2
      if (x_set_rotatoon_305 > (keyboard_X + 100) && x_set_rotatoon_305 < (keyboard_X + 100 + 65) && y_set_rotatoon_305 > (keyboard_Y + 70) && y_set_rotatoon_305 < ( keyboard_Y + 70 + 65)) {
        if (st == 1) {
          bp = 2;
        }
        if ( rp == 1) {
          bp1 = 2;
        }
        outbp(outbp_X, outbp_Y);
      }
      //3
      if (x_set_rotatoon_305 > (keyboard_X + 190) && x_set_rotatoon_305 < (keyboard_X + 190 + 65) && y_set_rotatoon_305 > (keyboard_Y + 70) && y_set_rotatoon_305 < ( keyboard_Y + 70 + 65)) {

        if (st == 1) {
          bp = 3;
        }
        if ( rp == 1) {
          bp1 = 3;
        }
        outbp(outbp_X, outbp_Y);
      }
      //4
      if (x_set_rotatoon_305 > (keyboard_X + 282) && x_set_rotatoon_305 < (keyboard_X + 282 + 65) && y_set_rotatoon_305 > (keyboard_Y + 70) && y_set_rotatoon_305 < ( keyboard_Y + 70 + 65)) {
        if (st == 1) {
          bp = 4;
        }
        if ( rp == 1) {
          bp1 = 4;
        }
        outbp(outbp_X, outbp_Y);
      }
      //5
      if (x_set_rotatoon_305 > (keyboard_X + 369) && x_set_rotatoon_305 < (keyboard_X + 369 + 65) && y_set_rotatoon_305 > (keyboard_Y + 70) && y_set_rotatoon_305 < ( keyboard_Y + 70 + 65)) {
        if (st == 1) {
          bp = 5;
        }
        if ( rp == 1) {
          bp1 = 5;
        }
        outbp(outbp_X, outbp_Y);
      }
      //6
      if (x_set_rotatoon_305 > (keyboard_X + 14) && x_set_rotatoon_305 < (keyboard_X + 14 + 65) && y_set_rotatoon_305 > (keyboard_Y + 157) && y_set_rotatoon_305 < ( keyboard_Y + 157 + 65)) {
        if (st == 1) {
          bp = 6;
        }
        if ( rp == 1) {
          bp1 = 6;
        }
        outbp(outbp_X, outbp_Y);
      }
      //7
      if (x_set_rotatoon_305 > (keyboard_X + 100) && x_set_rotatoon_305 < (keyboard_X + 100 + 65) && y_set_rotatoon_305 > (keyboard_Y + 157) && y_set_rotatoon_305 < ( keyboard_Y + 157 + 65)) {

        if (st == 1) {
          bp = 7;
        }
        if ( rp == 1) {
          bp1 = 7;
        }
        outbp(outbp_X, outbp_Y);
      }
      //8
      if (x_set_rotatoon_305 > (keyboard_X + 190) && x_set_rotatoon_305 < (keyboard_X + 190 + 65) && y_set_rotatoon_305 > (keyboard_Y + 157) && y_set_rotatoon_305 < ( keyboard_Y + 157 + 65)) {
        if (st == 1) {
          bp = 8;
        }
        if ( rp == 1) {
          bp1 = 8;
        }
        outbp(outbp_X, outbp_Y);
      }
      //9
      if (x_set_rotatoon_305 > (keyboard_X + 282) && x_set_rotatoon_305 < (keyboard_X + 282 + 65) && y_set_rotatoon_305 > (keyboard_Y + 157) && y_set_rotatoon_305 < ( keyboard_Y + 157 + 65)) {
        if (st == 1) {
          bp = 9;
        }
        if ( rp == 1) {
          bp1 = 9;
        }
        outbp(outbp_X, outbp_Y);
      }
      //10
      if (x_set_rotatoon_305 > (keyboard_X + 358) && x_set_rotatoon_305 < (keyboard_X + 358 + 145) && y_set_rotatoon_305 > (keyboard_Y + 146) && y_set_rotatoon_305 < ( keyboard_Y + 146 + 65)) {
        if (st == 1) {
          bp = 10;
        }
        if ( rp == 1) {
          bp1 = 10;
        }
        outbp(outbp_X, outbp_Y);
      }
      //11
      if (x_set_rotatoon_305 > (keyboard_X + 14) && x_set_rotatoon_305 < (keyboard_X + 14 + 145) && y_set_rotatoon_305 > (keyboard_Y + 242) && y_set_rotatoon_305 < ( keyboard_Y + 242 + 65)) {
        if (st == 1) {
          bp = 11;
        }
        if ( rp == 1) {
          bp1 = 11;
        }
        outbp(outbp_X, outbp_Y);
      }
      //12
      if (x_set_rotatoon_305 > (keyboard_X + 100) && x_set_rotatoon_305 < (keyboard_X + 100 + 65) && y_set_rotatoon_305 > (keyboard_Y + 242) && y_set_rotatoon_305 < ( keyboard_Y + 242 + 65)) {
        if (st == 1) {
          bp = 12;
        }
        if ( rp == 1) {
          bp1 = 12;
        }
        outbp(outbp_X, outbp_Y);
      }
      //13
      if (x_set_rotatoon_305 > (keyboard_X + 190) && x_set_rotatoon_305 < (keyboard_X + 190 + 65) && y_set_rotatoon_305 > (keyboard_Y + 242) && y_set_rotatoon_305 < ( keyboard_Y + 242 + 65)) {
        if (st == 1) {
          bp = 13;
        }
        if ( rp == 1) {
          bp1 = 13;
        }
        outbp(outbp_X, outbp_Y);
      }
      //14
      if (x_set_rotatoon_305 > (keyboard_X + 282) && x_set_rotatoon_305 < (keyboard_X + 282 + 65) && y_set_rotatoon_305 > (keyboard_Y + 242) && y_set_rotatoon_305 < ( keyboard_Y + 242 + 65)) {
        if (st == 1) {
          bp = 14;
        }
        if ( rp == 1) {
          bp1 = 14;
        }
        outbp(outbp_X, outbp_Y);
      }
      //15
      if (x_set_rotatoon_305 > (keyboard_X + 361) && x_set_rotatoon_305 < (keyboard_X + 361 + 65) && y_set_rotatoon_305 > (keyboard_Y + 248) && y_set_rotatoon_305 < ( keyboard_Y + 248 + 65)) {
        if (st == 1) {
          bp = 15;
        }
        if ( rp == 1) {
          bp1 = 15;
        }
        outbp(outbp_X, outbp_Y);
      }
      //16
      if (x_set_rotatoon_305 > (keyboard_X + 14) && x_set_rotatoon_305 < (keyboard_X + 14 + 65) && y_set_rotatoon_305 > (keyboard_Y + 320) && y_set_rotatoon_305 < ( keyboard_Y + 320 + 65)) {
        if (st == 1) {
          bp = 16;
        }
        if ( rp == 1) {
          bp1 = 16;
        }
        outbp(outbp_X, outbp_Y);
      }
      //17
      if (x_set_rotatoon_305 > (keyboard_X + 100) && x_set_rotatoon_305 < (keyboard_X + 100 + 65) && y_set_rotatoon_305 > (keyboard_Y + 320) && y_set_rotatoon_305 < ( keyboard_Y + 320 + 65)) {
        if (st == 1) {
          bp = 17;
        }
        if ( rp == 1) {
          bp1 = 17;
        }
        outbp(outbp_X, outbp_Y);
      }
      //18
      if (x_set_rotatoon_305 > (keyboard_X + 190) && x_set_rotatoon_305 < (keyboard_X + 190 + 65) && y_set_rotatoon_305 > (keyboard_Y + 320) && y_set_rotatoon_305 < ( keyboard_Y + 320 + 65)) {
        if (st == 1) {
          bp = 18;
        }
        if ( rp == 1) {
          bp1 = 18;
        }
        outbp(outbp_X, outbp_Y);
      }
      //19
      if (x_set_rotatoon_305 > (keyboard_X + 282) && x_set_rotatoon_305 < (keyboard_X + 282 + 65) && y_set_rotatoon_305 > (keyboard_Y + 320) && y_set_rotatoon_305 < ( keyboard_Y + 320 + 65)) {
        if (st == 1) {
          bp = 19;
        }
        if ( rp == 1) {
          bp1 = 19;
        }
        outbp(outbp_X, outbp_Y);
      }
      //20
      if (x_set_rotatoon_305 > (keyboard_X + 369) && x_set_rotatoon_305 < (keyboard_X + 369 + 65) && y_set_rotatoon_305 > (keyboard_Y + 320) && y_set_rotatoon_305 < ( keyboard_Y + 320 + 65)) {
        if (st == 1) {
          bp = 20;
        }
        if ( rp == 1) {
          bp1 = 20;
        }
        outbp(outbp_X, outbp_Y);
      }

      //<<
      if (x_set_rotatoon_305 > (keyboard_X + 443) && x_set_rotatoon_305 < (keyboard_X + 443 + 55) && y_set_rotatoon_305 > (keyboard_Y + 200) && y_set_rotatoon_305 < ( keyboard_Y + 200 + 65)) {
        sbp = 0;
        a = 0;
        block_key = 0;
        show_keyboard = 0;
        tft.fillRoundRect(300, 160, 480, 320, 0, Z);
        start_btn(start_X, start_Y);
        stop_btn(stop_X, stop_Y);
        home_btn(home_X, home_Y);
        speed_btn( speed_X , speed_Y);
        select_btn ( select_X , select_Y);
        repeat_btn ( repeat_X , repeat_Y);
        ck_speed(ck_speed_X, ck_speed_Y);
        ngang1( line1_X , line1_Y);
        ngang2( line2_X , line2_Y);
        doc1( line3_X , line3_Y);
        doc2( line4_X , line4_Y);


      }

    }


  }

  if ( quay > 0)
  {
      for ( int s = 0 ; s < bp1; s++)
  {
    digitalWrite(dirPin, LOW);
    for (  x = 0; x < vi_tri ; x++)
    {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(5000);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(5000);
    }
    myServo1.write(0);
    goc1 = myServo1.read();
    delay(1000);
    myServo1.write(18);
    goc1 = myServo1.read();
    delay(100);
    digitalWrite(dirPin, HIGH);
    for ( int  n = 0; n < 280 ;n++)
    {
      if( digitalRead(CB) == HIGH)
      break;
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(5100);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(5100);
      
    }
     quay =0;
      delay(500);
  }
   
 }


if ( homee > 0)
{
  digitalWrite(dirPin, HIGH);
    for ( int  n = 0; n < 200 ;n++)
    {
      if( digitalRead(CB) == HIGH)
      break;
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(5100);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(5100);
    }
    homee = 0;
}
Serial.println (giatri);
   
}

// vẽ đối tượng
void ck_speed(int xp, int yp)
{
  tft.fillRoundRect(xp, yp, 480, 160, 0, BLACKM);
  tft.fillRoundRect(xp + 2, yp + 2, 478, 158 , 0, LIGHTGREY);

}

void ngang1(int xp, int yp)
{



  tft.fillRoundRect(xp, yp, 150, 320, 0, BLACKM);
  tft.fillRoundRect(xp + 2, yp + 2, 148, 318, 0, CS);

  tft.drawLine(300.5, 160, 300.5, 320, BLACKM);
  tft.drawLine(300, 160.5, 480, 160.5, BLACKM);
  tft.drawLine(300, 161, 480, 161, BLACKM);
  tft.drawLine(301, 160, 301, 320, BLACKM);

  tft.fillRoundRect(302 + 2, 6 + 2, 174, 121, 50, CE);
  tft.drawRoundRect(302 + 2, 6 + 2, 174, 121, 50, WHITE);

  tft.setCursor( 368, 136);
  tft.setTextSize(3);
  tft.setTextColor(NAVY);
  tft.println("RPM");



  tft.setCursor(xp + 45, yp + 34);
  tft.setTextSize(2.5);
  tft.setTextColor(WHITE);
  tft.println("SPEED");
  tft.setCursor(xp + 28, yp + 55);
  tft.setTextSize(2.5);
  tft.setTextColor(WHITE);
  tft.println("SETTINGS");
  tft.drawRoundRect(speed_X, speed_Y, 110, 75, 10, WHITE);

  if ( bp2 > 90) {
    s = 15;
  }
  if ( bp2 < 120 && bp2 > 20 ) {
    s = 0;
  }
  if ( bp2 < 20) {
    z = 8;
  }
  if ( bp2 > 20) {
    z = 0;
  }

  tft.setCursor(speed_X + 36 - s + z, speed_Y + 24);
  tft.setTextSize(4);
  tft.setTextColor(BP);
  tft.print(bp2);
}

void doc1(int xp, int yp)
{
  tft.fillRoundRect(xp, yp, 150, 160, 0, BLACKM);
  tft.fillRoundRect(xp + 2, yp + 2, 148, 158, 0, CX);
  tft.setCursor(xp + 43, yp + 34);
  tft.setTextSize(2.5);
  tft.setTextColor(WHITE);
  tft.println("SELECT");
  tft.setCursor(xp + 18, yp + 55);
  tft.setTextSize(2.5);
  tft.setTextColor(WHITE);
  tft.println("OBJECTIVES");
  tft.drawRoundRect(select_X, select_Y, 110, 75, 10, WHITE);
  tft.drawRoundRect(repeat_X, repeat_Y, 110, 75, 10, WHITE);
  if ( bp > 9) {
    x = 12;
  }
  if ( bp < 10 ) {
    x = 0;
  }
  if ( bp > 19 ) {
    x = 9;
  }
  tft.setCursor(select_X + 44 - x, select_Y + 24);
  tft.setTextSize(4);
  tft.setTextColor(BP);
  tft.print(bp);

}

void ngang2(int xp, int yp)
{
  tft.fillRoundRect(xp, yp, 150, 320, 0, BLACKM);
  tft.fillRoundRect(xp + 2, yp + 2, 148, 318, 0, CD);
  tft.setCursor(xp + 42, yp + 34);
  tft.setTextSize(2.5);
  tft.setTextColor(WHITE);
  tft.println("STATUS");
   tft.fillRoundRect(152, 235, 145, 25, 0, CD);
        tft.setCursor(163,240);
        tft.setTextSize(2.5);
        tft.setTextColor(RED);
        tft.println("STOPPED @_@");
}

void doc2(int xp, int yp)
{
  tft.fillRoundRect(xp, yp, 150, 160, 0, BLACKM);
  tft.fillRoundRect(xp + 2, yp + 2, 148, 158, 0, CA);
  tft.setCursor(xp + 43, yp + 34);
  tft.setTextSize(2.5);
  tft.setTextColor(WHITE);
  tft.println("NUMBER");
  tft.setCursor(xp + 22, yp + 55);
  tft.setTextSize(2.5);
  tft.setTextColor(WHITE);
  tft.println("OF REPEAT");
  tft.drawRoundRect(repeat_X, repeat_Y, 110, 75, 10, WHITE);
  if (bp1 > 9) {
    x1 = 12;
  }
  if ( bp1 < 10 ) {
    x1 = 0;
  }
  if ( bp1 > 19 ) {
    x1 = 9;
  }
  tft.setCursor(repeat_X + 42 - x1, repeat_Y + 24);
  tft.setTextSize(4);
  tft.setTextColor(BP);
  tft.print(bp1);


}



void start_btn(int xp, int yp) {

  tft.fillRoundRect(xp, yp, 75, 75, 10, BLACKM);
  tft.fillRoundRect(xp + 2 , yp + 2, 71, 71, 10, DARKGREEN);
  tft.setCursor(xp + 9.5, yp + 29);
  tft.setTextSize(2.5);
  tft.setTextColor(WHITE);
  tft.println("START");
}


void stop_btn(int xp, int yp) {
  tft.fillRoundRect(xp, yp, 75, 75, 10, BLACKM);
  tft.fillRoundRect(xp + 2, yp + 2, 71, 71, 10, RED);
  tft.setCursor(xp + 14, yp + 29);
  tft.setTextSize(2.5);
  tft.setTextColor(WHITE);
  tft.println("STOP");
}


void home_btn(int xp, int yp) {
  tft.fillRoundRect(xp, yp, 164, 68, 10, BLACKM);
  tft.fillRoundRect(xp + 2, yp + 2, 160, 64, 10, OLIVE);
  tft.setCursor(xp + 49, yp + 25);
  tft.setTextSize(3);
  tft.setTextColor(WHITE);
  tft.println("HOME");
}




void start_btn_press(int xp, int yp) {
  tft.fillRoundRect(xp, yp, 75, 75, 10, BLACKM);

  
}
void stop_btn_press(int xp, int yp) {
  tft.fillRoundRect(xp, yp, 75, 75, 10, BLACKM);
}
void home_btn_press(int xp, int yp) {
  tft.fillRoundRect(xp, yp, 164, 68, 10, BLACKM);
}



void speed_btn(int xp, int yp) {
  tft.drawRoundRect(xp, yp, 110, 75, 10, WHITE);
}
void select_btn(int xp, int yp) {
  tft.drawRoundRect(xp, yp, 110, 75, 10, WHITE);
}
void repeat_btn(int xp, int yp) {
  tft.drawRoundRect(xp, yp, 110, 75, 10, WHITE);
}



void key_board( int xp , int yp) {
  

  if ( show_keyboard == 1) {
    tft.fillScreen(CD);
    tft.fillRoundRect(ss1_X + 420, ss1_Y + 200, 72, 65, 15, CD);
    // 1
    tft.fillRoundRect(xp + 14, yp + 70, 65, 65, 15, BP);
    tft.drawRoundRect(xp + 14, yp + 70, 65, 65, 15, WHITE);
    tft.setCursor(xp + 37, yp + 89);
    tft.setTextSize(4);
    tft.setTextColor(WHITE);
    tft.println("1");
    //2
    tft.fillRoundRect(xp + 100, yp + 70, 65, 65, 15, BP);
    tft.drawRoundRect(xp + 100, yp + 70, 65, 65, 15, WHITE);
    tft.setCursor(xp + 123, yp + 89);
    tft.setTextSize(4);
    tft.setTextColor(WHITE);
    tft.println("2");
    //3
    tft.fillRoundRect(xp + 193, yp + 70, 65, 65, 15, BP);
    tft.drawRoundRect(xp + 193, yp + 70, 65, 65, 15, WHITE);
    tft.setCursor(xp + 217, yp + 89);
    tft.setTextSize(4);
    tft.setTextColor(WHITE);
    tft.println("3");
    //4
    tft.fillRoundRect(xp + 282, yp + 70, 65, 65, 15, BP);
    tft.drawRoundRect(xp + 282, yp + 70, 65, 65, 15, WHITE);
    tft.setCursor(xp + 305, yp + 89);
    tft.setTextSize(4);
    tft.setTextColor(WHITE);
    tft.println("4");
    //5
    tft.fillRoundRect(xp + 369, yp + 70, 65, 65, 15, BP);
    tft.drawRoundRect(xp + 369, yp + 70, 65, 65, 15, WHITE);
    tft.setCursor(xp + 392, yp + 91);
    tft.setTextSize(4);
    tft.setTextColor(WHITE);
    tft.println("5");
    //6
    tft.fillRoundRect(xp + 14, yp + 157, 65, 65, 15, BP);
    tft.drawRoundRect(xp + 14, yp + 157, 65, 65, 15, WHITE);
    tft.setCursor(xp + 37, yp + 177);
    tft.setTextSize(4);
    tft.setTextColor(WHITE);
    tft.println("6");
    //7
    tft.fillRoundRect(xp + 100, yp + 157, 65, 65, 15, BP);
    tft.drawRoundRect(xp + 100, yp + 157, 65, 65, 15, WHITE);
    tft.setCursor(xp + 123, yp + 177);
    tft.setTextSize(4);
    tft.setTextColor(WHITE);
    tft.println("7");
    //8
    tft.fillRoundRect(xp + 190, yp + 157, 65, 65, 15, BP);
    tft.drawRoundRect(xp + 190, yp + 157, 65, 65, 15, WHITE);
    tft.setCursor(xp + 213, yp + 177);
    tft.setTextSize(4);
    tft.setTextColor(WHITE);
    tft.println("8");
    //9
    tft.fillRoundRect(xp + 282, yp + 157, 65, 65, 15, BP);
    tft.drawRoundRect(xp + 282, yp + 157, 65, 65, 15, WHITE);
    tft.setCursor(xp + 305, yp + 177);
    tft.setTextSize(4);
    tft.setTextColor(WHITE);
    tft.println("9");
    //10
    tft.fillRoundRect(xp + 369, yp + 157, 65, 65, 15, BP);
    tft.drawRoundRect(xp + 369, yp + 157, 65, 65, 15, WHITE);
    tft.setCursor(xp + 379, yp + 177);
    tft.setTextSize(4);
    tft.setTextColor(WHITE);
    tft.println("10");
    //11
    tft.fillRoundRect(xp + 14, yp + 242, 65, 65, 15, BP);
    tft.drawRoundRect(xp + 14, yp + 242, 65, 65, 15, WHITE);
    tft.setCursor(xp + 27, yp + 260);
    tft.setTextSize(4);
    tft.setTextColor(WHITE);
    tft.println("11");
    //12
    tft.fillRoundRect(xp + 100, yp + 242, 65, 65, 15, BP);
    tft.drawRoundRect(xp + 100, yp + 242, 65, 65, 15, WHITE);
    tft.setCursor(xp + 110, yp + 260);
    tft.setTextSize(4);
    tft.setTextColor(WHITE);
    tft.println("12");
    //13
    tft.fillRoundRect(xp + 190, yp + 242, 65, 65, 15, BP);
    tft.drawRoundRect(xp + 190, yp + 242, 65, 65, 15, WHITE);
    tft.setCursor(xp + 197, yp + 260);
    tft.setTextSize(4);
    tft.setTextColor(WHITE);
    tft.println("13");
    //14
    tft.fillRoundRect(xp + 282, yp + 242, 65, 65, 15, BP);
    tft.drawRoundRect(xp + 282, yp + 242, 65, 65, 15, WHITE);
    tft.setCursor(xp + 295, yp + 260);
    tft.setTextSize(4);
    tft.setTextColor(WHITE);
    tft.println("14");
    //15
    tft.fillRoundRect(xp + 369, yp + 242, 65, 65, 15, BP);
    tft.drawRoundRect(xp + 369, yp + 242, 65, 65, 15, WHITE);
    tft.setCursor(xp + 379, yp + 260);
    tft.setTextSize(4);
    tft.setTextColor(WHITE);
    tft.println("15");
    //16
    tft.fillRoundRect(xp + 14, yp + 320, 65, 65, 15, BP);
    tft.drawRoundRect(xp + 14, yp + 320, 65, 65, 15, WHITE);
    tft.setCursor(xp + 27, yp + 337);
    tft.setTextSize(4);
    tft.setTextColor(WHITE);
    tft.println("16");
    //17
    tft.fillRoundRect(xp + 100, yp + 320, 65, 65, 15, BP);
    tft.drawRoundRect(xp + 100, yp + 320, 65, 65, 15, WHITE);
    tft.setCursor(xp + 110, yp + 337);
    tft.setTextSize(4);
    tft.setTextColor(WHITE);
    tft.println("17");
    //18
    tft.fillRoundRect(xp + 190, yp + 320, 65, 65, 15, BP);
    tft.drawRoundRect(xp + 190, yp + 320, 65, 65, 15, WHITE);
    tft.setCursor(xp + 197, yp + 337);
    tft.setTextSize(4);
    tft.setTextColor(WHITE);
    tft.println("18");
    //19
    tft.fillRoundRect(xp + 282, yp + 320, 65, 65, 15, BP);
    tft.drawRoundRect(xp + 282, yp + 320, 65, 65, 15, WHITE);
    tft.setCursor(xp + 292, yp + 337);
    tft.setTextSize(4);
    tft.setTextColor(WHITE);
    tft.println("19");
    //20
    tft.fillRoundRect(xp + 369, yp + 320, 65, 65, 15, BP);
    tft.drawRoundRect(xp + 369, yp + 320, 65, 65, 15, WHITE);
    tft.setCursor(xp + 379, yp + 337);
    tft.setTextSize(4);
    tft.setTextColor(WHITE);
    tft.println("20");
    //ok
    tft.fillRoundRect(xp + 441, yp + 200, 52, 65, 15, DARKGREEN);
    tft.drawRoundRect(xp + 441, yp + 200, 52, 65, 15, WHITE);

  }

  
}

void outbp ( int xp, int yp)
{   

  if (  bp > 1 || bp1 > 1) {
    tft.fillRoundRect(xp + 441, yp + 200, 52, 65, 15, DARKGREEN);
    tft.drawRoundRect(xp + 441, yp + 200, 52, 65, 15, WHITE);
    tft.setCursor(xp + 449, yp + 222);
    tft.setTextSize(3);
    tft.setTextColor(WHITE);
    if ( st == 1) {
      tft.println(bp);
    }
    if ( rp == 1) {
      tft.println(bp1);
    }
  }
  
}
