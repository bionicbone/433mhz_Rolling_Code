**Solution Methodology**

The code is designed to be user configurable to add an element of uniqueness to each implementation which is a key part of the projects security. For example, a manufacture of a garage door has an implementation, hack one and you have hacked them all. 
Consider: The length of the list of random numbers can be decreased or increased (within memory limits), the amount of numbers sent each time between 2 and 10 is recommend (higher is more secure but more lag). The number of consecutive checks covers accidently presses on the Tx and allows the Rx to resync to the Tx position. The init-Value to be added once the list of Rolling Codes runs out. Even the Brute Force controls can be changed, here they are set so after 10 failed attempts the Rx Locks Out for 60 seconds, if repeated, 120, then 240 and 480 etc. A long press on the Tx button > 5 seconds a force a init-Value increament and restart of the new Rolling Code Loop (if activated), allowing emergancy resync of Tx to Rx and new numbers.
![User Configrable Settings](https://github.com/bionicbone/433mhz_Rolling_Code/blob/main/User%20Configrable%20Settings.png)

**Rolling Code and Init-Value Example**
![Rolling Code and Init-Value Example](https://github.com/bionicbone/433mhz_Rolling_Code/blob/main/Rolling%20Code%20and%20Init-Value%20Example.png)


**Initial Release Video**

[https://www.youtube.com/watch?v=JLMbpiywVxQ](https://youtu.be/TpmY-2w8CTI)

**Updates on 2nd Jan 2024**

All 4 Buttons are now added, could be an addition for equipment already using qaichip TX-118S-4 v2 & RX480E parts

code re-written, read "times out" if interference creeps in.

**Updates on 5th Jan 2024** 

User configrable init-value added to the loop of rolling codes once they have all been consumed, thus only increaments after x codes consumed and invisible to hacker when this occurs or doesn't occur. 

Rx "Lock Out" for ever increasing time when 10 (user configarable) false codes have been received.

Some documentaion has been added below.

**Update Video**

[https://youtu.be/VihT618iKPA?si=CvWJA-HzKL6Me9dn](https://youtu.be/VihT618iKPA?si=CvWJA-HzKL6Me9dn)

**Updates on 10th Jan 2024**

Add forced reset when button is pressed > 5 seconds, this applies the initValue to the rolling codes so they are not repeated and allows TX & Rx to resync at the begining of a new set of codes.

**Updates on 14th Jan 2024**

Add ESP32 Support
-required for Tx Deep Sleep ( coming soon... )
-required for Rx advanced feature ( coming soon... )
Add ATmega328P and ESP32 compile instructions
-around the debugging functions
-around pin setups
Add Tx Transmit LED on pinLED
Embed Tx ID onto first nibble of Rolling Code in Tx
Extract Tx ID rom first nibble of Rolling Code in Rx
Add Rx Tx Identification LEDs fro Tx0, Tx1, Tx2 ID
Share Rolling Codes for x number of attached Tx's
Perfect timing in high interferance environments (timing user configrable)
Tidied up some code - more to do
Tidied up debugging messages
Tested Perfect, no issues found

**Mulit-Tx Update Video**

[https://youtu.be/CfMDaaJQzlc](https://youtu.be/CfMDaaJQzlc)

**PulseView of Timing**
![PulseView1](https://github.com/bionicbone/433mhz_Rolling_Code/blob/main/PulseView%20(RX480%20Output%20Pins).png)

![PulseView2](https://github.com/bionicbone/433mhz_Rolling_Code/blob/main/PulseView%20(Tx%20Rx%20Timing).png)

**Tx & Rx Connections for Arduino Nano**
![Nano TX Rx Connections](https://github.com/bionicbone/433mhz_Rolling_Code/blob/main/Nano%20Tx%20Rx%20Connections.png)
