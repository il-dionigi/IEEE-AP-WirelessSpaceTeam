//Arduino Code

#include <stdlib.h>
#include "RF24.h"
#include "nRF24L01.h"

#define BUTTON_R 4
#define BUTTON_Y 3
#define BUTTON_G 2

// pins for Teensy to digitalWrite() to
#define R 19 
#define Y 18
#define G 17

#define CEPIN   9
#define CSPIN   10
#define SCK     13
#define MOSI    11
#define MISO    12

#define COM_CHANNEL 10
#define TEENSY_WRITE 0xE7E7E7E7E7
#define ARDUINO_WRITE 0xC2C2C2C2C2

const char colors[] = {R, Y, G};

RF24 radioA = RF24(CEPIN, CSPIN); // initialize
String series = "";
uint8_t len = 0;

void setup() {
  pinmode(BUTTON_G, INPUT);
  pinmode(BUTTON_Y, INPUT);
  pinmode(BUTTON_R, INPUT);

  radioA.begin();  //begin
  radioA.setChannel(COM_CHANNEL);  //set unique channel for communication
  radioA.setPALevel(RF24_PA_MIN);
  radioA.openWritingPipe(ARDUINO_WRITE);
  radioA.openReadingPipe(1, TEENSY_WRITE);
  radioA.setCRCLength(RF24_CRC_16);

  Serial.begin(9600);
}

void loop() {
  // stop loop until bytes available to read
  radioA.startListening();
  while (!radioA.available()) {}
  
  // read byte from teensy
  char newChar;
  radioA.read(&newChar, 1);
  radioA.stopListening();

  series += newChar;

  // check button presses
  
  char state[] = {0, 0, 0};  // red, yellow, green
  uint8_t stateIcr = 0;

  String input = "";
  uint8_t count = 0;
  char eval = 1;
  while (eval && (len - count)) {

    for (stateIcr = 0; stateIcr < 3, stateIcr++) {
      char currState = digitalRead(4 - stateIcr);

      if (state[stateIcr] > currState) {
      	 input += colors[stateIcr];
	 count++;
      }
      state[stateIcr] = currState;
    }
    if (input[count] != series[count])
      eval = 0;
  }
  radioA.write(&eval, 1);
}
