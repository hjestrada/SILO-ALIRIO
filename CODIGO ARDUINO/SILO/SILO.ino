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

//Bloque funcional Encoder y Menú

#define outputA 7
#define outputB 6
#define sw 5

int counter = -1; 
int aState;
int aLastState;  

#define led1 8
#define led2 9
#define led3 10





//::::::::::MENU::::::::::::::::::::::

String menu1[] = {"Tiempos","SetPoint","Abrir Puerta 1","Abrir Puerta 2","Dashboard"};
int sizemenu1 = sizeof(menu1) / sizeof(menu1[0]);

String menu2[] = {"Puerta 1","Puerta 2","Atras"};
int sizemenu2 = sizeof(menu2) / sizeof(menu2[0]);



String menu3[] = {"Izq -> Der","Der -> Izq","Atras"};
int sizemenu3 = sizeof(menu3) / sizeof(menu3[0]);

String linea1,linea2;
int seleccion = 0;
int pos = 0;
int level_menu = 0;
int opcion = 0;
bool btnpress = false;
byte brilloled3 = 0;
byte flecha[] = {B00000,B00100,B00110,B11111,B00110,B00100,B00000,B00000};





//----pines puente h

#define RPWM 38
#define LPWM 36
#define REN 34
#define LEN 32



//--------------------------------------------



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
  
  //--- encoder Menú----
  
  pinMode (outputA,INPUT);
  pinMode (outputB,INPUT);
  pinMode (sw,INPUT);
  digitalWrite(sw, HIGH);
  pinMode(led1,OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, flecha);
  fn_credits();
  fn_menu(counter,menu1,sizemenu1);
 

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

  
  //melodia();

}
void loop() {

  myRTC.updateTime();
    //Pantalla1();

//---bloque funcional menú

selectOption();


 //menu 1
  if(level_menu == 0){
 
    if(fn_encoder(sizemenu1) ){
      fn_menu(counter,menu1,sizemenu1);
    }


    
    if(btnpress){
      //led1
      if(counter == 0){
          counter = 0;
          fn_menu(counter,menu2,sizemenu2);
          level_menu = 1;  
      }

      //led2
      if(counter == 1){
          counter = 0;
          fn_menu(counter,menu2,sizemenu2);
          level_menu = 2;  
      }

      //led3
      if(counter == 2){
          counter = 0;
          fn_menu(counter,menu2,sizemenu2);
          level_menu = 3;  
      }


      //todos
      if(counter == 3){
          counter = 0;
          fn_menu(counter,menu2,sizemenu2);
          level_menu = 4;  
      }


      //secuencias
      if(counter == 4){
          counter = 0;
          fn_menu(counter,menu3,sizemenu3);
          level_menu = 5;  
      }

      //Intensidad
      if(counter == 5){
          counter = brilloled3; 
          level_menu = 6; 
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Brillo Led3"); 
          lcd.setCursor(0, 1);
          lcd.print(brilloled3);
           
      }
     
      btnpress = false;
    }

  }







  if(level_menu == 4){

    Serial.println("level1");
    if(fn_encoder(sizemenu2)){
      fn_menu(counter,menu2,sizemenu2);
    }
    
    if(btnpress){

      if(counter == 0){
        digitalWrite(led1,HIGH);
      }

      if(counter == 1){
        digitalWrite(led1,LOW);
      }
      
      if(counter == 2){
          counter = 0;
          fn_menu(counter,menu1,sizemenu1);
          level_menu = 0;   
      }
      
      btnpress = false;
    }
  }



  if(level_menu == 8){

    if(fn_encoder(sizemenu2)){
      fn_menu(counter,menu2,sizemenu2);
    }
    
    if(btnpress){

      if(counter == 0){
        digitalWrite(led2,HIGH);
      }

      if(counter == 1){
        digitalWrite(led2,LOW);
      }
      
      if(counter == 2){
          counter = 1;
          fn_menu(counter,menu1,sizemenu1);
          level_menu = 0;   
      }
      
      btnpress = false;
    }
  }




  if(level_menu == 12){

    if(fn_encoder(sizemenu2)){
      fn_menu(counter,menu2,sizemenu2);
    }
    
    if(btnpress){

      if(counter == 0){
        digitalWrite(led3,HIGH);
        brilloled3 = 10;
      }

      if(counter == 1){
        digitalWrite(led3,LOW);
        brilloled3 = 0;
      }
      
      if(counter == 2){
          counter = 2;
          fn_menu(counter,menu1,sizemenu1);
          level_menu = 0;   
      }
      
      btnpress = false;
    }
  }





  if(level_menu == 16){

    if(fn_encoder(sizemenu2)){
      fn_menu(counter,menu2,sizemenu2);
    }
    
    if(btnpress){

      if(counter == 0){
        digitalWrite(led1,HIGH);
        digitalWrite(led2,HIGH);
        digitalWrite(led3,HIGH);
        brilloled3 = 10;
      }

      if(counter == 1){
        digitalWrite(led1,LOW);
        digitalWrite(led2,LOW);
        digitalWrite(led3,LOW);
        brilloled3 = 0;
      }
      
      if(counter == 2){
          counter = 3;
          fn_menu(counter,menu1,sizemenu1);
          level_menu = 0;   
      }
      
      btnpress = false;
    }
  }





  if(level_menu == 20){

    if(fn_encoder(sizemenu3)){
      fn_menu(counter,menu3,sizemenu3);
    }
    
    if(btnpress){

      if(counter == 0){
        digitalWrite(led1,HIGH);
        delay(500);
        digitalWrite(led1,LOW);
        digitalWrite(led2,HIGH);
        delay(500);
        digitalWrite(led2,LOW);
        digitalWrite(led3,HIGH);
        delay(500);
        digitalWrite(led3,LOW);
        brilloled3 = 0;
      }

      if(counter == 1){
        digitalWrite(led3,HIGH);
        delay(500);
        digitalWrite(led3,LOW);
        digitalWrite(led2,HIGH);
        delay(500);
        digitalWrite(led2,LOW);
        digitalWrite(led1,HIGH);
        delay(500);
        digitalWrite(led1,LOW);
        brilloled3 = 0;
      }
      

      if(counter == 2){
          counter = 4;
          fn_menu(counter,menu1,sizemenu1);
          level_menu = 0; 
      }
      
      
      btnpress = false;
    }
  }




  if (level_menu == 24){
  
   
    if(fn_encoder(11)){
      brilloled3 = counter;
       fn_intensidad();
    }

    if(btnpress){
      counter = 5;
      level_menu = 0;

      fn_menu(counter,menu1,sizemenu1);
      btnpress = false;
    }
  
  
    
  }

}

void MotorUnoIzquierda() {

  lcd.init();
  digitalWrite(pinB, LOW);
  lcd.setCursor(0, 0);
  lcd.print("Giro Izquierda");
  lcd.setCursor(3, 1);
  lcd.print("Activado");
  analogWrite(LPWM, 255);
  analogWrite(RPWM, 0);
  digitalWrite(pinA, HIGH);
  delay(10000);
  ApagarLed();
}

void MotorUnoDerecha() {
  lcd.init();

  lcd.setCursor(0, 0);
  lcd.print("Giro Derecha");
  lcd.setCursor(3, 1);
  lcd.print("Activado");
  digitalWrite(pinB, HIGH);
  analogWrite(RPWM, 255);
  analogWrite(LPWM, 0);
  delay(10000);
  ApagarLed();


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

void ApagarLed() {
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, LOW);
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





//--- funciones encoder menu

void fn_menu(int pos,String menus[],byte sizemenu){
  lcd.clear();
  linea1="";
  linea2="";
   
  if((pos % 2) == 0){

     lcd.setCursor(0, 0);
     lcd.write(byte(0));
     linea1 = menus[pos];
    
    if(pos+1 != sizemenu){
      linea2 = menus[pos+1];
    }
    
  }else{
    linea1 = menus[pos-1];
    lcd.setCursor(0, 1);
    lcd.write(byte(0));
    linea2 = menus[pos];
  }
  
     lcd.setCursor(1, 0);
     lcd.print(linea1);

     lcd.setCursor(1, 1);
     lcd.print(linea2); 
   
}


bool fn_encoder(byte sizemenu){ 
  bool retorno = false;
  aState = digitalRead(outputA); 
  if (aState != aLastState){     
    if (digitalRead(outputB) != aState) { 
      counter --;
    } else {
      counter ++;
    }

    if(counter <=0){
      counter = 0;
    }
    
    if(counter >= sizemenu-1 ){
      counter = sizemenu-1;
    }
    
    retorno = true;

  } 
  aLastState = aState;
  return retorno; 
}




void selectOption(){
  if(digitalRead(sw) == LOW){
    delay(500);
    btnpress = true;
  }
}




void fn_intensidad(){
  analogWrite(led3,map(brilloled3,0,10,0,255));
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print(brilloled3);
}


void fn_credits(){

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

}
