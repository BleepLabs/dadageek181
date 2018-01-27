
int led1_pin =  0;                // The pin for LED1
int led1_state = LOW;             // The state of LED1

int led2_pin =  4;                // The LED2 pin
int led2_state = 0;             // The LED2 state

unsigned long  previous_time1 = 0;  // will store the last time LED1 was updated
unsigned long  previous_time2 = 0;  // will store the last time LED2 was updated

unsigned long current_time;        

unsigned long interval1;                //the interval that LED1 will change
unsigned long interval2;                //the interval that LED2 will change

int pot1_value; //store the reading from the potentiomeer aka knob


void setup() {
  // set both LED pins as output:
  pinMode(led1_pin, OUTPUT);
  pinMode(led2_pin, OUTPUT);

}

void loop()
{

  pot1_value = analogRead(A0); //returns 0 to 1023;
  interval1 = pot1_value;
  interval2 = pot1_value / 2;

  current_time = millis(); //call the function millis() to get the time in milliseconds that hve ellapsed since the device started

  if (current_time - previous_time1 > interval1) { //has "interval1" amount of time past since we last executed this code?
    previous_time1 = current_time;

    // if the LED is off turn it on and vice versa:
    if (led1_state == LOW)
      led1_state = HIGH;
    else
      led1_state = LOW;

    digitalWrite(led1_pin, led1_state);   // Write the value "led1_state" to "led1_pin.
  }


  if (current_time - previous_time2 > interval2) { //has "interval2" amount of time past since we last executed this code?
    previous_time2 = current_time;

    // if  LED2 is off turn it on and vice versa:
    if (led2_state == 0)
      led2_state = 1;
    else
      led2_state = 0;

    digitalWrite(led2_pin, led2_state);   // Write the value "led2_state" to "led2_pin.

  }

}

