#include <Wire.h>
#include <Servo.h>
Servo myServo1;
const int dirPin = 4;
const int stepPin = 5;
int servo1 = 6;
int goc1;
int vi_tri;
int bp1;

void setup()
{
  Wire.begin(7); // Khởi tạo thư viện i2c địa chỉ 7
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  Serial.begin(9600);
  Wire.onRequest(receiveEvent);
  myServo1.attach(servo1);
  
}


void receiveEvent() // hàm sự kiện nhận tín hiệu từ boad chủ
{
  while (Wire.available()) // chờ cho đến khi có tín hiệu
  {
    vi_tri = Wire.read(); // biến c để lưu dữ liệu nhận được
   bp1 = Wire.read();
  }

}

void loop()
{
  myServo1.write(35);
  goc1 = myServo1.read();

int index = My_data.lastIndexOf('/');
int length = My_data.length();
char sub_data = My_data.substring(0,index);
char sub_data1 = My_data.substring((index + 1), length);

vi_tri = sub_data.toInt();
bp1 = sub_data1.toInt();

  for ( int s = 0 ; s < bp1; s++)
  {
     // xung cấp cho step dựa vào vị trí được nhập trên master gửi xuống
    digitalWrite(dirPin, LOW);
    for ( int x = 0; x < vi_tri ; x++)
    {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(5000);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(5000);
    }
   // đập đối tượng khi chạy đến vị trí
    myServo1.write(15);
    goc1 = myServo1.read();
    delay(1000);
    myServo1.write(35);
    goc1 = myServo1.read();

  }
  
  Serial.println(vi_tri);
  Serial.println(bp1);
  delay(1000);
}
