#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform2;      //xy=666.6666946411133,151.66668319702148
AudioSynthNoisePink      pink1;          //xy=668.333366394043,210.00000953674316
AudioSynthWaveform       waveform1;      //xy=678.3333257039387,110.0000267028808
AudioFilterStateVariable filter2;        //xy=695.0000228881836,283.3333339691162
AudioMixer4              mixer2;         //xy=723.3333282470703,411.6666564941406
AudioEffectDelay         delay1;         //xy=736.3333206176758,586.666669845581
AudioMixer4              mixer1;         //xy=842.3333206176758,146.66668319702148
AudioEffectEnvelope      envelope1;      //xy=863.666633605957,283.3333034515381
AudioAnalyzePeak         peak1;          //xy=891.6666641235352,366.66667079925537
AudioFilterStateVariable filter1;        //xy=890.9999961853027,579.3332557678223
AudioOutputAnalog        dac1;           //xy=891.9999961853027,431.99998664855957
AudioConnection          patchCord1(waveform2, 0, mixer1, 1);
AudioConnection          patchCord2(pink1, 0, mixer1, 2);
AudioConnection          patchCord3(waveform1, 0, mixer1, 0);
AudioConnection          patchCord4(filter2, 0, envelope1, 0);
AudioConnection          patchCord5(mixer2, delay1);
AudioConnection          patchCord6(mixer2, dac1);
AudioConnection          patchCord7(mixer2, peak1);
AudioConnection          patchCord8(delay1, 0, filter1, 0);
AudioConnection          patchCord9(mixer1, 0, filter2, 0);
AudioConnection          patchCord10(envelope1, 0, mixer2, 0);
AudioConnection          patchCord11(filter1, 0, mixer2, 1);
// GUItool: end automatically generated code


unsigned long current_time;         // will store the current "time"
unsigned long  previous_time1 = 0;  // will store the last time LED1 was updated
unsigned long  previous_time2 = 0;  // will store the last time LED1 was updated
unsigned long  previous_time3 = 0;  // will store the last time LED1 was updated

int led1_pin =  3;                // The pin for LED1
int led1_state = 0;             // The state of LED1
int led2_pin =  4;                // The LED2 pin
int led2_state = 0;             // The LED2 state
int interval1 = 250;
int interval2 = 25;
int interval3 = 100;
int button_pin = 12;
int high_freq;
int audio_reading;
int button_state;
int prev_button_state;
float freq[3]; // an array to hold three floating point numbers
int pot_value;
int pcell_value;
int osc1_latch;
int osc1;

void setup() {
  //required to setup audio. if it's too low it won't run.
  AudioMemory(100); //255 is max
  pinMode(button_pin, INPUT_PULLUP);

  waveform1.begin(1, 0, WAVEFORM_TRIANGLE);
  waveform2.begin(1, 0, WAVEFORM_SQUARE);
  pink1.amplitude(1);;
  mixer1.gain(0, .3); //leave some headroom for the filter
  mixer1.gain(1, .3);
  mixer1.gain(2, 0);
  mixer2.gain(0, 1); //direct audio level
  mixer2.gain(1, 0); // feedback level
  // These numbers can add up to greater than 1 but that doesn't necessarily mean we will clip as it's just the level of amplification, not the level of the signal.
  delay1.delay(0, 150); //Delay out 0 set at 160 milliseconds

  filter1.frequency(5000); // frequency to set the low pass filter at. Anything about it will be attenuated.
  filter1.resonance(.7); //feedback of filter itself

  filter2.frequency(10000); // frequency to set the low pass filter at. Anything about it will be attenuated.
  filter2.resonance(2); //feedback of filter itself

  analogReadAveraging(21); // smooth readings

}


void loop()
{

  prev_button_state = button_state;
  button_state = digitalRead(button_pin);

  if (button_state == 0 && prev_button_state == 1) {
    envelope1.noteOn();
  }
  if (button_state == 1 && prev_button_state == 0) {
    envelope1.noteOff();
  }

  interval3 = map (analogRead(A0), 0, 1023, 1, 20);

  if (current_time - previous_time3 > interval3) { //has "interval2" amount of time past since we last executed this code?
    previous_time3 = current_time;

    if (osc1_latch == 1) {
      osc1 += 40; //add 4 to the current value of osc1
      if (osc1 > 1500) { // if it's over 255 chage the latch, flipping the direction
        osc1 = 1500; //we dont want it going above our 8 bit max
        osc1_latch = 0;
      }
    }

    if (osc1_latch == 0) {
      osc1 -= 40; //subtract 4 from the current value of osc1
      if (osc1 < 0) { // if it's less than 0 chage the latch, flipping the direction
        osc1 = 0; // dont want it under 0
        osc1_latch = 1;
      }

    }
  }

  analogWrite(led2_pin, map(osc1,0, 1500, 0, 255));

  //pot_value = map (analogRead(A0), 0, 1023, 100, 15000);  //(starting value, low start, hight start, low destionation, high destination)

  filter2.frequency(pcell_value + 1000 + osc1);

  pcell_value = analogRead(A2) * 2;

  freq[0] = pcell_value;
  freq[1] = pcell_value / 2.00; //an int divided by a float in a float is a float

  waveform1.frequency(freq[0]);
  waveform2.frequency(freq[1]);




  current_time = millis();
  if (current_time - previous_time1 > interval1) {
    previous_time1 = current_time;

    Serial.print("osc1 ");
    Serial.println(osc1);
    Serial.print("audio_reading ");
    Serial.println(audio_reading);
    Serial.print("processor ");
    Serial.println(AudioProcessorUsageMax());

    Serial.print("memory ");
    Serial.println(AudioMemoryUsageMax());
    Serial.println();
    AudioProcessorUsageMaxReset();
    AudioMemoryUsageMaxReset();
  }

  if (current_time - previous_time2 > interval2) {
    previous_time2 = current_time;
    if (peak1.available()) {
      audio_reading = peak1.read() * 255;  // reading is a float from 0.00 to 1.00. led is 0-255
    }

    analogWrite(led1_pin, audio_reading);
  }
}

