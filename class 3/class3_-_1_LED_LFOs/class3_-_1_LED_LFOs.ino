int led1_pin =  3;                // the number of the LED1 pin
int led2_pin =  4;                // the number of the LED2 pin
int led1_state;
int led2_state;

unsigned long  previous_time1;
unsigned long  previous_time2;
unsigned long  previous_time3;

unsigned long current_time;

int interval1;
int interval2;
int interval3 = 30;

int pot1_value;
int pot2_value;

int prev_button1_state;
int button1_state;
int latch1 = 1;

int prev_button2_state;
int button2_state;
int latch2 = 0;

int button1_pin = 12;
int button2_pin = 9;

int osc1;
int osc1_latch;

int osc2;
int osc2_latch;

int osc3;
int osc3_latch;
float osc3bright;


void setup() {

  pinMode(led1_pin, OUTPUT); // set the LED pins as outputs
  pinMode(led2_pin, OUTPUT);
  Serial.begin(9600);
  pinMode(button1_pin, INPUT_PULLUP); //Without this on the correct pin digitalRead won't work
  pinMode(button2_pin, INPUT_PULLUP); //Without this on the correct pin digitalRead won't work

  analogWriteFrequency(led1_pin, 187500 ); // makes the LEDs a little smoother looking by increasing the PWM frequency to 187.5kHz
  analogWriteFrequency(led2_pin, 187500 );

}

void loop()
{
  current_time = millis(); //call the function millis() to get the time in milliseconds that hve ellapsed since the device started

  pot1_value = analogRead(A0); // returns a value from 0 to 1023 (10bits)
  interval1 = pot1_value / 20; //20 is arbitrary

  pot2_value = analogRead(A1); // returns a value from 0 to 1023 (10bits)
  interval2 = pot2_value / 20; //20 is arbitrary

  prev_button1_state = button1_state; // what was the button state last loop?
  button1_state = digitalRead(button1_pin); // update the button

  if (button1_state == 0 && prev_button1_state == 1) { // is the button being pressed now (0) and was it not being pressed last loop?
    latch1 = !latch1; //set latch equal to NOT latch one. Set it to it's opposite
  }

  if (current_time - previous_time1 > interval1) { //has "interval2" amount of time past since we last executed this code?
    previous_time1 = current_time;

    if (osc1_latch == 1) {
      osc1 += 4; //add 4 to the current value of osc1
      if (osc1 > 255) { // if it's over 255 chage the latch, flipping the direction
        osc1 = 255; //we dont want it going above our 8 bit max
        osc1_latch = 0;
      }
    }

    if (osc1_latch == 0) {
      osc1 -= 4; //subtract 4 from the current value of osc1
      if (osc1 < 0) { // if it's less than 0 chage the latch, flipping the direction
        osc1 = 0; // dont want it under 0
        osc1_latch = 1;
      }

    }

  }

  if (current_time - previous_time2 > interval2) { //has "interval2" amount of time past since we last executed this code?
    previous_time2 = current_time;

    if (osc2_latch == 1) {
      osc2 += 4; //add 4 to the current value of osc1
      if (osc2 > 255) { // if it's over 255 chage the latch, flipping the direction
        osc2 = 255; //we dont want it going above our 8 bit max
        osc2_latch = 0;
      }
    }

    if (osc2_latch == 0) {
      osc2 -= 4; //subtract 4 from the current value of osc1
      if (osc2 < 0) { // if it's less than 0 chage the latch, flipping the direction
        osc2 = 0; // dont want it under 0
        osc2_latch = 1;
      }

    }

  }

  if (current_time - previous_time3 > interval3) { //has "interval2" amount of time past since we last executed this code?
    previous_time3 = current_time;

    if (osc3_latch == 1) {
      osc3 += 4; //add 4 to the current value of osc1
      if (osc3 > 255) { // if it's over 255 chage the latch, flipping the direction
        osc3 = 255; //we dont want it going above our 8 bit max
        osc3_latch = 0;
      }
    }

    if (osc3_latch == 0) {
      osc3 -= 4; //subtract 4 from the current value of osc1
      if (osc3 < 0) { // if it's less than 0 chage the latch, flipping the direction
        osc3 = 0; // dont want it under 0
        osc3_latch = 1;
      }

    }

    osc3bright = osc3 / 255.0; //important that it have the .0 otherwise it would not be calculated as a float so everything would be rounded down to 0.


  }

  if (latch1 == 0) {
    led1_state = osc1 * osc3bright;   //triangle wave with intensity controlled by osc3. osc1 goes from 0-255, osc3bright goes from 0.0-1.0
    led2_state = osc2 * osc3bright;
  }
  
  if (latch1 == 1) {
    led1_state = osc1_latch * osc3;  //square wave with intensity controlled by osc3. osc1_latch is 0 or 1, osc3 goes from 0-255
    led2_state = osc2_latch * osc3;
  }
  
  analogWrite(led1_pin, led1_state);   // Write the value "led1_state" to "led1_pin. thios is a PWM pin so we can send it values from 0-255;
  analogWrite(led2_pin, led2_state);


}

