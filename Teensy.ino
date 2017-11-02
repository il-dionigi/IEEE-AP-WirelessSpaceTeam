#include <RF24.h>

#define COM_CHANNEL 10

#define CEPIN   9
#define CSPIN   10
#define SCK     13
#define MOSI    11
#define MISO    12

#define TEENSY_WRITE 0xE7E7E7E7E7
#define ARDUINO_WRITE 0xC2C2C2C2C2

bool transmitted = false;
bool received  = false;
char testWriteA = '$';
char testWriteT = '&';

void setup() {
  // Initializing Radio
  RF24 radioT(CEPIN, CSPIN);
  radioT.begin();

  // Set communication channel
  radioT.setChannel(COM_CHANNEL);
  radioT.setPALevel(RF24_PA_MIN);

    // Set R/W Pipes - Make helper to reopen every time?
  radioT.openReadingPipe(1, ARDUINO_WRITE);
  radioT.openWritingPipe(TEENSY_WRITE);

  radioT.setCRCLength(RF24_CRC_16);
  
  Serial.begin(9600);
}

void loop() {
  
  // Start listening
  radioT.startListening();

  if (!received)
  {
    int msgSize = 0;
    char msg[]="";
      
    msgSize = radioT.getDynamicPayloadSize();
    if (msgSize > 0) {
      radioT.read( &msg, msgSize );
      if (msg == testWriteA)
      {
        Serial.print("Teensy successfully read");
        received = true;
      }
    } 
  }
  else if (!transmitted)
  { // Test Teensy
      radioT.stopListening();
      radioT.write(&testWriteT, sizeof(testWriteT));
      if (radioT.available())
      {
        Serial.print("Teensy successfully wrote");
        transmitted = true;
      }
      radioT.startListening();
  }
}
