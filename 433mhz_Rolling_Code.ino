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
#define MODE

// Uncomment RANDOM_NUMBERS line to create a list of random numbers over serial monitor.
// NOTE: connect any value but different value resistors to A0 as voltage dividor to create a random seed otherwise numbers will be default NANO random numbers.
#define RANDOM_NUMBERS

// user can change the rolling code values (1-15 inc.), but must ensure Tx and Rx have the same order, length must be divisable by sizeofSendingRollingCode
uint8_t rollingCode[966] = { 3, 12, 6, 1, 10, 12, 10, 5, 13, 2, 7, 15, 12, 3, 15, 3, 13, 5, 8, 12, 12, 1, 2, 8, 10, 1, 5, 8, 11, 13, 13, 15, 12, 12, 8, 1, 1, 10, 9, 11, 2, 9, 14, 1, 3, 15, 12, 7, 3, 14, 2, 9, 7, 2, 10, 15, 5, 15, 14, 9, 11, 2, 8, 2, 13, 4, 12, 2, 5, 14, 9, 13, 2, 10, 2, 4, 11, 5, 4, 12, 14, 1, 3, 13, 13, 14, 13, 15, 4, 14, 6, 2, 4, 9, 13, 15, 11, 2, 4, 14, 15, 1, 13, 9, 5, 3, 14, 15, 10, 5, 4, 5, 8, 15, 15, 12, 5, 15, 3, 14, 9, 13, 12, 11, 8, 7, 15, 7, 15, 3, 6, 4, 5, 11, 5, 10, 13, 13, 14, 4, 5, 12, 1, 7, 6, 9, 4, 10, 9, 3, 7, 12, 10, 12, 3, 12, 9, 5, 4, 1, 14, 1, 8, 6, 13, 7, 6, 5, 3, 14, 2, 3, 8, 13, 15, 9, 1, 3, 10, 5, 13, 8, 5, 3, 8, 11, 13, 12, 1, 13, 12, 4, 6, 2, 15, 1, 14, 7, 13, 7, 15, 14, 14, 9, 1, 6, 15, 1, 11, 10, 1, 9, 12, 4, 1, 12, 4, 4, 6, 5, 7, 2, 13, 13, 15, 11, 10, 8, 15, 7, 11, 13, 13, 1, 10, 12, 4, 3, 3, 12, 4, 14, 3, 1, 15, 12, 15, 3, 1, 1, 6, 5, 5, 14, 6, 9, 12, 11, 3, 7, 9, 5, 9, 4, 14, 12, 13, 5, 3, 5, 2, 11, 8, 8, 8, 10, 12, 11, 5, 14, 11, 1, 10, 6, 2, 13, 10, 9, 15, 12, 4, 11, 8, 11, 13, 11, 2, 1, 1, 10, 10, 10, 15, 2, 1, 7, 10, 12, 6, 14, 6, 13, 14, 7, 7, 11, 4, 1, 7, 1, 1, 11, 9, 12, 8, 13, 4, 15, 9, 5, 3, 4, 15, 3, 2, 7, 13, 5, 9, 9, 14, 1, 11, 12, 12, 7, 3, 1, 3, 2, 12, 7, 5, 5, 5, 14, 4, 2, 7, 1, 13, 9, 11, 12, 14, 1, 5, 13, 4, 10, 7, 9, 1, 7, 10, 9, 8, 11, 10, 2, 4, 11, 12, 5, 7, 6, 1, 10, 10, 2, 2, 10, 8, 10, 1, 11, 14, 7, 3, 5, 2, 1, 15, 5, 7, 3, 10, 1, 10, 11, 5, 6, 10, 3, 4, 3, 3, 12, 7, 3, 15, 13, 9, 9, 12, 8, 12, 2, 4, 9, 8, 2, 8, 2, 12, 6, 10, 11, 4, 14, 15, 4, 1, 13, 1, 5, 6, 13, 7, 13, 11, 3, 9, 5, 14, 10, 11, 6, 4, 15, 13, 7, 4, 3, 1, 8, 10, 3, 15, 10, 9, 11, 12, 7, 11, 2, 14, 6, 2, 2, 6, 10, 1, 8, 10, 8, 13, 11, 4, 2, 11, 10, 8, 10, 6, 12, 12, 14, 3, 10, 5, 11, 10, 9, 5, 4, 11, 13, 14, 14, 5, 9, 3, 2, 6, 10, 11, 6, 11, 14, 2, 4, 15, 6, 13, 7, 15, 15, 4, 12, 7, 8, 7, 15, 5, 9, 14, 6, 6, 15, 2, 11, 7, 3, 6, 7, 13, 10, 11, 1, 1, 1, 13, 14, 2, 9, 13, 12, 15, 14, 13, 2, 2, 6, 2, 4, 3, 11, 5, 7, 3, 2, 12, 7, 9, 8, 1, 12, 12, 10, 8, 11, 2, 10, 2, 8, 11, 13, 8, 2, 2, 11, 8, 9, 8, 8, 13, 14, 14, 5, 13, 5, 1, 1, 13, 5, 4, 2, 9, 5, 11, 11, 10, 9, 4, 8, 11, 7, 2, 5, 15, 5, 3, 11, 10, 4, 15, 1, 6, 5, 2, 3, 5, 8, 12, 1, 2, 6, 2, 8, 6, 11, 11, 14, 3, 7, 7, 6, 12, 6, 15, 12, 6, 1, 1, 14, 10, 3, 8, 1, 3, 3, 8, 14, 13, 1, 13, 8, 6, 11, 1, 5, 12, 6, 14, 7, 9, 7, 14, 15, 14, 10, 3, 7, 1, 5, 15, 14, 14, 8, 11, 2, 14, 4, 5, 4, 14, 4, 1, 12, 9, 13, 4, 15, 10, 1, 5, 4, 1, 9, 9, 15, 1, 12, 5, 4, 10, 9, 9, 9, 13, 9, 9, 12, 13, 9, 6, 3, 14, 4, 14, 11, 1, 5, 2, 4, 4, 9, 6, 9, 15, 5, 8, 10, 8, 14, 4, 2, 2, 5, 5, 5, 10, 9, 15, 15, 7, 9, 13, 1, 13, 15, 15, 3, 4, 2, 11, 13, 5, 5, 13, 3, 10, 14, 14, 7, 7, 15, 13, 9, 5, 15, 9, 8, 7, 1, 14, 5, 11, 5, 11, 11, 15, 6, 13, 15, 12, 8, 12, 13, 2, 9, 3, 14, 1, 4, 13, 15, 3, 10, 8, 1, 13, 3, 12, 3, 13, 2, 1, 12, 7, 10, 9, 2, 15, 14, 4, 10, 4, 4, 12, 2, 4, 4, 1, 6, 15, 6, 2, 9, 9, 13, 12, 5, 3, 6, 5, 3, 12, 10, 5, 5, 12, 15, 5, 9, 11, 8, 6, 3, 6, 14, 5, 7, 12, 6, 9, 2, 14, 3, 14, 3, 10, 15, 15, 9, 15, 2, 15, 11, 13, 7, 11, 10, 6, 10, 12, 13, 9, 13, 4, 2, 2, 14, 13, 10, 5, 6, 13, 11, 8, 11, 8, 14, 11, 15, 3, 15, 2, 3, 3, 9, 14, 7, 10, 11, 11, 14, 6, 3, 11, 12, 9, 7, 5, 14, 10, 6, 7, 9, 7, 12, 8, 7, 1, 14, 12, 11, 2, 7, 13, 5, 2, 13, 12, 9, 2, 13, 3, 8, 10, 8, 10, 7, 2, 1, 10, 10, 6, 15, 12, 2, 10, 7, 6, 4 };
uint8_t sizeofSendingRollingCode = 2;  // (2 - 10) increase this for extra security but will take longer to transmit, rollingCode[xxx] must be divisable by sizeofSendingRollingCode
uint8_t consecutiveChecks = 10;        // user can change this, lower means Tx & Rx will quickly become out of sync on failed attempts, higher will allow the Rx to resync to Tx but reduces security by increasing the number of correct rolling codes. 
uint8_t initValue = 3;                 // user can change this, values 5 and 10 and 15 are weak, other values can be used with varying strength. No guidance is given to make all systems as unique as possible
uint16_t bruteForceInitialLockDownTime = 60;  // (seconds) User can change this, each time 10 invalide codes is received the current number will be doubled for the lock down time, thus 60 seconds, then 120, 240, 480 etc.
uint8_t bruteForceMaxBeforeLockDown = 10;  // (times) User can change this, if this many incorrect codes is received lock down will be initiated.

// Uncomment for No Debugging to speed up execution
//#define debug(fmt, ...)
//#define debugLoop(fmt, ...) 
//#define debugChangesLoop(fmt, ...)

// Nano Version
char buffer[60];  // Must uncomment for Nano Debugging
#define debug(fmt, ...) sprintf(buffer, fmt "\r", ##__VA_ARGS__); Serial.print(buffer);  // Nano
#define debugLoop(fmt, ...) sprintf(buffer, "%s: " fmt "\r\n", __func__, ##__VA_ARGS__); Serial.print(buffer);  // Nano
#define debugChangesLoop(fmt, ...) sprintf(buffer, "%s: " fmt "\r\n", __func__, ##__VA_ARGS__); Serial.print(buffer);  // Nano

// ESP32 Version
//#define debug(fmt, ...) Serial.printf(fmt "\r\n" ##__VA_ARGS__)  // ESP
//#define debugLoop(fmt, ...) Serial.printf("%s: " fmt "\r\n", __func__, ##__VA_ARGS__)  // ESP

uint16_t sizeofRollingCode = 0;
uint8_t pins[4] = { 4,5,6,7 };   // Sets up the pins to be used on the Arduino
uint8_t sizeofPins = 0;
uint8_t buttonAndOutputPins[4] = { 8,9,10,11 };
uint8_t sizeofbuttonAndOutputPins = 0;
uint16_t rollingCodeNumber = 0;
uint8_t checkRepeatCode[10] = { 0 };
uint8_t data[11] = { 0 };
uint8_t bruteForceCounter = 0;
uint64_t bruteForceLockDownTime = bruteForceInitialLockDownTime;

// The setup() function runs once each time the micro-controller starts
void setup() {
  Serial.begin(115200);
  sizeofPins = sizeof pins;
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

#if defined MODE && !defined RANDOM_NUMBERS
void loop() {
  // Tx Mode

  //check if button pressed
  for (uint8_t i = 0; i < sizeofbuttonAndOutputPins; i++) {

    if (digitalRead(buttonAndOutputPins[i]) == LOW) {
      uint8_t functionButtons = 0;
      // read users buttons
      // TODO must capture all user buttons, allow for slight delay in pressing two user buttons together for example
      // always capture the intial button press
      functionButtons = 0 | (i + 1);
      // check all buttons , OR comparision will not interfer with initial button pressed set above
      for (uint8_t x = 0; x < sizeofbuttonAndOutputPins; x++) {
        if (digitalRead(x) == LOW) functionButtons | (x + 1);
      }
      debug("Button Value = %d \n", functionButtons);

      // Prepare the Transmission Array
      // place debugging outside of transmission loop so baud is not effected
      debug("Transmit Rolling Code: \n");
      for (uint8_t i = 0; i < sizeofSendingRollingCode; i++) {
        data[i] = rollingCode[rollingCodeNumber + i];
        debug(" %d, ", data[i]);
      }
      // add the button data
      data[sizeofSendingRollingCode] = functionButtons;
      debug(" Buttons: %d \n", data[sizeofSendingRollingCode]);
      debug(" in Position: %d \n", sizeofSendingRollingCode);

      // send the data (rolling code & button value)
      for (uint8_t number = 0; number < sizeofSendingRollingCode + 1; number++) {
        uint64_t pulseTimer = millis() + 300;  // Minimum pulse duty cycle is 290ms, increase if many errors are received 

        for (uint8_t i = 0; i < sizeofPins; i++) {
          if (bitRead(data[number], i)) digitalWrite(pins[i], LOW); else digitalWrite(pins[i], HIGH);
        }
        delay(5);   // give time for quichip to detect change

        // Reset the Tx pins
        for (uint8_t i = 0; i < sizeofPins; i++) {
          digitalWrite(pins[i], HIGH);
        }

        // control the timing
        while (millis() <= pulseTimer);
      }

      // TODO - Change this so where sizeofRollingCode is not divisable by sizeofSendingRollingCode then the next sequency through is different to the last.
      // Thus, the next run through may start at psotion 1 or 2 ect to given a different roll for 3 numbers etc.
      rollingCodeNumber = rollingCodeNumber + sizeofSendingRollingCode;
      ApplyInitValueToRollingCodeLoop();
    }
  }
}

#endif // Tx Mode

  // Rx Mode
#if !defined MODE && !defined RANDOM_NUMBERS
void loop() {

  // Read the data being received by the Rx, if any check it for validity
  // QaiChip modules need to be bound Tx to Rx, thus if data is accepted by the Rx we should validate it.
FAIL:
  if (Rx_AcceptData()) {
    if (CheckRepeatedRollingCode()) {
      ApplyInitValueToRollingCodeLoop();
      goto FAIL;
    }

    // check the rolling code
    uint16_t tryRollingNumber = 0;
    uint8_t passed = 0;

    // check the next x rolling codes
    for (uint8_t i = 0; i < consecutiveChecks * sizeofSendingRollingCode; i = i + sizeofSendingRollingCode) {
      tryRollingNumber = rollingCodeNumber + i;
      if (tryRollingNumber >= sizeofRollingCode) tryRollingNumber = 0;

      for (uint16_t x = tryRollingNumber; x < tryRollingNumber + sizeofSendingRollingCode; x++) {
        if (data[x - tryRollingNumber] == rollingCode[x]) {
          debug("p.%d *** RC Correct *** %d = %d \n", x, data[x - tryRollingNumber], rollingCode[x]);
          passed++;
        }
        else {
          debug("p.%d !!! RC INCORRECT !!! %d <> %d \n", x, data[x - tryRollingNumber], rollingCode[x]);
          passed = 0;
        }
      }
      if (passed == sizeofSendingRollingCode) break;
    }

    if (passed != sizeofSendingRollingCode) {
      rollingCodeNumber += sizeofSendingRollingCode;
      debug(" !!! Failed Rolling Code Checks !!!\n");
      bruteForceCounter++;
      if (bruteForceCounter >= bruteForceMaxBeforeLockDown) InitiateLockDown();
      ApplyInitValueToRollingCodeLoop();
      goto FAIL;
    }
    
    rollingCodeNumber = tryRollingNumber + sizeofSendingRollingCode;
    debug(" *** Passed Rolling Code Checks ***\n");
    bruteForceCounter = 0;
    bruteForceLockDownTime = bruteForceInitialLockDownTime;
    ApplyInitValueToRollingCodeLoop();

    ActivateRxButtonPins();
  }
}



uint8_t Rx_AcceptData() {
  //debug("AcceptData() Called \n");
  uint8_t countOfDataReceived = 0;
  uint64_t transmissionTimer = millis() + (1000 * sizeofSendingRollingCode);  // Pulse duty cycle is 287ms
  uint8_t readCode = 0;
  uint64_t pulseTimer = 0;
  if (digitalRead(2)) {
    while (millis() <= transmissionTimer) {
      if (digitalRead(2)) {
        //debug("digitalRead Passed \n");
        pulseTimer = millis() + 50;  // Pulse duty cycle is 287ms 

        for (int8_t i = sizeofPins - 1; i >= 0; i--) {
          bitWrite(readCode, i, digitalRead(pins[i]));
        }
        //debug("countOfDataReceived = %d \n", countOfDataReceived);
        debug("%d, ", readCode);
        data[countOfDataReceived] = readCode;
        countOfDataReceived++;
        if (countOfDataReceived == sizeofSendingRollingCode + 1) {
          debug("\nRecieved %d bytes - terminating \n", countOfDataReceived);
          return countOfDataReceived;
        }
        // control the timing
        while (digitalRead(2) || millis() <= pulseTimer);
      }
    }
    debug(" !!! Only Recieved %d bytes - TimeOut !!!\n", countOfDataReceived);
  }
  return countOfDataReceived;
}



bool CheckRepeatedRollingCode() {
  // check rolling code is not a repeat of the last one
  // TODO - if we receive the same rolling code then send "Hack Attack" text message to mobile
  //        Since qaichip is bound to Rx, then anything reaching this stage must be a record and playback message
  uint8_t checkRepeatCodeCounter = 0;
  for (uint8_t i = 0; i < sizeofSendingRollingCode; i++) {
    if (checkRepeatCode[i] == data[i]) checkRepeatCodeCounter++;
  }
  if (checkRepeatCodeCounter == sizeofSendingRollingCode) {
    debug("Rolling Code Repeat Detected \n");
    return true;
  }
  else {   // capture this rolling code for next time
    for (uint8_t i = 0; i < sizeofSendingRollingCode; i++) {
      checkRepeatCode[i] = data[i];
    }
  }
  return false;
}


void ActivateRxButtonPins() {
  uint8_t functionButtons = data[sizeofSendingRollingCode];
  for (uint8_t i = 0; i < sizeofbuttonAndOutputPins; i++) {
    debug("button bit % d = % d \n", i, bitRead(functionButtons, i));
  }
  // activate Rx pins for 210ms based on original qaichip Tx
  digitalWrite(buttonAndOutputPins[functionButtons - 1], HIGH);
  uint64_t waitTimer = millis() + 210;
  while (millis() <= waitTimer);
  for (uint8_t i = 0; i < sizeofbuttonAndOutputPins; i++) {
    digitalWrite(buttonAndOutputPins[i], LOW);
  }
}


void InitiateLockDown() {
  uint64_t LockDownTimer = millis() + (bruteForceLockDownTime * 1000);
  debug("Lock Down Started \n");
  debug("bruteForceLockDownTime: %u s\n", bruteForceLockDownTime);
  while (millis() < LockDownTimer);
  debug("Lock Down Endded\n");
  // double the lock down time in case it is a constant threat.
  bruteForceLockDownTime *= 2;
  bruteForceCounter = 0;
}

#endif // RxMode


#ifdef RANDOM_NUMBERS
void RandomCodeGenorator() {
  // Choose 2 random resitors and connect 1 from 5v to A0 and the other from GND to A0 to make a voltage divider
  debug("\n AO reading %d used as Random Seed \n", analogRead(A0));
  debug("Random Codes: \n");
  randomSeed(analogRead(A0));
  for (uint16_t i = 0; i < 1106; i++) {
    random(analogRead(A0));
    byte randNumber = random(15) + 1;
    debug("%d, ",randNumber); 
  }
}
#endif // RANDOM_NUMBERS


#if !defined RANDOM_NUMBERS
void ApplyInitValueToRollingCodeLoop() {
  // Apply initValue to the rollingCode[] pattern once the pattern has been used
  if (rollingCodeNumber >= sizeofRollingCode) {
    debug("New Rolling Code Loop Genorating \n");
    debug("rollingCodeNumber = %d, sizeofRollingCode = %d \n", rollingCodeNumber, sizeofRollingCode);
    for (uint16_t y = 0; y < sizeofRollingCode; y++) {
      debug("Position %d was %d ", y, rollingCode[y]);
      rollingCode[y] += initValue;
      if (rollingCode[y] > 15) rollingCode[y] = int(rollingCode[y] / 15);
      debug("now %d \n", rollingCode[y]);
    }
    rollingCodeNumber = 0;
  }
}
#endif