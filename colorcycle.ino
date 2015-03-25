// colorcycle 1.2 includes an rgb switch for different types of LED strips that can be "RGB" 
// or "GRB". This also gives us a fade to dark from both red and green on the same strip 

#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

#define PIN            6 //NeoPixel data control pin

#define NUMPIXELS      8 // number of pixels

int potpin = 0;  // analog pin used to connect the potentiometer
int rgbswitchin = 12;
int rgbswitchout = 13 ;
int val;    // variable to read the value from the analog pin 
int R=0, G=0, B=0;  // set our color values
//set our pixel values
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 10; // delay 

void setup() {
  pinMode(rgbswitchin, INPUT);
  pinMode(rgbswitchout, OUTPUT);
  digitalWrite(rgbswitchout, HIGH);
  
  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {
  int readrgb = digitalRead(rgbswitchin);
  val = analogRead(potpin);    // reads the value of the potentiometer (value between 0 and 1023)
  val = map(val, 0, 1023, 0, 2040);     // scale it to choose a color
  if (val >= 0 && val <=255){ R=val; G=0; B=0;}
  else if (val > 255 && val <= 510){R=255; G=val-255; B=0;}
  else if (val >510 && val <= 765){R= 255- (val - 510); G=255; B=0;}
  else if (val >765 && val <= 1020){R=0; G=255; B=val-765;}
  else if (val >1020 && val <= 1275){R=0; G= 255 - (val - 1020); B=255;}
  else if (val >1275 && val <= 1530){R=val-1275; G=0; B=255;}
  else if (val >1530 && val <= 1785){R=255; G=0; B= 255-(val-1530);}
  else if (val >1785 && val <= 2040){R=255; G= val-1785; B=val-1785;}
  else {R=0; G=0; B=0;} // failsafe


  if (readrgb == HIGH){ // then swap Red and Green 
    int foo = 0;
    foo = R; R=G; G=foo;
    }

  for(int i=0;i<NUMPIXELS;i++){
  
  
    
    pixels.setPixelColor(i, pixels.Color(R,G,B)); // set color value

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).

  }
} // end loop
