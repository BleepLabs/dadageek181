
//The first thing we do is initialize variables. Here we name the variables we want to store data in.

int led1_pin =  0;                // the number of the pin that the LED is attached to. "int" describes a type of number
int led1_state = 0;             // remembers what we want the state of the LED to be. Well start with 0 aka off or LOW
unsigned long previous_time = 0;   // will store last time the LED was updated. "unsigned long" is another type of number
unsigned long current_time;         // stores the current number of milliseconds since the device was reset. We havent set it equal to anything so it will defualt to 0
int interval1 = 1000;        ///the interval at which LED1 will change in milliseconds. We'll start with 500 = .5 seconds

//End of initialization


void setup() //The setup. This part of the code runs just once after the teensy resets.
{
  pinMode(led1_pin, OUTPUT); // set the LED pin as output. 

 // end of setup


void loop() // The loop. This part of the code will run over and over again as fast as the Teensy can go.
{
  
  current_time = millis(); 
  // Call the function "millis()". 
  // It returns the time in milliseconds that have ellapsed since the device started which we store in the varible "current_time"
  // That means for the rest or this loop "current_time" will be equal to that number of milliseconds


  if (current_time - previous_time > interval1) { 
    //has "interval1" amount of time past since we last executed this code?
    //If the current time minus the last time is bigger that the interval then this part of the code is run
    //If not then it dosen't and we do the next thing below it

    previous_time = current_time;  //remember waht time it is now

    // if the LED is off turn it on and vice versa:
    if (led1_state == LOW)
      led1_state = HIGH;
    else
      led1_state = LOW;

    digitalWrite(led1_pin, led1_state);   
    // Ouptut the value "led1_state" to "led1_pin.
    //if "led1_state" is low aka "0" the LED will be off
    //if "led1_state" is high aka "1" the LED will be on
    //it's digital so it can only be on or off, 1 or 0, high or low.

  } // the if statement is now over.


} // Loop is over so it starts again with no wait.

