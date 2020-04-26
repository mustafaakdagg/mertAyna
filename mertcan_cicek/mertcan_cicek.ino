#include <Servo.h>
#include <SD.h>
#include <SPI.h>
#include <OneWire.h>
#include <DallasTemperature.h>
int lt;
int rt;
int ld;
int rd;

int avt;
int avd;
int avl;
int avr;
int dvert;
int dhoriz;

#define ONE_WIRE_BUS 7

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

float Celcius = 0;
int minDegrees;
int maxDegrees;
int minFeedback;
int maxFeedback;
int tolerance = 0;
int feedbackPin = A5;

File myFile;
int pinCS = 10;

Servo horizontal; // horizontal servo

int servoh = 90; // stand horizontal servo
int servohLimitHigh = 180;
int servohLimitLow = 0;
Servo vertical; // vertical servo
int counter = 0;
int temp;
int temp2;
int servov = 90;
int servovLimitHigh = 180;
int servovLimitLow = 40;
int ldrlt = 1; //LDR top left - BOTTOM LEFT <--- BDG
int ldrrt = 3; //LDR top rigt - BOTTOM RIGHT
int ldrld = 0; //LDR down left - TOP LEFT
int ldrrd = 2; //ldr down rigt - TOP RIGHT
int dtime = 20; int tol = 20 ;


void setup() {
  delay(100);
  Serial.begin(9600);
  sensors.begin();
  pinMode(pinCS, OUTPUT);



  horizontal.attach(5);
  vertical.attach(3);




  horizontal.write(170);
  Serial.println(90);
  delay(10000);

}
  void loop() {



  if (counter == 6) {
    temp = servoh;
    temp2 = servov;
    counter = 0;

    if (servoh < 90) {
      for (int i = temp; i <= 90; i++) {
        servoh = servoh + 1;
        horizontal.write(servoh);
        delay(dtime);
      }
    }
    else {
      for (int i = temp; i >= 90; i--) {
        servoh = servoh - 1;
        horizontal.write(servoh);
        delay(dtime);
      }
    }
    for (int i = temp2; i <= 180; i++) {
      servov = servov + 1;
      vertical.write(servov);
      delay(dtime);
    }
    delay(180000);
    myFile = SD.open("test.txt", FILE_WRITE);
    if (myFile) {
      myFile.print("after turned and waited for 3 minutes(C):");
      sensors.requestTemperatures();
      Celcius = sensors.getTempCByIndex(0);
      myFile.println(Celcius);
      myFile.close();
      Serial.println(" bekledi yazıldı");
    }
    else {
      Serial.println("error opening test.txt");
    }
    if (temp < 90) {
      for (int i = 90; i >= temp; i--) {
        servoh = servoh - 1;
        horizontal.write(servoh);
        delay(dtime);
      }
    }
    else if (temp > 90) {
      for (int i = 90; i <= temp; i++) {
        servoh = servoh + 1;
        horizontal.write(servoh);
        delay(dtime);
      }
    }
    for (int i = 180; i >= temp2; i--) {
      servov = servov - 1;
      vertical.write(servov);
      delay(dtime);
    }



  }
  else {

    ldrRead();



    if (lt > 200 || rt > 200 || ld > 200 || rd > 200) {
      if (-1 * tol > dvert || dvert > tol) // check if the diffirence is in the

      {
        if (avt > avd )
        {

          servov = ++servov;
          if (servov > servovLimitHigh)
          {
            servov = servovLimitHigh;
          }
        }
        else if (avt < avd )
        {
          servov = --servov;
          if (servov < servovLimitLow)
          {
            servov = servovLimitLow;
          }
        }


        delay(50);
        vertical.write(servov);
      }
      if (-1 * tol > dhoriz || dhoriz > tol || -1 * tol > dvert || dvert > tol) // check if the diffirence is in the

      {
        if (avl > avr || lt > rt)
        {

          servoh = --servoh;
          if (servoh < servohLimitLow)
          {
            servoh = servohLimitLow;
          }
        }
        else if (avl < avr || lt < rt)
        {

          servoh = ++servoh;
          if (servoh > servohLimitHigh)
          {
            servoh = servohLimitHigh;
          }


        }
        horizontal.write(servoh - 1);
        delay(dtime);
      }


      if (0 < lt - rt && lt - rt < 10 && 0 < avt - avd && avt - avd < 10) {
        Serial.print("yakaladık");
        counter++;
        Serial.println(" ");
        if (servov > 100) {
          for (int i = 0; i < servov * 19 / 30 + 1; i++) {
            servov = servov - 1;
            vertical.write(servov);
            delay(50);
          }
        }
        else {
          for (int i = 0; i < servov * 14 / 30 + 1; i++) {
            servov = servov - 1;
            vertical.write(servov);
            delay(50);
          }
        }
        myFile = SD.open("test.txt", FILE_WRITE);
        if (myFile) {
          myFile.print("temperature(C):");
          sensors.requestTemperatures();
          Celcius = sensors.getTempCByIndex(0);
          myFile.println(Celcius);
          myFile.close();
          Serial.println("yazıldı");
          Serial.println(Celcius);

        }


        delay(300000);
      }
    }
    if (lt < 100 && rt < 100 && ld < 100 && rd < 100) {
      temp = servoh;
      temp2 = servov;
      counter = 0;
      if (servoh < 90) {
        for (int i = temp; i <= 90; i++) {
          servoh = servoh + 1;
          horizontal.write(servoh);
          Serial.println(servoh);
          delay(dtime);
        }
      }
      else {
        for (int i = temp; i > 90; i--) {
          servoh = servoh - 1;
          horizontal.write(servoh);
          delay(dtime);
        }
      }
      for (int i = temp2; i <= 180; i++) {
        servov = servov + 1;
        vertical.write(servov);
        delay(dtime);
      }
    }
  }
}

void calibrate(Servo servo, int analogPin, int minPos, int maxPos)
{
  // Move to the minimum position and record the feedback value
  servo.write(minPos);
  minDegrees = minPos;
  delay(2000); // make sure it has time to get there and settle
  minFeedback = analogRead(analogPin);

  // Move to the maximum position and record the feedback value
  servo.write(maxPos);
  maxDegrees = maxPos;
  delay(2000); // make sure it has time to get there and settle
  maxFeedback = analogRead(analogPin);
}

void ldrRead() {
  lt = analogRead(ldrlt); // top left
  rt = analogRead(ldrrt); // top right
  ld = analogRead(ldrld); // down left
  rd = analogRead(ldrrd); // down right
  // dtime=diffirence time, tol=toleransi
  avt = (lt + rt) / 2; // average value top
  avd = (ld + rd) / 2; // average value down
  avl = (lt + ld) / 2; // average value left
  avr = (rt + rd) / 2; // average value right
  dvert = avt - avd; // check the diffirence of up and down
  dhoriz = avl - avr;// check the diffirence og left and rigt
  Serial.print(counter);
  Serial.print(" ");
  Serial.print(lt);
  Serial.print(" ");
  Serial.print(rt);
  Serial.print(" ");
  Serial.print(ld);
  Serial.print(" ");
  Serial.print(rd);
  Serial.println(" ");
}
