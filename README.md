# HeartMoji

HeartMoji is a hardware and software project created for my 2nd anniversary with my girlfriend. It is a Printed Circuit board (PCB) with an array of LEDs in the shape of a heart. It uses a NodeMCU Amica to control the status of the LEDs and to interface with a ThingSpeak channel over Wifi. There is also a website that is used to change the LED status from anywhere in the world.

## Hardware
The hardware for this project is basic and consists of mostly simple parts. The raw schematic and PCB files can be found in the "AltiumFiles" folder while there is a PDF version of both in "HeartMoji.pdf."

<ol>
  <li>NodeMCU Amica</li>
  <li>Red LED x9</li>
  <li>Push Button</li>
  <li>Linear Regulator</li>
  <li>Power Jack</li>
  <li>250 ohm Resistor x9</li>
  <li>10k ohm Resistor</li>
  <li>330 ohm Resistor</li>
  <li>1k ohm Resistor</li>
</ol>

## Software
The software for this project consists of an arduino sketch that is loaded onto the NodeMCU Amica and a website. Both rely on the ThingSpeak API to interact.

## Future Work
There are a few changes I would like to make to the final result but overall I am proud of the work. First, I would fix the case files. The tolerances and spacing for the necessary ports on the case do not align depending on the 3D printer. Second, I would update the website so it has a little more going on. It is quite basic and I think I could make it look prettier over time. Lastly, I want to add more functionality to the device. By this I mean that I want the LEDs to do more and cooler things.
