# Wireless Space Team
*03 November 2017*

This project concerns creating a wireless variance of the [Space Team](https://play.google.com/store/apps/details?id=com.sleepingbeastgames.spaceteam) game by communicating between two microcontrollers using SPI methods with the Nordic NRF24l01P modules.
  
Using the Teensy as the slave and the Arduino as the master, the Teensy starts the game by randomly choosing a red, green, or blue LED to flash and relay the pattern wirelessly to the Arduino. The player has to press the buttons corresponding to the pattern which the Arduino then checks for accuracy. On the correct combination, the Arduino sends a success message to the Teensy which then chooses another random LED to add to the current pattern and transmit to the Arduino. This continues, the Teensy gradually increasing the length of the pattern, until the player errs and the game is over.

The spec for this project can be found in [spec.pdf](https://github.com/il-dionigi/IEEE_AP_WirelessSpaceTeam_RF24/blob/master/spec.pdf) and the final Arduino and Teensy codes are within the respective folders entitled [arduinoFinal](https://github.com/il-dionigi/IEEE_AP_WirelessSpaceTeam_RF24/tree/master/arduinoFinal) and [teensyFinal](https://github.com/il-dionigi/IEEE_AP_WirelessSpaceTeam_RF24/tree/master/teensyFinal). 
The files [nRF24L01.h](https://github.com/il-dionigi/IEEE_AP_WirelessSpaceTeam_RF24/blob/master/nRF24L01.h) and [RF24.cpp](https://github.com/il-dionigi/IEEE_AP_WirelessSpaceTeam_RF24/blob/master/RF24.cpp) accordingly contain the registers and methods for the SRI protocol which our team had to figure out ourselves. The rest of the files were contributed by  Stefan Engelke <mbox@stefanengelke.de>, J. Coliz <maniacbug@ymail.com>, and the IEEE AP project leads. 
  
**Collaborators:**  
[Brian Dionigi](https://github.com/il-dionigi) | [Kevin Ke-En Sun](https://github.com/inherentlyMalicious) | [Koji Kusumi](https://github.com/kojiboji) | [Rob Griffith](https://github.com/rwgriffithv)