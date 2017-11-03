//Teensy Code

#include <stdlib.h>
#include "RF24.h"
#include "nRF24L01.h"

// pins to digitalWrite() to
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

const RF24* radioT;
string series = "";
uint8_t len = 0;

setup() {
  *radioT = RF24(CEPIN, CSPIN); // initialize
  radioT->begin();  //begin
  radioT->setChannel(COM_CHANNEL);  //set unique channel for communication
  radioT->setPALevel(RF24_PA_MIN);
  // open reading pipe 1 @ address given
  // Reads from registers in arduino to pipe
  // Teensy will write its registers from this pipe at this 
  // address using radio.openWriting(ARDUINO_WRITE)
  radioT->openWritingPipe(TEENSY_WRITE);
  radioT->openReadingPipe(1, ARDUINO_WRITE);
  radioT->setCRCLength(RF24_CRC_16);

  Serial.begin(9600);
}

loop() {
  char newChar = colors[random(0, 2)];
  series += newChar;
  len++;

  //  display series with leds
  int i = 0;
  for (; i < len; i++) {
    digitalWrite(series[i], HIGH);
    delay(333);
    digitalWrite(series[i], LOW);
  }

  //  write newChar to arduino write( const void* buf, uint8_t len );
  radioT.write(&newChar, 1);

  //  read signal from arduino
  radioT->startListening();
  while (!radioT->available()) {} // stop loop until bytes available to read

  char result = 0;
  radioT->read(&result, 1); // read 1 byte (will be 1 or 0) into result
  radioT->stopListening();

  //  if good, flash green and continue, else flash red and terminate exit(1)  
  if (result) {
    digitalWrite(R, HIGH);
    delay(2000);
    digitalWrite(R, LOW);
    exit(1);
  }

  digitalWrite(G, HIGH);
  delay(2500);
  digitalWrite(G, LOW);   

}
