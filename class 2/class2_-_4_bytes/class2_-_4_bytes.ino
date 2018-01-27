unsigned long  previous_time1;
unsigned long current_time;
unsigned long interval1 = 100;

int led1_pin =  3;               
int led2_pin =  4;             


int pot1_value; //store the reading from the potentiomeer

int led_value; // waht to send the LEDs

void setup() {

 
}

void loop()
{
  current_time = millis();

  pot1_value = analogRead(A0);
  led_value = pot1_value;

  analogWrite(led1_pin, led_value);

  analogWrite(led2_pin, (led_value - 255) * -1); // inverts led_value

  if (current_time - previous_time1 > interval1) { // you can't print too fast. 10 times a second is plenty but you can go faster
    previous_time1 = current_time;

    Serial.print("pot1_value ");
    Serial.println(pot1_value);
    Serial.print("led_value  ");
    Serial.println(led_value);
    Serial.println();

  }
}
