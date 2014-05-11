/* Marker delivery code designed for testing different (PWM) voltages across the
DC pump. Once the best values are found, the PWM and timing variables will be 
permanently fixed */

//Define physical pins to use.
#define sigIn 4
#define pwmOut 9    //Temporarily use Pin 9 (Pin 6 blown)

int PWMval=255;       //Set output to motor (via MOSFET) to 5V
int Timer_Start=0;    //Initialise a start timer variable
int Timer_End=0;      //Initialise an end timer variable

//Begin initialise function.
void setup(){
  pinMode(sigIn, INPUT_PULLUP);
  /*Set a pin to input for testing and enable internal pullup resistor.*/
  pinMode(pwmOut, OUTPUT);    //Set the signal out pin.
  Serial.begin(9600);         //Establish serial comms for testing.
}

//Begin main loop function.
void loop(){
  //When input pin is high:
  while(digitalRead(sigIn) == HIGH){
    Timer_Start=millis();      //Set timer to ms after arduino epoch.
    analogWrite(pwmOut, 0);    //Keep MOSFET off.
  };

  //When input pin is low (signal from switch):
  while(digitalRead(sigIn) == LOW){
    Timer_End=millis()-Timer_Start;    //Keep time between press/depress.
    Serial.print("Held for ");
    Serial.println(Timer_End);         //Output held time to user.
    analogWrite(pwmOut, PWMval);       //Power MOSFET
  };
}
