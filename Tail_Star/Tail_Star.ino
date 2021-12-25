#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 150

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806, define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 2
#define CLOCK_PIN 13

#define INNER_LOWER 129
#define INNER_UPPER 150

#define OUTER_LOWER 36
#define OUTER_UPPER 97
#define OUTER_STEPS 3
#define OUTER_CONTI 5

#define TAIL_1_LOWER 116 // 13
#define TAIL_1_UPPER 129
#define TAIL_2_LOWER 96 // 18
#define TAIL_2_UPPER 114
#define TAIL_3_LOWER 26 // 11
#define TAIL_3_UPPER 37

//for star
int OUTLEDS[OUTER_UPPER - OUTER_LOWER] = {
    36,37,38,39,44,
    45,46,47,48,49,50,51,56,
    57,58,59,60,61,62,63,64,
    69,70,71,72,73,74,75,76,
    81,82,83,84,85,86,87,88,
    93,94,95,96,97
  };
  
int Outter_Leds[10];

//for tail
int Tail_1_Leds[10];
int Tail_2_Leds[10];
int Tail_3_Leds[10];

// Define the array of leds
CRGB leds[NUM_LEDS];



void setup()
{
  Serial.begin(9600);
  Serial.println("resetting");
  LEDS.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
  LEDS.setBrightness(84);

//  Arrays_Init(OUTER_LOWER, OUTER_UPPER, OUTER_CONTI, OUTER_STEPS, Inner_Leds);
//  PrintArray(Inner_Leds, sizeof(Inner_Leds) / sizeof(int));
//  Serial.println(sizeof(Inner_Leds) / sizeof(int));
//  Arrays_Init(10, 20,Outter_Leds);
//  Arrays_Init(10, 20,Inner_Leds);
//  for (int i = OUTER_LOWER; i < OUTER_UPPER; i++){
//    leds[i] = CRGB::Blue;
//  }
//  FastLED.show();
  for (int i = 0; i < NUM_LEDS; i++){
    leds[i] = CRGB::Black;
  }
  FastLED.show();


  for (int i = 0; i < sizeof(OUTLEDS) / sizeof(int); i++){
    leds[OUTLEDS[i]] = CRGB::Blue;
  }
  for (int i = INNER_LOWER; i < INNER_UPPER; i++){
    leds[i] = CRGB::Blue;
  }
  FastLED.show();
}

void fadeall(int fade){
  for (int i = 0; i < NUM_LEDS; i++){
    leds[i].nscale8(fade);
  }
}

void allOFF(){
  for (int i = 0; i < NUM_LEDS; i++){
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}

void patternOne(CRGB color ){
   for (int i = INNER_LOWER; i < INNER_UPPER; i++){
    leds[i] = color;
    FastLED.show();
//    delay(30);
  }
  FastLED.show();
  delay(200);
  allOFF();
  fadeall(100);
  
  for (int i = 0; i < sizeof(OUTLEDS) / sizeof(int); i++){
    leds[OUTLEDS[i]] = color;
  }
  for (int i = INNER_LOWER; i < INNER_UPPER; i++){
    leds[i] = color;
  }
  FastLED.show();
  delay(30);
//  allOFF();
  fadeall(100);
  
  for (int i = 0; i < TAIL_2_UPPER - TAIL_2_LOWER; i++){
    if((TAIL_3_UPPER-TAIL_2_LOWER)<i){
      leds[TAIL_3_UPPER-i] = color;
    }
    if((TAIL_1_LOWER-TAIL_1_UPPER)<i){
      leds[TAIL_1_UPPER-i] = color;
    }
    leds[TAIL_2_LOWER+i] = color;
    FastLED.show();
    delay(30);
  }

  delay(100);
  for (int i = 0; i < sizeof(OUTLEDS) / sizeof(int); i++){
    leds[OUTLEDS[i]] = color;
  }
  FastLED.show();
  delay(100);
  allOFF();
//  fadeall(100);
}

void patternTwo(CRGB incolor, CRGB outcolor, int downDelay, int upDelay){
    for (int i = downDelay; i < upDelay; i++){
    for (int i = INNER_LOWER; i < INNER_UPPER; i++){
      leds[i] = incolor;
    }
    FastLED.show();
    delay(i*2);//200
//    allOFF();
    fadeall(100);
    
    for (int i = 0; i < sizeof(OUTLEDS) / sizeof(int); i++){
      leds[OUTLEDS[i]] = outcolor;
    }
    for (int i = INNER_LOWER; i < INNER_UPPER; i++){
      leds[i] = incolor;
    }
    FastLED.show();
    delay(i);
//    allOFF();
    fadeall(10);
  }
  for (int i = 0; i < TAIL_2_UPPER - TAIL_2_LOWER; i++){
    if((TAIL_3_UPPER-TAIL_2_LOWER)<i){
      leds[TAIL_3_UPPER-i] = outcolor;
    }
    if((TAIL_1_LOWER-TAIL_1_UPPER)<i){
      leds[TAIL_1_UPPER-i] = incolor;
    }
    leds[TAIL_2_LOWER+i] = outcolor;
    FastLED.show();
    delay(30);
    fadeall(200);
  }
}

void patternThree(CRGB incolor, CRGB outcolor){
  for (int i = 0; i < sizeof(OUTLEDS) / sizeof(int); i++){
    leds[OUTLEDS[i]] = outcolor;
    FastLED.show();
    delay(30);
    fadeall(100);
  }
  
//  allOFF();

  for (int i = 0; i < TAIL_2_UPPER - TAIL_2_LOWER; i++){
    if((TAIL_3_UPPER-TAIL_2_LOWER)<i){
      leds[TAIL_3_UPPER-i] = outcolor;
    }
    leds[TAIL_2_LOWER+i] = outcolor;
    FastLED.show();
    delay(30);
    fadeall(200);
  }
  
  
  for (int i = 0; i < TAIL_2_UPPER - TAIL_2_LOWER ; i++){
    leds[TAIL_2_UPPER+i] = incolor;
    FastLED.show();
    delay(30);
    fadeall(200);
  }
   for (int i = INNER_LOWER; i < INNER_UPPER; i++){
      leds[i] = incolor;
      FastLED.show();
      delay(30);
      fadeall(200);
    }
    allOFF();
  }


void patternFour( CRGB color1, CRGB color2){
  for (int i = 26; i < 150; i++){
    leds[150-i] = color1;
    leds[i] = color2;
//    leds[i+25] = color1;
//    leds[i+10] = color2;
    FastLED.show();
    delay(30);
    fadeall(200);
  }
}

void patternFive( CRGB color1){
    for (int i = 0; i < 100; i++){
      leds[random(29, NUM_LEDS)] = color1;
      FastLED.show();
      delay(30);
      fadeall(200);
    }
}

void patternSix( CRGB color1){
    for (int i = 0; i < 100; i++){
      leds[random(29, NUM_LEDS)] = color1;
      FastLED.show();
      delay(random(0, 100));
      fadeall(200);
    }
}

void patternSeven(){
    for (int i = 0; i < 100; i++){
      leds[random(29, NUM_LEDS)] = CRGB(random(0,255), random(0,255), random(0,255));
      FastLED.show();
      delay(random(0, 100));
      fadeall(200);
    }
}

void loop()
{

//  delay(1000);

  
//  delay(1000);
//  for (int i = 0; i < 30; i++){
//    for (int i = INNER_LOWER; i < INNER_UPPER; i++){
//      leds[i] = CRGB::Blue;
//    }
//    FastLED.show();
//    delay(i*2);//200
//    allOFF();
//    
//    for (int i = 0; i < sizeof(OUTLEDS) / sizeof(int); i++){
//      leds[OUTLEDS[i]] = CRGB::Blue;
//    }
//    for (int i = INNER_LOWER; i < INNER_UPPER; i++){
//      leds[i] = CRGB::White;
//    }
//    FastLED.show();
//    delay(i);
//    allOFF();
//  }
//  for (int i = 0; i < TAIL_2_UPPER - TAIL_2_LOWER; i++){
//    if((TAIL_3_UPPER-TAIL_2_LOWER)<i){
//      leds[TAIL_3_UPPER-i] = CRGB::Blue;
//    }
//    if((TAIL_1_LOWER-TAIL_1_UPPER)<i){
//      leds[TAIL_1_UPPER-i] = CRGB::White;
//    }
//    leds[TAIL_2_LOWER+i] = CRGB::Blue;
//    FastLED.show();
//    delay(30);
//  }

//  delay(200);
//  for (int i = 0; i < sizeof(OUTLEDS) / sizeof(int); i++){
//    leds[OUTLEDS[i]] = CRGB::Blue;
//    FastLED.show();
//    delay(20);
//  }
//  allOFF();
//
//  for (int i = 0; i < TAIL_2_UPPER - TAIL_2_LOWER; i++){
//    if((TAIL_3_UPPER-TAIL_2_LOWER)<i){
//      leds[TAIL_3_UPPER-i] = CRGB::Blue;
//    }
//    leds[TAIL_2_LOWER+i] = CRGB::Blue;
//    FastLED.show();
//    delay(30);
//  }
//  
//  for (int i = 0; i < TAIL_2_UPPER - TAIL_2_LOWER ; i++){
//    leds[TAIL_2_UPPER+i] = CRGB::White;
//    FastLED.show();
//    delay(30);
//  }
//    for (int i = INNER_LOWER; i < INNER_UPPER; i++){
//      leds[i] = CRGB::White;
//      FastLED.show();
//      delay(30);
//    }

  patternThree(CRGB::White, CRGB::Blue);
  patternThree(CRGB::White, CRGB::Yellow );
  patternThree(CRGB::White, CRGB::Red);
  patternThree(CRGB::White, CRGB::Purple );
  patternThree(CRGB::White, CRGB::Aqua );

  patternTwo(CRGB::White, CRGB::Blue, 30, 40);
  patternTwo(CRGB::White, CRGB::Red, 30, 40);
  patternTwo(CRGB::White, CRGB::Orange, 30, 40);
  patternTwo(CRGB::White, CRGB::Green, 30, 40);
  patternTwo(CRGB::White, CRGB::Purple, 30, 40);
  patternTwo(CRGB::White, CRGB::Pink, 30, 40);
  patternTwo(CRGB::White, CRGB::Aqua, 30, 40);

  patternTwo(CRGB::White, CRGB::White, 30, 60);
  patternTwo(CRGB::Blue, CRGB::Blue, 30, 60);
  patternTwo(CRGB::Orange, CRGB::Orange, 30, 60);
  patternTwo(CRGB::Aqua, CRGB::Aqua, 30, 60);
  patternTwo(CRGB::Pink, CRGB::Pink, 30, 60);
  patternTwo(CRGB::Green, CRGB::Green, 30, 60);
  
  
  patternFour(CRGB::Blue, CRGB::White);
  patternFour(CRGB::White, CRGB::Red);
  patternFour(CRGB::Purple , CRGB::White);
  patternFour(CRGB::White, CRGB::Aqua);
  patternFour(CRGB::Yellow , CRGB::White);
  patternFour(CRGB::White, CRGB::Green);
  patternFour(CRGB::Orange, CRGB::White);
  patternFour(CRGB::White, CRGB::Aqua);
  
  patternOne(CRGB::Aqua);
  patternOne(CRGB::White);
  patternOne(CRGB::Blue);
  patternOne(CRGB::Red);
  patternOne(CRGB::Orange);
  patternOne(CRGB::Yellow);
  patternOne(CRGB::Green);
  patternOne(CRGB::Purple);
  patternOne(CRGB::Pink);
  patternOne(CRGB::Red);

  patternFive(CRGB::Aqua);
  patternFive(CRGB::White);
  patternFive(CRGB::Blue);
  patternFive(CRGB::Red);
  patternFive(CRGB::Orange);
  patternFive(CRGB::Yellow);
  patternFive(CRGB::Green);
  patternFive(CRGB::Purple);
  patternFive(CRGB::Pink);
  patternFive(CRGB::Red);

  patternSix(CRGB::Aqua);
  patternSix(CRGB::White);
  patternSix(CRGB::Blue);
  patternSix(CRGB::Red);
  patternSix(CRGB::Orange);
  patternSix(CRGB::Yellow);
  patternSix(CRGB::Green);
  patternSix(CRGB::Purple);
  patternSix(CRGB::Pink);
  patternSix(CRGB::Red);

  patternSeven();
  patternSeven();
  patternSeven();
  patternSeven();
  patternSeven();
  

}
