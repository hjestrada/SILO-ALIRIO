const int pinBuzzer = 8;
int numeroTonos = 12;
int tonos[] = {261, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494};
void setup() {
}
void loop() {
  alarma();
stopAlarma();

}



int alarma() {
  for (int i = 0; i < numeroTonos; i++) {
    tone(pinBuzzer, tonos[i]);
    delay(200);
  }
}

int stopAlarma() {
  noTone(pinBuzzer);
  delay(1000);
}
