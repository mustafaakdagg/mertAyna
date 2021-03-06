#include <Servo.h>
#include <SD.h>
#include <SPI.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 6
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
int x = 0;
float Celcius = 0;
int minDegrees;
int maxDegrees;
int minFeedback;
int maxFeedback;
int tolerance = 10;
int l = 15, k = 0;
int tempPot;
int tempPott;

File myFile;
int pinCS = 10;

Servo horizontal;
Servo vertical;
int pot;
int servoh = 90;
int servohLimitHigh = 180;
int servohLimitLow = 0;

int counter = 0;
int temp;
int temp2;
int servov = 90;
int servovLimitHigh = 180;
int servovLimitLow = 40;

int ldrlt = A3;
int ldrrt = A1;
int ldrld = A2;
int ldrrd = A0;
int feedbackPin = A5;
int dtime = 30; int tol = 10  ;
int lt; int rt; int ld; int rd;
int avt; int avd; int avl; int avr; int dvert; int dhoriz;
int timer = 0;
int potPin = A4;
int potDeger; int ver;


void setup() {
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  horizontal.attach(5);
  vertical.attach(3);

  Serial.begin(9600);
  sensors.begin();
  pinMode(pinCS, OUTPUT);
  pinMode(A4, INPUT);
  pinMode(ldrlt, INPUT);
  pinMode(ldrrt, INPUT);
  pinMode(ldrld, INPUT);
  pinMode(ldrrd, INPUT);

  for (int i = 0; i < 90; i++) {
    horizontal.write(servoh - i);
  }
  //  calibrate(horizontal, feedbackPin , 0, 270);
//851 627 719 681 
//880 668 748 732
//959 803 867 882 

//1010
//980
//988
//1010
  for (int i = 0; i < 90; i++) {
    horizontal.write(servoh - i);
  }
  delay(1000);
  horizontal.write(90);
  vertical.write(servov);
  delay(10000);
  counter = 0;

}
void loop() {

  if (counter >= 6) {                                     //eger 30 dk olduysa
    counter = 0;
    guneyeDon();
    for (int i = 0 ; i < 120; i++) {
      delay(1000);
    }
    counter = 0;
  }
  if (lt < 125 && rt < 125 && ld < 125 && rd < 125) {      //eğer karanlığa girdiyse
    karanlikKontrolu();
    while (lt < 125 && rt < 125 && ld < 125 && rd < 125) {
      ldrRead();
    }
  }
  else {                                                  //normal çalışma

    ldrRead();
    gunesBul();
    if (lt-rd<tol && lt-rd > -tol && rt-ld<tol && rt-ld>-tol) {
      yansit();
      timer = 0;
      tempPot = servov;
      for (int i = 0 ; i < 3000; i++) {
        ldrRead();
        potOku();
        delay(100);
///////////////////////////////////////////////////
        if(pot != l){
          if(pot-l>0){
           for(int i = 0;i<(pot-l);i++){
            tempPot = tempPot+1;
            vertical.write(tempPot);
            delay(50);
           }
          }
          else if(pot-l<0){
            for(int i = 0;i<l-pot;i++){
            tempPot = tempPot -1;
            vertical.write(tempPot);
            delay(50);
           }
          } 
        }
/////////////////////////
        
        l = pot;
      }
           if(tempPot>servov){
           for(int i = 0;i<tempPot-servov;i++){
            tempPot = tempPot-1;
            vertical.write(tempPot);
            delay(50);
           }
          }
          else if(tempPot<servov){
            for(int i = 0;i<servov-tempPot;i++){
            tempPot = tempPot +1;
            vertical.write(tempPot);
            delay(50);
           }
          } 
      
  
      counter++;
      timer++;
      l=0;


    }
  }
}
void calibrate(Servo servo, int analogPin, int minPos, int maxPos) {

  for (int i = 270; i > minPos; i--) {
    if (servoh > 0) {
      servoh--;
      servo.write(servoh);
      delay(15);
    }
    else {
      servo.write(minPos);
      minDegrees = minPos;
    }
  }
  delay(1000);
  minFeedback = analogRead(analogPin);

  for (int i = 0; i < maxPos; i++) {
    if (servoh < 270) {
      servoh++;
      servo.write(servoh);
      delay(15);
    }
    else {
      servo.write(maxPos);
      maxDegrees = maxPos;
    }
  }
  delay(1000);
  maxFeedback = analogRead(analogPin);

}

void ldrRead() {

  lt = analogRead(ldrlt); // top left
  rt = analogRead(ldrrt); // top right
  ld = analogRead(ldrld); // down left
  rd = analogRead(ldrrd); // down right
  rt=rt+80;
 rd=rd+80;
  Serial.print(" ");
  Serial.print(lt );
  Serial.print(" ");
  Serial.print(rt );
  Serial.print(" ");
  Serial.print(ld );
  Serial.print(" ");
  Serial.print(rd);
  Serial.println(" ");

  avt = (lt + rt) / 2; // average value top
  avd = (ld + rd) / 2; // average value down
  avl = (lt + ld) / 2; // average value left
  avr = (rt + rd) / 2; // average value right

  dvert = avt - avd; // check the diffirence of up and down
  dhoriz = avl - avr;// check the diffirence og left and rigt
}

void guneyeDon() {
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
    if (servov < 180) {
      servov = servov + 1;
    }
    else {
      servov = 180;
    }
    delay(dtime);
    vertical.write(servov);
  }
}

void devamEt() {
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
  for (int i = 180; i >= temp2 - pot; i--) {
    servov = servov - 1;
    vertical.write(servov);
    delay(dtime);
  }
}

void karanlikKontrolu() {

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
      Serial.println(servoh);
      delay(dtime);
    }
  }
  for (int i = temp2; i <= 180; i++) {
    if (servov < servovLimitHigh) {
      servov = servov + 1;
      vertical.write(servov);
      delay(dtime);
    }
  }

}

void gunesBul() {
  ldrRead();
  if (lt > 125 || rt > 125 || ld > 125 || rd > 125) {
    if ( tol > lt-rd || tol>rt-ld || tol > rd-lt|| tol>ld -rt) {// check if the diffirence is in the

      if (lt>rd && rt > ld )
      {
        servov = ++servov;
        if (servov >= servovLimitHigh)
        {
          servov = servovLimitHigh;
        }
      }
      else if (lt < rd && rt < ld)
      {
        servov = servov - 1;
        if (servov < servovLimitLow)
        {
          servov = servovLimitLow;
        }
      }
      delay(50);
      vertical.write(servov);

    }
    if ( tol > lt-rd || tol>rt-ld || tol > rd-lt|| tol>ld -rt)// check if the diffirence is in the

    {
      if (lt>rd && ld>rt)
      {

        servoh = --servoh;
        if (servoh < servohLimitLow)
        {
          servoh = servohLimitLow;
        }
      }
      else if (lt<rd && ld<rt)
      {
        servoh = ++servoh;
        if (servoh > servohLimitHigh)
        {
          servoh = servohLimitHigh;
        }
      }

    }
    horizontal.write(servoh);
    delay(dtime);
  }


}

void yansit() {

  Serial.print("yakaladık");
  Serial.println(" ");
  if (servov > 100) {
    for (int i = 0; i < servov * 16 / 30 + 1; i++) {
      servov = servov - 1;
      vertical.write(servov);
      delay(50);
    }
  }
  else {
    for (int i = 0; i < servov * 9 / 30 + 1; i++) {
      servov = servov - 1;
      vertical.write(servov);
      delay(50);
    }
  }
}

void potOku() {
  potDeger  = analogRead(potPin);
  pot = map(potDeger, 58, 1020, 0, 30);
  Serial.println(pot);
}
