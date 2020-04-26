int potPin = A4;
int potDeger;
int ldrlt = A1;
int ldrrt = A3;
int ldrld = A0;
int ldrrd = A2;
void setup() {
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
potDeger  = analogRead(potPin);
int pot = map(potDeger,58,1020,0,20);
Serial.print(potDeger);
int   lt = analogRead(ldrlt); // top left
 int  rt = analogRead(ldrrt); // top right
  int ld = analogRead(ldrld); // down left
  int rd = analogRead(ldrrd); // down right

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
