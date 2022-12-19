#include <Wire.h>
#define potmeterPin A3
const byte pin_a = 2; //kênh a
const byte pin_b = 3;//kênh b
const byte pin_fwd = 5; //thuận
const byte pin_bwd = 4; //nghịch
const byte pin_pwm = 6;// băm xung
const int stepPin = 8;
const int dirPin = 7;
unsigned long  x = 0;
int encoder = 0;
int p, p1;
double sv_speed = 255.00;      //0~255
double pv_speed = 0.00;
int sp = 0;
int a = 0 ;
volatile long chieu_quay1 = 0;                      // chiều quay ~ thuận (0) ~ ngược (1)
volatile long chieu_quay2 = 0;
int set_speed = 150;             //          0~180.00
int c = 0;
double rotate = 20.00;         //   nhập số vòng muốn quay
int maxp = 0;
int minp = 0;
int sptb = 0;
double e_speed = 0.0; // lỗi vận tốc = speed cài đặt - speed đo được
double e_speed_pre = 0.0;  //lỗi cuối của vận tốc
double e_speed_sum = 0.0;  // tổng lỗi của vận tốc
double pwm_pulse = 0.0;     // 0~255
double kp = 0.00;        //
double ki = 0.00;        //
double kd = 0.00;        //
//
char voltBuff[7];

int timer1_counter; //timer đếm xung từ encoder kênh A
int i, pwm_step = 1 ;
int pulse_dt , stop_for = 0;
int delay_time = 0;
volatile long EncoderCount, y, pulse_step = 0;

void setup()
{
  Wire.begin(6); // Khởi tạo thư viện i2c địa chỉ 6
  Wire.onReceive(receiveEvent); // khởi tạo chế độ nhận tín hiệu từ boad chủ
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  pinMode(pin_a, INPUT_PULLUP);
  pinMode(pin_b, INPUT_PULLUP);
  pinMode(pin_fwd, OUTPUT);
  pinMode(pin_bwd, OUTPUT);
  pinMode(pin_pwm, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode (10, INPUT);
  pinMode (11, INPUT);
  Wire.onRequest(requestEvent);
  attachInterrupt(digitalPinToInterrupt(pin_a), detect_a, RISING);
  attachInterrupt(digitalPinToInterrupt(pin_b), detect_b, RISING);
  Serial.begin(9600);

  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  timer1_counter = 59286;   // chọn tốc độ đọc xung của timer (34286 cho 0.5sec) (59286 cho 0.1sec)


  TCNT1 = timer1_counter;
  TCCR1B |= (1 << CS12);
  TIMSK1 |= (1 << TOIE1);
  interrupts();

  analogWrite(pin_pwm, 0);
  digitalWrite(pin_fwd, 0); //>> dừng motor
  digitalWrite(pin_bwd, 0);

}


void receiveEvent() // hàm sự kiện nhận tín hiệu từ boad chủ
{
  while (Wire.available()) // chờ cho đến khi có tín hiệu
  {
    c = Wire.read(); // biến c để lưu dữ liệu nhận được

  }
}

void loop ()
{ //1023
  p = analogRead(potmeterPin); // đọc tín hiệu từ biến trở 0 ~
  delay_time = map(p, 40, 1023, 2440, 830);
  y = rotate * 748;
  if ( digitalRead(11) == LOW)
  { chieu_quay1 = chieu_quay1 + 1;
  }

  if ( digitalRead(10) == LOW)
  { chieu_quay1 = 0;
  }

  if ( p > 32)
  {

    if (chieu_quay1 == 0)
    {
      c =  map(p, 30, 1023, 30, 180);
      delayMicroseconds(100);
      digitalWrite(pin_fwd, 1);     //chạy thuận
      digitalWrite(pin_bwd, 0);
    }

    if ( chieu_quay1 > 0)
    {
      c =  map(p, 30, 1023, 30, 180);
      delayMicroseconds(100);
      digitalWrite(pin_fwd, 0);     //chạy n
      digitalWrite(pin_bwd, 1);
    }
  }



  if ( c == 2 ) {

    digitalWrite(pin_fwd, 0);     //chạy ngược
    digitalWrite(pin_bwd, 1);
    digitalWrite(dirPin, HIGH);
    kp = 0.8;
    ki = 0.5;
    kd = 0.95;
    pwm_step = 679;
    delay(200);
    for ( x = 0; x < (EncoderCount / 3.74); x++) {
      delayMicroseconds(100);
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(pwm_step); //
      digitalWrite(stepPin, LOW);
      delayMicroseconds(pwm_step);

    }
  }

  if ( p < 30)
  {
    if (c == 20)
    {
      for ( int s ; c > 0; s ++)
      {
        digitalWrite(dirPin, LOW);
        digitalWrite(pin_fwd, 1);     //chạy thuận
        digitalWrite(pin_bwd, 0);
        kp = 0.89;
        ki = 0.68;
        kd = 0.15;
        pwm_step = 3980;
        delay(200);
        for ( x = 0; x < (EncoderCount / 3.74); x++) {
          delayMicroseconds(100);
          digitalWrite(stepPin, HIGH);
          delayMicroseconds(pwm_step); //
          digitalWrite(stepPin, LOW);
          delayMicroseconds(pwm_step);
        }
        digitalWrite(dirPin, HIGH);
        digitalWrite(pin_fwd, 0);     //chạy n
        digitalWrite(pin_bwd, 1);
        kp = 0.89;
        ki = 0.68;
        kd = 0.15;
        pwm_step = 3980;
        delay(200);
        for ( x = 0; x < (EncoderCount / 3.74); x++) {
          delayMicroseconds(100);
          digitalWrite(stepPin, HIGH);
          delayMicroseconds(pwm_step); //
          digitalWrite(stepPin, LOW);
          delayMicroseconds(pwm_step);
        }
      }
    }

    if (c == 40)
    {
      for ( int z ; c > 0; z ++)
      {
        digitalWrite(dirPin, LOW);
        digitalWrite(pin_fwd, 1);     //chạy thuận
        digitalWrite(pin_bwd, 0);
        kp = 0.98;
        ki = 0.7;
        kd = 0.87;
        pwm_step = 4230;
        delay(200);
        for ( x = 0; x < (EncoderCount / 3.74); x++) {
          delayMicroseconds(100);
          if (digitalRead(11) == LOW || c == 0)
            break;
          digitalWrite(stepPin, HIGH);
          delayMicroseconds(pwm_step); //
          digitalWrite(stepPin, LOW);
          delayMicroseconds(pwm_step);
        }

        delayMicroseconds(100);
        if (digitalRead(11) == LOW)
        {
          c = 0;
        }
        delay(200);
        c = a;
        digitalWrite(dirPin, HIGH);
        digitalWrite(pin_fwd, 0);     //chạy n
        digitalWrite(pin_bwd, 1);
        kp = 0.98;
        ki = 0.7;
        kd = 0.87;
        pwm_step = 4230;
        delay(200);
        for ( x = 0; x < (EncoderCount / 3.74); x++) {
          delayMicroseconds(100);
          digitalWrite(stepPin, HIGH);
          delayMicroseconds(pwm_step); //
          digitalWrite(stepPin, LOW);
          delayMicroseconds(pwm_step);
        }
      }
    }

    if ( c == 60 )
    {
      if ( digitalRead(11) == HIGH)
      {
        delayMicroseconds(100);
        digitalWrite(pin_fwd, 1);     //chạy thuận
        digitalWrite(pin_bwd, 0);
        digitalWrite(dirPin, LOW);
        kp = 0.8;
        ki = 0.4;
        kd = 0.8;
        pwm_step = 4800;
        delay(1600);
        for ( x = 0; x < (EncoderCount / 3.74); x++) {
          delayMicroseconds(100);
          digitalWrite(stepPin, HIGH);
          delayMicroseconds(pwm_step);
          digitalWrite(stepPin, LOW);
          delayMicroseconds(pwm_step);
        }
      }

      if ( digitalRead(10) == HIGH)
      {
        digitalWrite(pin_fwd, 0);     //chạy n
        digitalWrite(pin_bwd, 1);
        digitalWrite(dirPin, HIGH);
        kp = 0.8;
        ki = 0.4;
        kd = 0.8;
        pwm_step = 4800;
        for ( x = 0; x <  (EncoderCount / 3.74); x++) {
          delayMicroseconds(100);
          digitalWrite(stepPin, HIGH);
          delayMicroseconds(pwm_step);
          digitalWrite(stepPin, LOW);
          delayMicroseconds(pwm_step);
        }
      }
    }

    if (c == 80)
    {
      if (digitalRead(11) == HIGH)
      {
        digitalWrite(pin_fwd, 1);     //chạy thuận
        digitalWrite(pin_bwd, 0);
        digitalWrite(dirPin, LOW);
        kp = 0.95;
        ki = 0.84;
        kd = 0.3;
        pwm_step = 3440;
        delay(800);
        for ( x = 0; x <  (EncoderCount / 3.74); x++) {
          delayMicroseconds(100);
          digitalWrite(stepPin, HIGH);
          delayMicroseconds(pwm_step); //
          digitalWrite(stepPin, LOW);
          delayMicroseconds(pwm_step);
        }
      }

      if ( digitalRead(10) == HIGH)
      {
        delayMicroseconds(100);
        digitalWrite(pin_fwd, 0);     //chạy n
        digitalWrite(pin_bwd, 1);
        digitalWrite(dirPin, HIGH);
        kp = 0.75;
        ki = 0.84;
        kd = 0.53;
        pwm_step = 4460;
        delay(800);
        for ( x = 0; x <  (EncoderCount / 3.74); x++) {
          delayMicroseconds(100);
          digitalWrite(stepPin, HIGH);
          delayMicroseconds(pwm_step); //
          digitalWrite(stepPin, LOW);
          delayMicroseconds(pwm_step);
        }
      }
    }

    if (c == 100)
    {
      if ( digitalRead(11) == HIGH)
      {
        chieu_quay2 = 0;
        delay(100);
        delayMicroseconds(100);
        digitalWrite(pin_fwd, 1);     //chạy thuận
        digitalWrite(pin_bwd, 0);
        digitalWrite(dirPin, LOW);
        kp = 0.9;
        ki = 0.85;
        kd = 0.95;
        pwm_step = 5645;
        delay(200);
        for ( x = 0; x <  (EncoderCount / 3.74); x++) {
          delayMicroseconds(100);
          digitalWrite(stepPin, HIGH);
          delayMicroseconds(pwm_step); //
          digitalWrite(stepPin, LOW);
          delayMicroseconds(pwm_step);
        }

      }

      if ( digitalRead(10) == HIGH)
      {

        delayMicroseconds(100);
        digitalWrite(pin_fwd, 0);     //chạy n
        digitalWrite(pin_bwd, 1);
        digitalWrite(dirPin, HIGH);
        kp = 0.99;
        ki = 0.75;
        kd = 0.95;
        pwm_step = 5645;
        delay(200);
        for ( x = 0; x <  (EncoderCount / 3.74); x++) {
          delayMicroseconds(100);
          digitalWrite(stepPin, HIGH);
          delayMicroseconds(pwm_step); //
          digitalWrite(stepPin, LOW);
          delayMicroseconds(pwm_step);
        }
      }
    }

    if ( c == 120)
    {
      if ( digitalRead(11) == HIGH)
      {

        delayMicroseconds(100);
        digitalWrite(pin_fwd, 1);     //chạy thuận
        digitalWrite(pin_bwd, 0);
        digitalWrite(dirPin, LOW);
        kp = 0.88;
        ki = 0.35;
        kd = 0.92;
        pwm_step = 4235;
        delay(200);
        for ( x = 0; x < (EncoderCount / 3.74); x++) {
          delayMicroseconds(100);
          digitalWrite(stepPin, HIGH);
          delayMicroseconds(pwm_step); //
          digitalWrite(stepPin, LOW);
          delayMicroseconds(pwm_step);


        }

      }

      if ( digitalRead(10) == HIGH)
      {
        delayMicroseconds(100);
        digitalWrite(pin_fwd, 0);     //chạy n
        digitalWrite(pin_bwd, 1);
        digitalWrite(dirPin, HIGH);
        kp = 0.88;
        ki = 0.35;
        kd = 0.92;
        pwm_step = 4235;
        delay(200);
        for ( x = 0; x <  (EncoderCount / 3.74); x++) {
          delayMicroseconds(100);
          digitalWrite(stepPin, HIGH);
          delayMicroseconds(pwm_step); //
          digitalWrite(stepPin, LOW);
          delayMicroseconds(pwm_step);


        }

      }
    }

  }
}

// tính xung encoder kênh A
void detect_a() {
  encoder += 1;

  bool PinB = digitalRead(pin_b);
  bool PinA = digitalRead(pin_a);

  if (PinB == LOW) {
    if (PinA == HIGH)
    {
      EncoderCount++;
    }
    else {
      EncoderCount--;
    }
  }

  else {
    if (PinA == HIGH) {
      EncoderCount--;
    }
    else {
      EncoderCount++;
    }
  }
}





ISR(TIMER1_OVF_vect)     //hàm timer để đọc xung encoder
{ //đếm
  TCNT1 = timer1_counter;   // cài đặt timer bắt đầu
  pv_speed = 60.0 * (encoder / 300.0) / 0.3; //tính vận tốc thực dựa vào xung encoder kênh A
  encoder = 0;


  if ( chieu_quay1 == 1)
  {
    if ( EncoderCount > y)
    {
      c = 0;
    }
  }

  if ( chieu_quay2 == 1)
  {
    if ( (-1 * EncoderCount) > y)
    {
      c = 0;
    }
  }


  // tính vận tốc trung bình và gửi lên master

  if ( pv_speed > c )
  {
    maxp = pv_speed;
  }


  if ( pv_speed < c )
  {
    minp = pv_speed;
  }


  sptb = (minp + maxp) / 2;
  if ( pv_speed < 1)
  {
    sptb = 0; // vận tốc trung bình
  }

  // cân bằng xung để đạt vận tốc cài đặt thông qua pid
  if ( c > 0) {
    e_speed = c - pv_speed;
    pwm_pulse =  (e_speed * kp + e_speed_sum * ki + (e_speed - e_speed_pre) * kd );
    e_speed_pre = e_speed;
    e_speed_sum += e_speed;
    if (e_speed_sum > 4000) e_speed_sum = 4000;
    if (e_speed_sum < -4000) e_speed_sum = -4000;
  }
  else {
    e_speed = 0;
    e_speed_pre = 0;
    e_speed_sum = 0;
    pwm_pulse = 0;
  }


  Serial.print(pv_speed); Serial.print("\n");
  Serial.print("      \t");
  Serial.print(pwm_pulse); Serial.print("\n");
  Serial.print("               \t");
  Serial.print( EncoderCount); Serial.print("\n");



  //cài đặt tốc độ mới cho servo và stepper

  if (pwm_pulse <255 & pwm_pulse >0) {
    analogWrite(pin_pwm, pwm_pulse); // xuất vận tốc theo pwm_pluse đã qua cân bằng pid
  }
  else if (pwm_pulse > 255) {
    analogWrite(pin_pwm, 255);
  }
  else
  {
    analogWrite(pin_pwm, 0);
  }

}


void requestEvent()
{


  Wire.write(sptb); //gửi vận tốc trung bình lên master

}
// tính xung kênh B
void detect_b() {
  bool PinB = digitalRead(pin_a);
  bool PinA = digitalRead(pin_b);

  if (PinA == LOW) {
    if (PinB == HIGH) {
      EncoderCount--;
    }
    else {
      EncoderCount++;
    }
  }

  else {
    if (PinB == HIGH) {
      EncoderCount++;
    }
    else {
      EncoderCount--;
    }
  }
}
