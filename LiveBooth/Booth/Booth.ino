/*------------------------------------------------------------------------
  Example sketch for Adafruit Thermal Printer library for Arduino.
  Demonstrates a few text styles & layouts, bitmap printing, etc.

  IMPORTANT: DECLARATIONS DIFFER FROM PRIOR VERSIONS OF THIS LIBRARY.
  This is to support newer & more board types, especially ones that don't
  support SoftwareSerial (e.g. Arduino Due).  You can pass any Stream
  (e.g. Serial1) to the printer constructor.  See notes below.

  You may need to edit the PRINTER_FIRMWARE value in Adafruit_Thermal.h
  to match your printer (hold feed button on powerup for test page).
  ------------------------------------------------------------------------*/

#include "Adafruit_Thermal.h"
#include "lab.h"
#include "SoftwareSerial.h"
#define TX_PIN 6 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 5 // Arduino receive   GREEN WIRE   labeled TX on printer

SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor

// -----------------------------------------------------------------------
const int buttonPin = 2; //button to trigger the things

word buttonState = 0xAAAA; //state to start the button 

void setup() {

  // This line is for compatibility with the Adafruit IotP project pack,
  // which uses pin 7 as a spare grounding point.  You only need this if
  // wired up the same way (w/3-pin header into pins 5/6/7):
  pinMode(7, OUTPUT); digitalWrite(7, LOW);
  pinMode(buttonPin, INPUT_PULLUP);

  // NOTE: SOME PRINTERS NEED 9600 BAUD instead of 19200, check test page.
  mySerial.begin(19200);  // Initialize SoftwareSerial
  Serial.begin(19200);
  Serial.flush();
}

void loop() {
  buttonState = (buttonState << 1) | digitalRead(buttonPin); // logic calc -- thanks C 
  if(buttonState == 1){
     doPrinter();
     buttonState = 0;
  }
}

void doPrinter(){
  printer.begin();        // Init printer (same regardless of serial type)
  // Print the 75x75 pixel logo in adalogo.h:
  printer.feed(2);
  printer.print("Thanks for coming to 99F <3!");
 // printer.printBitmap(400, 216, lab_data);
  printer.println("Save the date for");
  printer.println("our Valentines Party!");
  printer.feed(2);
  printer.setDefault(); // Restore printer to defaults
  printer.sleep();      // Tell printer to sleep
  delay(3000L);         // Sleep for 3 seconds
  printer.wake();       // MUST wake() before printing again, even if reset
  }
