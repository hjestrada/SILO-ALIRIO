/* Dev:  @hjestrada
  Tecnoparque nodo Pitalito
*/



#include <SHT1x.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <virtuabotixRTC.h> //Libreria

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

// Pines sensores  SHT10

#define dataPin  17
#define clockPin 16
#define dataPin2  15
#define clockPin2 14

#define RPWM 38
#define LPWM 36
#define REN 34
#define LEN 32

int duration = 12;
virtuabotixRTC myRTC(2, 3, 4); // Si cambiamos los PIN de conexión, debemos cambiar aquí tambien

SHT1x sht1x(dataPin, clockPin);
SHT1x sht1x2(dataPin2, clockPin2);



/* declaración de variables */
int spk = 13;                                         // altavoz a GND y pin 13
int c[5] = {131, 262, 523, 1046, 2093}; // frecuencias 4 octavas de Do
int cs[5] = {139, 277, 554, 1108, 2217}; // Do#
int d[5] = {147, 294, 587, 1175, 2349}; // Re
int ds[5] = {156, 311, 622, 1244, 2489}; // Re#
int e[5] = {165, 330, 659, 1319, 2637}; // Mi
int f[5] = {175, 349, 698, 1397, 2794}; // Fa
int fs[5] = {185, 370, 740, 1480, 2960}; // Fa#
int g[5] = {196, 392, 784, 1568, 3136}; // Sol
int gs[5] = {208, 415, 831, 1661, 3322}; // Sol#
int a[5] = {220, 440, 880, 1760, 3520}; // La
int as[5] = {233, 466, 932, 1866, 3729}; // La#
int b[5] = {247, 494, 988, 1976, 3951}; // Si

void nota(int a, int b);            // declaración de la función auxiliar. Recibe dos números enteros.

const int pinA = 11;
const int pinB = 8;
const int pinC = 10;
const int pinD = 9;


void setup() {
  //myRTC.setDS1302Time(00, 11, 11, 1, 28, 3, 2022); // SS, MM, HH, DW, DD, MM, YYYY


  //-pines Led
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);

  //-Pines motores
  pinMode(RPWM, OUTPUT);
  pinMode(LPWM, OUTPUT);
  pinMode(LEN, OUTPUT);
  pinMode(REN, OUTPUT);
  digitalWrite(REN, HIGH);
  digitalWrite(LEN, HIGH);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(2, 0);
  lcd.print("Tecnoparque");
  lcd.setCursor(2, 1);
  lcd.print("Nodo Pitalito");
  lcd.init();
  lcd.backlight();
  lcd.setCursor(4, 0);
  lcd.print("Taller");
  lcd.setCursor(3, 1);
  lcd.print("Industrial");
  lcd.init();
  lcd.setCursor(3, 0);
  lcd.print("El Cafetero");
  lcd.init();
  //melodia();

}
void loop() {

  myRTC.updateTime();

  ledPrueba();
  Pantalla1();
  
  //delay(1000);
  //  Pantalla2();
  //  delay(1000);
  //  Pantalla3();
  //  delay(1000);
  //  Pantalla4();
  //  delay(1000);
  //  fechahora();

}


void ledPrueba() {
  digitalWrite(pinA, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for a second
  digitalWrite(pinA, LOW);    // turn the LED off by making the voltage LOW
  delay(500);
  digitalWrite(pinB, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for a second
  digitalWrite(pinB, LOW);    // turn the LED off by making the voltage LOW
  delay(500);
  digitalWrite(pinC, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for a second
  digitalWrite(pinC, LOW);    // turn the LED off by making the voltage LOW
  delay(500);
  digitalWrite(pinD, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for a second
  digitalWrite(pinD, LOW);    // turn the LED off by making the voltage LOW
  delay(500);

}


void nota(int frec, int t)
{
  tone(spk, frec);     // suena la nota frec recibida
  delay(t);                // para despues de un tiempo t
}


int melodia() {
  nota(g[2], 500); noTone(spk); delay(100);
  nota(g[2], 500); noTone(spk); delay(100);
  nota(g[2], 500); noTone(spk); delay(100);
  nota(ds[2], 500); noTone(spk); delay(1);
  nota(as[2], 125); noTone(spk); delay(25);
  nota(g[2], 500); noTone(spk); delay(100);
  nota(ds[2], 500); noTone(spk); delay(1);
  nota(as[2], 125); noTone(spk); delay(25);
  nota(g[2], 500);
  noTone(spk); delay(2000);
}

void mensajeAlerta() {

  lcd.setCursor(2, 0);
  lcd.print("Hector Jaime Estrada");
  lcd.scrollDisplayLeft();
  delay(1000);
}
void fechahora() {

  lcd.init();
  lcd.backlight();
  lcd.setCursor(4, 0);
  lcd.print(myRTC.dayofmonth); // Se puede cambiar entre día y mes si se utiliza el sistema Americano
  lcd.print("/");
  lcd.print(myRTC.month);
  lcd.print("/");
  lcd.print(myRTC.year);
  lcd.print(" ");
  lcd.setCursor(6, 1);
  lcd.print(myRTC.hours);
  lcd.print(":");
  lcd.print(myRTC.minutes);
  //lcd.print(":");
  //lcd.println(myRTC.seconds);


}


void Pantalla1() {

  int temp_c;
  int humidity;
  int temp_c2;
  int humidity2;

  temp_c = sht1x.readTemperatureC();
  humidity = sht1x.readHumidity();
  temp_c2 = sht1x2.readTemperatureC();
  humidity2 = sht1x2.readHumidity();

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("TP1:");
  lcd.setCursor(4, 0);
  lcd.print(temp_c);
  lcd.setCursor(7, 0);
  lcd.print("TP2:");
  lcd.setCursor(11, 0);
  lcd.print(temp_c2);
  lcd.setCursor(14, 0);
  lcd.print("*C");

  lcd.setCursor(0, 1);
  lcd.print("HP1:");
  lcd.setCursor(4, 1);
  lcd.print(humidity);
  lcd.setCursor(7, 1);
  lcd.print("HP2:");
  lcd.setCursor(11, 1);
  lcd.print(humidity2);
  lcd.setCursor(14, 1);
  lcd.print("HR");


}

void Pantalla2() {
  lcd.init();
  lcd.setCursor(0, 0);
  lcd.print("AJUSTES PUERTAS");
  lcd.setCursor(0, 1);
  lcd.print("1(");
  lcd.setCursor(3, 1);
  lcd.print(")");
  lcd.setCursor(5, 1);
  lcd.print("2(");
  lcd.setCursor(8, 1);
  lcd.print(")");
  lcd.setCursor(11, 1);
  lcd.print("S(");
  lcd.setCursor(14, 1);
  lcd.print(")");
}

void Pantalla3() {
  lcd.init();
  lcd.setCursor(5, 0);
  lcd.print("PISO 1");
  lcd.setCursor(1, 1);
  lcd.print("Temp:(");
  lcd.setCursor(9, 1);
  lcd.print(") *C");
}
void Pantalla4() {
  lcd.init();
  lcd.setCursor(5, 0);
  lcd.print("PISO 2");
  lcd.setCursor(1, 1);
  lcd.print("Temp:(");
  lcd.setCursor(9, 1);
  lcd.print(") *C");
}

void pruebaMotores() {

  analogWrite(RPWM, 255);
  analogWrite(LPWM, 0);
  delay(10000);

  analogWrite(LPWM, 255);
  analogWrite(RPWM, 0);
  delay(10000);
}

void paroMotores() {

  analogWrite(RPWM, 0);
  analogWrite(LPWM, 0);
  delay(10000);

  analogWrite(LPWM, 0);
  analogWrite(RPWM, 0);
  delay(10000);
}
