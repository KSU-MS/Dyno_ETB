/*********************
Kennesaw State ETB Servo code
Uses this servo:
https://www.hobbytown.com/ecopower-wp110t-cored-waterproof-high-torque-metal-gear-digital-servo-ecp-110t/p734713

**********************/

// include the library code:
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_RGBLCDShield.h>
#include <utility/Adafruit_MCP23017.h>
#include <Servo.h>

// The shield uses the I2C SCL and SDA pins. On classic Arduinos
// this is Analog 4 and 5 so you can't use those for analogRead() anymore
// However, you can connect other I2C sensors to the I2C bus and share
// the I2C bus.
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
Servo etb_servo;
int etbClosed=0;
int etbOpen=90;
int etbPosition = 0; //variable that contains the degrees

//
// These #defines make it easy to set the backlight color
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

//State var define
uint8_t state=0;
void etb_state_machine(uint8_t etb_state);
void setup() {
  // Debugging output
  Serial.begin(9600);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  etb_servo.attach(3);
  // Print a message to the LCD. We track how long it takes since
  // this library has been optimized a bit and we're proud of it :)
  int time = millis();
  lcd.print("ETB Powered UP!");
  lcd.setBacklight(WHITE);
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the current position of ETBt:
  lcd.print(etbPosition);

  //Check for button presses
  uint8_t buttons = lcd.readButtons();

  //Serial input from keyboard for custom TB angles
  if(Serial.available()){
    String message=(Serial.readString());
    int userreq=message.toInt();
    Serial.println(userreq);
    //Validation for inputs being int between 0-90 degrees
    if(userreq<=etbOpen && userreq>=etbClosed){
      etb_servo.write(userreq);
    }
    //Print out custom angle to LCD
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Custom angle ");
    lcd.setCursor(0,1);
    lcd.print(userreq);
  }

  //Actions to take depending on what button was pressed
  if (buttons) {
    lcd.clear();
    lcd.setCursor(0,0);
    if (buttons & BUTTON_UP) {
      lcd.print("+1 deg.");
      lcd.setBacklight(YELLOW);
      etbPosition++;
    }

    if (buttons & BUTTON_DOWN) {
      lcd.print("-1 deg.");
      lcd.setBacklight(RED);
      etbPosition--;
    }

    if (buttons & BUTTON_LEFT) {
      lcd.print("Closed or Idle ");
      lcd.setBacklight(TEAL);
      etbPosition=etbClosed; 
    }

    if (buttons & BUTTON_RIGHT) {
      lcd.print("Wide Open! ");
      lcd.setBacklight(GREEN);
      etbPosition=etbOpen;
    }
    
    if (buttons & BUTTON_SELECT) {
      lcd.print("Zero");
      lcd.setBacklight(VIOLET);
      etbPosition=0;
    }
    
    //Checks for invalid ranges on TPS to prevent +/- beyond bounds
    if(etbPosition>etbOpen){
      etbPosition=etbOpen;
    }
    if(etbPosition<etbClosed){
      etbPosition=etbClosed;
    }
    
    //Final write of position to servo
    etb_servo.write(etbPosition);
    delay(100);
    lcd.setCursor(5,1);
    lcd.print(etb_servo.read());    
  }



}
void etb_state_machine(uint8_t etb_state){
  switch (etb_state)  {
    case 0:{

    }
    case 1:{

    }
    case 2:{

    }
    case 3:{

    }
  }
}