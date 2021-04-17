// NeoPoxel library
#include <Adafruit_NeoPixel.h>
#define LED_PIN 6      // pin # connected to the NeoPixels
#define sensorPin 2   // pin for the connectors

// NeoPixels in-use counts
#define LED_COUNT 3
int interval = 172; // time between blinks
int delay_time = 500; //used with delay function
int sensorValue = 0;  // initial connector pin to 0; not connected
int flag = false;  // check when the 2 objects just got connected and no code in loop was executed yet

// NEO_KHZ800: 800 KHz bitstream w/WS2812 LEDs
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
Serial.begin(9600);
pinMode(sensorPin, INPUT);
strip.begin();           // intilize NeoPixel strip object
strip.show();            // Turn OFF all pixels
strip.setBrightness(255); //(brightness level; max = 255)
}

void loop() {
sensorValue = digitalRead(sensorPin); //LOW if objects are not connected to the other, HIGH otherwise
    
if (sensorValue == LOW)
{ 
  strip.clear();         // turn off pixels
  strip.setPixelColor(0, 255, 203, 192); //color chosen for the Pokemon
  strip.show(); // Update strip
  delay(delay_time); //stay on this period of time
  strip.clear(); // turn off pixels
  strip.Color(0, 0, 0); //OFF
  strip.show(); // Update strip to OFF
  delay(delay_time); // stay off this period of time (mimic blinking)
}
else {
    // execute if this is the first time in the loop after connected
    if (flag == false){
      flag = true;
      delay(delay_time); // this delay time will allow the 2 clocks of boards to semi-sync and start the code almost the same time
      }
  forward(strip.Color(255, 203, 192), interval); // blink from neopixel 1 to 3 with interval time in between
  backward(strip.Color(255, 203, 192), interval); // blink backwards from neopixel 3 to 1with interval time in between
}
}
void forward(uint32_t color, int wait) {
  for(int b=0; b< (LED_COUNT-1); b++) { //loop over pixels (We have 3, 1 for each layer)
    strip.clear();         // turn off pixels
    //for(int c=b; c<strip.numPixels(); c += 3) { // this for can be used if we want variable number of neopixels; but as we have predifined 3, we can omit
      sensorValue = digitalRead(sensorPin);
      if (sensorValue == 0) {  // if disconnected, immediately stop executing
      break;
    }
    else {
      strip.setPixelColor(b, color); // Set pixel 'b' to value 'color'
      strip.show(); // Update strip
      delay(wait);  // Pause
    }
  //}
}
}

void backward(uint32_t color, int wait) {
  for(int b=(LED_COUNT-1); b>0 ; b--) { //loop over pixels (We have 3, 1 for each layer)
    strip.clear();         // turn off pixels
    //for(int c=b; c<strip.numPixels(); c += 3) { // this for can be used if we want variable number of neopixels; but as we have predifined 3, we can omit
      sensorValue = digitalRead(sensorPin);
      if (sensorValue == 0) {  // if disconnected, immediately stop executing
      break;
    }
    else {
      strip.setPixelColor(b, color); // Set pixel 'b' to value 'color'
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause
    }
  //}
}
}
