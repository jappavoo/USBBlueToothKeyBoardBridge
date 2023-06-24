# USBBlueToothKeyBoardBridge
My kludgy code to use an Adafruit BlueFruit Feather M0 as a usb to bluetooth keyboard bridge


NOTES:

   USB Power is provided via PowerBoost500 that is connected to a battery or external usb source
   +5 from the power boost 500 is connected to USB voltage pin on M0
   GND from power boost 500 is connect to GND pin on M0
   PowerBoost Enable is connected to gnd via switch to disable outputs (acts as on off switch)


   feather Serial1 can be used to debug codeL
       connect white of break out cable to TX on Feather
       connect green of break out cable to RX on Feather
       connect +5 and GND to USB and gnd normally connect to power boost
       must only have one power source being used


   To recharge plug usb pwer into power boost usb port

   Keyboard should be plugged into the feather usb port.


