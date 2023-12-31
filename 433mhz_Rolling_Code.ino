/*
    Name:         qiachip 433mhz_Rolling_Code.ino
    Created:	    28/12/2023 15:01:03
    Author:       Bionicbone
    MCU:          Arduino Nano   (powered with 5v)
    qiachip parts:TX-118S-4 v2 & RX480E   (powered with 5v)
                  TX Pin 1 --> Nano D6    <-- looks strange but TX / RX has illogical pins orders :( 
                  TX Pin 2 --> Nano D7    <-- looks strange but TX / RX has illogical pins orders :(
                  TX Pin 3 --> Nano D5
                  TX Pin 4 --> Nano D4
                  RX Pin D0 --> Nano D4
                  RX Pin D1 --> Nano D5
                  RX Pin D2 --> Nano D6
                  RX Pin D3 --> Nano D7
                  RX Pin VT --> Nano D2
    Resistors:    Only required if using random number generator, any values connected, one from 5v to pin A0 and one from GND to pin A0 for voltage divider (random seed)
    Button:       Button to ground Tx Nano Pin D2 when pressed, to transmit data
*/

// Uncomment MODE line to flash Tx, comment to flash Rx
//#define MODE

// Uncomment RANDOM_NUMBERS line to create a list of random numbers over serial monitor.
// NOTE: connect any value but different value resistors to A0 as voltage dividor to create a random seed otherwise numbers will be default NANO random numbers.
//#define RANDOM_NUMBERS

// user can change the rolling code values (1-15 inc.), but must ensure Tx and Rx have the same order, length must be divisable by sizeofSendingRollingCode
uint8_t rollingCode[1400] = { 5, 9, 12, 15, 11, 4, 7, 3, 6, 2, 6, 12, 15, 7, 11, 9, 5, 14, 7, 12, 9, 12, 5, 10, 5, 6, 8, 12, 3, 2, 12, 1, 5, 4, 5, 14, 5, 7, 14, 8, 11, 2, 7, 5, 9, 4, 8, 6, 4, 13, 15, 4, 13, 4, 10, 6, 5, 8, 1, 14, 5, 9, 5, 9, 10, 7, 2, 2, 13, 6, 14, 8, 8, 8, 8, 8, 8, 11, 12, 1, 3, 13, 11, 12, 2, 2, 13, 8, 8, 12, 1, 13, 13, 14, 3, 5, 3, 4, 9, 15, 11, 1, 8, 7, 15, 2, 15, 11, 15, 5, 2, 10, 5, 3, 10, 7, 14, 4, 14, 1, 3, 2, 13, 1, 10, 8, 10, 6, 5, 11, 3, 12, 14, 3, 1, 3, 7, 2, 1, 6, 9, 7, 15, 3, 13, 11, 10, 5, 11, 14, 14, 9, 3, 7, 5, 15, 6, 8, 15, 4, 13, 3, 4, 15, 10, 1, 3, 8, 14, 10, 5, 14, 2, 8, 13, 5, 9, 15, 13, 7, 7, 2, 14, 2, 6, 6, 11, 11, 7, 13, 14, 8, 3, 14, 13, 1, 6, 12, 3, 2, 4, 12, 2, 2, 7, 9, 8, 7, 7, 8, 6, 3, 8, 8, 7, 4, 12, 2, 12, 12, 4, 3, 14, 7, 7, 9, 4, 10, 14, 7, 8, 7, 11, 8, 7, 3, 2, 7, 2, 6, 5, 8, 8, 3, 9, 10, 3, 7, 3, 11, 1, 9, 3, 8, 2, 8, 15, 12, 5, 6, 5, 5, 15, 6, 7, 9, 8, 10, 6, 5, 10, 15, 12, 14, 15, 4, 14, 9, 4, 13, 8, 9, 8, 8, 12, 12, 4, 11, 11, 5, 9, 11, 2, 13, 13, 14, 14, 5, 5, 1, 3, 2, 12, 1, 15, 14, 15, 14, 9, 4, 9, 15, 10, 6, 2, 6, 13, 3, 2, 14, 4, 11, 12, 7, 7, 12, 11, 13, 2, 7, 5, 12, 6, 11, 1, 10, 12, 14, 6, 3, 11, 1, 15, 2, 6, 13, 2, 2, 9, 15, 12, 13, 14, 4, 7, 5, 15, 8, 10, 12, 14, 5, 4, 11, 12, 2, 1, 11, 4, 13, 15, 3, 2, 2, 14, 1, 6, 9, 6, 4, 6, 5, 1, 14, 10, 10, 10, 15, 14, 8, 4, 10, 3, 3, 6, 11, 9, 15, 11, 12, 11, 12, 8, 5, 11, 8, 10, 8, 7, 3, 13, 4, 12, 3, 15, 10, 15, 11, 15, 15, 5, 5, 6, 7, 12, 3, 2, 13, 3, 7, 15, 9, 1, 13, 11, 6, 15, 5, 14, 13, 5, 13, 10, 3, 15, 11, 8, 14, 1, 6, 12, 2, 11, 12, 15, 14, 8, 9, 8, 13, 2, 10, 2, 4, 6, 6, 12, 13, 7, 8, 10, 1, 3, 14, 7, 4, 14, 13, 5, 2, 4, 10, 7, 1, 12, 3, 8, 1, 6, 10, 1, 15, 8, 15, 1, 9, 2, 12, 13, 2, 1, 13, 15, 15, 8, 15, 9, 8, 14, 14, 12, 8, 13, 3, 4, 14, 13, 1, 8, 10, 2, 9, 6, 1, 15, 2, 12, 4, 8, 5, 3, 2, 5, 4, 15, 12, 11, 7, 2, 4, 10, 6, 1, 8, 7, 12, 8, 11, 3, 6, 8, 15, 9, 9, 2, 2, 9, 13, 2, 2, 7, 5, 11, 6, 6, 13, 15, 14, 5, 6, 2, 14, 14, 2, 3, 14, 9, 3, 15, 9, 6, 8, 15, 9, 6, 8, 4, 6, 10, 1, 12, 14, 9, 13, 15, 1, 12, 9, 9, 14, 2, 13, 13, 4, 10, 2, 3, 2, 1, 5, 15, 2, 8, 12, 7, 4, 15, 14, 8, 5, 1, 14, 13, 2, 6, 9, 15, 12, 8, 3, 7, 13, 1, 4, 13, 5, 3, 14, 12, 15, 10, 12, 15, 12, 13, 10, 8, 2, 12, 10, 5, 13, 14, 14, 10, 10, 4, 8, 11, 10, 15, 15, 14, 1, 15, 11, 14, 11, 10, 4, 14, 2, 9, 14, 9, 7, 8, 12, 10, 13, 14, 15, 15, 4, 12, 9, 13, 14, 13, 5, 11, 4, 9, 10, 7, 5, 10, 4, 10, 12, 13, 14, 12, 7, 11, 7, 5, 11, 1, 4, 4, 11, 15, 8, 2, 12, 4, 10, 3, 11, 12, 7, 7, 14, 7, 7, 9, 9, 4, 13, 15, 14, 13, 2, 9, 9, 14, 5, 13, 13, 11, 3, 15, 3, 15, 12, 10, 13, 15, 5, 12, 3, 7, 12, 14, 8, 5, 1, 1, 11, 8, 11, 14, 10, 8, 11, 7, 13, 1, 14, 10, 6, 11, 15, 2, 10, 11, 9, 1, 7, 1, 4, 12, 4, 10, 14, 3, 4, 12, 6, 8, 4, 7, 14, 4, 4, 5, 7, 4, 2, 7, 4, 6, 4, 5, 4, 10, 12, 14, 3, 6, 11, 7, 13, 10, 8, 1, 1, 1, 14, 4, 11, 14, 6, 8, 14, 7, 8, 15, 7, 9, 7, 11, 9, 11, 10, 3, 2, 15, 13, 1, 4, 15, 15, 13, 12, 13, 14, 8, 2, 7, 6, 3, 4, 12, 13, 6, 2, 3, 9, 14, 7, 15, 5, 9, 13, 11, 9, 6, 10, 13, 9, 7, 3, 5, 12, 4, 11, 5, 13, 6, 12, 13, 4, 2, 12, 6, 10, 2, 10, 10, 15, 11, 3, 13, 15, 3, 5, 15, 3, 4, 1, 2, 10, 8, 10, 12, 15, 9, 1, 11, 5, 6, 1, 11, 13, 3, 3, 7, 2, 10, 6, 13, 3, 6, 14, 1, 3, 4, 14, 8, 9, 14, 6, 12, 7, 14, 4, 1, 1, 9, 15, 11, 13, 15, 14, 3, 12, 6, 1, 3, 10, 6, 13, 7, 15, 10, 6, 7, 3, 11, 9, 1, 2, 15, 8, 12, 12, 3, 10, 2, 1, 4, 8, 10, 2, 8, 6, 15, 10, 11, 14, 14, 13, 1, 10, 4, 1, 5, 13, 1, 15, 4, 3, 3, 11, 14, 15, 7, 11, 1, 15, 5, 3, 7, 4, 1, 4, 10, 1, 2, 15, 6, 10, 15, 10, 8, 1, 2, 15, 9, 10, 9, 9, 9, 12, 4, 12, 3, 6, 12, 2, 1, 12, 15, 1, 3, 10, 8, 10, 9, 14, 14, 4, 11, 11, 14, 3, 11, 5, 13, 10, 1, 8, 4, 1, 13, 1, 7, 2, 8, 10, 11, 7, 10, 11, 14, 2, 14, 13, 13, 14, 14, 11, 15, 11, 9, 10, 14, 15, 14, 14, 2, 14, 4, 8, 2, 7, 6, 2, 5, 4, 7, 14, 5, 12, 11, 12, 2, 1, 10, 5, 12, 1, 2, 9, 7, 10, 3, 15, 10, 8, 9, 10, 8, 8, 9, 5, 14, 2, 13, 9, 1, 3, 5, 3, 12, 1, 8, 5, 8, 6, 1, 12, 15, 7, 14, 3, 7, 1, 11, 9, 8, 2, 9, 10, 7, 1, 2, 4, 9, 12, 2, 6, 2, 6, 2, 12, 4, 13, 2, 5, 3, 15, 10, 5, 12, 1, 8, 2, 13, 10, 2, 3, 1, 10, 12, 4, 2, 7, 9, 6, 7, 7, 11, 13, 10, 9, 13, 5, 6, 9, 15, 5, 2, 15, 4, 6, 9, 2, 13, 15, 11, 2, 5, 14, 1, 9, 10, 7, 4, 15, 15, 9, 13, 9, 10, 15, 9, 1, 3, 4, 1, 6, 12, 3, 9, 13, 3, 15, 2, 4, 14, 8, 6, 11, 10, 4, 7, 4, 4, 14, 11, 15, 7, 6, 10, 6, 8, 2, 2, 9, 15, 4, 2, 1, 1, 7, 12, 12, 2, 10, 9, 14, 13, 15, 7, 1, 5, 12, 7, 14, 8, 12, 6, 8, 14, 6, 9, 2, 9, 12, 14, 15, 11, 13, 2, 5, 6, 9, 14, 8, 4, 15, 15, 10, 15, 14, 8, 1, 14, 5, 11, 11, 2, 3, 7, 5, 9, 11, 15, 13, 8, 9, 7, 1, 13, 8, 14, 14, 4, 1, 13, 15, 9, 12, 1, 13, 4, 8, 11, 4, 10, 1, 4, 12, 12, 11, 9, 1, 12, 8, 1, 5, 2, 12, 14, 13, 15, 9, 10, 4, 14, 7, 7, 8, 1, 5, 8, 15, 10, 7, 7, 15, 13, 13, 9, 13, 13, 15, 13, 11, 10, 2, 15, 6, 15, 15, 5, 1, 1, 5, 7, 8, 3, 13, 12, 12, 10, 12, 4, 8, 1, 9, 7, 6, 9, 8, 8, 5 };
uint8_t sizeofSendingRollingCode = 7;  // user can increase this for extra security but will take longer to transmit, rollingCode[xxx] must be divisable by sizeofSendingRollingCode
uint8_t consecutiveChecks = 10;        // user can change this, lower means Tx & Rx will quickly become out of sync on failed attempts, higher will allow the Rx to resync to Tx but reduces security by increasing the number of correct rolling codes. 
uint8_t preamble[3] = { 15,15,15 };    // Preamble may be depreciated since the qiachip already performs this, and will allow increased rolling code security                                    

char buffer[60];
//#define debug(fmt, ...)
//#define debugLoop(fmt, ...) 

// Nano Version
#define debug(fmt, ...) sprintf(buffer, fmt "\r", ##__VA_ARGS__); Serial.print(buffer);  // Nano
#define debugLoop(fmt, ...) sprintf(buffer, "%s: " fmt "\r\n", __func__, ##__VA_ARGS__); Serial.print(buffer);  // Nano

// ESP32 Version
//#define debug(fmt, ...) Serial.printf(fmt "\r\n" ##__VA_ARGS__)  // ESP
//#define debugLoop(fmt, ...) Serial.printf("%s: " fmt "\r\n", __func__, ##__VA_ARGS__)  // ESP

uint8_t sizeofPreamble = 0;
uint16_t sizeofRollingCode = 0;
uint8_t pins[4] = { 4,5,6,7 };   // Sets up the pins to be used on the Arduino
uint8_t sizeofPins = 0;
uint64_t pulseTimer = 0;  //unsigned long pulseTimer = 0;
uint8_t readCode = 0;
uint8_t errorCounter = 0;
uint16_t rollingCodeNumber = 0;
// TODO - this will need to increase if sizeofSendingRollingCode is changed from 7
uint8_t readRollingCode[7] = { 0 };
uint8_t checkRepeatCode[7] = { 0 };


// The setup() function runs once each time the micro-controller starts
void setup() {
  Serial.begin(115200);
  sizeofPins = sizeof pins;
  sizeofPreamble = sizeof preamble;
  sizeofRollingCode = sizeof rollingCode;

#ifdef RANDOM_NUMBERS
  RandomCodeGenorator();
  while (true);
#endif  //RANDOM_NUMBERS 

  // Tx Mode
#if defined MODE && !defined RANDOM_NUMBERS
  pinMode(2, INPUT_PULLUP);
  for (int i = 0; i < 4; i++) {
    pinMode(pins[i], OUTPUT);
  }
#endif // Tx Mode 


  // Rx Mode
#if !defined MODE && !defined RANDOM_NUMBERS
  pinMode(2, INPUT);
  for (int i = 0; i < 4; i++) {
    pinMode(pins[i], INPUT);
  }
 #endif // Rx Mode 
}

// Add the main program code into the continuous loop() function

// On Raising edge of Rx signal the Tx will go HIGH for 210ms
// Rx signal must hold LOW for 2ms for stable signal, but given Tx will be HIGH for 210ms then Rx may as well be HIGH for 285ms
// Tx will need to be LOW state for 80ms minimum before next signal, thus duty cycle is 287ms absolute minimum.

void loop() {
  // Tx Mode
#if defined MODE && !defined RANDOM_NUMBERS
  // Set all pins HIGH, no transmision
  for (byte i = 0; i < sizeofPins; i++) {
    digitalWrite(pins[i], HIGH);
  }

  //check if button pressed
  if (digitalRead(2) == LOW) {

    // send preamble
    for (byte number = 0; number < sizeofPreamble; number++) {
      pulseTimer = millis() + 300;  // Pulse duty cycle is 287ms 

      for (byte i = 0; i < sizeofPins; i++) {
        if (bitRead(preamble[number], i)) digitalWrite(pins[i], LOW); else digitalWrite(pins[i], HIGH);
      }
      delay(3);   // give time for the qiachip to detect change

      // Reset the Tx pins
      for (byte i = 0; i < sizeofPins; i++) {
        digitalWrite(pins[i], HIGH);
      }

      // control the timing
      while (millis() <= pulseTimer);
    }
   
    // send the rolling code
    debug("Transit Rolling Code: \n");
    for (byte number = 0; number < sizeofSendingRollingCode; number++) {
      pulseTimer = millis() + 300;  // Pulse duty cycle is 287ms 

      for (byte i = 0; i < sizeofPins; i++) {
        if (bitRead(rollingCode[rollingCodeNumber + number], i)) digitalWrite(pins[i], LOW); else digitalWrite(pins[i], HIGH);
      }
      debug(" % d, ", rollingCode[rollingCodeNumber + number]);
      delay(3);   // give time for xxx to detect change

      // Reset the Tx pins
      for (byte i = 0; i < sizeofPins; i++) {
        digitalWrite(pins[i], HIGH);
      }

      // control the timing
      while (millis() <= pulseTimer);
    }
    debug("\n");

    // TODO - Change this so where sizeofRollingCode is not divisable by sizeofSendingRollingCode then the next sequency through is different to the last.
    // Thus, the next run through may start at psotion 1 or 2 ect to given a different roll for 3 numbers etc.
    rollingCodeNumber = rollingCodeNumber + sizeofSendingRollingCode;
    if (rollingCodeNumber >= sizeofRollingCode) rollingCodeNumber = 0;
  }

#endif // Tx Mode

  // Rx Mode
#if !defined MODE && !defined RANDOM_NUMBERS
  // Read preamble
  FAIL :
  uint8_t preambleCounter = 0;
  uint8_t passed = 0;
  while (preambleCounter < sizeofPreamble) {
    if (digitalRead(2)) {
      if (ReadDataPins() == preamble[preambleCounter]) preambleCounter++; else preambleCounter = 0;
      debug("Preamble = %d \n", preambleCounter); 
    }
  }


  // read the rolling code
  debug("sizeofSendingRollingCode: %d \n", sizeofSendingRollingCode);
  debug("Rolling Code: ");
  uint8_t sendingRollingCodeCounter = 0;
  while (sendingRollingCodeCounter < sizeofSendingRollingCode) {
    if (digitalRead(2)) {
      readRollingCode[sendingRollingCodeCounter] = ReadDataPins();
      debug("%d , ",readRollingCode[sendingRollingCodeCounter]); 
      sendingRollingCodeCounter++;
    }
  }
  debug("\n");
   

  // check rolling code is not a repeat of the last one
  uint8_t checkRepeatCodeCounter = 0;
  for (uint8_t i = 0; i < sizeofSendingRollingCode; i++) {
    if (checkRepeatCode[i] == readRollingCode[i]) checkRepeatCodeCounter++;
  }
  if (checkRepeatCodeCounter == sizeofSendingRollingCode) {
    debug("Rolling Code Repeat Detected \n");
    goto FAIL;
  }
  else {   // capture this rolling code for next time
    for (uint8_t i = 0; i < sizeofSendingRollingCode; i++) {
      checkRepeatCode[i] = readRollingCode[i];
    }
  }


  
  // check the rolling code
  uint16_t tryRollingNumber = 0;
  passed = 0;

  // check next 5 rolling codes
  for (uint8_t i = 0; i < consecutiveChecks * sizeofSendingRollingCode; i = i + sizeofSendingRollingCode) {
    tryRollingNumber = rollingCodeNumber + i;
    if (tryRollingNumber >= sizeofRollingCode) tryRollingNumber = 0;
    
    for (uint16_t x = tryRollingNumber; x < tryRollingNumber + sizeofSendingRollingCode; x++) {
      if (readRollingCode[x - tryRollingNumber] == rollingCode[x]) {
        debug("Try rolling Code Position %d \n", x);
        debug(" *** Rolling Code Correct *** %d = %d \n", readRollingCode[x - tryRollingNumber], rollingCode[x]); 
        passed++;
      }
      else {
        debug("Try rolling Code Position %d \n", x);
        debug(" Rolling Code INCORRECT %d <> %d \n", readRollingCode[x - tryRollingNumber], rollingCode[x]);
        passed = 0;
      }
    }
    if (passed == sizeofSendingRollingCode) break;
  }
    
  if (passed != sizeofSendingRollingCode) {
    rollingCodeNumber += sizeofSendingRollingCode;
    goto FAIL;
  }
  rollingCodeNumber = tryRollingNumber + sizeofSendingRollingCode;
  if (rollingCodeNumber >= sizeofRollingCode) rollingCodeNumber = 0;

  debug(" *** Passed Rolling Code Checks ***\n");

#endif // RxMode
}


int8_t ReadDataPins() {
  if (digitalRead(2)) {
    pulseTimer = millis() + 250;  // Pulse duty cycle is 287ms 
    readCode = 0;
    for (int8_t i = sizeofPins - 1; i >= 0; i--) {
      bitWrite(readCode, i, digitalRead(pins[i]));
    }
    
    // control the timing
    while (digitalRead(2) || millis() <= pulseTimer);

    return readCode;
  }
}

#ifdef RANDOM_NUMBERS
void RandomCodeGenorator() {
  // Choose 2 random resitors and connect 1 from 5v to A0 and the other from GND to A0 to make a voltage divider
  debug("\n AO reading %d used as Random Seed \n", analogRead(A0));
  debug("Random Codes: \n");
  randomSeed(analogRead(A0));
  for (uint16_t i = 0; i < 1400; i++) {
    random(analogRead(A0));
    byte randNumber = random(15) + 1;
    debug("%d, ",randNumber); 
  }
}
#endif // RANDOM_NUMBERS