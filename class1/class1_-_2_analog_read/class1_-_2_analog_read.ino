
int led1_pin =  0;                // The pin for LED1
int led1_state = 0;             // The state of LED1

unsigned long  previous_time1 = 0;  // will store the last time LED1 was updated
unsigned long current_time;         // will store the current "time"
unsigned long interval1;              //the interval at which LED1 will change

int pot1_value; //store the reading from the potentiomeer aka knob


void setup() {
  // set both LED pins as output:
  pinMode(led1_pin, OUTPUT);

}

void loop()
{

  pot1_value = analogRead(A0); //Read the analog voltage at pin A0. Returns 0 for 0volts and 1023 for the max voltage (3.3V). This is due to it being a 10 bit ADC
  interval1 = pot1_value;

  current_time = millis();

  if (current_time - previous_time1 > interval1) { //has "interval1" amount of time past since we last executed this code?
    previous_time1 = current_time; //if so enter this part of code and remeber at what time we did that

    // if the LED is off turn it on and vice versa:
    if (led1_state == 0)
      led1_state = 1;
    else
      led1_state = 0;

    digitalWrite(led1_pin, led1_state);   // Write the value "led1_state" to led1_pin.
  }

}



