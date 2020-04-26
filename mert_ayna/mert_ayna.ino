#include <Servo.h> 
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Servo horizontal; 
int servoh=90; 
int servohLimitHigh = 180;
int servohLimitLow = 0;
Servo vertical; 
int servov =90; 
int servovLimitHigh = 175;
int servovLimitLow = 5;
int ldrlt = A1; 
int ldrrt = A3; 
int ldrld = A0;
int ldrrd = A2; 


void setup(){
Serial.begin(9600);
lcd.begin(16, 2);

lcd.print("Solar");
horizontal.attach(9);
vertical.attach(10);
delay(5000);


}
void loop() {
lcd.setCursor(0, 1);
lcd.print("Tracking");
lcd.setCursor(9, 0);
lcd.print("hor:");
lcd.print(servoh);

lcd.setCursor(9, 1);
lcd.print("ver:");
lcd.print(servov);

int lt = analogRead(ldrlt); // top left
int rt = analogRead(ldrrt); // top right
int ld = analogRead(ldrld); // down left
int rd = analogRead(ldrrd); // down right
int dtime = 50; int tol = 10 ; // dtime=diffirence time, tol=toleransi
int avt = (lt + rt) / 2; // average value top
int avd = (ld + rd) / 2; // average value down
int avl = (lt + ld) / 2; // average value left
int avr = (rt + rd) / 2; // average value right
int dvert = avt - avd; // check the diffirence of up and down
int dhoriz = avl - avr;// check the diffirence og left and rigt
Serial.print(lt);
Serial.print(" ");
Serial.print(rt);
Serial.print(" ");
Serial.print(ld);
Serial.print(" ");
Serial.print(rd);
Serial.print(" ");
Serial.print(servov);
Serial.println(" ");


if (-1*tol > dvert || dvert > tol) // check if the diffirence is in the

 {
 if (avt+5 > avd)
 {
 servov = --servov;
 if (servov > servovLimitHigh)
 {
 servov = servovLimitHigh;
 }
 }
 else if (avt+5 < avd)
 {
 servov= ++servov;
 if (servov < servovLimitLow)
 {
 servov = servovLimitLow;
 }
 }

 vertical.write(servov);
 }
if (-1*tol > dhoriz || dhoriz > tol) 

 {
 if (avl>avr+200)
 {
 servoh = --servoh;
 if (servoh < servohLimitLow)
 {
 servoh = servohLimitLow;
 }
 }
 else if (avl<avr )
 {
 servoh = ++servoh;
 if (servoh > servohLimitHigh)
 {
 servoh = servohLimitHigh;
 }
  
 
 }
 horizontal.write(servoh);
  delay(dtime);
 }


}
