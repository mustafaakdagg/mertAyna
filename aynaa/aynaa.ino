#include <Servo.h> // include Servo library
// 180 horizontal MAX
Servo horizontal; // horizontal servo
int servoh=90; // 90; // stand horizontal servo
int servohLimitHigh = 180;
int servohLimitLow = 0;
Servo vertical; // vertical servo
int servov =90; 
int servovLimitHigh = 130;
int servovLimitLow = 10;
int ldrlt = 0; //LDR top left - BOTTOM LEFT <--- BDG
int ldrrt = 2; //LDR top rigt - BOTTOM RIGHT
int ldrld = 1; //LDR down left - TOP LEFT
int ldrrd = 3; //ldr down rigt - TOP RIGHT
void setup(){
Serial.begin(9600);
horizontal.attach(9);
vertical.attach(10);
delay(1000);


}
void loop() {
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
 if (avt > avd)
 {
 servov = ++servov;
 if (servov > servovLimitHigh)
 {
 servov = servovLimitHigh;
 }
 }
 else if (avt < avd)
 {
 servov= --servov;
 if (servov < servovLimitLow)
 {
 servov = servovLimitLow;
 }
 }

 
 delay(50);
 vertical.write(servov);
 }
if (-1*tol > dhoriz || dhoriz > tol) // check if the diffirence is in the

 {
 if (avl > avr)
 {
 servoh = --servoh;
 if (servoh < servohLimitLow)
 {
 servoh = servohLimitLow;
 }
 }
 else if (avl < avr)
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


 if (0< lt-rd && lt-rd< 15){
  Serial.print("yakaladık");
Serial.println(" ");
 for(int i =1;i<21;i++){
  servov = servov-1;
 vertical.write(servov);
 delay(50);
 }
 delay(300000);
 }

}
