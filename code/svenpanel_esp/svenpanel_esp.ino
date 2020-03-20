#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "AudioFileSourceSD.h"
#include "AudioOutputI2SNoDAC.h"
//#include "AudioGeneratorFLAC.h"
#include "AudioGeneratorMP3.h"
//#include "AudioGeneratorWAV.h"

// You may need a fast SD card. Set this as high as it will work (40MHz max).
#define SPI_SPEED SD_SCK_MHZ(20)

#define SS D0   // Chip Select SD Card

File dir;
AudioFileSourceSD *source = NULL;
AudioOutputI2SNoDAC *output = NULL;
AudioGeneratorMP3 *decoder = NULL;

void setup() {
  WiFi.mode(WIFI_OFF);
  WiFi.forceSleepBegin();
  Serial.begin(115200);
  Serial.println();
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
  delay(1000);

  audioLogger = &Serial;  
  source = new AudioFileSourceSD();
//  output = new AudioOutputI2SNoDAC();
  //decoder = new AudioGeneratorFLAC();
//  decoder = new AudioGeneratorMP3();
  //decoder = new AudioGeneratorWAV();

  SD.begin(SS, SPI_SPEED);  //TODO: add if
  dir = SD.open("/");
  digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
}

void loop() {
  ESP.deepSleep(0);

/*  
 if ((decoder) && (decoder->isRunning())) {
    if (!decoder->loop()) decoder->stop();
  } else {
    File file = dir.openNextFile();
    if (file) {      
      if (String(file.name()).endsWith(".mp3")) {
        source->close();
        if (source->open(file.name())) { 
          Serial.printf_P(PSTR("Playing '%s' from SD card...\n"), file.name());
          decoder->begin(source, output);
        } else {
          Serial.printf_P(PSTR("Error opening '%s'\n"), file.name());
        }
      } 
    } else {
      Serial.println(F("Playback form SD card done\n"));
      
      delay(1000);
    }       
  }*/
}
