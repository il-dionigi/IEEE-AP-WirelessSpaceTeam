#include <RF24.h>

#define BUTTON1 2
#define BUTTON2 3
#define BUTTON3 4

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
  // put your setup code here, to run once:
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
  pinMode(BUTTON3, INPUT);

  // Initializing Radio
  RF24::RF24 radioA(CEPIN, CSPIN);
  radioA.begin();

  // Set communication channel
  radioA.setChannel(COM_CHANNEL);
  radioA.setPALevel(RF24_PA_MIN);

  // Set R/W Pipes - Make helper to reopen every time?
  radioA.openReadingPipe(1, TEENSY_WRITE);
  radioA.openWritingPipe(ARDUINO_WRITE);

  radioA.setCRCLength(RF24_CRC_16);
  
  //Serial.begin(9600);
}

void loop() {
  
  // Start listening
  radioA.startListening();

  if (!transmitted)
  { // Test arduino
      radioA.stopListening();
      radioA.write(&testWriteA, sizeof(testWriteA));
      if (radioA.available())
      {
        Serial.print("Arduino successfully wrote");
        transmitted = true;
      }
      radioA.startListening();
  } else if (!received)
  {
    int msgSize = 0;
    char msg[]="";
      
    msgSize = radio.getDynamicPayloadSize();
    if (msgSize > 0) {
      radioA.read( &msg, msgSize );
      if (msg == testWriteB)
      {
        Serial.print("Arduino successfully read");
        received = true;
      }
    } 
  }
}
