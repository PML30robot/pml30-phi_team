#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S4, HTServo,  HTServo,  none,     none)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorTetrix, openLoop, encoder) //FL
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorTetrix, openLoop, encoder) //BL
#pragma config(Motor,  mtr_S1_C2_1,     motorF,        tmotorTetrix, openLoop, encoder) //FR
#pragma config(Motor,  mtr_S1_C2_2,     motorG,        tmotorTetrix, openLoop, encoder) // BR
#pragma config(Motor,  mtr_S1_C3_2,     motorI,        tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     motorH,        tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C4_1,     motorJ,        tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C4_2,     motorK,        tmotorTetrix, openLoop, encoder)
#pragma config(Servo,  srvo_S4_C1_1,    servo1,               tServoStandard)
#pragma config(Servo,  srvo_S4_C1_2,    servo2,               tServoStandard)
#pragma config(Servo,  srvo_S4_C1_3,    servo3,               tServoStandard)
#pragma config(Servo,  srvo_S4_C1_4,    servo4,               tServoStandard)
#pragma config(Servo,  srvo_S4_C1_5,    servo5,               tServoStandard)
#pragma config(Servo,  srvo_S4_C1_6,    servo6,               tServoStandard)
#pragma config(Servo,  srvo_S4_C2_1,    servo7,               tServoStandard)
#pragma config(Servo,  srvo_S4_C2_2,    servo8,               tServoStandard)
#pragma config(Servo,  srvo_S4_C2_3,    servo9,               tServoStandard)
#pragma config(Servo,  srvo_S4_C2_4,    servo10,              tServoStandard)
#pragma config(Servo,  srvo_S4_C2_5,    servo11,              tServoStandard)
#pragma config(Servo,  srvo_S4_C2_6,    servo12,              tServoStandard)

#define teleop

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
const byte TopHat_Forward = 0;
const byte TopHat_Forward_Left = 1;
const byte TopHat_Turn_Right = 2;
const byte TopHat_Backward_Right = 3;
const byte TopHat_Backward = 4;
const byte TopHat_Backward_Left = 5;
const byte TopHat_Turn_Left= 6;
const byte TopHat_Forward_Right = 7;


byte a = -50;

void R(const byte nr) // control of right wheel pair
{
	motor[FR] = nr;
	motor[BR] = -nr;
}

void L(const byte nl)// control of left wheel pair
{
	motor[FL] = -nl;
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
   if(joy2Btn(Y_BTN) > 0)
   {
     a = -a;
     motor[L_BLADE] = 50 + a;
		 motor[R_BLADE] = 50 + a;
     while (joy2Btn(2) > 0)
     	 wait1Msec(1);
   }
   if (joy2Btn(A_BTN) > 0)
   {
     b = -b;
     motor[L_BLADE] = -50 + b;
		 motor[R_BLADE] = -50 + b;
     while (joy2Btn(4) > 0)
     	 wait1Msec(1);
   }
   while (nMotorEncoder[UL] <= 0)
   {
   	 motor[L_BLADE] = -100;
   	 motor[R_BLADE] = -100;
   }
 }
}

task Ball_side()
{
	waitForStart();

	while (true)
	{
		if (joy1Btn(X_BTN) > 0)
		{
			servo[servoBall2] = 60;
			servo[servoBall] = 160;
	  }
		if (joy1Btn(B_BTN) > 0)
		{
			servo[servoBall2] = Blade2_Open;
			servo[servoBall] = Blade_Open;
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
	 		ON_power(true);

	 		while(joy1Btn(START_BTN) > 0 || joy1Btn(BACK_BTN) == 0){
	 			wait1Msec(1);
	 		}
	 	}
	}
}

task MvClaw() // control of mechanism that capture rolling goals
{

	waitForStart();

  while (true)
  {
  	if(joy1Btn(LB_BTN ) == 1)
  	{
			servo[servoMvClawsRight] = Goal_Captured;
			servo[servoMvClawsLeft] = abs(difference - servoValue[servoMvClawsRight]);
		}
    if(joy1Btn(LT_BTN) == 1)
    {
  		servo[servoMvClawsRight] = Goal_Released;
  		servo[servoMvClawsLeft] = abs(difference - servoValue[servoMvClawsRight]);
  	}
  }
}

task MvClaw2() // control of additional gripper for rolling goals
{
  waitForStart();

  while (true)
  {
  	if(joy1Btn(Y_BTN ) == 1){
			servo[servoMvClaws2] = Goal_Side_Captured;
		}

    if(joy1Btn(RB_BTN) == 1){
  		servo[servoMvClaws2] = Goal_Side_Released;
  	}
  }
}

task tube () // control of mechanism overturning the bucket
{
	waitForStart();
	while(true)
	{
  	if(joystick.joy1_y1 < -90)
  	{
	  	servo[servoTubeLeft] = Bucket_Vertical;
	  	servo[servoTubeRight] = Bucket_Vertical;
	  }
    if(joystick.joy1_y1 > 90)
    {
  	  servo[servoTubeLeft] = Bucket_Overturned;
  	  servo[servoTubeRight] = Bucket_Overturned;
  	}
  }
}

/*task elevator() // control of lift
{
	waitForStart();

	while(true)
	{
			/*if(nMotorEncoder[UL] < 0)
			{
				motor[UR] = -100;
    		motor[UL] = 100;
  		}
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
	    if (joy1Btn() == 1) // 60cm
	    {
	      wait1Msec(50);
	      while (-nMotorEncoder[UL] < )
	      {
	      	motor[UR] = 100;
	      	motor[UL] = -100;
	      	motor[URT] = 100;
	      	motor[ULT] = -100;
	      }
	    }
	    if (joy1Btn() == 1) // 90cm
	    {
	      wait1Msec(50);
	      while (-nMotorEncoder[UL] < )
	      {
	      	motor[UR] = 100;
	      	motor[UL] = -100;
	      	motor[URT] = 100;
	      	motor[ULT] = -100;
	      }
	    }
	    if (joy1Btn() == 1) // 120cm
	    {
	      wait1Msec(50);
	      while (-nMotorEncoder[UL] < )
	      {
	      	motor[UR] = 100;
	      	motor[UL] = -100;
	      	motor[URT] = 100;
	      	motor[ULT] = -100;
	      }
	    }
	    if (joy1Btn() == 1) // 0cm
	    {
	      wait1Msec(50);
	      while (-nMotorEncoder[UL] > 0)
	      {
	      	motor[UR] = -100;
	      	motor[UL] = 100;
	      	motor[URT] = -100;
	      	motor[ULT] = 100;
	      }
	    }
    	motor[UR] = 0;
      motor[UL] = 0;
      motor[URT] = 0;
      motor[ULT] = 0;
  	//}
  }
}*/


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

	  while(joystick.joy2_TopHat == TopHat_Forward)
		{
	    R(-100 + 80 * k);
	    L(-100 + 80 * k);
	  }
	  while(joystick.joy2_TopHat == TopHat_Forward_Left)
		{
	    R(0);
	    L(-100);
	  }
	  while(joystick.joy2_TopHat == TopHat_Turn_Right)
		{
	    R(100 - 30 * k);
	    L(-100 + 30 * k);
	  }
	  while(joystick.joy2_TopHat == TopHat_Backward_Right)
		{
		  R(100);
	    L(0);
	  }
	  while(joystick.joy2_TopHat == TopHat_Backward)
		{
	    R(100 - 80 * k);
	    L(100 - 80 * k);
	  }
	  while(joystick.joy2_TopHat == TopHat_Backward_Left)
		{
		  R(0);
	    L(100);
	  }
	  while(joystick.joy2_TopHat == TopHat_Turn_Left)
		{
	    R(-100 + 30 * k);
	    L(100 - 30 * k);
	  }
	  while(joystick.joy2_TopHat == TopHat_Forward_Right)
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

	//StartTask(elevator);

	while(true)
	{
		getJoystickSettings(joystick);
  }

  //OFF_power();
}
