#include <avr/sleep.h>
#include <SdFat.h>
#include <TMRpcm.h>
#include <SPI.h>
//#include <SD.h>

#define SD_ChipSelectPin 10  //use digital pin 4 on arduino Uno, nano etc, or can use other pins
//#define CHIP_SELECT_PIN  10
#define SPEAKER_PIN      9
#define RAIL_EN 2   // Mosfet Gate Pin

SdFat sd;
TMRpcm tmrpcm;

void setup() {
  pinMode(RAIL_EN, OUTPUT);   //enables 5V Rail for Peripherie
  pinMode(LED_BUILTIN, OUTPUT);
  set_sleep_mode (SLEEP_MODE_PWR_DOWN);  
  sleep_enable();
  ADCSRA = 0;  // disable ADC
  tmrpcm.speakerPin = SPEAKER_PIN;
  Serial.begin(9600);
  Serial.println("\n\n--- Svenpanel ---");
  

  digitalWrite(RAIL_EN, LOW);   // enable Rail
  
  Serial.print("Initializing SD card...");
  
  if ( !sd.begin(SD_ChipSelectPin, SPI_FULL_SPEED) ) {
    Serial.println("Failed!");
  }
  else{
    Serial.println("Done.");
    if (sd.exists("001.wav")) {
      Serial.println("001.wav exists, attempt to play");
      //tmrpcm.setVolume(6);    //1-7
      tmrpcm.play( "001.wav" );
      while(tmrpcm.isPlaying()){
        delay(1);
      }
      tmrpcm.disable();
      /*File myFile = SD.open("001.wav");
      if (myFile) {
      }
      else{
        Serial.println("error opening test.wav");
      }
      myFile.close();*/
      
    } else {
      Serial.println("001.wav doesn't exist.");
    }
  }
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(2000);
  Serial.println("going to sleep");
  delay(100);
  digitalWrite(RAIL_EN, HIGH);
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  sleep_cpu ();
}
