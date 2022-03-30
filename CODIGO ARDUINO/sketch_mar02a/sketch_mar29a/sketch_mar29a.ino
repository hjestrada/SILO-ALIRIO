   /*
  BTS7960-43A-Driver
  made on 22 Nov 2020
  by Amir Mohammad Shojaee @ Electropeak
  Home

*/

#define RPWM 38
#define LPWM 36
#define REN 34
#define LEN 32



int out1;
int out2;

void setup() {
  Serial.begin(9600);
  pinMode(RPWM,OUTPUT);
  pinMode(LPWM,OUTPUT);
  pinMode(LEN,OUTPUT);
  pinMode(REN,OUTPUT);
  digitalWrite(REN,HIGH);
  digitalWrite(LEN,HIGH);

}
 
 
void loop() {
  

    analogWrite(RPWM,255);
    analogWrite(LPWM,0);
    delay(10000);

    analogWrite(LPWM,255);
    analogWrite(RPWM,0);
     delay(10000);
  }
