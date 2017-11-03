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
char arr[] = "kojiboji";
char testWriteT = '&';
RF24 radioT(CEPIN, CSPIN);

void setup() {
  // Initializing Radio
  
  radioT.begin();

  // Set communication channel
  radioT.setChannel(COM_CHANNEL);
  radioT.setPALevel(RF24_PA_MIN);

    // Set R/W Pipes - Make helper to reopen every time?
  radioT.openReadingPipe(1, ARDUINO_WRITE);
  radioT.openWritingPipe(TEENSY_WRITE);

  radioT.setCRCLength(RF24_CRC_16);
  
  Serial.begin(9600);
  Serial.println("Hello Teensy");
}

void loop() {
  
  // Start listening
  //radioT.startListening();

 /* if (!received)
  {
    int msgSize = 0;
    char msg[]="";
      
    msgSize = radioT.getDynamicPayloadSize();
    if (msgSize > 0) {
      radioT.read( &msg, msgSize );
      if (msg[0] == testWriteA)
      {
        Serial.print("Teensy successfully read");
        received = true;
      }
    } 
  }*/
     /*//radioT.stopListening();
      radioT.write(&testWriteT, sizeof(testWriteT));
      //if (radioT.available())
      //{
        Serial.println("Teensy successfully wrote");
        Serial.println(sizeof(testWriteT));
        //transmitted = true;
      //}
*/
      //if(!transmitted)
      //{
        radioT.write(&arr, sizeof(arr));
        Serial.println("Teensy successfully wrote");
        Serial.println(sizeof(testWriteT));
        //transmitted = true;
      //}
  
}
