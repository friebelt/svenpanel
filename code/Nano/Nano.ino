#include <avr/sleep.h>
#include <SdFat.h>
#include <TMRpcm.h>
#include <SPI.h>
//#include <SD.h>

#define SD_ChipSelectPin 10  //use digital pin 4 on arduino Uno, nano etc, or can use other pins
//#define CHIP_SELECT_PIN  10
#define SPEAKER_PIN      9
#define RAIL_EN 3   // Mosfet Gate Pin
#define SERIALIZER_INT 2
#define SERIALIZER_PS 4
#define SERIALIZER_CLK 5
#define SERIALIZER_OUT 6
#define SERIALIZER_FREQ 1   // in ns

#define BTN01 19
#define BTN02 18
#define BTN03 17
#define BTN04 16
#define BTN05 20
#define BTN06 21
#define BTN07 -1
#define BTN08 -1

#define BTN09 11
#define BTN10 10
#define BTN11 9
#define BTN12 8
#define BTN13 12
#define BTN14 13
#define BTN15 14
#define BTN16 15

#define BTN17 4
#define BTN18 3
#define BTN19 2
#define BTN20 1
#define BTN21 5
#define BTN22 6
#define BTN23 7
#define BTN24 -1


SdFat sd;
TMRpcm tmrpcm;

void pin2Interrupt(void)
{
  /* This will bring us back from sleep. */
  
  /* We detach the interrupt to stop it from 
   * continuously firing while the interrupt pin
   * is low.
   */
  detachInterrupt(0);
}


void setup() {
  // declare Intputs
  pinMode(SERIALIZER_INT, INPUT);
  pinMode(SERIALIZER_OUT, INPUT);

  // declare Outputs
  pinMode(RAIL_EN, OUTPUT);   //enables 5V Rail for Peripherie
  pinMode(SERIALIZER_CLK, OUTPUT);
  pinMode(SERIALIZER_PS, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  
  set_sleep_mode (SLEEP_MODE_PWR_DOWN);  
  sleep_enable();
  ADCSRA = 0;  // disable ADC to safe energy
  
  tmrpcm.speakerPin = SPEAKER_PIN;
  //tmrpcm.setVolume(6);    //1-7
  Serial.begin(9600);
  Serial.println();
  Serial.println();
  Serial.println("--- Svenpanel ---");
  

  digitalWrite(RAIL_EN, LOW);   // enable Rail

  attachInterrupt(digitalPinToInterrupt(SERIALIZER_INT), blablub, HIGH);
} // end setup()


// the loop function runs over and over again forever
void loop() {
  digitalWrite(RAIL_EN, LOW);    // enable power for peripherie
  int btn_num = poll_serializer();
  delay(20);  // give the rail a sec to build up voltage
  if (btn_num >= 0){
    String file_name(btn_num);
    file_name = file_name + ".wav";
    Serial.print("try to play file: ");
    Serial.println(file_name);
    if ( sd.begin(SD_ChipSelectPin, SPI_FULL_SPEED) ) {
      if ( sd.exists(file_name.c_str()) ) {
        tmrpcm.play( file_name.c_str() );
        while(tmrpcm.isPlaying()){
        delay(1);
        }
        tmrpcm.disable();
      }
      else{
        Serial.println("file does not exist on SD Card");
      }
    }
    else{
      Serial.println("Failed to initialize SD!");
    }
  }

  Serial.println("going to sleep");
  Serial.println();
  digitalWrite(RAIL_EN, HIGH);    // disable power for peripherie
  delay(100);

  sleep_cpu ();
}

void blablub(){
  //detachInterrupt(digitalPinToInterrupt(SERIALIZER_INT));
  Serial.println("interrrupt!");
}
