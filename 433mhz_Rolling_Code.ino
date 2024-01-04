/*
    Name:         qiachip 433mhz_Rolling_Code.ino
    Created:	    28/12/2023 15:01:03
    Author:       Bionicbone
    MCU:          Arduino Nano   (powered with 5v)
    qiachip parts:TX-118S-4 v2 & RX480E   (powered with 5v)
                  TX Pin 1 --> Tx Nano D6    <-- looks strange but TX / RX has illogical pins orders :( 
                  TX Pin 2 --> Tx Nano D7    <-- looks strange but TX / RX has illogical pins orders :(
                  TX Pin 3 --> Tx Nano D5
                  TX Pin 4 --> Tx Nano D4
                  Tx Nano D8  --> Button 1 to GND when pressed
                  Tx Nano D9  --> Button 2 to GND when pressed
                  Tx Nano D10 --> Button 3 to GND when pressed
                  Tx Nano D11 --> Button 4 to GND when pressed
                  RX Pin D0 --> Rx Nano D4
                  RX Pin D1 --> Rx Nano D5
                  RX Pin D2 --> Rx Nano D6
                  RX Pin D3 --> Rx Nano D7
                  RX Pin VT --> Rx Nano D2
                  Rx Nano D8  --> High signal when TX Pin 1 active
                  Rx Nano D9  --> High signal when TX Pin 2 active
                  Rx Nano D10 --> High signal when TX Pin 3 active
                  Rx Nano D11 --> High signal when TX Pin 4 active
    Resistors:    Only required if using random number generator, any values connected, one from 5v to pin A0 and one from GND to pin A0 for voltage divider (random seed)
    Button:       Button to ground Tx Nano Pin D2 when pressed, to transmit data
*/

// Uncomment MODE line to flash Tx, comment to flash Rx
//#define MODE

// Uncomment RANDOM_NUMBERS line to create a list of random numbers over serial monitor.
// NOTE: connect any value but different value resistors to A0 as voltage dividor to create a random seed otherwise numbers will be default NANO random numbers.
//#define RANDOM_NUMBERS

// user can change the rolling code values (1-15 inc.), but must ensure Tx and Rx have the same order, length must be divisable by sizeofSendingRollingCode
uint8_t rollingCode[994] = { 9, 10, 1, 7, 14, 7, 13, 13, 4, 3, 4, 1, 14, 13, 6, 10, 9, 12, 6, 1, 10, 1, 2, 12, 9, 4, 8, 8, 13, 3, 8, 1, 9, 7, 9, 12, 9, 6, 12, 15, 6, 3, 13, 2, 2, 7, 15, 4, 7, 3, 14, 15, 10, 7, 4, 11, 9, 8, 9, 5, 9, 2, 9, 2, 4, 6, 3, 11, 10, 11, 12, 8, 8, 15, 8, 8, 8, 14, 8, 9, 5, 10, 6, 1, 3, 11, 10, 8, 8, 8, 9, 10, 3, 5, 5, 2, 5, 7, 10, 7, 14, 9, 15, 6, 14, 11, 7, 6, 7, 2, 11, 4, 2, 5, 4, 6, 5, 7, 5, 9, 5, 3, 10, 1, 12, 15, 4, 4, 2, 6, 13, 1, 12, 5, 1, 13, 6, 11, 9, 4, 2, 13, 14, 13, 10, 6, 4, 9, 14, 5, 12, 10, 13, 6, 9, 14, 4, 15, 14, 7, 10, 13, 7, 7, 12, 9, 5, 8, 12, 12, 2, 12, 3, 15, 3, 2, 2, 7, 3, 6, 6, 3, 5, 3, 4, 11, 6, 6, 6, 3, 5, 8, 13, 12, 10, 1, 4, 1, 5, 3, 15, 8, 3, 11, 6, 2, 15, 6, 13, 8, 4, 5, 8, 8, 13, 15, 1, 11, 1, 8, 15, 13, 5, 13, 6, 2, 15, 12, 12, 6, 8, 6, 14, 8, 13, 13, 11, 13, 11, 4, 2, 15, 15, 5, 10, 12, 5, 6, 13, 14, 1, 2, 13, 15, 3, 15, 14, 8, 2, 4, 2, 9, 14, 4, 6, 10, 15, 4, 11, 9, 12, 14, 1, 5, 7, 15, 5, 2, 7, 3, 8, 2, 15, 8, 1, 8, 15, 6, 6, 9, 2, 14, 3, 3, 10, 12, 12, 9, 2, 1, 5, 11, 1, 1, 14, 5, 14, 5, 10, 15, 2, 7, 12, 11, 11, 4, 10, 13, 11, 5, 15, 6, 8, 6, 6, 8, 6, 3, 3, 6, 2, 8, 11, 6, 1, 12, 1, 12, 4, 13, 6, 9, 7, 3, 4, 3, 11, 11, 10, 7, 1, 10, 5, 7, 6, 9, 14, 8, 4, 1, 12, 2, 7, 14, 1, 3, 9, 6, 7, 10, 7, 5, 11, 3, 12, 1, 11, 10, 11, 15, 4, 9, 9, 5, 4, 12, 12, 14, 12, 15, 7, 4, 13, 13, 11, 14, 10, 14, 6, 1, 6, 1, 15, 2, 6, 15, 12, 8, 6, 13, 3, 15, 8, 5, 14, 12, 7, 14, 14, 14, 2, 2, 11, 6, 8, 5, 11, 10, 13, 6, 7, 10, 1, 10, 14, 4, 14, 9, 5, 3, 9, 10, 12, 13, 14, 14, 8, 5, 9, 4, 8, 3, 6, 8, 14, 12, 8, 10, 8, 10, 11, 4, 3, 15, 4, 4, 1, 3, 13, 15, 12, 1, 13, 5, 13, 15, 12, 10, 2, 11, 15, 12, 6, 9, 8, 13, 8, 1, 11, 4, 1, 14, 15, 14, 1, 2, 3, 1, 10, 11, 9, 3, 14, 7, 15, 7, 2, 8, 5, 5, 1, 8, 3, 13, 15, 5, 10, 9, 8, 4, 11, 2, 11, 1, 14, 3, 1, 7, 15, 9, 13, 11, 9, 15, 14, 8, 14, 13, 11, 15, 12, 11, 9, 8, 6, 8, 8, 6, 13, 4, 15, 7, 10, 10, 3, 3, 10, 10, 3, 11, 6, 9, 14, 4, 11, 10, 7, 12, 9, 11, 11, 12, 5, 3, 13, 5, 2, 5, 14, 2, 4, 15, 14, 2, 11, 15, 7, 4, 12, 1, 1, 12, 2, 3, 7, 1, 8, 10, 2, 5, 11, 3, 10, 15, 12, 11, 5, 3, 9, 2, 7, 11, 8, 8, 6, 15, 7, 5, 15, 9, 9, 12, 3, 11, 11, 2, 7, 1, 15, 5, 13, 3, 1, 7, 3, 9, 5, 5, 1, 7, 12, 8, 7, 1, 10, 12, 15, 11, 8, 12, 9, 3, 12, 12, 4, 12, 7, 15, 14, 12, 14, 14, 12, 1, 14, 6, 5, 14, 4, 7, 5, 11, 2, 5, 2, 13, 8, 1, 12, 3, 12, 14, 7, 15, 1, 10, 10, 5, 10, 2, 14, 7, 10, 12, 13, 2, 12, 7, 4, 8, 3, 5, 1, 13, 6, 13, 9, 6, 1, 15, 15, 6, 14, 8, 3, 1, 15, 4, 13, 6, 1, 13, 6, 5, 13, 6, 10, 10, 15, 3, 14, 5, 3, 11, 2, 2, 5, 2, 10, 10, 14, 13, 14, 5, 7, 8, 4, 3, 7, 9, 1, 5, 13, 1, 12, 15, 2, 1, 9, 14, 8, 6, 5, 4, 8, 6, 13, 3, 9, 12, 12, 4, 6, 14, 3, 12, 14, 10, 9, 6, 9, 7, 1, 7, 12, 12, 5, 7, 1, 4, 8, 15, 6, 5, 15, 15, 9, 13, 7, 3, 6, 7, 4, 7, 9, 7, 12, 8, 5, 5, 11, 6, 13, 3, 12, 8, 1, 9, 9, 5, 7, 6, 12, 11, 15, 5, 6, 15, 14, 13, 2, 6, 6, 10, 14, 4, 13, 11, 7, 3, 9, 7, 7, 7, 3, 1, 3, 12, 8, 3, 13, 4, 5, 15, 8, 10, 11, 3, 5, 2, 5, 6, 7, 9, 2, 10, 14, 2, 11, 4, 10, 2, 13, 5, 2, 8, 15, 14, 9, 3, 4, 1, 3, 15, 11, 1, 11, 4, 11, 12, 12, 7, 6, 5, 10, 14, 13, 2, 7, 13, 7, 1, 11, 12, 8, 12, 8, 14, 2, 9, 14, 9, 4, 9, 14, 3, 13, 5, 13, 3, 12, 11, 3, 5, 11, 5, 1, 13, 7, 5, 8, 2, 12, 4, 8, 6, 5, 7, 1, 1, 2, 7, 14, 10, 7, 12, 13, 1, 4, 9, 13, 4, 11, 3, 6, 7, 12, 11, 13, 13, 14, 10, 1, 11, 7, 15, 8, 1, 5, 12, 11, 1, 7, 15, 4, 3, 15, 4, 14, 4, 14, 12, 12, 3, 9, 12, 7, 9, 2, 3, 9, 7, 15, 13 };
uint8_t sizeofSendingRollingCode = 7;  // user can increase this for extra security but will take longer to transmit, rollingCode[xxx] must be divisable by sizeofSendingRollingCode
uint8_t consecutiveChecks = 10;        // user can change this, lower means Tx & Rx will quickly become out of sync on failed attempts, higher will allow the Rx to resync to Tx but reduces security by increasing the number of correct rolling codes. 
uint8_t preamble[3] = { 15,15,15 };    // Preamble may be depreciated since the qiachip already performs this, and will allow increased rolling code security                                    

char buffer[60];
#define debug(fmt, ...)
#define debugLoop(fmt, ...) 
//#define debugChangesLoop(fmt, ...)

// Nano Version
//#define debug(fmt, ...) sprintf(buffer, fmt "\r", ##__VA_ARGS__); Serial.print(buffer);  // Nano
//#define debugLoop(fmt, ...) sprintf(buffer, "%s: " fmt "\r\n", __func__, ##__VA_ARGS__); Serial.print(buffer);  // Nano
#define debugChangesLoop(fmt, ...) sprintf(buffer, "%s: " fmt "\r\n", __func__, ##__VA_ARGS__); Serial.print(buffer);  // Nano

// ESP32 Version
//#define debug(fmt, ...) Serial.printf(fmt "\r\n" ##__VA_ARGS__)  // ESP
//#define debugLoop(fmt, ...) Serial.printf("%s: " fmt "\r\n", __func__, ##__VA_ARGS__)  // ESP

uint8_t sizeofPreamble = 0;
uint16_t sizeofRollingCode = 0;
uint8_t pins[4] = { 4,5,6,7 };   // Sets up the pins to be used on the Arduino
uint8_t sizeofPins = 0;
uint8_t buttonAndOutputPins[4] = { 8,9,10,11 };
uint8_t sizeofbuttonAndOutputPins = 0;
uint64_t pulseTimer = 0;  //unsigned long pulseTimer = 0;
uint8_t readCode = 0;
uint8_t errorCounter = 0;
uint16_t rollingCodeNumber = 0;
// TODO - this will need to increase if sizeofSendingRollingCode is changed from 7
uint8_t readRollingCode[7] = { 0 };
uint8_t checkRepeatCode[7] = { 0 };
uint8_t buttons = 0;


// The setup() function runs once each time the micro-controller starts
void setup() {
  Serial.begin(115200);
  sizeofPins = sizeof pins;
  sizeofPreamble = sizeof preamble;
  sizeofRollingCode = sizeof rollingCode;
  sizeofbuttonAndOutputPins = sizeof buttonAndOutputPins;

#ifdef RANDOM_NUMBERS
  RandomCodeGenorator();
  while (true);
#endif  //RANDOM_NUMBERS 

  // Tx Mode
#if defined MODE && !defined RANDOM_NUMBERS
  // Set up inputs for the buttons on the Tx
  for (uint8_t i = 0; i < sizeofbuttonAndOutputPins; i++) {
    pinMode(buttonAndOutputPins[i], INPUT_PULLUP);
  }
  // Set all Tx signal pins HIGH, no transmision
  for (uint8_t i = 0; i < sizeofPins; i++) {
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], HIGH);
  }
  Serial.println("Tx Mode \n");
#endif // Tx Mode 


  // Rx Mode
#if !defined MODE && !defined RANDOM_NUMBERS
  // Pin D2 is used to detect the VT signal from the Rx that indicates that there is an quichip authorised incoming transmission
  pinMode(2, INPUT_PULLUP);  
  // Set up the output for the Rx for the User Buttons
  for (uint8_t i = 0; i < sizeofbuttonAndOutputPins; i++) {
    pinMode(buttonAndOutputPins[i], OUTPUT);
    digitalWrite(buttonAndOutputPins[i], LOW);
  }
  Serial.println("Rx Mode \n");
 #endif // Rx Mode 
}

// Add the main program code into the continuous loop() function

// On Raising edge of Rx signal the Tx will go HIGH for 210ms
// Rx signal must hold LOW for 2ms for stable signal, but given Tx will be HIGH for 210ms then Rx may as well be HIGH for 285ms
// Tx will need to be LOW state for 80ms minimum before next signal, thus duty cycle is 287ms absolute minimum.

void loop() {
  // Tx Mode
#if defined MODE && !defined RANDOM_NUMBERS


  //check if button pressed
  for (uint8_t i = 0; i < sizeofbuttonAndOutputPins; i++) {

    if (digitalRead(buttonAndOutputPins[i]) == LOW) {

      // read users buttons
      // TODO must capture all user buttons, allow for slight delay in pressing two user buttons together for example
      // always capture the intial button press
      buttons = 0 | (i + 1);
      // check all buttons , OR comparision will not interfer with initial button pressed set above
      for (uint8_t x = 0; x < sizeofbuttonAndOutputPins; x++) {
        if (digitalRead(x) == LOW) buttons | (x + 1);
      }
      debug("Button Value = %d", buttons);

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
        debug(" %d, ", rollingCode[rollingCodeNumber + number]);
        delay(3);   // give time for quichip to detect change

        // Reset the Tx pins
        for (byte i = 0; i < sizeofPins; i++) {
          digitalWrite(pins[i], HIGH);
        }

        // control the timing
        while (millis() <= pulseTimer);
      }
      debug("\n");

      // send the button presses
      pulseTimer = millis() + 300;  // Pulse duty cycle is 287ms 

      for (byte i = 0; i < sizeofbuttonAndOutputPins; i++) {
        if (bitRead(buttons, i)) digitalWrite(pins[i], LOW); else digitalWrite(pins[i], HIGH);
        debug("button bit % d = % d \n", i, bitRead(buttons, i));
      }
      debug("Transmit Button Value %d \n", buttons);
      delay(3);   // give time for quichip to detect change

      // Reset the Tx pins
      for (byte i = 0; i < sizeofPins; i++) {
        digitalWrite(pins[i], HIGH);
      }

      // control the timing
      while (millis() <= pulseTimer);


      // TODO - Change this so where sizeofRollingCode is not divisable by sizeofSendingRollingCode then the next sequency through is different to the last.
      // Thus, the next run through may start at psotion 1 or 2 ect to given a different roll for 3 numbers etc.
      rollingCodeNumber = rollingCodeNumber + sizeofSendingRollingCode;
      if (rollingCodeNumber >= sizeofRollingCode) rollingCodeNumber = 0;
    }
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
  debugChangesLoop("sizeofSendingRollingCode: %d \n", sizeofSendingRollingCode);
  debugLoop("Rolling Code: ");
  uint8_t sendingRollingCodeCounter = 0;
  while (sendingRollingCodeCounter < sizeofSendingRollingCode) {
    if (digitalRead(2)) {
      readRollingCode[sendingRollingCodeCounter] = ReadDataPins();
      debugChangesLoop("%d , ", readRollingCode[sendingRollingCodeCounter]);
      sendingRollingCodeCounter++;
    }
  }
  debug("\n");


  // read the Buttons value
  sendingRollingCodeCounter = 0;
  while (sendingRollingCodeCounter < 1) {
    if (digitalRead(2)) {
      buttons = ReadDataPins();
      debugChangesLoop("Button %d ", buttons);
      for (byte i = 0; i < sizeofbuttonAndOutputPins; i++) {
        debugChangesLoop("button bit % d = % d \n", i, bitRead(buttons, i));
      }
      sendingRollingCodeCounter++;
    }
  }



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
    debugChangesLoop(" !!! Failed Rolling Code Checks !!!\n");
    goto FAIL;
  }
  rollingCodeNumber = tryRollingNumber + sizeofSendingRollingCode;
  if (rollingCodeNumber >= sizeofRollingCode) rollingCodeNumber = 0;

  debugChangesLoop(" *** Passed Rolling Code Checks ***\n");


  // activate Rx pins for 210ms based on buttons pressed on Tx
  digitalWrite(buttonAndOutputPins[buttons - 1], HIGH);
  debugChangesLoop("Buttons = %d pin %d value HIGH", buttons, buttonAndOutputPins[buttons -1]);

  delay(210);
  for (uint8_t i = 0; i < sizeofbuttonAndOutputPins; i++) {
    digitalWrite(buttonAndOutputPins[i], LOW);
  }
}


uint8_t ReadDataPins() {
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
#endif // RxMode


#ifdef RANDOM_NUMBERS
void RandomCodeGenorator() {
  // Choose 2 random resitors and connect 1 from 5v to A0 and the other from GND to A0 to make a voltage divider
  debug("\n AO reading %d used as Random Seed \n", analogRead(A0));
  debug("Random Codes: \n");
  randomSeed(analogRead(A0));
  for (uint16_t i = 0; i < 994; i++) {
    random(analogRead(A0));
    byte randNumber = random(15) + 1;
    debug("%d, ",randNumber); 
  }
}
#endif // RANDOM_NUMBERS