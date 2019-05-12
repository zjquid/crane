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
int bhome = 0; // grove street, home
int bmug = 90; // use joystick_servo.ino to troubleshoot
int bpos = 0; // grove street, home

// the arm servo - controls the arm of the crane/dipper mech
Servo armservo;
int arm;
int ahome = 120; // use joystick_servo.ino to find what servo position should be default
int adip = 50; // read directly above
int apos = 120; // grove street, home

// activation etc
int act = 0;
int button = 0;

void setup() {
  
	baseservo.attach(9); // base servo connects to pin ~9
	armservo.attach(10); // arm servo connects to pin ~10
	Serial.begin(9600); // for troubleshooting
  pinMode(6, INPUT);

}

void loop() {

  Serial.print("int act = ");
  Serial.println(act);

// init facing user
	baseservo.write(bhome);
  button = analogRead(0);
  Serial.println(button);
// waiting for input (not really waiting)
	if (button > 1022)
	{
    Serial.println(button);
		act = 1;
    Serial.println(act);
	}

// now the program starts
  if (act == 0)
  {
    Serial.println("Waiting...");
    delay(100);
  }
	if (act == 1)
	{
		for (bpos = bhome; bpos < bmug; bpos++) // gradually points the crane assembly towards the mug.
		{
      Serial.print("Base direction = ");
      Serial.println(bpos);
			baseservo.write(bpos); // resets base
      armservo.write(apos); // resets arm
			delay(10);
		} 
// the crane is now at the mug
		for (apos = ahome; apos > adip; apos--) // gradually dips
		{
      Serial.print("Arm direction = ");
      Serial.println(apos);
			armservo.write(apos);
			delay(10);
		} 
// the teabag is dipped
    Serial.println("Brewing tea...");
		delay(900);
// mmm brewtime
    for (apos = adip; apos < ahome; apos++) // gradually raises
    {
      Serial.print("Arm direction = ");
      Serial.println(apos);
      armservo.write(apos);
      delay(10);
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
      delay(10);
    } 
// assembly now back at home
    act = 0;
    Serial.println("Tea is ready");

	}	
	


	}
