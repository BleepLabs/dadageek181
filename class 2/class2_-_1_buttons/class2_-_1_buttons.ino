int led1_pin =  3;                // the number of the LED1 pin
int led1_state = 1;             // remebers the state of the LED1

int led2_pin =  4;                // the number of the LED2 pin
int led2_state = 1;             // remebers the state of the LED2

unsigned long  previous_time1 = 0;  // will store last time LED1 was updated
unsigned long  previous_time2 = 0;  // will store last time LED2 was updated

unsigned long current_time;         // will store the current "time"

unsigned long interval1 = 500;                //the interval that LED1 will change
unsigned long interval2 = 25;                //the interval that LED2 will change

int pot1_value; //store the reading from the potentiomeer

int prev_button1_state;
int button1_state;
int latch1 = 1;

int prev_button2_state;
int button2_state;
int latch2 = 0;

int button1_pin = 12;
int button2_pin = 9;

int osc1;
byte expo_table[300];


void setup() {

  pinMode(led1_pin, OUTPUT); // set the LED pins as outputs
  pinMode(led2_pin, OUTPUT);

  pinMode(button1_pin, INPUT_PULLUP); //Without this on the correct pin digitalRead won't work
  pinMode(button2_pin, INPUT_PULLUP); //Without this on the correct pin digitalRead won't work

}

void loop()
{
  current_time = millis(); //call the function millis() to get the time in milliseconds that hve ellapsed since the device started

  pot1_value = analogRead(A0); // returns a value from 0 to 1023 (10bits)
  interval2 = pot1_value / 20; //20 is arbitrary

  prev_button1_state = button1_state; // what was the button state last loop?
  button1_state = digitalRead(button1_pin); // update the button

  prev_button2_state = button2_state;
  button2_state = digitalRead(button2_pin);

  if (button1_state == 0 && prev_button1_state == 1) { // is the button being pressed now (0) and was it not being pressed last loop?
    latch1 = !latch1; //set latch equal to NOT latch one. Set it to it's opposite
  }

  if (button2_state == 0 && prev_button2_state == 1) {
    latch2 = !latch2;
  }

  if (current_time - previous_time2 > interval2) { //has "interval2" amount of time past since we last executed this code?
    previous_time2 = current_time;

    if (latch2 == 0) {
      osc1 += 4; //add 4 to the current value of osc1
      if (osc1 > 255) { // if it's over 255, make it 0. The highest value we can analogWrite is 255 (8 bits)
        osc1 = 0;
      }
    }

    if (latch2 == 1) {
      osc1 -= 4; //subtract 4 from the current value of osc1
      if (osc1 < 0) { // if it's less than 0, make it 255. 
        osc1 = 255; 
      }

    }

    if (latch1 == 0) {
      led1_state = osc1;
      led2_state = 10;
    }

    if (latch1 == 1) {
      led1_state = 10;
      led2_state = osc1;      
    }

    analogWrite(led1_pin, led1_state);   // Write the value "led2_state" to "led2_pin.
    analogWrite(led2_pin, led2_state);   // Write the value "10" to "led2_pin.

  }


}

