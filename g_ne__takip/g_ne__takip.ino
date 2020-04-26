#include <Servo.h> // include Servo library
// 180 horizontal MAX
Servo horizontal; // horizontal servo
int servoh = 180; // 90; // stand horizontal servo
int servohLimitHigh = 175;
int servohLimitLow = 5;
// 65 degrees MAX
Servo vertical; // vertical servo
int servov = 45; // 90; // stand vertical servo
int servovLimitHigh = 60;
int servovLimitLow = 1;
// LDR pin connections
// name = analogpin;
int ldrlt = 0; //LDR top left - BOTTOM LEFT <--- BDG
int ldrrt = 1; //LDR top rigt - BOTTOM RIGHT
int ldrld = 2; //LDR down left - TOP LEFT
int ldrrd = 3; //ldr down rigt - TOP RIGHT
void setup(){
Serial.begin(9600);
horizontal.attach(9);
vertical.attach(10);
horizontal.write(180);
vertical.write(45);
delay(3000);
}
void loop() {
int lt = analogRead(ldrlt); // top left
int rt = analogRead(ldrrt); // top right
int ld = analogRead(ldrld); // down left
int rd = analogRead(ldrrd); // down right
int dtime = 10; int tol = 90; // dtime=diffirence time, tol=toleransi
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
 else if (avl = avr)
 {
 delay(5000);
 }
 horizontal.write(servoh);
 }

}
