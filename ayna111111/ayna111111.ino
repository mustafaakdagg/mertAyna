#include <Servo.h>
#include <SD.h>
#include <SPI.h>
#include <OneWire.h>
#include <DallasTemperature.h>

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



int servoh = 90; // stand horizontal servo
int servohLimitHigh = 180;
int servohLimitLow = 0;

int counter = 0;
int temp;
int temp2;
int servov = 90;
int servovLimitHigh = 170;
int servovLimitLow = 40;
int ldrlt = 3; //LDR top left - BOTTOM LEFT <--- BDG
int ldrrt = 0; //LDR top rigt - BOTTOM RIGHT
int ldrld = 1; //LDR down left - TOP LEFT
int ldrrd = 2; //ldr down rigt - TOP RIGHT
int dtime = 20; int tol = 5 ;


void setup() {


  Serial.begin(9600);
  sensors.begin();
  pinMode(pinCS, OUTPUT);

  if (SD.begin()) {
    Serial.println("SD card is ready to use.");
  }
  else {
    Serial.println("SD card initialization failed");

  }
  
  cli();
  /* Ayarlamaların yapılabilmesi için öncelikle kesmeler durduruldu */

  /* Timer1 kesmesi saniyede bir çalışacak şekilde ayarlanacaktır (1 Hz)*/
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A = 15624;
  /* Bir saniye aralıklar için zaman sayıcısı ayarlandı */
  TCCR1B |= (1 << WGM12);
  /* Adımlar arasında geçen süre kristal hızının 1024'e bölümü olarak ayarlandı */
  TCCR1B |= (1 << CS12) | (1 << CS10);
  TIMSK1 |= (1 << OCIE1A);
  /* Timer1 kesmesi aktif hale getirildi */

  sei();


}


void loop() {
 Serial.println(counter);
 delay(50);

}

ISR(TIMER1_COMPA_vect) {

 counter++;

}
