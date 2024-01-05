**Initial Release Video**

![Initial Release Video](https://youtu.be/TpmY-2w8CTI?si=Plb3RdlSTm27eQY5)


**Updates**

All 4 Buttons are now added, could be an addition for equipment already using qaichip TX-118S-4 v2 & RX480E parts

Better timing, code re-written, read "times out" if interference creeps in.

User configrable init-value added to the loop of rolling codes once they have all been consumed, thus only increaments after x codes consumed and invisible to hacker when this occurs or doesn't occur. 

Rx "Lock Out" for ever increasing time when 10 (user configarable) false codes have been received.

**PulseView of Timing**
![PulseView](https://github.com/bionicbone/433mhz_Rolling_Code/blob/main/PulseView%20(RX480%20Output%20Pins).png)

**Tx & Rx Connections for Arduino Nano**
![Nano TX Rx Connections](https://github.com/bionicbone/433mhz_Rolling_Code/blob/main/Nano%20Tx%20Rx%20Connections.png)
