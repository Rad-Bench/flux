// Created by RadBench: youtube.com/radbenchyt
// Made for A flux Capacitor with a 10 light NanoLed strip

// DFPlayer Stuff
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

void printDetail(uint8_t type, int value);


///////////////////////////////////////////////////////////////////////////////////////////


//IR

uint32_t Previous;
#include <IRremote.h>
int receiver = 3; // initialize pin 3 as the receiver pin
IRrecv irrecv(receiver); //Create new instance of receiver
decode_results results;

//Remote

#define button_0 0xFF6897
#define button_1 0xFF30CF
#define button_2 0xFF18E7
#define button_3 0xFF7A85
#define button_4 0xFF10EF
#define button_5 0xFF38C7
#define button_6 0xFF5AA5
#define button_7 0xFF42BD
#define button_8 0xFF4AB5
#define button_9 0xFF52AD
#define buttonStop 0xFFE21D
#define volUp 0xFF629D
#define volDwn 0xFFA857
#define btnUp 0xFF906F 
#define btnDown 0xFFE01F
#define powerButton 0xFFA25D




///////////////////////////////////////////////////////////////////////////////////////////

// LEDS

uint8_t hue = 0;

#include <FastLED.h>
#define NUM_LEDS 22


#define DATA_PIN 5
#define CLOCK_PIN 13
#define ledColor Yellow
int delaySpeed = 80;
const unsigned long eventInterval = 1000;
unsigned long previousTime = 0;

   int timeTravel;
  int smoothChase;
  int movieChase;
  int movieSpeed = 34.45;
  int movieChaseSimple;
  int thirtyChase;
  int radChase;
  int radChase2;
  int rainbowChase;

// This is an array of leds.  One item for each led in your strip.
CRGB leds[NUM_LEDS];




///////////////////////////////////////////////////////////////////////////////////////////


void setup() {


  // Single LED
  pinMode(12, OUTPUT);

  // DFPlayer Setup
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);

  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true);
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.volume(29);  //Set volume value. From 0 to 30
  
  // STARTUP SOUND AND CHASE
  myDFPlayer.play(2);  //Play mp3 
  delay(600);
  radChase2 = 1;

  // End DFPLayer Setup

  // IR setup
  Serial.begin(9600);
  irrecv.enableIRIn(); //Start the receiver

  // LED Setup ///////////////////////////////////////////////////////

  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);  // GRB ordering is typical
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
  FastLED.clear();

}

void loop() {

 
  while (!irrecv.isIdle());  // if not idle, wait till complete

  if (irrecv.decode(&results)) { // if we have received an IR Signal
    Serial.println (results.value, HEX); // display HEX results

    if (results.value == 0xFFFFFFFF) {
      results.value = Previous;
    }
    switch (results.value) {

      case button_1:
      // time travel
        timeTravel = 1;
        smoothChase = 0;
        movieChase = 0;
        thirtyChase = 0;
        movieChaseSimple = 0;
        radChase = 0;
        radChase2 = 0;
        rainbowChase = 0;
        // set delay speed for time travel
        delaySpeed = 113;
        // play audio track 1
        myDFPlayer.playMp3Folder(1); //play specific mp3 in SD:/MP3/0004.mp3; File Name(0~65535)
        break;
      case powerButton:  smoothChase = 0; timeTravel = 0;
        myDFPlayer.stop();
        timeTravel = 0;
        thirtyChase = 0;
        smoothChase = 0;
        movieChase = 0;
        movieChaseSimple = 0;
        radChase = 0;
        radChase2 = 0;
        rainbowChase = 0;
        FastLED.clear();
        FastLED.show();
        break;
      case button_9:
        // stop current audio and play audio track
        myDFPlayer.stop();
        myDFPlayer.playMp3Folder(6);
        break;
      case button_2:
      // smooth chase
      // stop current audio and play audio track
        myDFPlayer.stop();
        myDFPlayer.playMp3Folder(3);
        timeTravel = 0;
        smoothChase = 1;
        movieChase = 0;
        movieChaseSimple = 0;
        thirtyChase = 0;
        radChase = 0;
        radChase2 = 0;
        rainbowChase = 0;
        delaySpeed = 80;
        Serial.println("button_2 Pressed. smoothChase:");
        break;
      case button_3:
      // thirty fps
      // stop current audio and play audio track
        myDFPlayer.stop();
        myDFPlayer.playMp3Folder(4);
          //set movie speed
        movieSpeed = 33.33;
        
        timeTravel = 0;
        smoothChase = 0;
        movieChase = 0;
        movieChaseSimple = 0;
        thirtyChase = 1;
        radChase = 0;
        radChase2 = 0;
        rainbowChase = 0;
        Serial.println("button_3 Pressed. 30fps");

        break;
      case button_4:
       // 24 fps
       //imitating 6 leds from film
       // stop current audio and play audio track
        myDFPlayer.stop();
        myDFPlayer.playMp3Folder(5);
        //set movie speed
        movieSpeed = 22.97;
        // set loop
        timeTravel = 0;
        thirtyChase = 0;
        smoothChase = 0;
        movieChase = 1;
        movieChaseSimple = 0;
        radChase = 0;
        radChase2 = 0;
        rainbowChase = 0;
        Serial.println("button_4 Pressed. Movie Chase 24fps");
        break;
      case button_5:
        //24 fps simple
        // stop current audio and play audio track
        myDFPlayer.stop();
        myDFPlayer.playMp3Folder(3);
        //set movie speed
        movieSpeed = 34.45;
        // set loop
        timeTravel = 0;
        thirtyChase = 0;
        smoothChase = 0;
        movieChase = 0;
        movieChaseSimple = 1;
        radChase = 0;
        radChase2 = 0;
        rainbowChase = 0;
        Serial.println("button_5 Pressed. 24FPS simple");
        break;
      case button_6:
        //Rad Chase
        // stop current audio and play audio track
        myDFPlayer.stop();
        myDFPlayer.playMp3Folder(4);
        //set movie speed
        movieSpeed = 66.66;
        // set loop
        timeTravel = 0;
        thirtyChase = 0;
        smoothChase = 0;
        movieChase = 0;
        movieChaseSimple = 0;
        radChase = 1;
        radChase2 = 0;
        rainbowChase = 0;
        break;
      case button_7:
        //Rad Chase
        // stop current audio and play audio track
        myDFPlayer.stop();
        myDFPlayer.playMp3Folder(5);
        //set movie speed
        movieSpeed = 66.66;
        // set loop
        timeTravel = 0;
        thirtyChase = 0;
        smoothChase = 0;
        movieChase = 0;
        movieChaseSimple = 0;
        radChase = 0;
        radChase2 = 1;
        rainbowChase = 0;
        break;
      case button_8:
        //Rainbow Chase
        // stop current audio and play audio track
        myDFPlayer.stop();
        myDFPlayer.playMp3Folder(5);
        //set movie speed
        movieSpeed = 66.66;
        // set loop
        timeTravel = 0;
        thirtyChase = 0;
        smoothChase = 0;
        movieChase = 0;
        movieChaseSimple = 0;
        radChase = 0;
        radChase2 = 0;
        rainbowChase = 1;
        break;
        // button up pressed, decrease delay timers - go faster
       case btnUp:

         if (movieSpeed > 24) {
           movieSpeed = movieSpeed - 10;
         }
         if (delaySpeed > 20) {
          delaySpeed = delaySpeed - 20;
         }
         // Smaller increments for delay speeds under 20
         if (delaySpeed <= 20 && delaySpeed > 4) {
          delaySpeed = delaySpeed - 4;
         }
        
        Serial.println("BtnUp pressed");
        Serial.println(movieSpeed);
        break;
        // button down pressed increase delays - go slower
       case btnDown:

         if (movieSpeed < 200) {
           movieSpeed = movieSpeed + 10;
         }
         if (delaySpeed < 160) {
          delaySpeed = delaySpeed + 20;
         }
        
        Serial.println("BtnDown pressed");
        Serial.println(movieSpeed);
        break;
    }
    
    while (!irrecv.isIdle());  // if not idle, wait till complete
      irrecv.resume(); // next value
    
  }



  // ----------------- SMOOTH CHASE ------------------------

  if (smoothChase == 1) {
    timeTravel = 0;

//    delaySpeed = 80;
    delay(100);

    // Move LEDS
    for (int i = 0; i < 16; i = i + 1) {

      if(i - 6 >= 0) {
        leds[i - 6] = CHSV(32, 128, 20);
        leds[10] = CRGB::Black;
        leds[11] = CRGB::Black;
        leds[12] = CRGB::Black;
        leds[13] = CRGB::Black;
        leds[14] = CRGB::Black;
        leds[15] = CRGB::Black;
      }
      if(i - 5 >= 0) {
        leds[i - 5] = CHSV(32, 128, 40);
        leds[10] = CRGB::Black;
        leds[11] = CRGB::Black;
        leds[12] = CRGB::Black;
        leds[13] = CRGB::Black;
        leds[14] = CRGB::Black;
        leds[15] = CRGB::Black;
      }
      if(i - 4 >= 0) {
        leds[i - 4] = CHSV(32, 128, 70);
        leds[10] = CRGB::Black;
        leds[11] = CRGB::Black;
        leds[12] = CRGB::Black;
        leds[13] = CRGB::Black;
        leds[14] = CRGB::Black;
        leds[15] = CRGB::Black;
      }
      if(i - 3 >= 0) {
        leds[i - 3] = CHSV(32, 128, 180);
        leds[10] = CRGB::Black;
        leds[11] = CRGB::Black;
        leds[12] = CRGB::Black;
        leds[13] = CRGB::Black;
        leds[14] = CRGB::Black;
        leds[15] = CRGB::Black;
      }
      if(i - 2 >= 0) {
        leds[i - 2] = CHSV(32, 128, 70);
        leds[10] = CRGB::Black;
        leds[11] = CRGB::Black;
        leds[12] = CRGB::Black;
        leds[13] = CRGB::Black;
        leds[14] = CRGB::Black;
        leds[15] = CRGB::Black;
      }
      if(i - 1 >= 0) {
        leds[i - 1] = CHSV(32, 128, 40);
        leds[10] = CRGB::Black;
        leds[11] = CRGB::Black;
        leds[12] = CRGB::Black;
        leds[13] = CRGB::Black;
        leds[14] = CRGB::Black;
        leds[15] = CRGB::Black;
      }
        leds[i] = CHSV(32, 128, 20);
        leds[10] = CRGB::Black;
        leds[11] = CRGB::Black;
        leds[12] = CRGB::Black;
        leds[13] = CRGB::Black;
        leds[14] = CRGB::Black;
        leds[15] = CRGB::Black;
        

      // Show the leds

      FastLED.show();
      
      delay(delaySpeed);
      FastLED.clear();
      FastLED.show();
      smoothChase = 1;
      timeTravel = 0;




    }

    
  }

    // ----------------- MOVIE CHASE - imitates 6 LEDs - matches 24fps speed from the movie------------------------

  if (movieChase == 1) {
    timeTravel = 0;
    smoothChase = 0;


    // Move LEDS
    for (int i = 0; i < 5; i = i + 1) {

      // LED 1
      if(i = 0) {
        leds[0] = CHSV(22, 200, 100);
        leds[1] = CHSV(22, 200, 100);
        
        FastLED.show();
        delay(movieSpeed);
        FastLED.clear();
      }
      // LED 2
      if(i = 1) {
        leds[1] = CHSV(22, 200, 100);
        leds[2] = CHSV(22, 200, 100);

        FastLED.show();
        delay(movieSpeed);
        FastLED.clear();
      }
      // LED 3
      if(i = 2) {
        leds[2] = CHSV(22, 200, 100);
        leds[3] = CHSV(22, 200, 100);
        FastLED.show();
        delay(movieSpeed);
        FastLED.clear();
      }
      // LED 4
      if(i = 3) {
        leds[4] = CHSV(22, 200, 15);
        leds[5] = CHSV(22, 200, 100);
        FastLED.show();
        delay(movieSpeed);
        FastLED.clear();
      }
      // LED 5
      if(i = 4) {
        leds[6] = CHSV(22, 200, 100);
        leds[7] = CHSV(22, 200, 100);
        FastLED.show();
        delay(movieSpeed);
        FastLED.clear();
      }
      // LED 6
      if(i = 5) {
        leds[8] = CHSV(22, 200, 100);
        leds[9] = CHSV(22, 200, 100);
        FastLED.show();
        delay(movieSpeed);
        FastLED.clear();
      }
        
      movieChase = 1;
      smoothChase = 0;
      timeTravel = 0;
    }
    
  }

  // ----------------- RAD CHASE ------------------------

  if (radChase == 1) {




    // Move LEDS
    for (int i = 0; i < 6; i = i + 1) {

      if(i = 1) {
        leds[0] = CHSV(28, 120, 100);
        leds[1] = CHSV(28, 120, 100);
        FastLED.show();
        delay(movieSpeed);
        FastLED.clear();
      }
      if(i = 2) {
        leds[2] = CHSV(28, 120, 100);
        leds[3] = CHSV(28, 120, 100);
        FastLED.show();
        delay(movieSpeed);
        FastLED.clear();
      }
      if(i = 3) {
        leds[4] = CHSV(28, 120, 100);
        leds[5] = CHSV(28, 120, 100);
        FastLED.show();
        delay(movieSpeed);
        FastLED.clear();
      }
      if(i = 4) {
        leds[6] = CHSV(28, 120, 100);
        leds[7] = CHSV(28, 120, 100);
        FastLED.show();
        delay(movieSpeed);
        FastLED.clear();
      }
      if(i = 5) {
        leds[8] = CHSV(28, 120, 100);
        leds[9] = CHSV(28, 120, 100);
        FastLED.show();
        delay(movieSpeed);
        FastLED.clear();
      }
        
      radChase = 1;

    }
    
  }


// ----------------- RAD CHASE 2------------------------

  if (radChase2 == 1) {




    // Move LEDS
    for (int i = 0; i < 10; i = i + 1) {

      if(i < 10) {
        leds[i] = CHSV(28, 200, 120);
        leds[i - 1] = CHSV(28, 200, 30);
        leds[i + 1] = CHSV(28, 200, 30);
        FastLED.show();
        delay(movieSpeed);
        FastLED.clear();
      }
        
      radChase2 = 1;

    }
    
  }

  // ----------------- MOVIE CHASE SIMPLE ------------------------

  if (movieChaseSimple == 1) {

    


    // Move LEDS
    for (int i = 0; i < 5; i = i + 1) {

      if(i = 1) {
        leds[2] = CHSV(22, 200, 100);
        FastLED.show();
        delay(movieSpeed);
        FastLED.clear();
      }
      if(i = 2) {
        leds[4] = CHSV(22, 200, 100);
        FastLED.show();
        delay(movieSpeed);
        FastLED.clear();
      }
      if(i = 3) {
        leds[6] = CHSV(22, 200, 100);
        FastLED.show();
        delay(movieSpeed);
        FastLED.clear();
      }
      if(i = 4) {
        leds[8] = CHSV(22, 200, 100);
        FastLED.show();
        delay(movieSpeed);
        FastLED.clear();
      }
        
      movieChaseSimple = 1;

    }
    
  }

   // ----------------- THIRTY FPS CHASE - For shooting at 30fps------------------------

  if (thirtyChase == 1) {

    // Move LEDS
    for (int i = 0; i < 5; i = i + 1) {

      if(i = 1) {
        leds[0] = CHSV(32, 128, 100);
        leds[1] = CHSV(32, 128, 100);
        leds[2] = CHSV(32, 128, 15);
        FastLED.show();
        delay(movieSpeed);
        FastLED.clear();
      }
      if(i = 2) {
        leds[2] = CHSV(32, 128, 15);
        leds[3] = CHSV(32, 128, 100);
        leds[4] = CHSV(32, 128, 100);
        FastLED.show();
        delay(movieSpeed);
        FastLED.clear();
      }
      if(i = 3) {
        leds[5] = CHSV(32, 128, 100);
        leds[6] = CHSV(32, 128, 100);
        leds[7] = CHSV(32, 128, 15);
        FastLED.show();
        delay(movieSpeed);
        FastLED.clear();
      }
      if(i = 4) {
        leds[7] = CHSV(32, 128, 15);
        leds[8] = CHSV(32, 128, 100);
        leds[9] = CHSV(32, 128, 100);
        FastLED.show();
        delay(movieSpeed);
        FastLED.clear();
      }
        
      thirtyChase = 1;

    }
    
  }


  // ----------------- TimeTravel ------------------------

  if (timeTravel == 1) {

    unsigned long currentTime = millis();


    // Move LEDS
    for (int i = 0; i < 20; i = i + 1) {

      if (i - 6 >= 0) {
        leds[i - 6] = CHSV(28, 150, 60);
      }
      if (i - 5 >= 0) {
        leds[i - 5] = CHSV(28, 150, 100);
      }
      if (i - 4 >= 0) {
        leds[i - 4] = CHSV(28, 150, 160);
      }
      if (i - 3 >= 0) {
        leds[i - 3] = CHSV(28, 150, 220);
      }
      if (i - 2 >= 0) {
        leds[i - 2] = CHSV(28, 150, 160);
      }
      if (i - 1 >= 0) {
        leds[i - 1] = CHSV(28, 150, 100);
      }
      leds[i] = CHSV(28, 200, 60);
      leds[10] = CRGB::Black;
      leds[11] = CRGB::Black;
      leds[12] = CRGB::Black;
      leds[13] = CRGB::Black;
      leds[14] = CRGB::Black;
      leds[15] = CRGB::Black;
      leds[16] = CRGB::Black;
      leds[17] = CRGB::Black;
      leds[18] = CRGB::Black;
      leds[19] = CRGB::Black;
      leds[20] = CRGB::Black;


      // Show the leds

      FastLED.show();

      FastLED.clear();
      timeTravel = 1;

      // Wait a little bit
      delay(delaySpeed);

    }

    // Reduce delay time so each sequence is faster than the last
    delaySpeed = delaySpeed * .837;

    if (delaySpeed < 1) {
      // leds[5] = CRGB::Black;

      previousTime = millis();

      
              if (millis() < previousTime + 4000) {
                // ZIIIP!  Moment of time travel
                
                digitalWrite(12, HIGH);
                for(int y = 0; y < 22; y++) {
                leds[y] = CRGB::Blue;
                FastLED.show();
                }
                
                delay(3300);
                FastLED.clear();
                FastLED.show();
//                for(int x = 0; x < 9; x++) {
//                leds[x] = CRGB::Black;
//                FastLED.show();
//                }
                // Single LED
                digitalWrite(12, LOW);
                // Delay after blue light
                delay(850);

      // First Burst
      for (int i = 0; i < 10; i++) {
        leds[i] = CHSV(28, 110, 120);
        leds[10] = CRGB::Blue;
        leds[11] = CRGB::Blue;
        leds[12] = CRGB::Blue;
        leds[13] = CRGB::Blue;
        leds[14] = CRGB::Blue;
        leds[15] = CRGB::Blue;
        leds[16] = CRGB::Blue;
        leds[17] = CRGB::Blue;
        leds[18] = CRGB::Blue;
        leds[19] = CRGB::Blue;
        leds[20] = CRGB::Blue;
        leds[21] = CRGB::Blue;
        
       FastLED.show();
      }
     
      // Single LED
      digitalWrite(12, HIGH);
      delay(300);
      FastLED.clear();
      FastLED.show();
      // Single LED
      digitalWrite(12, LOW);
      delay(400);

      // Second Burst
      for (int i = 0; i < 21; i++) {
        leds[i] = CHSV(28, 110, 120);
        leds[10] = CRGB::Blue;
        leds[11] = CRGB::Blue;
        leds[12] = CRGB::Blue;
        leds[13] = CRGB::Blue;
        leds[14] = CRGB::Blue;
        leds[15] = CRGB::Blue;
        leds[16] = CRGB::Blue;
        leds[17] = CRGB::Blue;
        leds[18] = CRGB::Blue;
        leds[19] = CRGB::Blue;
        leds[20] = CRGB::Blue;
        leds[21] = CRGB::Blue;
        FastLED.show();
      }
      // Single LED
      digitalWrite(12, HIGH);
      delay(1000);
      delaySpeed = 80;
      timeTravel = 0;
      smoothChase = 1;
      FastLED.clear();
      FastLED.show();
      // Single LED
      digitalWrite(12, LOW);
      //          chase();
      //          exit(0);
      //          reset();



              }

    }


  } 

  // ------------ END timeTravel --------------------



// ----------------- RAINBOW CHASE ------------------------

  if (rainbowChase == 1) {

  
      for (int i = 0; i < 10; i++) {
        leds[i] = CHSV(hue + (i * 10), 255, 150);
      }
      for (int y = 10; y > 9 && y < 22; ++y) {
        leds[y] = CHSV(hue + (y * 10), 255, 250);
      }
    
      //You can change the pattern speed here
      EVERY_N_MILLISECONDS(1){
        hue++;
      }
      
      FastLED.show();
      rainbowChase = 1;
    }

}
