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
#pragma config(Servo,  srvo_S4_C2_1,    servo7,               tServoNone)
#pragma config(Servo,  srvo_S4_C2_2,    servo8,               tServoNone)
#pragma config(Servo,  srvo_S4_C2_3,    servo9,               tServoNone)
#pragma config(Servo,  srvo_S4_C2_4,    servo10,              tServoNone)
#pragma config(Servo,  srvo_S4_C2_5,    servo11,              tServoNone)
#pragma config(Servo,  srvo_S4_C2_6,    servo12,              tServoNone)

#define autonom

#include "JoystickDriver.c"
#include "power.h"
#include "inicializate_motors.h"

void L_R (const byte ii, const byte jj, const int tt) // + forward; - backward
{
	motor[FR] = -jj;
	motor[FL] = ii;
	motor[BR] = jj;
	motor[BL] = -ii;
	wait1Msec(tt);
}

void L_R2 (const byte ii, const byte jj, const int tt) // + forward; - backward
{
	motor[FR] = -jj;
	motor[FL] = ii;
	motor[BR] = jj;
	motor[BL] = -ii;
	wait1Msec(tt);
	servo[servoMvClawsRight] = Goal_Captured;
  servo[servoMvClawsLeft] = difference - Goal_Captured;
	motor[FR] = -jj;
	motor[FL] = ii;
	motor[BR] = jj;
	motor[BL] = -ii;
	wait1Msec(tt);
}

void UP (const byte iii, const unsigned short ttt) // control of lift by "wait"
{
	motor[UR] = iii;
	motor[UL] = -iii;
	motor[URT] = iii;
	motor[ULT] = -iii;
	wait1Msec(ttt);

}

void lift (const byte pow, const unsigned short high) // control of lift by encoder
{
	nMotorEncoder[UL] = 0;

	while (abs(nMotorEncoder[UL]) < high)
	{
    UP(pow, 1);
	}
	motor[UR] = 0;
	motor[UL] = 0;
	motor[URT] = 0;
	motor[ULT] = 0;
}

void L_R_UP (const byte i, const byte j, const byte k, const unsigned short t)
{
	motor[FR] = -j;
	motor[FL] = i;
	motor[BR] = j;
	motor[BL] = -i;
	motor[UR] = k;
	motor[UL] = -k;
	motor[URT] = k;
	motor[ULT] = -k;
	wait1Msec(t);
}

void Servosetup() // initialization of servos and motors
{
	//inicializate_resetPower();
	//wait10Msec(30);
	inicializete_motors();
}

void zero()
{
  L_R_UP(0, 0, 0, 1);
}

void motion_elevator(const unsigned int l, const unsigned int h)
{
	nMotorEncoder[BL] = 0;
	nMotorEncoder[UL] = 0;
	while (-nMotorEncoder[BL] < l && -nMotorEncoder[UL] < h)
	{
  		L_R_UP(20, 20, 100, 1);
  }
  zero();
  while (-nMotorEncoder[BL] < l)
	{
			L_R(20, 20, 1);
	}
	zero();
}

void LR(const byte pow, unsigned int l_ramp_goal) // moving
{
	nMotorEncoder[BL] = 0;
	l_ramp_goal *= 1024 / 3.1415 * 10;
	while(abs(nMotorEncoder[BL]) < l_ramp_goal)
	{
	  motor[FR] = -pow;
	  motor[BR] = pow;
	  motor[FL] = pow;
	  motor[BL] = -pow;
	  nxtDisplayBigTextLine(1, "%d", nMotorEncoder[BL]);
  }

  motor[FR] = 0;
  motor[BR] = 0;
  motor[FL] = 0;
  motor[BL] = 0;
}

void motion(unsigned int l_ramp_goal, const byte a) // moving to rolling goal and capture it
{
	int enc;

  nMotorEncoder[FR] = 0;
	nMotorEncoder[BL] = 0;
  //L_R(a * -100, a * -100, 1500);
  enc = nMotorEncoder[BL];
  nxtDisplayBigTextLine(1, "%i", enc);
  l_ramp_goal *= 1024 / 3.1415 * 10;

	/*while(a * nMotorEncoder[BL] < l_ramp_goal - 4096)// * 1024 /(3.1415 * 10 ))// - 50)
	{
    L_R(a * -100, a * -100, 1);
    enc = nMotorEncoder[BL];
    nxtDisplayBigTextLine(2, "%i", enc);
  }
*/
  while(abs(nMotorEncoder[BL]) < l_ramp_goal)
	{
    L_R(a * -20, a * -20, 1);
  }
  servo[servoMvClawsRight] = Goal_Captured;
  servo[servoMvClawsLeft] = abs(difference - Goal_Captured);
  wait10Msec(10);
  while(abs(nMotorEncoder[BL]) < l_ramp_goal + 500)
  {
    L_R(a * -20, a * -20, 1);
  }

  zero();
}

void elevator(const unsigned int h) // raise the bucket and overturn it
{
	nMotorEncoder[UL] = 0;
  UP(100, 500);
  if(-nMotorEncoder[UL] < 10)
  {
    while(true)
    {
  	  UP(0, 1);
    }
  }
 	while(abs(nMotorEncoder[UL]) < h)
	{
    UP(100, 1);
  }

  UP(0, 1);
  servo[servoTubeRight] = Bucket_Overturned;
  servo[servoTubeLeft] = Bucket_Overturned;
  wait1Msec(500);
	servo[servoTubeRight] = Bucket_Overturned;
  servo[servoTubeLeft] = Bucket_Overturned;
  wait1Msec(2000);

  servo[servoTubeRight] = Bucket_Vertical;
  servo[servoTubeLeft] = Bucket_Vertical;

  L_R(20, 20, 200);

  UP(0, 1);
}

void R(const unsigned int l_ramp_goal, const byte pow) // turn by right wheel pair
{
	nMotorEncoder[FR] = 0;

	while(abs(nMotorEncoder[FR])  < l_ramp_goal)
	{
    L_R(0, pow, 1);
  }

  zero();
}

void L(const unsigned int l_ramp_goal, const byte pow) // turn by left wheel pair
{
	nMotorEncoder[BL] = 0;

	while(abs(nMotorEncoder[BL]) < l_ramp_goal)
	{
    L_R(pow, 0, 1);
    nxtDisplayBigTextLine(2, "%i", nMotorEncoder[FR]);
  }

  zero();
}

void rotate_left(const unsigned int l_turn)
{
	nMotorEncoder[BL] = 0;
	nMotorEncoder[FR] = 0;
	while(abs(nMotorEncoder[FR]) < l_turn)
	{
    L_R(-100, 100, 1);
  }

  zero();
}

void rotate_right(const unsigned int l_turn)
{
	nMotorEncoder[FL] = 0;
	nMotorEncoder[FR] = 0;
	while(abs(nMotorEncoder[FR]) + abs(nMotorEncoder[FL]) < l_turn * 2)
	{
    L_R(50, -50, 1);
  }

  zero();
}


void TakeBall()
{
  motor[R_BLADE] = 100;
  motor[L_BLADE] = 100;
}

task down(){
	wait10Msec(100);
	while(-nMotorEncoder[UL] > 10)
  {
    UP(-100, 1);
  }
  UP(0,1);
  wait10Msec(1);
  servo[servoBall2] = Blade2_Open;
	servo[servoBall] = Blade_Open;
	wait10Msec(30);
	motor[motorB] = -100;
	motor[motorC] = -100;
	wait10Msec(10000);
}

task riseUp(){
	wait1Msec(500);
	lift(100, 3000);
}

task main()
{
	const int waitTime = 10;
	Servosetup();
	wait1Msec(1000);

	 waitForStart();

   servo[servoMvClawsRight] = Goal_Released;
   servo[servoMvClawsLeft] =  difference - Goal_Released;
   StartTask(riseUp);

   LR(-50, 305);//go to 30cm goal
   L_R2(-20,-20, 500);
   lift(-20, 3000);  //  to 30cm goal}
   servo[servoMvClawsRight] = Goal_Captured;
   servo[servoMvClawsLeft] = difference - Goal_Captured;
   wait1Msec(500);

   LR(50, 43); // go back with the 30cm goal
   wait10Msec(waitTime);
   servo[servoMvClawsRight] = Goal_Released;
   servo[servoMvClawsLeft] = difference -  Goal_Released; // release the 30cm goal
   wait1Msec(500);

   LR(50, 38); // go back from the 30cm goal
   wait10Msec(waitTime);
   rotate_right(500); // rotate to 90cm goal
   wait10Msec(10);
   LR(-50, 65); // ride to 90cm goal and stop near the 30cm goal
   servo[servoMvClaws2] = Goal_Side_Captured;
   wait1Msec(500);//capture to 30cm goal
   L_R2(-20, -20, 1500); // ride and capture to 90cm goal
   wait10Msec(10);

   rotate_left(530); // rotate to parking zone
   LR(20, 9);
   L_R2(-20,-20, 250);
   elevator(8500); // put the ball to 90cm goal
   //StartTask(down);
   wait10Msec(10);
   LR(100, 305); // go to the parking zone
   rotate_left(500); // rotate in the parking zone

   //elevator();
   //rotate(1000);
   //L(2000, -100);
   //wait1Msec(1000);
   //motion(800, 1);
   //L(1000, 100);
   //motion(8000,-1);*/

		motor[FR] = 0;
    motor[BR] = 0;
    motor[FL] = 0;
    motor[BL] = 0;
    motor[UR] = 0;
    motor[UL] = 0;
    motor[URT] = 0;
    motor[ULT] = 0;

    //OFF_power();

    while(true){
    	wait10Msec(10);
    }
}
