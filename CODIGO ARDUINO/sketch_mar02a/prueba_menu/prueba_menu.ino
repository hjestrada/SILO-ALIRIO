/* Define digital pins used to read the encoder */
#define DT 7
#define CLK 6
#define SW 5
int counter;
byte DialPos;
byte Last_DialPos;
 
void setup()
{
  Serial.begin(9600);
  pinMode(DT, INPUT);   
  pinMode(CLK, INPUT); 
  pinMode(SW, INPUT); 
  digitalWrite(SW, HIGH);
 
  /* Reset the counter */
  counter = 0;
}
 
/* Main program */
void loop()
{
    /* Read the status of the dial */
    DialPos = (digitalRead(CLK) << 1) | digitalRead(DT);
  
    /* Is the dial being turned anti-clockwise? */
    if (DialPos == 3 && Last_DialPos == 1)
    {
      counter--;
    }
  
    /* Is the dial being turned clockwise? */
    if (DialPos == 3 && Last_DialPos == 2)
    {
      counter++;
    }
  
    /* Output the counter to the serial port */
    Serial.println(counter);
  
    /* Is the switch pressed? */
    if(!digitalRead(SW))
      Serial.println("Switch pressed!");
  
    /* Save the state of the encoder */
    Last_DialPos = DialPos;
   
}
