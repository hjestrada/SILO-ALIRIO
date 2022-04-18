/*
  |---------------------------|
  | Dev:  @hjestrada 5          |
  | Tecnoparque nodo Pitalito! |
  |---------------------------|
*/



#include <SHT1x.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <virtuabotixRTC.h>  //Libreria
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pines sensores  SHT10

#define dataPin 17
#define clockPin 16
#define dataPin2 15
#define clockPin2 14

SHT1x sht1x(dataPin, clockPin);
SHT1x sht1x2(dataPin2, clockPin2);



//----pines puente h

#define RPWM 38
#define LPWM 36
#define REN 34
#define LEN 32


#define RPWM2 41
#define LPWM2 43
#define REN2 45
#define LEN2 47


//:::::::::::ENCODER::::::::::::::::::::::::::

//- pines encoder menu

#define outputA 7
#define outputB 6
#define sw 5

#define led1 8
#define led2 9
#define led3 10

const int pinA = 11;
const int pinB = 8;
const int pinC = 10;
const int pinD = 9;

int counter = -1;
int aState;
int aLastState;
String Scount;

//::::::::::MENU::::::::::::::::::::::
String menu1[] = { "Puerta 1", "Puerta 2", "DashBoard", "Tiempo Ap 1", "Tiempo Ap 2", "Setpoint Temp", "Setpoint Hum" };
int sizemenu1 = sizeof(menu1) / sizeof(menu1[0]);

String menu2[] = { "Apertura", "Cierre", "Atras" };
int sizemenu2 = sizeof(menu2) / sizeof(menu2[0]);

String menu3[] = { "", "Der -> Izq", "Atras" };
int sizemenu3 = sizeof(menu3) / sizeof(menu3[0]);

String linea1, linea2;
int seleccion = 0;
int pos = 0;
int level_menu = 0;
int opcion = 0;
bool btnpress = false;
byte brilloled3 = 0;
byte flecha[] = { B00000, B00100, B00110, B11111, B00110, B00100, B00000, B00000 };

void setup() {
  Serial.begin(9600);
  pinMode(outputA, INPUT);
  pinMode(outputB, INPUT);
  pinMode(sw, INPUT);
  digitalWrite(sw, HIGH);
  pinMode(led1, OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, flecha);
  fn_credits();
  fn_menu(counter, menu1, sizemenu1);

  //-Pines motores
  pinMode(RPWM, OUTPUT);
  pinMode(LPWM, OUTPUT);
  pinMode(LEN, OUTPUT);
  pinMode(REN, OUTPUT);
  pinMode(RPWM2, OUTPUT);
  pinMode(LPWM2, OUTPUT);
  pinMode(LEN2, OUTPUT);
  pinMode(REN2, OUTPUT);

  digitalWrite(REN, HIGH);
  digitalWrite(LEN, HIGH);

  digitalWrite(REN2, HIGH);
  digitalWrite(LEN2, HIGH);

  //-pines Led
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
}

void loop() {

  selectOption();

  //menu 1
  if (level_menu == 0) {

    if (fn_encoder(sizemenu1)) {
      fn_menu(counter, menu1, sizemenu1);
    }

    if (btnpress) {
      //Puerta 1
      if (counter == 0) {
        counter = 0;
        fn_menu(counter, menu2, sizemenu2);
        level_menu = 1;
      }

      //Puerta 2
      if (counter == 1) {
        counter = 0;
        fn_menu(counter, menu2, sizemenu2);
        level_menu = 2;
      }

      //Dashboard
      if (counter == 2) {
        counter = 0;
        //fn_menu(counter, menu2, sizemenu2);

        while (1) {
          DashBoard();

          if (digitalRead(sw) == LOW) {
            fn_menu(counter, menu1, sizemenu1);
            break;
          }
        }
      }

      //Tiempo Ap 1

      if (counter == 3) {
        counter = 0;
        //counter = brilloled3;
        //-------------
        int Posicion = 0;
        int PinCLKanterior = LOW;
        int n = LOW;
        n = digitalRead(outputA);

        if ((PinCLKanterior == LOW) && (n == HIGH)) {

          if (digitalRead(outputB) == LOW) {
            Posicion--;
          } else {
            Posicion++;

          }

        }
        PinCLKanterior = n;
        if ((digitalRead(sw) == LOW)) {
          Posicion = 0;
        }

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("T-Apertura 1");
        lcd.setCursor(0, 1);
        lcd.print(Posicion);
        level_menu = 6;
      }

      //Tiempo Ap 2
      if (counter == 4) {
        counter = 0;
        counter = brilloled3;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("T-Apertura 2");
        lcd.setCursor(0, 1);
        lcd.print(brilloled3);
        level_menu = 6;
      }

      //setpoint temp
      if (counter == 5) {

        counter = brilloled3;
        level_menu = 6;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Temperatura *C");
        lcd.setCursor(0, 1);
        lcd.print(brilloled3);
      }

      //Setpoint HUM
      if (counter == 6) {
        counter = brilloled3;
        level_menu = 6;  //
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Humedad %");
        lcd.setCursor(0, 1);
        lcd.print(brilloled3);
      }

      btnpress = false;
    }
  }

  //-------------------


  if (level_menu == 1) {

    Serial.println("level1");
    if (fn_encoder(sizemenu2)) {
      fn_menu(counter, menu2, sizemenu2);
    }

    if (btnpress) {

      if (counter == 0) {

        MotorUnoDerecha();

        counter == 2;
      }

      if (counter == 1) {

        MotorUnoIzquierda();

        counter == 2;
      }

      if (counter == 2) {
        counter = 0;

        fn_menu(counter, menu1, sizemenu1);
        paroMotores();
        level_menu = 0;
      }

      btnpress = false;
    }
  }


  //---------------------------------------------





  if (level_menu == 2) {

    if (fn_encoder(sizemenu2)) {
      fn_menu(counter, menu2, sizemenu2);
    }

    if (btnpress) {

      if (counter == 0) {
        MotorDosDerecha();
      }

      if (counter == 1) {

        MotorDosIzquierda();
      }

      if (counter == 2) {
        counter = 1;
        fn_menu(counter, menu1, sizemenu1);
        paroMotores();
        //fn_menu(counter, menu1, sizemenu1);
        level_menu = 0;
      }

      btnpress = false;
    }
  }




  if (level_menu == 3) {

    if (fn_encoder(sizemenu2)) {
      fn_menu(counter, menu2, sizemenu2);
    }

    if (btnpress) {

      if (counter == 0) {
        digitalWrite(led3, HIGH);
        brilloled3 = 10;
      }

      if (counter == 1) {
        digitalWrite(led3, LOW);
        brilloled3 = 0;
      }

      if (counter == 2) {
        counter = 2;
        fn_menu(counter, menu1, sizemenu1);
        level_menu = 0;
      }

      btnpress = false;
    }
  }

  //----------------------------------------


  if (level_menu == 6) {
    if (fn_encoder(100)) {
      brilloled3 = counter;
      fn_intensidad();
    }

    if (btnpress) {
      counter = 5;
      level_menu = 0;
      fn_menu(counter, menu1, sizemenu1);
      btnpress = false;
    }
  }
}



void fn_menu(int pos, String menus[], byte sizemenu) {
  lcd.clear();
  linea1 = "";
  linea2 = "";

  if ((pos % 2) == 0) {

    lcd.setCursor(0, 0);
    lcd.write(byte(0));
    linea1 = menus[pos];

    if (pos + 1 != sizemenu) {
      linea2 = menus[pos + 1];
    }

  } else {
    linea1 = menus[pos - 1];
    lcd.setCursor(0, 1);
    lcd.write(byte(0));
    linea2 = menus[pos];
  }

  lcd.setCursor(1, 0);
  lcd.print(linea1);

  lcd.setCursor(1, 1);
  lcd.print(linea2);
}


bool fn_encoder(byte sizemenu) {
  bool retorno = false;
  aState = digitalRead(outputA);
  if (aState != aLastState) {
    if (digitalRead(outputB) != aState) {
      counter--;
    } else {
      counter++;
    }

    if (counter <= 0) {
      counter = 0;
    }

    if (counter >= sizemenu - 1) {
      counter = sizemenu - 1;
    }

    retorno = true;
  }
  aLastState = aState;
  return retorno;
}




void selectOption() {
  if (digitalRead(sw) == LOW) {
    delay(1000);
    btnpress = HIGH;
  }
}


void fn_intensidad() {
 // analogWrite(led3, map(brilloled3, 0, 100, 0, 255));
  lcd.setCursor(0, 1);
  lcd.print(brilloled3);
}


void fn_credits() {

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



void MotorDosIzquierda() {
  digitalWrite(pinC, LOW);

  lcd.init();
  //  digitalWrite(pinB, LOW);
  lcd.setCursor(0, 0);
  lcd.print("Cierre Puerta");
  lcd.setCursor(3, 1);
  lcd.print("2");
  analogWrite(LPWM2, 255);
  analogWrite(RPWM2, 0);
  digitalWrite(pinD, HIGH);
}



void MotorDosDerecha() {
  digitalWrite(pinD, LOW);

  lcd.init();

  lcd.setCursor(0, 0);
  lcd.print("Apertura Puerta");
  lcd.setCursor(3, 1);
  lcd.print("2");
  digitalWrite(pinC, HIGH);
  analogWrite(RPWM2, 255);
  analogWrite(LPWM2, 0);
}

void MotorUnoIzquierda() {
  digitalWrite(pinA, LOW);

  lcd.init();
  //  digitalWrite(pinB, LOW);
  lcd.setCursor(0, 0);
  lcd.print("Cierre Puerta");
  lcd.setCursor(3, 1);
  lcd.print("1");
  analogWrite(LPWM, 255);
  analogWrite(RPWM, 0);
  digitalWrite(pinB, HIGH);
}



void MotorUnoDerecha() {
  digitalWrite(pinB, LOW);

  lcd.init();

  lcd.setCursor(0, 0);
  lcd.print("Apertura Puerta");
  lcd.setCursor(3, 1);
  lcd.print("1");
  digitalWrite(pinA, HIGH);
  analogWrite(RPWM, 255);
  analogWrite(LPWM, 0);
}
void paroMotores() {
  ApagarLed();
  analogWrite(RPWM, 0);
  analogWrite(LPWM, 0);
  // delay(10000);

  analogWrite(LPWM2, 0);
  analogWrite(RPWM2, 0);
  //delay(10000);
}

void ApagarLed() {
  digitalWrite(pinA, LOW);
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);
  digitalWrite(pinD, LOW);
}

void DashBoard() {

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
