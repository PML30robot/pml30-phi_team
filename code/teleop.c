#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  HTServo,  none,     none)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     motorF,        tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     motorG,        tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     motorH,        tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     motorI,        tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C4_1,     motorJ,        tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C4_2,     motorK,        tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S2_C1_1,    servo1,               tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    servo2,               tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    servo3,               tServoStandard)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoStandard)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoStandard)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoStandard)
#pragma config(Servo,  srvo_S2_C2_1,    servo7,               tServoNone)
#pragma config(Servo,  srvo_S2_C2_2,    servo8,               tServoNone)
#pragma config(Servo,  srvo_S2_C2_3,    servo9,               tServoNone)
#pragma config(Servo,  srvo_S2_C2_4,    servo10,              tServoNone)
#pragma config(Servo,  srvo_S2_C2_5,    servo11,              tServoNone)
#pragma config(Servo,  srvo_S2_C2_6,    servo12,              tServoNone)

#include "JoystickDriver.c"
#include "power.h"
#include "inicializate_motors.h"

const byte X_BTN = 1;
const byte Y_BTN = 4;
const byte A_BTN = 2;
const byte B_BTN = 3;
const byte LB_BTN = 5;
const byte RB_BTN = 6;
const byte LT_BTN = 7;
const byte RT_BTN = 8;
const byte BACK_BTN = 9;
const byte START_BTN = 10;
const byte STICK_LEFT_BTN = 11;
const byte STICK_RIGHT_BTN = 12;

byte a = -50;

void R(const byte nr) // control of right wheel pair
{
	motor[FR] = nr;
	motor[BR] = nr;
}

void L(const byte nl)// control of left wheel pair
{
	motor[FL] = nl;
	motor[BL] = nl;
}

void Servosetup() // initialization of servos and motors
{
	inicializete_motors();
	inicializate_resetPower();
}

task Ball() // control of gripper for balls
{
	byte b = 50;

	waitForStart();

	while (true)
	{
   if(joy2Btn(A_BTN) > 0)
   {
     a = -a;
     motor[L_BLADE] = 50 + a;
		 motor[R_BLADE] = 50 + a;
     while (joy2Btn(2) > 0)
     	 wait1Msec(1);
   }
   if (joy2Btn(Y_BTN) > 0)
   {
     b = -b;
     motor[L_BLADE] = -50 + b;
		 motor[R_BLADE] = -50 + b;
     while (joy2Btn(4) > 0)
     	 wait1Msec(1);
   }
 }
}

task Ball_side()
{
	waitForStart();

	servo[servoBall2] = 160;
	servo[servoBall] = 210 - servo[servoBall2];

	while (true)
	{
		servo[servoBall] = 210 - servo[servoBall2];
		if (joy1Btn(X_BTN) > 0)
		{
			servo[servoBall2] = 35;
			servo[servoBall] = 210 - servo[servoBall2];
	  }
		if (joy1Btn(B_BTN) > 0)
		{
			servo[servoBall2] = 160;
			servo[servoBall] = 210 - servo[servoBall2];
	  }
	}
}

task power_reset
{
	ON_power();
	waitForStart();

	while (true){
	 	if (joy1Btn(BACK_BTN) > 0){
	 		OFF_power();

	 		while(joy1Btn(BACK_BTN) > 0 || joy1Btn(START_BTN) == 0){
	 			wait1Msec(1);
	 		}
	 	}

	 	if (joy1Btn(START_BTN) > 0){
	 		ON_power();

	 		while(joy1Btn(START_BTN) > 0 || joy1Btn(BACK_BTN) == 0){
	 			wait1Msec(1);
	 		}
	 	}
	}
}

task MvClaw() // control of mechanism that capture rolling goals
{
	const byte clse = 17, opn = 50;

	waitForStart();

  while (true)
  {
  	servo[servoMvClaws3] = 260 - ServoValue[servoMvClaws];
  	if(joy1Btn(LB_BTN ) == 1)
  	{
			servo[servoMvClaws] = clse;
		}
    if(joy1Btn(LT_BTN) == 1)
    {
  		servo[servoMvClaws] = opn;
  	}
  }
}

task MvClaw2() // control of additional gripper for rolling goals
{
  const byte clse = 0;
  const int opn = 140;

  waitForStart();

  while (true)
  {
  	if(joy1Btn(Y_BTN ) == 1){
			servo[servoMvClaws2] = clse;
		}

    if(joy1Btn(RB_BTN) == 1){
  		servo[servoMvClaws2] = opn;
  	}
  }
}

task tube () // control of mechanism overturning the bucket
{
	const ubyte r2 = 155, start_val = 0;
	byte state = 23;

	waitForStart();

	while(true)
	{
  	if(joystick.joy1_y1 < -90)
  	{
	  	servo[servoTube] = start_val;
	  }
    if(joystick.joy1_y1 > 90)
    {
  	  servo[servoTube] = r2;
  	}
  	if (joy1Btn(2) > 0)
  	{
  		state = -state;
  		servo[servoTube] = 122 + state;
  		while (joy1Btn(2) > 0)
  			wait1Msec(1);
  	}
  }
}

task elevator() // control of lift
{
	waitForStart();

	while(true)
	{
	/*if(nMotorEncoder[UL] < 0)
	{
		motor[UR] = -100;
    motor[UL] = 100;
	}
	else*/
	//{
		/*if(nMotorEncoder[UL] > 25000)
	  {
	  	motor[UR] = 100;
      motor[UL] = -100;
	  }
	  else*/
	 // {
	    if(abs(joystick.joy1_y2) > 90 && abs(nMotorEncoder[UL]) < 15000)
	    {
	    	a = -50;
     		motor[L_BLADE] = 50 + a;
		 		motor[R_BLADE] = 50 + a;
	    	motor[UR] = 100 * joystick.joy1_y2 / abs(joystick.joy1_y2);
        motor[UL] = -100 * joystick.joy1_y2 / abs(joystick.joy1_y2);
        motor[URT] = 100 * joystick.joy1_y2 / abs(joystick.joy1_y2);
        motor[ULT] = -100 * joystick.joy1_y2 / abs(joystick.joy1_y2);
	    }
	    else
	    {
    		motor[UR] = 0;
        motor[UL] = 0;
        motor[URT] = 0;
        motor[ULT] = 0;
    	}
  	//}
  }
}


task  motion() // control of robot's moving
{
  bool k = 0;

  waitForStart();

	while(true)
	{
			 motor[FR] = 0;
			 motor[BR] = 0;
			 motor[FL] = 0;
			 motor[BL] = 0;
	    /*while(abs(joystick.joy2_y1) + abs(joystick.joy2_x1) > 10)
		  {
		    motor[FR] = (-joystick.joy2_y1 + joystick.joy2_x1) * 100 / 128;
	      motor[BR] = (-joystick.joy2_y1 + joystick.joy2_x1) * 100 / 128;
	      motor[FL] = (-joystick.joy2_y1 - joystick.joy2_x1) * 100 / 128;
	      motor[BL] = (-joystick.joy2_y1 - joystick.joy2_x1) * 100 / 128;
	    }
	   /* else
	    {
	    	if(abs(joystick.joy2_y1) + abs(joystick.joy2_x1) > 10 && joy2Btn(10) == 1)
	      {
	      	motor[BR] = (-joystick.joy2_y1 + joystick.joy2_x1) * 100 / 128 * k;
	        motor[BL] = (-joystick.joy2_y1 - joystick.joy2_x1) * 100 / 128 * k;
	        motor[FR] = 0;
	        motor[FL] = 0;
	      }*/
	  if((joy2Btn(6) == 1) || (joy2Btn(7) == 1))
	  {
	  	k = true;
	  }
	  else
	  {
	  	k = false;
	  }

	  while(joystick.joy2_TopHat == 0)
		{
	    R(-100 + 80 * k);
	    L(-100 + 80 * k);
	  }
	  while(joystick.joy2_TopHat == 1)
		{
	    R(0);
	    L(-100);
	  }
	  while(joystick.joy2_TopHat == 2)
		{
	    R(100 - 30 * k);
	    L(-100 + 30 * k);
	  }
	  while(joystick.joy2_TopHat == 3)
		{
		  R(100);
	    L(0);
	  }
	  while(joystick.joy2_TopHat == 4)
		{
	    R(100 - 80 * k);
	    L(100 - 80 * k);
	  }
	  while(joystick.joy2_TopHat == 5)
		{
		  R(0);
	    L(100);
	  }
	  while(joystick.joy2_TopHat == 6)
		{
	    R(-100 + 30 * k);
	    L(100 - 30 * k);
	  }
	  while(joystick.joy2_TopHat == 7)
		{
		  R(-100);
	    L(0);
	  }
	  while(joystick.joy2_TopHat == -1)
		{
	    R(0);
	    L(0);
	  }

	}
}

task main()
{
  Servosetup();
  StartTask(MvClaw);
  StartTask(MvClaw2);
 // StartTask(Claw);
	StartTask(Ball);
	StartTask(Ball_side);
	StartTask(tube);
	StartTask(motion);
	StartTask(power_reset);

	StartTask(elevator);

	while(true)
	{
		getJoystickSettings(joystick);
  }

  OFF_power();
}
