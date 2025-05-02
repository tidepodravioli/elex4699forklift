///////////////////////////////////////////////////////////////////////////////////////////
// Tiva C TM4C123G Energia Communication System for ELEX4618 & ELEX4699
// Prepared by Craig Hennessey
// As modified for use by Rafael Banalan
// Last Edited: May 2, 2025
///////////////////////////////////////////////////////////////////////////////////////////

#include <Servo.h>

#define SWITCH_S1 33
#define SWITCH_S2 32
#define SWITCH_J1 5

#define RGBLED_RED_PIN 39
#define RGBLED_GRN_PIN 38
#define RGBLED_BLU_PIN 37

#define JOYSTICK_X 2
#define JOYSTICK_Y 26

#define SERVO_PORT0 19

// protocol CHANNEL integer indexes into array to select to the A? pin
#define DIGITAL_PINS 6
#define ANALOG_PINS 5
#define SERVO_PINS 1
int D_PIN [] = {SWITCH_S1, SWITCH_S2, RGBLED_RED_PIN, RGBLED_GRN_PIN, RGBLED_BLU_PIN, SWITCH_J1};
int A_PIN [] = {JOYSTICK_X, JOYSTICK_Y, RGBLED_RED_PIN, RGBLED_GRN_PIN, RGBLED_BLU_PIN};
int S_PIN [] = {SERVO_PORT0};

// Constants for the ELEX4618 communication protocol TYPE field
enum {ALIVE = -1, DIGITAL = 0, ANALOG, SERVO};

Servo myservo[SERVO_PINS];

int type;
int channel;
int value;

#define BAUD_RATE 115200

void setup()
{
  // initialize serial port
  Serial.begin(BAUD_RATE);

  // initialize digital IO to Input 
  for (int digital_index = 1; digital_index <= 40; digital_index++)
  {
    pinMode(digital_index, INPUT_PULLUP);
  }
  // initialize joystick switches
  pinMode(JOYSTICK_X, INPUT);
  pinMode(JOYSTICK_Y, INPUT);

  // initialize pushbuttons on uC to Input (not on Boosterpack)
  pinMode(SWITCH_S1, INPUT_PULLUP);
  pinMode(SWITCH_S2, INPUT_PULLUP);
  pinMode(SWITCH_J1, INPUT_PULLUP);

  // initialize LED on uC to ON (not on Boosterpack). Turn off RGB LED
  pinMode(RED_LED, OUTPUT);
  digitalWrite(RED_LED, HIGH);
  pinMode(RGBLED_RED_PIN, OUTPUT);
  pinMode(RGBLED_GRN_PIN, OUTPUT);
  pinMode(RGBLED_BLU_PIN, OUTPUT);
  digitalWrite(RGBLED_RED_PIN, LOW);
  digitalWrite(RGBLED_GRN_PIN, LOW);
  digitalWrite(RGBLED_BLU_PIN, LOW);

  // initialize servo pins to output
  pinMode(SERVO_PORT0, OUTPUT);

  // Attach servo pins to the servo objects
  myservo[0].attach(SERVO_PORT0);

/*
  Serial.print("\n////////////////////////////////////////////////////////////////////////////////////");
  Serial.print("\n// ELEX 4618 IO Communication for TM4C123G V3.0 Student");
  Serial.print("\n// By: STUDENT NAME, DATE");
  Serial.print("\n// TM4C123G: Digital In/Out 1-40 on 4x 10 pin headers");
  Serial.print("\n// TM4C123G: Digital In 41 & 42 are PUSH1 and PUSH2 (TM4C123G)");
  Serial.print("\n// TM4C123G: Analog in A0 to A15 (0-15)");
  Serial.print("\n// TM4C123G: Analog out not supported");
  Serial.print("\n// TM4C123G: Servo 19,4,5,6 header (0-3)");
  Serial.print("\n// BoosterPack: Joystick (Analog 9,15), Accelerometer (Analog 11,13,14)");
  Serial.print("\n// BoosterPack: Buttons (Digital 32,33), LED (Digital 37,38,39)");
  Serial.print("\n// Protocol: DIRECTION (G/S) TYPE (0=D, 1=A, 2=S) CHANNEL VALUE");
  Serial.print("\n// Example: G 0 0, S 2 1 100");
  Serial.print("\n////////////////////////////////////////////////////////////////////////////////////\n");*/
}

void loop()
{
  /////////////////////////////////////////
  // TODO: Flash LED ON/OFF
  // Hint: If you use DELAY your program will run slowly.
  // Hint: Use millis() to measure elapsed time and toggle LED
  /////////////////////////////////////////

  // While there is data in the serial port buffer, continue to process
  while (Serial.available() > 0)
  {
    // Read the first character
    char ch = Serial.read();

    // If it's a COMMAND character (first character in ELEX4618 protocol) then move to next step
    if (ch == 'G' || ch == 'g' || ch == 'S' || ch == 's')
    {      
      // Read the space delimited next value as an integer (TYPE from protocol)
      type = Serial.parseInt();
      // Read the space delimited next value as an integer (CHANNEL from protocol)
      channel = Serial.parseInt();

      // If a SET command then read the space delimited next value as an integer (VALUE from protocol)
      if (ch == 'S' || ch == 's')
      {      
        value = Serial.parseInt();
      }

      /////////////////////////////////////////
      // TODO: Get / Set Digital
      /////////////////////////////////////////
      // IF GET DO A DIGITAL READ and return the VALUE
      // IF SET DO A DIGITAL WRITE
      bool sendAck = true;
      
      if(ch == 'G' || ch == 'g')
      {
        if(type == ALIVE)
        { 
          value = -1;
          sendAck = true;
        }
        else if(type == DIGITAL && ch >= 0 && channel < DIGITAL_PINS)
        {
          value = digitalRead(D_PIN[channel]);
          sendAck = true;
        }
        else if(type == ANALOG && channel >= 0 && channel < ANALOG_PINS)
        {
          value = analogRead(A_PIN[channel]);
          sendAck = true;
        }
        else if(type == SERVO && channel >= 0 && channel < SERVO_PINS)
        {
          value = myservo[channel].read();
          sendAck = true;
        }
      }
      else if(ch == 'S' || ch == 's')
      {
        if(type == DIGITAL && channel >= 0 && channel < DIGITAL_PINS)
        {
          digitalWrite(D_PIN[channel], value);
          sendAck = true;
        }
        else if(type == ANALOG && channel >= 0 && channel < ANALOG_PINS)
        {
          analogWrite(A_PIN[channel], value);
          sendAck = true;
        }
        else if(type == SERVO && channel >= 0 && channel < SERVO_PINS)
        {
          myservo[channel].write(value);
          sendAck = true;
        }
      }

      // Format and send response
      if(sendAck)
      {
        Serial.print ("A ");
        Serial.print (type);
        Serial.print (" ");
        Serial.print (channel);
        Serial.print (" ");
        Serial.print (value);
        Serial.print ("\n");
      }
      }
  }
}
