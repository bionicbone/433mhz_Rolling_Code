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

**RollJam Investigations Video**  
[https://youtu.be/gohp3LFnj8Y](https://youtu.be/gohp3LFnj8Y)

**Decoding the QiaChip Signals Video**  
[https://youtu.be/DBNdfk8Yu3U](https://youtu.be/DBNdfk8Yu3U)

**PulseView of Timing**

The correct connection method when using a logic analyzer is at both Nano side connections not at the Rx Tx because the outputs on the Rx and Tx are not logical. Think of it as the Tx Nano is transmitting a nibble (4 bits) of data and the Rx Nano is receiving that nibble of data. Here are some close up pictures to help.

Logic Analyzer
![DSC00073](https://github.com/bionicbone/433mhz_Rolling_Code/assets/7845867/5f58b94e-5015-4e45-8481-3c4371b61772)

Tx Nano
![DSC00074](https://github.com/bionicbone/433mhz_Rolling_Code/assets/7845867/4a711066-c10e-4a55-b3d6-95a00ff8540a)

Rx Nano
![DSC00076](https://github.com/bionicbone/433mhz_Rolling_Code/assets/7845867/079acf95-4e34-4057-9b5d-7d913e13cf4e)

Results, short pulse is the Tx, Long Pulse is the Rx. The Tx should pulse a pattern and the Rx should receive the same pattern.
![PulseView1](https://github.com/bionicbone/433mhz_Rolling_Code/blob/main/PulseView%20(RX480%20Output%20Pins).png)

![PulseView2](https://github.com/bionicbone/433mhz_Rolling_Code/blob/main/PulseView%20(Tx%20Rx%20Timing).png)

**Tx & Rx Connections for Arduino Nano**
![Nano TX Rx Connections](https://github.com/bionicbone/433mhz_Rolling_Code/blob/main/Nano%20Tx%20Rx%20Connections.png)

**Watch the above videos for more information**

Tx Nano
![DSC00084](https://github.com/bionicbone/433mhz_Rolling_Code/assets/7845867/8c3b369c-008a-4d64-9549-cf2db4eaaa40)

![DSC00085](https://github.com/bionicbone/433mhz_Rolling_Code/assets/7845867/4e7ff7af-a664-4805-9a6a-3a887bf1698e)

![DSC00087](https://github.com/bionicbone/433mhz_Rolling_Code/assets/7845867/78143535-a7f3-4c08-882b-8b96a292f79c)

![DSC00086](https://github.com/bionicbone/433mhz_Rolling_Code/assets/7845867/64bff07f-60d4-42f4-8239-1040f59840a8)

Rx Nano
![DSC00081](https://github.com/bionicbone/433mhz_Rolling_Code/assets/7845867/7a4ddcb5-e1f7-47b9-9360-e9f12c40baed)

![DSC00082](https://github.com/bionicbone/433mhz_Rolling_Code/assets/7845867/05e247a5-adff-43fc-a4f4-85e4eff011bb)

![DSC00083](https://github.com/bionicbone/433mhz_Rolling_Code/assets/7845867/1cabe503-e7e5-49e9-89c4-14c02838744b)

Tx ESP32S
![DSC00088](https://github.com/bionicbone/433mhz_Rolling_Code/assets/7845867/90471e75-18bc-4dcc-b14b-36287cf97699)

![DSC00089](https://github.com/bionicbone/433mhz_Rolling_Code/assets/7845867/5c868292-2191-4588-93f9-5d7f4a2518fc)

![DSC00090](https://github.com/bionicbone/433mhz_Rolling_Code/assets/7845867/b0b2030f-b9c5-4d89-bde2-ab35de4876c3)

![DSC00091](https://github.com/bionicbone/433mhz_Rolling_Code/assets/7845867/feeb637a-3dc8-4862-ba9d-9524abce5e2a)

![DSC00092](https://github.com/bionicbone/433mhz_Rolling_Code/assets/7845867/1b9d0faf-afe4-4088-a540-7691293f6f98)

![DSC00093](https://github.com/bionicbone/433mhz_Rolling_Code/assets/7845867/354788cb-a193-4cef-b115-c9e7e62e76bf)

Rx ESP32
![DSC00094](https://github.com/bionicbone/433mhz_Rolling_Code/assets/7845867/30f422ed-bda6-4436-bd3a-219453a39c78)

![DSC00095](https://github.com/bionicbone/433mhz_Rolling_Code/assets/7845867/1e3ba498-e4b5-4f17-bbad-685f01d04a20)

![DSC00096](https://github.com/bionicbone/433mhz_Rolling_Code/assets/7845867/badee17d-245e-4c25-999b-01e3647cf4de)

![DSC00097](https://github.com/bionicbone/433mhz_Rolling_Code/assets/7845867/fbcbe548-0877-47e7-b5f8-e120f2a79131)

![DSC00098](https://github.com/bionicbone/433mhz_Rolling_Code/assets/7845867/006d2af5-92c8-4c33-92c7-c574dffa18bb)

![DSC00099](https://github.com/bionicbone/433mhz_Rolling_Code/assets/7845867/e83eea62-5dd5-49f2-a5d6-9fcff2da095d)


Disclaimer:

This software is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. This software is used at your own risk. I am under no obligation to maintain, support or leave this software or documentation in the public domain, likewise I am under no obligation to release designs for all the sensors or other electronics that I have developed.
