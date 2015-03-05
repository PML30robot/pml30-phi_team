#include "JoystickDriver.c"
#include "power.h"
#include "inicializate_motors.h"

void L_R (int ii, int jj, int tt) // + forward; - backward
{
	motor[FR] = -jj;
	motor[FL] = -ii;
	motor[BR] = -jj;
	motor[BL] = -ii;
	wait1Msec(tt);
}

void UP (int iii, int ttt) // control of lift by "wait"
{
	motor[UR] = iii;
	motor[UL] = -iii;
	motor[URT] = iii;
	motor[ULT] = -iii;
	wait1Msec(ttt);
}

void L_R_UP (int i, int j, int k, int t)
{
	motor[FR] = -j;
	motor[FL] = -i;
	motor[BR] = -j;
	motor[BL] = -i;
	motor[UR] = k;
	motor[UL] = -k;
	motor[URT] = k;
	motor[ULT] = -k;
	wait1Msec(t);
}

void Servosetup() // initialization of servos and motors
{
	inicializete_motors();
	inicializate_resetPower();
}


void zero()
{
  L_R_UP(0, 0, 0, 1);
}

void motion_elevator(int l, int h)
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

void motion(int l_ramp_goal, int a) // moving to rolling goal and capture it
{
  nMotorEncoder[FR] = 0;
	nMotorEncoder[BL] = 0;

  while(a * nMotorEncoder[BL] < l_ramp_goal)
	{
    L_R(a * -20, a * -20, 1);
  }
  servo[servoMvClaws] = 17;
  servo[servoMvClaws3] = 261 - ServoValue[servoMvClaws];
  while(a * nMotorEncoder[BL] < l_ramp_goal + 200)
  {
    L_R(a * -20, a * -20, 1);
  }

  zero();
}

void elevator(int h) // raise the bucket and overturn it
{
	nMotorEncoder[UL] = 0;
  UP(100, 1000);
  if(-nMotorEncoder[UL] < 10)
  {
    while(true)
    {
  	  UP(0, 1);
    }
  }

 	while(-nMotorEncoder[UL] < h)
	{
    UP(100, 1);
  }

  UP(0, 1);

  servo[servoTube] = 245;
  wait1Msec(3500);

  servo[servoTube] = 70;

  while(nMotorEncoder[UL] < -10)
  {
    UP(-100, 1);
  }

  UP(0, 1);
}

void R(float l_ramp_goal, int pow) // turn by right wheel pair
{
	nMotorEncoder[FR] = 0;
	while(abs(nMotorEncoder[FR]) < l_ramp_goal)
	{
    L_R(0, pow, 1);
  }

  motor[FR] = pow;
  motor[BR] = pow;

  zero();
}

void L(float l_ramp_goal, int pow) // turn by left wheel pair
{
	nMotorEncoder[BL] = 0;
	while(abs(nMotorEncoder[BL]) < l_ramp_goal)
	{
    L_R(pow, 0, 1);
    nxtDisplayBigTextLine(2, "%i", nMotorEncoder[FR]);
  }

  motor[FL] = pow;
  motor[BL] = pow;

  zero();
}

void rotate(float l_ramp_goal) // moving on circle
{
	wait1Msec(500);
	nMotorEncoder[BL] = 0;
	nMotorEncoder[FR] = 0;
	while(nMotorEncoder[FR] < l_ramp_goal)
	{
    L_R(-60, 100, 1);
  }

  L_R(100, 100, 1);

  zero();
}

void rotate2(float l_ramp_goal) // "tank turning"
{
	wait1Msec(500);
	nMotorEncoder[BL] = 0;
	nMotorEncoder[FR] = 0;
	while(-nMotorEncoder[FR]  < l_ramp_goal)
	{
    L_R(50, -100, 1);
  }
  L_R(100, 100, 1);

  zero();
}

void LR(int pow, float l_ramp_goal) // moving
{
	nMotorEncoder[BL] = 0;
	while(abs(nMotorEncoder[BL]) < l_ramp_goal)
	{
	  motor[FR] = -pow;
	  motor[BR] = -pow;
	  motor[FL] = -pow;
	  motor[BL] = -pow;
  }

  motor[FR] = 0;
  motor[BR] = 0;
  motor[FL] = 0;
  motor[BL] = 0;
}

task main()
{
	 Servosetup();
	 waitForStart();
   servo[servoMvClaws] = 55;
   servo[servoMvClaws3] = 261 - ServoValue[servoMvClaws];
   motion(9500, 1); // ride to the 60cm goal
   //elevator(7300); // put the ball to 60cm goal
   rotate(3000);// { rotate with
   L(1500, -100);// 60cm goal }
   LR(-20, 1500); // go back with 60cm goal
   servo[servoMvClaws] = 55; // { release
   servo[servoMvClaws3] = 261 - ServoValue[servoMvClaws]; // 60cm goal}
   LR(20, 1500); // return
   rotate2(3000); // rotate to 90cm goal and stop near the 60cm goal
   servo[servoMvClaws2] = 0; // capture to 30cm goal
   rotate2(1000); // rotate to 90cm goal
   motion(1500, 1); // ride to the 90cm goal and capture it
   //elevator(10000); // put the ball to 90cm goal
   R(1500, 100); // rotate to the parking zone
   LR(50, 10000); // move rolling goals to the parking zone
   L(2000, 100); // rotate in the parking zone
   LR(50, 1000); // moving in parking zone*/
	 zero();
	 OFF_power();
}
