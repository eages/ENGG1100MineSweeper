/* Marker delivery code designed for testing different (PWM) voltages across the
DC pump. Once the best values are found, the PWM and timing variables will be 
permanently fixed */

//Define physical pins to use.
#define sigIn 4
#define pwmOut 6

int PWMval=255; 	//Set output to motor (via MOSFET) to 5V
int timing=0; 		//Initialise a timer variable

//Begin initialise function.
void setup(){
	pinMode(sigIn, INPUT); 		//Set pin 4 to be an input for testing.
	pinMode(pwmOut, OUTPUT); 	//Set the signal out pin.
	Serial.begin(9600); 		//Establish serial comms for testing.
}

//Begin main loop function.
void loop(){
	//When there's no signal to input pin:
	while(digitalRead(sigIn) == LOW);
		timing=millis();	//Set timer to ms after arduino epoch.
	analogWrite(pwmOut, PWMval); 	//Send the defined signal to MOSFET.

	//When there's a signal to input pin:
	while(digitalRead(sigIn) == HIGH);
	timing=millis()-timing; 	//????
	Serial.print("Held for ");
	Serial.println(timing); 	//Output held time to user.
	digitalWrite(pwmOut, LOW); 	//????
}
