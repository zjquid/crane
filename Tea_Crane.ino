/*
 * written by Andrew Hooke
 * 4/29/19 - 
 * 
 * Servo connections: 
 * Brown: ground
 * Red: 5v
 * Orange: input pin
 */

#include <Servo.h>

// the base servo - controls the direction of the crane
Servo baseservo;
int base;
int bhome = 20; // grove street, home
int bmug = 90; // position of mug
int bpos = 20; // same as bhome, this changes throughout program

// the arm servo - controls the arm of the crane/dipper mech
Servo armservo;
int arm;
int ahome = 165; // grove street, home
int adip = 110; // read directly above
int apos = 165; // same as apos, this changes throughout program

// activation and how the program gets started
int act = 0;
int button = 0;

void setup() {
  
	baseservo.attach(9); // base servo connects to pin ~9
	armservo.attach(10); // arm servo connects to pin ~10
  baseservo.write(bhome); // base servo moves to home position  
  armservo.write(ahome); // arm servo moves to home position
	Serial.begin(9600); // for troubleshooting - any Serial commands are purely for troubleshooting

}

void loop() {

  Serial.print("int act = ");
  Serial.println(act);

// init facing user
	baseservo.write(bhome);
  button = analogRead(0);
  Serial.println(button);
// waiting for input (not really waiting)
	if (button > 1022) // since we are using an analog input for the button, the value must be > 1022, rather than 'high' or 'low'. This is more precise.
	{
    Serial.println(button);
		act = 1;
    Serial.println(act);
	}

// now the program starts
  if (act == 0)
  {
    Serial.println("Waiting..."); // waiting for button to be pressed
    delay(100);
  }
	if (act == 1) // button is now pressed
	{
		for (bpos = bhome; bpos < bmug; bpos++) // gradually points the crane assembly towards the mug - changes bpos and writes servo to variable
		{
      Serial.print("Base direction = ");
      Serial.println(bpos);
			baseservo.write(bpos); // resets base
      armservo.write(apos); // resets arm
			delay(10); // change delay so it makes sense
		} 
    
// the crane is now at the mug

		for (apos = ahome; apos > adip; apos--) // gradually dips - changes apos and writes servo to variable
		{
      Serial.print("Arm direction = ");
      Serial.println(apos);
			armservo.write(apos);
			delay(10); // change delay so it makes sense
		} 
    
// the teabag is dipped

    Serial.println("Brewing tea...");
		delay(900); // change delay to whatever the brewing time is (90 seconds, 90000 milliseconds is typical)
   
// mmm brewtime

    for (apos = adip; apos < ahome; apos++) // gradually raises
    {
      Serial.print("Arm direction = ");
      Serial.println(apos);
      armservo.write(apos);
      delay(10); // change delay so it makes sense
    }
    
// arm returned to home position

    Serial.println("Watch for drips!");
    delay (600);
    
// waits for drips

    for (bpos = bmug; bpos > bhome; bpos--) // gradually points the crane assembly back to home/driptray.
    {
      Serial.print("Base direction = ");
      Serial.println(bpos);
      baseservo.write(bpos);
      delay(10); // change delay so it makes sense
    } 
    
// assembly now back at home

    act = 0; // this makes it so the program won't run again until the button is pressed
    Serial.println("Tea is ready");

	}	
	


	}
