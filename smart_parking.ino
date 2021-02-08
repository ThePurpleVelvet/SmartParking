#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>
#include <Servo.h>

BlynkTimer timer;
Servo myServo1;

char auth[] = "tCgN92mpJSmjI6zOHoQvq7brjHYqINu6";
char ssid[] = "Rosemary";
char pass[] = "passwordapa";

// Gate Sensor
int ir_s1 = D1;
int ir_s2 = D2;

// Parking Slot Sensor
int ir_s3 = D5;
int ir_s4 = D6;
int ir_s5 = D7;

int total = 3;
int space;

int flag1 = 0;
int flag2 = 0;

WidgetLED led1(V10);
WidgetLED led2(V11);
WidgetLED led3(V12);

void parkingSlot1()
{
  int detected = digitalRead(D5);
  if (detected == 1) {
    led1.off();
    //Serial.println("LED : off");
  } else {
    led1.on();
    //Serial.println("LED : on");
  }
}

void parkingSlot2()
{
  int detected = digitalRead(D6);
  if (detected == 1) {
    led2.off();
    //Serial.println("LED : off");
  } else {
    led2.on();
    //Serial.println("LED : on");
  }
}

void parkingSlot3()
{
  int detected = digitalRead(D7);
  if (detected == 1) {
    led3.off();
    //Serial.println("LED : off");
  } else {
    led3.on();
    //Serial.println("LED : on");
  }
}

// PROGRAM START

void setup() {
Serial.begin(9600);
Blynk.begin(auth, ssid, pass);
  
pinMode(ir_s1, INPUT);
pinMode(ir_s2, INPUT);
pinMode(ir_s3, INPUT);
pinMode(ir_s4, INPUT);
pinMode(ir_s5, INPUT);
  
myServo1.attach(D0);
myServo1.write(0);  

space = total;

  timer.setInterval(1000L, parkingSlot1);
  timer.setInterval(1000L, parkingSlot2);
  timer.setInterval(1000L, parkingSlot3);
}

void loop() {
//  RUNNING BLYNK
Blynk.run();
timer.run();

//  PRINTING PARKING SLOT
    Serial.print("Space = ");
    Serial.println(space);
    Serial.print("Flag1 = ");
    Serial.println(flag1);
    Serial.print("Flag2 = ");
    Serial.println(flag2);
    delay (1500);

//  PROGRAM LOOP STARTS
   
  if(digitalRead (ir_s1) == LOW && flag1 == 0)
  {
    if(space > 0)
    {
      flag1 = 1;
      if(flag2 == 0)
      {
        myServo1.write(100); 
        space = space - 1;
      } 
    }else
    { 
      Serial.println("Full Parking");
      delay (1500);
    }
}

if(digitalRead (ir_s2) == LOW && flag2 == 0)
{
  flag2 = 1;
  if(flag1 == 0)
  {
    myServo1.write(100); 
    space = space + 1;
  }
}

if(flag1 == 1 && flag2 == 1)
{
  delay (1000);
  myServo1.write(0);
  flag1=0; 
  flag2=0;
}
  

} // END PROGRAM
