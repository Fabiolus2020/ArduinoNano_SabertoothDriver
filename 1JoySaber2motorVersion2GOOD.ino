//created by Fabiolus 2021/01/08
//the_fabiolous@hotmail.com
/*


  Reference:
  - https://www.dimensionengineering.com/info/arduino
  - https://www.dimensionengineering.com/datasheets/Sabertooth2x25v2.pdf
  dipswitch wizzard
  - https://www.dimensionengineering.com/datasheets/SabertoothDIPWizard/start.htm

  Hardware:
  - 1x Arduino Uno
  - 1x Sabertooth 25 Dual 25A Motor Driver version 2
  - 1 x Mini Thumb Joystick
  - 2 x dc motors (using servo library since Sabertooth seem to only accept for R/C or micro controller control


  Features:
  - Move 2 motors using one Joystick Independently

  The circuit:
  - First motor signal out PWM pin 6 to sabertooth S1
  - Second motor signal out PWM pin 5 to sabertooth S2
  - Joystick1 X angle attached to analog pins A0
  - Joystick1 Y angle attached to analog pins A1


  Author:
  Fabiolus
sabertooth switch
1= down rc mode input
2= up rc mode input
3= up using Nimh battery
4= up mixed mode differential drive
5= down exponential response
6= down 4x sensivity mode

*/

#include <Servo.h>

const int joyX1 = A0;        // Joystick 1 X Axis
const int joyY1 = A1;        // Joystick 1 Y Axis
int SW = 2;                 // button
int SW_state = 0;           //button state
int Xval;                  //value to control speed for POT X
int Yval;                  //value to control speed for POT Y

Servo ST1, ST2;     //two motors

#define GreenLed  7    // green led
#define RedLed  8      // red led
void setup() {

// attach Servo and assign pin with min/max
  ST1.attach(6, 1000, 2000);
  ST2.attach(5, 1000, 2000);


//setting pin mode
  pinMode(SW, INPUT_PULLUP);
  pinMode(GreenLed, OUTPUT);
  pinMode(RedLed, OUTPUT);


  // Inizialize Serial
  Serial.begin(9600);
}


void loop() {

  //SW_state = digitalRead(SW);
  //Serial.println(SW_state);
  // analogRead values go from 0 to 1023, analogWrite values from 0 to 255

  Xval = analogRead(joyX1);
  Xval = map(Xval, 0, 1023, 0, 180);     // scale it to use it with the servo (result  between 0 and 180)

  Yval = analogRead(joyY1);
  Yval = map(Yval, 0, 1023, 0, 180);     // scale it to use it with the servo (result between 70 and 180)


  // sets the servo position according to the scaled value
 // ST1.write(servoVal);                           // sets the servo position according to the scaled value
 // ST2.write(servoVal2);
  delay(15);                                        // waits for the servo to get there

  if (digitalRead(SW) == LOW) {

    ST1.attach(6, 1000, 2000);
    ST2.attach(5, 1000, 2000);
    ST1.write(Xval);                           // sets the servo position according to the scaled value
    ST2.write(Yval);

    digitalWrite(RedLed, LOW);
    digitalWrite(GreenLed, HIGH);

  }  else  {

    ST1.detach();                           // sets the servo position according to the scaled value
    ST2.detach();
    digitalWrite(RedLed, HIGH);
    digitalWrite(GreenLed, LOW);
  }

}
