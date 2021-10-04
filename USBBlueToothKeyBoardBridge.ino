/*
 Keyboard Controller Example

 Shows the output of a USB Keyboard connected to
 the Native USB port on an Arduino Zero

 created 8 Oct 2012
 by Cristian Maglie

 http://arduino.cc/en/Tutorial/KeyboardController

 This sample code is part of the public domain.
 */

// NOTE I HAVE CHANGE Adafruit_Parser.h to force hardware serial debug output
//#if defined(ARDUINO_SAMD_ZERO) && defined(SERIAL_PORT_USBVIRTUAL)
// // JA CHANGE TO ALLOW HARDWARE SERIAL FORCING
//#define SerialDebug Serial1
//#else
//#define SerialDebug Serial
//#endif

#include <Arduino.h>
#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

#include "BluefruitConfig.h"

// Require keyboard control library
#include <KeyboardController.h>

//#define DEBUG

/*=========================================================================
    APPLICATION SETTINGS

    FACTORYRESET_ENABLE       Perform a factory reset when running this sketch
   
                              Enabling this will put your Bluefruit LE module
                              in a 'known good' state and clear any config
                              data set in previous sketches or projects, so
                              running this at least once is a good idea.
   
                              When deploying your project, however, you will
                              want to disable factory reset by setting this
                              value to 0.  If you are making changes to your
                              Bluefruit LE device via AT commands, and those
                              changes aren't persisting across resets, this
                              is the reason why.  Factory reset will erase
                              the non-volatile memory where config data is
                              stored, setting it back to factory default
                              values.
       
                              Some sketches that require you to bond to a
                              central device (HID mouse, keyboard, etc.)
                              won't work at all with this feature enabled
                              since the factory reset will clear all of the
                              bonding data stored on the chip, meaning the
                              central device won't be able to reconnect.
    MINIMUM_FIRMWARE_VERSION  Minimum firmware version to have some new features
    -----------------------------------------------------------------------*/
    #define FACTORYRESET_ENABLE         0
    #define MINIMUM_FIRMWARE_VERSION    "0.6.6"
/*=========================================================================*/


// Create the bluefruit object,
/* ...hardware SPI, using SCK/MOSI/MISO hardware SPI pins and then user selected CS/IRQ/RST */
Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);

struct {
  char ld; // left digit
  char rd; // right digit 
} const trantable[]= {
  { '0', '0' },
{ '0', '1' },
{ '0', '2' },
{ '0', '3' },
{ '0', '4' },
{ '0', '5' },
{ '0', '6' },
{ '0', '7' },
{ '0', '8' },
{ '0', '9' },
{ '0', 'a' },
{ '0', 'b' },
{ '0', 'c' },
{ '0', 'd' },
{ '0', 'e' },
{ '0', 'f' },
{ '1', '0' },
{ '1', '1' },
{ '1', '2' },
{ '1', '3' },
{ '1', '4' },
{ '1', '5' },
{ '1', '6' },
{ '1', '7' },
{ '1', '8' },
{ '1', '9' },
{ '1', 'a' },
{ '1', 'b' },
{ '1', 'c' },
{ '1', 'd' },
{ '1', 'e' },
{ '1', 'f' },
{ '2', '0' },
{ '2', '1' },
{ '2', '2' },
{ '2', '3' },
{ '2', '4' },
{ '2', '5' },
{ '2', '6' },
{ '2', '7' },
{ '2', '8' },
{ '2', '9' },
{ '2', 'a' },
{ '2', 'b' },
{ '2', 'c' },
{ '2', 'd' },
{ '2', 'e' },
{ '2', 'f' },
{ '3', '0' },
{ '3', '1' },
{ '3', '2' },
{ '3', '3' },
{ '3', '4' },
{ '3', '5' },
{ '3', '6' },
{ '3', '7' },
{ '3', '8' },
{ '3', '9' },
{ '3', 'a' },
{ '3', 'b' },
{ '3', 'c' },
{ '3', 'd' },
{ '3', 'e' },
{ '3', 'f' },
{ '4', '0' },
{ '4', '1' },
{ '4', '2' },
{ '4', '3' },
{ '4', '4' },
{ '4', '5' },
{ '4', '6' },
{ '4', '7' },
{ '4', '8' },
{ '4', '9' },
{ '4', 'a' },
{ '4', 'b' },
{ '4', 'c' },
{ '4', 'd' },
{ '4', 'e' },
{ '4', 'f' },
{ '5', '0' },
{ '5', '1' },
{ '5', '2' },
{ '5', '3' },
{ '5', '4' },
{ '5', '5' },
{ '5', '6' },
{ '5', '7' },
{ '5', '8' },
{ '5', '9' },
{ '5', 'a' },
{ '5', 'b' },
{ '5', 'c' },
{ '5', 'd' },
{ '5', 'e' },
{ '5', 'f' },
{ '6', '0' },
{ '6', '1' },
{ '6', '2' },
{ '6', '3' },
{ '6', '4' },
{ '6', '5' },
{ '6', '6' },
{ '6', '7' },
{ '6', '8' },
{ '6', '9' },
{ '6', 'a' },
{ '6', 'b' },
{ '6', 'c' },
{ '6', 'd' },
{ '6', 'e' },
{ '6', 'f' },
{ '7', '0' },
{ '7', '1' },
{ '7', '2' },
{ '7', '3' },
{ '7', '4' },
{ '7', '5' },
{ '7', '6' },
{ '7', '7' },
{ '7', '8' },
{ '7', '9' },
{ '7', 'a' },
{ '7', 'b' },
{ '7', 'c' },
{ '7', 'd' },
{ '7', 'e' },
{ '7', 'f' },
{ '8', '0' },
{ '8', '1' },
{ '8', '2' },
{ '8', '3' },
{ '8', '4' },
{ '8', '5' },
{ '8', '6' },
{ '8', '7' },
{ '8', '8' },
{ '8', '9' },
{ '8', 'a' },
{ '8', 'b' },
{ '8', 'c' },
{ '8', 'd' },
{ '8', 'e' },
{ '8', 'f' },
{ '9', '0' },
{ '9', '1' },
{ '9', '2' },
{ '9', '3' },
{ '9', '4' },
{ '9', '5' },
{ '9', '6' },
{ '9', '7' },
{ '9', '8' },
{ '9', '9' },
{ '9', 'a' },
{ '9', 'b' },
{ '9', 'c' },
{ '9', 'd' },
{ '9', 'e' },
{ '9', 'f' },
{ 'a', '0' },
{ 'a', '1' },
{ 'a', '2' },
{ 'a', '3' },
{ 'a', '4' },
{ 'a', '5' },
{ 'a', '6' },
{ 'a', '7' },
{ 'a', '8' },
{ 'a', '9' },
{ 'a', 'a' },
{ 'a', 'b' },
{ 'a', 'c' },
{ 'a', 'd' },
{ 'a', 'e' },
{ 'a', 'f' },
{ 'b', '0' },
{ 'b', '1' },
{ 'b', '2' },
{ 'b', '3' },
{ 'b', '4' },
{ 'b', '5' },
{ 'b', '6' },
{ 'b', '7' },
{ 'b', '8' },
{ 'b', '9' },
{ 'b', 'a' },
{ 'b', 'b' },
{ 'b', 'c' },
{ 'b', 'd' },
{ 'b', 'e' },
{ 'b', 'f' },
{ 'c', '0' },
{ 'c', '1' },
{ 'c', '2' },
{ 'c', '3' },
{ 'c', '4' },
{ 'c', '5' },
{ 'c', '6' },
{ 'c', '7' },
{ 'c', '8' },
{ 'c', '9' },
{ 'c', 'a' },
{ 'c', 'b' },
{ 'c', 'c' },
{ 'c', 'd' },
{ 'c', 'e' },
{ 'c', 'f' },
{ 'd', '0' },
{ 'd', '1' },
{ 'd', '2' },
{ 'd', '3' },
{ 'd', '4' },
{ 'd', '5' },
{ 'd', '6' },
{ 'd', '7' },
{ 'd', '8' },
{ 'd', '9' },
{ 'd', 'a' },
{ 'd', 'b' },
{ 'd', 'c' },
{ 'd', 'd' },
{ 'd', 'e' },
{ 'd', 'f' },
{ 'e', '0' },
{ 'e', '1' },
{ 'e', '2' },
{ 'e', '3' },
{ 'e', '4' },
{ 'e', '5' },
{ 'e', '6' },
{ 'e', '7' },
{ 'e', '8' },
{ 'e', '9' },
{ 'e', 'a' },
{ 'e', 'b' },
{ 'e', 'c' },
{ 'e', 'd' },
{ 'e', 'e' },
{ 'e', 'f' },
{ 'f', '0' },
{ 'f', '1' },
{ 'f', '2' },
{ 'f', '3' },
{ 'f', '4' },
{ 'f', '5' },
{ 'f', '6' },
{ 'f', '7' },
{ 'f', '8' },
{ 'f', '9' },
{ 'f', 'a' },
{ 'f', 'b' },
{ 'f', 'c' },
{ 'f', 'd' },
{ 'f', 'e' },
{ 'f', 'f' }
};



struct {
  uint8_t kc;
  uint8_t mask;
} const ModsDesc[] = {
  { 0xE0, LeftCtrl },
  { 0xE1, LeftShift },
  { 0xE2, Alt },
  { 0xE3, LeftCmd },
  { 0xE4, RightCtrl },
  { 0xE5, RightShift },
  { 0xE6, AltGr },
  { 0xE7, RightCmd }
};

void setupBTLE(bool fr=false);

class MyKeyBoardController : public KeyboardController {
  protected:
   const int8_t MODLDIDX=19; 
   uint8_t pressed_;
   uint8_t pressedArray_[6];
   const int8_t keyLdIdx_[6] = { 25, 28, 31, 34, 37, 40 }; 
   char    pressedString_[42+2]; 
  
   
   virtual void OnControlKeysChanged(uint8_t before, uint8_t after) {
#ifdef DEBUG
     Serial1.print("OCKC before: ");
     Serial1.print(before,HEX);
     Serial1.print(":");
     Serial1.print(before & LeftCtrl);
     Serial1.print(" after:");
     Serial1.print(after,HEX);
     Serial1.print(":");
     Serial1.println(after & LeftCtrl);
#endif

     for (int m=0; m<sizeof(ModsDesc); m++) {
      uint8_t mask = ModsDesc[m].mask;
      uint8_t kc = ModsDesc[m].kc;
      if ( !(before & mask) && (after & mask)) {
        OnKeyDown(after, kc);
      } else if ((before & mask) && !(after & mask)) {
        OnKeyUp(after, kc);
      }
     }
   };
   
   virtual void OnKeyDown(uint8_t mod, uint8_t key) {
 #ifdef DEBUG   
      Serial1.print("+ pressed_:");
      Serial1.print(pressed_,HEX);
      Serial1.print(" m:");
      Serial1.print(mod,HEX);
      Serial1.print(" k:");
      Serial1.println(key,HEX);
#endif      
      int i=0;

      if ((mod == 0xf) && (key == 0x15) ) setupBTLE(true);
      
      for (; i<6; i++) {
        if (!(pressed_ & 1<<i)) break;
      }

      if (i<6) {
        uint8_t kldIdx = keyLdIdx_[i];
        pressedString_[MODLDIDX]   = trantable[mod].ld;
        pressedString_[MODLDIDX+1] = trantable[mod].rd;
        pressedString_[kldIdx] = trantable[key].ld;
        pressedString_[kldIdx+1] = trantable[key].rd;
        pressed_ |= ((uint8_t)1<<i);
        pressedArray_[i] = key;
#ifdef DEBUG        
        Serial1.println(pressedString_);
#endif        
        ble.write(pressedString_,43);
      }
    
   };

   virtual void OnKeyUp(uint8_t mod, uint8_t key) {
#ifdef DEBUG    
      Serial1.print("- m:");
      Serial1.print(mod,HEX);
      Serial1.print(" k:");
      Serial1.println(key,HEX);
#endif
      for (int i=0; i<6; i++) {
        if ((pressed_ & ((uint8_t)1<<i)) && (pressedArray_[i] == key)) {
          uint8_t kldIdx = keyLdIdx_[i];
          pressedString_[MODLDIDX]   = trantable[mod].ld;
          pressedString_[MODLDIDX+1] = trantable[mod].rd;
          pressedString_[kldIdx] = '0';
          pressedString_[kldIdx+1] = '0';
          pressed_ &= ~(((uint8_t)1) << i);
#ifdef DEBUG          
          Serial1.println(pressedString_);
#endif          
          ble.write(pressedString_,43);
        }
      }
   };
  public:
   MyKeyBoardController(USBHost &usb) : KeyboardController(usb), pressed_(0) { 
      strncpy(pressedString_,"AT+BLEKEYBOARDCODE=00-00-00-00-00-00-00-00\n",sizeof(pressedString_));
    }
  
};

// on a feather or non-debug Zero, use Serial1 (since USB is taken!)
#define SerialDebug Serial1

// Initialize USB Controller
USBHost usb;

// Attach keyboard controller to USB
MyKeyBoardController keyboard(usb);

// A small helper
void error(const __FlashStringHelper*err) {
  SerialDebug.println(err);
  while (1);
}
void printKey();

uint32_t lastUSBstate = 0;

void setupBTLE(bool fr)
{
  /* Initialise the module */
#ifdef DEBUG  
  SerialDebug.print(F("Initialising the Bluefruit LE module: "));
#endif

  if ( !ble.begin(VERBOSE_MODE) )
  {
    error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }
#ifdef DEBUG  
  SerialDebug.println( F("OK!") );
#endif

  if ( FACTORYRESET_ENABLE || fr )
  {
    /* Perform a factory reset to make sure everything is in a known state */
    SerialDebug.println(F("Performing a factory reset: "));
    if ( ! ble.factoryReset() ){
      error(F("Couldn't factory reset"));
    }
  }

  /* Disable command echo from Bluefruit */
  ble.echo(false);

#ifdef DEBUG
  SerialDebug.println("Requesting Bluefruit info:");
  /* Print Bluefruit information */
  ble.info();
  
  /* Change the device name to make it easier to find */
  SerialDebug.println(F("Setting device name to 'JA Fourier Keyboard': "));
#endif  
  if (! ble.sendCommandCheckOK(F( "AT+GAPDEVNAME=JA Fourier Keyboard" )) ) {
    error(F("Could not set device name?"));
  }

  /* Enable HID Service */
#ifdef DEBUG 
  SerialDebug.println(F("Enable HID Service (including Keyboard): "));
#endif  
  if ( ble.isVersionAtLeast(MINIMUM_FIRMWARE_VERSION) )
  {
#ifdef DEBUG    
    SerialDebug.println("BleHIDEn=on");
#endif    
    if ( !ble.sendCommandCheckOK(F( "AT+BleHIDEn=On" ))) {
      error(F("Could not enable Keyboard"));
    }
  }else
  {
    if (! ble.sendCommandCheckOK(F( "AT+BleKeyboardEn=On"  ))) {
      error(F("Could not enable Keyboard"));
    }
  }

  /* Add or remove service requires a reset */
#ifdef DEBUG  
  SerialDebug.println(F("Performing a SW reset (service changes require a reset): "));
#endif
  if (! ble.reset() ) {
    error(F("Couldn't reset??"));
  }

  /* Disable command echo from Bluefruit */
  ble.echo(false);

#ifdef DEBUG  
  SerialDebug.println();
  SerialDebug.println(F("Go to your phone's Bluetooth settings to pair your device"));
  SerialDebug.println(F("then open an application that accepts keyboard input"));
#endif  
}

void setup()
{
  
  SerialDebug.begin( 115200 );
#ifdef DEBUG  
  SerialDebug.println("USBHost to BlueTooth LE Keyboard Bridge Program started");
#endif

  setupBTLE();

  if (usb.Init() == -1)
	  SerialDebug.println("USB Host did not start.");

#ifdef DEBUG
  SerialDebug.println("USB Host started");
#endif
  delay( 20 );
}

void loop()
{
  // Process USB tasks
  usb.Task();

  uint32_t currentUSBstate = usb.getUsbTaskState();
  if (lastUSBstate != currentUSBstate) {
#ifdef DEBUG    
    SerialDebug.print("USB state changed: 0x"); 
    SerialDebug.print(lastUSBstate, HEX); 
    SerialDebug.print(" -> 0x"); 
    SerialDebug.println(currentUSBstate, HEX);
    switch (currentUSBstate) {
      case USB_ATTACHED_SUBSTATE_SETTLE: SerialDebug.println("Device Attached"); break;
      case USB_DETACHED_SUBSTATE_WAIT_FOR_DEVICE: SerialDebug.println("Detached, waiting for Device"); break;
      case USB_ATTACHED_SUBSTATE_RESET_DEVICE: SerialDebug.println("Resetting Device"); break;
      case USB_ATTACHED_SUBSTATE_WAIT_RESET_COMPLETE: SerialDebug.println("Reset complete"); break;
      case USB_STATE_CONFIGURING: SerialDebug.println("USB Configuring"); break;
      case USB_STATE_RUNNING: SerialDebug.println("USB Running"); break;
    }
#endif    
    lastUSBstate = currentUSBstate;
  }
}
