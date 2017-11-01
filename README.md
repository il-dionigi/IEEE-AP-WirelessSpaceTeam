
**See http://tmrh20.github.io/RF24 for all documentation**

**
1.	Initialize Radio w/Constructor + CE & CSN Pins
	
	F24::RF24(	uint8_t _cepin,
				uint8_t _cspin 
	)		
	Arduino Constructor

	Creates a new instance of this driver. Before using, you create an instance and send in the unique pins that this chip is connected to.

	Parameters
	_cepin	The pin attached to Chip Enable on the RF module
	_cspin	The pin attached to Chip Select

2.	Begin Function

	bool RF24::begin ( void )	
	Begin operation of the chip

	Call this in setup(), before calling any other methods.

3.	Set Communication Channel
	
	void setChannel (uint8_t channel)

4.	Set Power Amplifier level to RF24_PA_MIN

	void RF24::setPALevel ( uint8_t level )	

	Set Power Amplifier (PA) level to one of four levels: RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH and RF24_PA_MAX

	The power levels correspond to the following output levels respectively: NRF24L01: -18dBm, -12dBm,-6dBM, and 0dBm

	SI24R1: -6dBm, 0dBm, 3dBM, and 7dBm.

5.	Set R/W Pipes (Reading Pipe of Tx matches Writing Pipe of Rx & viceversa)
	
	void RF24::openReadingPipe ( uint8_t number,
	const uint8_t * address 
	)		

	Up to 6 pipes can be open for reading at once. Open all the required reading pipes, and then call startListening().

	Pipes 0 and 1 will store a full 5-byte address. Pipes 2-5 will technically only store a single byte, borrowing up to 4 additional bytes from pipe #1 per the assigned address width.

	Parameters
	number:	Which pipe# to open, 0-5.
	address:	The 24, 32 or 40 bit address of the pipe to open.

	void RF24::openWritingPipe ( const uint8_t * address )	

	Open a pipe for writing via byte array. Old addressing format retained for compatibility.

	Only one writing pipe can be open at once, but you can change the address you'll write to. Call stopListening() first.

	Addresses are assigned via a byte array, default is 5 byte address length s *

6.	CRCL Length to RF24_CRC_16 (Can be 1|2 bytes)

	void RF24::setCRCLength ( rf24_crclength_e length )	
	CRC checking cannot be disabled if auto-ack is enabled

	Parameters
	length:	RF24_CRC_8 for 8-bit or RF24_CRC_16 for 16-bit

7.	In Loop, Begin Listening

	void RF24::startListening ( void )	
	Start listening on the pipes opened for reading.

	Be sure to call openReadingPipe() first.
	Do not call write() while in this mode, without first calling stopListening()
	call available() to check for incoming traffic =, and read() to get it.

8.	In Loop, Call Available Funct when Bytes to be Read

	bool RF24::available ( void )	
	Check whether there are bytes available to be read

	true if there is a payload, else false

9.	In Loop, Stop Listening when Bytes Transmited & Received

	void RF24::stopListening ( void )	
	Stop listening for incoming messages, and switch to transmit mode.

	Do this before calling write().