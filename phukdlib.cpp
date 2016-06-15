/*
The following is Irongeek's PHUKD Library
 ver 0.4

 Project Page:
 http://www.irongeek.com/i.php?page=security/programmable-hid-usb-keystroke-dongle 

 To learn more about Teensyduino see:
 http://www.pjrc.com/teensy/teensyduino.html
 Look in arduino-xxxx\hardware\teensy\cores\usb_hid\usb_api.h for key definitions
 Edit arduino-xxxx\hardware\teensy\cores\usb_hid\usb_private.h to change USB Vendor and Product ID

 Compile Notes: Make sure you set the correct board type under Tools->Board, and the correct Tools->USB type as well.

 OS X Spotlight and Terminal code provided by Adam Baldwin and Aaron Howell ngenuity-is.com / evilpacket.net
 jp (.ronin) http://www.hackfromacave.com also provide some source code for the OS X side, but I ended up using
 Adam and Aaron's.

 Should work now with Arduino 1.0.

 */

#include "WProgram.h"
#include "phukdlib.h"

/********************************************************************
 * Opens the run bar and executes the command.
 ********************************************************************/
void CommandAtRunBarMSWIN(const char *SomeCommand){
  //digitalWrite(ledPin, HIGH);   // set the LED on
  for(int i=0; i<5; i++){
    Keyboard.set_modifier((uint8_t)MODIFIERKEY_LEFT_GUI); //Windows key
    Keyboard.set_key1((uint8_t)KEY_R); // use r key
    Keyboard.send_now(); // send strokes
    delay(150);
    Keyboard.set_modifier(0); //prep release of  control keys
    Keyboard.set_key1(0); //have to do this to keep it from hitting key multiple times.
    Keyboard.send_now(); //Send the key changes
    delay(150);
  }
  delay(1500);
  SlowType(SomeCommand, 50);
  Keyboard.set_key1((uint8_t)KEY_ENTER);
  Keyboard.send_now();
  Keyboard.set_key1(0);
  Keyboard.send_now();
}

/********************************************************************
 * Opens the run bar and executes the command.
 ********************************************************************/
void CommandAtRunBarGnome(const char *SomeCommand){
  //digitalWrite(ledPin, HIGH);   // set the LED on
  Keyboard.set_modifier((uint8_t)MODIFIERKEY_ALT); //Hold Alt key
  Keyboard.set_key1((uint8_t)KEY_F2); // use F2 key
  Keyboard.send_now(); // send strokes
  Keyboard.set_modifier(0); //prep release of  control keys
  Keyboard.set_key1(0); //have to do this to keep it from hitting key multiple times.
  Keyboard.send_now(); //Send the key changes
  delay(1500);
  SlowType(SomeCommand, 50);
  Keyboard.set_key1((uint8_t)KEY_ENTER);
  Keyboard.send_now();
  Keyboard.set_key1(0);
  Keyboard.send_now();
}

/********************************************************************
 * Opens spotlight and executes the command. -Adam Baldwin
 ********************************************************************/
void CommandAtRunBarOSX(const char *SomeCommand){
  Keyboard.set_modifier((uint8_t)MODIFIERKEY_GUI);
  Keyboard.set_key1((uint8_t)KEY_SPACE); // use Space key
  Keyboard.send_now(); // send strokes
  delay(1500);  // Weird timing for slow systems
  Keyboard.set_modifier(0); //prep release of  control keys
  Keyboard.set_key1(0); //have to do this to keep it from hitting key multiple times.
  Keyboard.send_now(); //Send the key changes
  delay(1000);
  SlowType(SomeCommand, 50);
  delay(1000);
  Keyboard.set_key1((uint8_t)KEY_ENTER);
  Keyboard.send_now();
  Keyboard.set_key1(0);
  Keyboard.send_now();
}

/********************************************************************
 * Opens New Terminal and executes command. -Adam Baldwin
 ********************************************************************/
void CommandAtNewTerminal(const char *SomeCommand){
  CommandAtRunBarOSX("Terminal");
  // Open a new terminal in case another one was open
  delay(1000);
  Keyboard.set_modifier((uint8_t)MODIFIERKEY_GUI);
  Keyboard.set_key1((uint8_t)KEY_N);
  Keyboard.send_now(); // send strokes
  Keyboard.set_modifier(0); //prep release of  control keys
  Keyboard.set_key1(0); //have to do this to keep it from hitting key multiple times.
  Keyboard.send_now(); //Send the key changes
  delay(1500);
  SlowType(SomeCommand, 50);
  Keyboard.set_key1((uint8_t)KEY_ENTER);
  Keyboard.send_now();
  Keyboard.set_key1(0);
  Keyboard.send_now();
  Keyboard.print("exit");
  Keyboard.set_key1((uint8_t)KEY_ENTER);
  Keyboard.send_now();
  Keyboard.set_key1(0);
  Keyboard.send_now();
}

/********************************************************************
 * Opens the run bar and executes the command. -Aaron Howell
 ********************************************************************/
void ShrinkCurWinOSX(){
  Keyboard.set_modifier((uint8_t)MODIFIERKEY_GUI); //clover key
  Keyboard.set_key1((uint8_t)KEY_H); // clover-h hides window, clover-m minimizes window
  Keyboard.send_now();
  delay(250);
  Keyboard.set_modifier(0);
  Keyboard.set_key1(0);
  Keyboard.send_now();
}

/********************************************************************
 * Shrinks the active window to help hide it.
 ********************************************************************/
void ShrinkCurWin(){
  Keyboard.set_modifier((uint8_t)MODIFIERKEY_ALT);
  Keyboard.set_key1((uint8_t)KEY_SPACE);
  Keyboard.send_now();
  delay(250);
  Keyboard.set_modifier(0);
  Keyboard.set_key1(0);
  Keyboard.send_now();
  Keyboard.print("n");
}

void ShrinkCurWinMSWIN(){
  ShrinkCurWin();
}

void ShrinkCurWinGnome(){
  ShrinkCurWin();
}

/********************************************************************
 * This function simplifies the pressing and releasing of a key.
 ********************************************************************/
void PressAndRelease(int KeyCode,int KeyCount){
  int KeyCounter=0;
  for (KeyCounter=0;  KeyCounter!=KeyCount; KeyCounter++){
    Keyboard.set_key1(KeyCode); // use r key
    Keyboard.send_now(); // send strokes
    Keyboard.set_key1(0);
    Keyboard.send_now(); // send strokes
  }
}

/*********************************************************************
 * ledkeys returns the setting of the "lock keys"
 * Num Lock = 1
 * CAPS Lock = 2
 * Scroll Lock = 4
 * Add them together to get combos, for example if all three are on, 7 would be the result
 *********************************************************************/
int ledkeys(void)
{
  return int(keyboard_leds);
}

/*********************************************************************
 * Returns TRUE if NUM Lock LED is on and FALSE otherwise. 
 *********************************************************************/
boolean IsNumbOn(void)
{
  if ((ledkeys() & 1) == 1){
    return true;
  }
  else {
    return false;
  }
}

/*********************************************************************
 * Returns TRUE if Caps Lock LED is on and FALSE otherwise. 
 **********************************************************************/
boolean IsCapsOn(void)
{
  if ((ledkeys() & 2) == 2){
    return true;
  }
  else {
    return false;
  }
}

/*********************************************************************
 * Returns TRUE if Scroll Lock LED is on and FALSE otherwise. 
 **********************************************************************/
boolean IsScrlOn(void)
{
  if ((ledkeys() & 4) == 4){
    return true;
  }
  else {
    return false;
  }
}

/********************************************************************
 * Type with a delay between keystrokes
 ********************************************************************/
//void CommandAtRunBarMSWIN(const char *SomeCommand){
void SlowType(const char *SomeCommand, int Delay){
  for(const char* it = SomeCommand; *it; ++it) {
    Keyboard.print(*it);
    delay(Delay);
  }
}

//********************************************************************
