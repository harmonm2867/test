void setup() {
  cli();
  // Setting up ADCSRA, ADCSRB, and ADMUX
  ADCSRA = 0xEF;
  ADCSRB = 0x00;
  ADMUX = 0x40;
  sei();
  Serial.begin(9600);
}
volatile unsigned int avrgC = 0; //variable to hold center sensor value
volatile unsigned int avrgL = 0; //variable to hold left sensor value
volatile unsigned int avrgR = 0; //variable to hold right sensor value
void loop() {

  Serial.print("Center: ");
  Serial.print(avrgC);
  Serial.print(" ");

  Serial.print("Left: ");
  Serial.print(avrgL);
  Serial.print(" ");

  Serial.print("Right: ");
  Serial.println(avrgR);

}
ISR(ADC_vect)
{

  //static unsigned int avrgC = 0; //variable to hold center sensor value
  //static unsigned int avrgL = 0; //variable to hold left sensor value
  //static unsigned int avrgR = 0; //variable to hold right sensor value

  //circulate between saving A0, A1, and A2's ADC results
  switch (ADMUX)
  {
    case 0x40:
      avrgC = ADC; //store result to variable for center sensor
      ADMUX = 0x41; //switch to A1 being currently active
      break;
    case 0x41:
      avrgL = ADC; //store result to variable for left sensor
      ADMUX = 0x42; //switch to A2 being currently active
      break;
    case 0x42:
      avrgR = ADC; //store result to variable for right sensor
      ADMUX = 0x40; //switch to A0 being currently active
      break;

  }
}
