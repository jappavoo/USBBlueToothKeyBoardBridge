# USBBlueToothKeyBoardBridge
My kludgy code to use an Adafruit QTPY ESP-S3 or A BlueFruit Feather M0 as a usb to
bluetooth keyboard bridge.  The M0 is actually to slow given the use of a second
chip to do the bluetooth communications via 9600 baud ASCII serial AT Commands.

So the function version I am using is the QTPY version which has native support for both
BLE and USB.  Code was very hard to find for host usb communications.  See comments in code
for where I finally found some working examples.

SEE git@github.com:jappavoo/javortex.git for my QMK configuration for the keyboard

TODOS:
SW:
1. Media keys like mute, volume up and down are not working
2. Add support for acting as a mouse -- so that I can have native middle mouse button
3. Work on adding sleep states to save power -- power consumption is probably really bad

HW:
Replace current battery with a bigger one to improve battery life time.

PARTS and connections
   1. Keebio Fourier 1.2 Keyboard kit (See my QMK repo for firmware setup
      git@github.com:jappavoo/javortex.git)
   2. Two Elite-c controlers -- I socketed them on to the keyboard pcb 
   3. 3D printed case -- adjusted middle height + 5 mm to account for socketed elite-c controllers
   4. Adafruit PowerBoost 500 -- charge battery, provide +5 volts for usb vbus, and use enable to
      turn ble functionality on and off
   5. QTPY-ESP32 to act as bluetooth bridge: acts as usb host for one of the elite-c controllers
      and connects to computer as BLE keyboard.  It relays keyreports from elite-c to computer
   6. hacked up cables to connect things up as follows
       ELITE-C
        VBUS - to PowerBoost 500 +5 and to custom usb cable VBUS (RED) that connects QTPY
	GND  - to PowerBoost 500 GND and to custom usb cable GND (BLACK) that connects QTPY
	D+, D- - to custom usb cable WHITE and GREEN that connects QTPY
   7. added header pins to QTPY to support serial debugging on HW UART of QTPY
   8. switch connected to PowerBoost 500 enable and gnd.  Close switch to disable PowerBoost 500
      +5 output -- will still charge battery -- exposed at TSSR cable jack in case
   9. Added opening in case to expose usb port of powerboost 500 -- use this to charge or power
      bluetooth functionality
  10. *** DON'T think it is save to connect via physical usb connections and powerboost and both
      will be trying to drive VBUS of usb -- have taped usb openning in case closed to avoid
      mistakes
  11. Adafruit USB UART breakout cable for debugging
  
NOTES:

   USB Power is provided via PowerBoost500 that is connected to a battery or external usb source
   +5 from the power boost 500 is connected to USB voltage pin on elite-c
   GND from power boost 500 is connect to GND pin on elite-c
   PowerBoost Enable is connected to gnd via switch to disable outputs (acts as on off switch)

   QTPY  Serial1 can be used to debug code
       connect white of break out cable to TX on QTPY
       connect green of break out cable to RX on QTPY
       disconnect Powerboost from  elite-c and connect VBUS +5 and GND to USB +5 and GND 
       must only have one power source being used and must match computer
  
   To recharge plug usb pwer into power boost usb port


 Most of this code came from https://github.com/touchgadget/esp32-usb-host-demos
 Many thinks!!! It was the only working example I could find for host usb 
 communications that works for ESP32-S3

JA HACKS :
 To program QTPY connect usb to computer usb directly and reset board (hold boot, click reset, release boot)
 DEBUGGING
   USE Serial1 via usb break out to test:
   attach power from usb breakout cable to elite-c VBUS and GND via cable I have hacked on
   attach USB transmit (white) of breakout to QTPY TX pin
   attach USB recieve  (green) of breakout to QTPY RX pin


