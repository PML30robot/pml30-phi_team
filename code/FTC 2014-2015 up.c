#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Motor,  mtr_S1_C1_1,     FR,            tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     BR,            tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     FL,            tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     BL,            tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     UL,            tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     ULT,           tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C4_1,     UR,            tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C4_2,     URT,           tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S2_C1_1,    servoBall,            tServoContinuousRotation)
#pragma config(Servo,  srvo_S2_C1_2,    servoTube,            tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    servoMvClaws,         tServoStandard)
#pragma config(Servo,  srvo_S2_C1_4,    servoTube2,           tServoStandard)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

int a = 64;

void Servosetup()
{
		servo[servoClaws] = 235;
	servo[servoBall] = 127;
	servo[servoTube] = 152;
	servo[servoMvClaws] = 255;
	nMotorEncoder[FR] = 0;
	nMotorEncoder[FL] = 0;
	nMotorEncoder[BR] = 0;
	nMotorEncoder[BL] = 0;
	nMotorEncoder[UR] = 0;
	nMotorEncoder[UL] = 0;
	nMotorEncoder[URT] = 0;
	nMotorEncoder[ULT] = 0;
}

void motion(int l_ramp_goal, int a)
{
	int enc;
  nMotorEncoder[BR] = 0;
	nMotorEncoder[BL] = 0;
	while((a * (-nMotorEncoder[BR]) / 1000) * 3.14159265 * 10 < l_ramp_goal - 50)
	{
	  motor[FR] = a * 100;
    motor[BR] = a * 100;
    motor[FL] = a * 100;
    motor[BL] = a * 100;
    enc = -nMotorEncoder[BR];
    nxtDisplayBigTextLine(2, "%i", enc);
  }

  motor[FR] = -100;
  motor[BR] = -100;
  motor[FL] = -100;
  motor[BL] = -100;
//  wait1Msec(100);

  while((a * (-nMotorEncoder[BR]) / 1000) * 3.14159265 * 10 < l_ramp_goal)
	{
	  motor[FR] = a * 20;
    motor[BR] = a * 20;
    motor[FL] = a * 20;
    motor[BL] = a * 20;
  }
  servo[servoMvClaws] = 18;
  while(( a * (-nMotorEncoder[BR]) / 1000) * 3.14159265 * 10 < l_ramp_goal + 18)
  {
    motor[FR] = a * 10;
    motor[BR] = a * 10;
    motor[FL] = a * 10;
    motor[BL] = a * 10;

  }

  motor[FR] = 0;
  motor[BR] = 0;
  motor[FL] = 0;
  motor[BL] = 0;
}

void elevator()
{
	int enc;
	nMotorEncoder[UL] = 0;
	while(nMotorEncoder[UL] < 12500)
	{
    motor[UR] = -100;
    motor[UL] = 100;
    servo[servoTube] = 152;
    enc = nMotorEncoder[UL];
    //nxtDisplayBigTextLine(1, "%i", enc);
    if(nMotorEncoder[UL] > 5000)
    	servo[servoBall] = 127;
  }
  motor[UR] = 0;
  motor[UL] = 0;
  servo[servoTube] = 152;

 	while(nMotorEncoder[UL] > 8500)
	{
    motor[UR] = 100;
    motor[UL] = -100;
    servo[servoTube] = 152;
    servo[servoBall] = 127;
  }
  motor[UR] = 0;
  motor[UL] = 0;

  servo[servoTube] = 8;
  wait1Msec(4000);

  servo[servoTube] = 152;
  while(nMotorEncoder[UL] > 0)
  {
    motor[UR] = 100;
    motor[UL] = -100;
    servo[servoBall] = 127;
  }

  motor[UR] = 0;
  motor[UL] = 0;
  servo[servoBall] = 255;
}

void rotate(float l_ramp_goal)
{
	nMotorEncoder[BR] = 0;
	while((-nMotorEncoder[BR] / 1000) * 3.14159265 * 10 < l_ramp_goal)
	{
	  motor[FR] = 100;
    motor[BR] = 100;
    motor[FL] = -100;
    motor[BL] = -100;
  }

  motor[FR] = -100;
  motor[BR] = -100;
  motor[FL] = 100;
  motor[BL] = 100;

  motor[FR] = 0;
  motor[BR] = 0;
  motor[FL] = 0;
  motor[BL] = 0;

 // servo[servoMvClaws] = 90;
}



task main()
{
 waitForStart();

	//StartTask(stage);
	//StartTask(tube);
   servo[servoMvClaws] = 50;
   servo[servoBall] = 255;
   motion(310, 1);
   elevator();
   //servo[servoBall] = 127;
   //rotate(0.1);
   //motion(100, -1);

	while(true)
	{
		motor[FR] = 0;
    motor[BR] = 0;
    motor[FL] = 0;
    motor[BL] = 0;
    motor[UR] = 0;
    motor[UL] = 0;
  }
}
