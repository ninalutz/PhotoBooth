
// Include Libraries
#include "Arduino.h"
#include "Button.h"
#include "lab.h"
#include "Adafruit_Thermal.h"
#include "lab.h"
#include "SoftwareSerial.h"
#define TX_PIN 6 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 5 // Arduino receive   GREEN WIRE   labeled TX on printer

// Pin Definitions
#define ARCADEBUTTON_PIN_NO	2

SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor

// Global variables and defines

// object initialization
Button ArcadeButton(ARCADEBUTTON_PIN_NO);


// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(19200);
    mySerial.begin(19200);  // Initialize SoftwareSerial
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");

    pinMode(7, OUTPUT); digitalWrite(7, LOW);
    
    ArcadeButton.init();

}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
    bool ArcadeButtonVal = ArcadeButton.read();
    
    Serial.print(F("Val: ")); 
    
    Serial.println(ArcadeButtonVal);

    if(ArcadeButtonVal){
        Serial.println("HELLO");
        doPrinter();
        delay(2000);
      }
}


void doPrinter(){
  printer.begin();        // Init printer (same regardless of serial type)
  // Print the 75x75 pixel logo in adalogo.h:
  printer.feed(2);
  printer.println("Thanks for coming to 99F <3!");
  printer.printBitmap(400, 216, lab_data);
  printer.println("Save the date for our");
  printer.println("Valentines Party!");
  printer.feed(4);
  printer.setDefault(); // Restore printer to defaults
  printer.sleep();      // Tell printer to sleep
  delay(3000L);         // Sleep for 3 seconds
  printer.wake();       // MUST wake() before printing again, even if reset
  }
