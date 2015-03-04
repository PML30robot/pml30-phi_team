#include "JoystickDriver.c"
#include "power.h"
#include "inicializate_motors.h"

void L_R (const byte ii, const byte jj, const byte tt) // + forward; - backward
{
	motor[FR] = -jj;
	motor[FL] = -ii;
	motor[BR] = -jj;
	motor[BL] = -ii;
	wait1Msec(tt);
}

void L_R2 (const byte ii, const byte jj, const byte tt) // + forward; - backward
{
	motor[FR] = -jj;
	motor[FL] = -ii;
	motor[BR] = -jj;
	motor[BL] = -ii;
	wait1Msec(tt);
	servo[servoMvClaws] = 17;
	servo[servoMvClaws3] = 260 - ServoValue[servoMvClaws];
	motor[FR] = -jj;
	motor[FL] = -ii;
	motor[BR] = -jj;
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

void motion(const unsigned int l_ramp_goal, const byte a) // moving to rolling goal and capture it
{
	int enc;

  nMotorEncoder[FR] = 0;
	nMotorEncoder[BL] = 0;
  //L_R(a * -100, a * -100, 1500);
  enc = nMotorEncoder[BL];
  nxtDisplayBigTextLine(1, "%i", enc);
  /*if(a * nMotorEncoder[BL] < 10)
  {
  	while(true)
  	{
  		for (; pow >= 0; pow--)
  		{
        L_R(-pow, -pow, 5);
        enc = nMotorEncoder[BL];
        nxtDisplayBigTextLine(2, "%i", enc);
      }
  	}
  }
 /* if (SensorValue[S3] == color)
  {
  	  nMotorEncoder[BR] = 0;
    	nMotorEncoder[BL] = 0;*/
	while(a * nMotorEncoder[BL] < l_ramp_goal - 4096)// * 1024 /(3.1415 * 10 ))// - 50)
	{
    L_R(a * -100, a * -100, 1);
    enc = nMotorEncoder[BL];
    nxtDisplayBigTextLine(2, "%i", enc);
  }
  /*for (int pow = a * 100; pow >= a * 20; pow--)
  {
  	L_R(-pow, -pow, 5);
  }*/
  while(a * nMotorEncoder[BL] < l_ramp_goal)
	{
    L_R(a * -20, a * -20, 1);
  }
  servo[servoMvClaws] = 17;
  servo[servoMvClaws3] = 243;
  while(a * nMotorEncoder[BL] < l_ramp_goal + 500)
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

 	while(-nMotorEncoder[UL] < h)
	{
    UP(100, 1);
  }

  UP(0, 1);
 servoChangeRate[servoTube]=5;
  servo[servoTube] = 245;
  wait1Msec(2500);

  servo[servoTube] = 70;

  while(nMotorEncoder[UL] < -10)
  {
    UP(-100, 1);
  }

  UP(0, 1);
}

void R(const unsigned int l_ramp_goal, const byte pow) // turn by right wheel pair
{
	nMotorEncoder[FR] = 0;

	while(abs(nMotorEncoder[FR])  < l_ramp_goal)
	{
    L_R(0, pow, 1);
  }

  motor[FR] = -pow;
  motor[BR] = -pow;

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

  motor[FL] = pow;
  motor[BL] = pow;

  zero();
}

void rotate(const unsigned int l_ramp_goal)
{
	wait1Msec(500);
	nMotorEncoder[BL] = 0;
	nMotorEncoder[FR] = 0;
	while(nMotorEncoder[FR] < l_ramp_goal)
	{
    L_R(-100, 50, 1);
  }

  L_R(100, 100, 1);

  zero();
}

void rotate2(const unsigned int l_ramp_goal)
{
	wait1Msec(500);
	nMotorEncoder[BL] = 0;
	nMotorEncoder[FR] = 0;
	while(-nMotorEncoder[FR] < l_ramp_goal)
	{
    L_R(50, -100, 1);
  }

  L_R(100, 100, 1);

  zero();
}

void LR(const byte pow, const unsigned int l_ramp_goal) // moving
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

void TakeBall()
{
  motor[R_BLADE] = 100;
  motor[L_BLADE] = 100;
}


task main()
{
	 Servosetup();

	 waitForStart();

	 ON_power();
	 wait1Msec(20);

   servo[servoMvClaws] = 65;
   servo[servoMvClaws3] = 195;

   LR(-50, 2500); // go to space near the ramp
   //rotate(1200); // rotate to 30cm goal
   LR(-50, 9600);//go to 30cm goal
   servo[servoMvClaws] = 17;
   servo[servoMvClaws3] = 243;
   lift(100, 3000); //{ put
   L_R2(-20,-20, 500); // the ball
   lift(-20, 3000); //  to 30cm goal}
   servo[servoMvClaws] = 17;
   servo[servoMvClaws3] = 243;
   wait1Msec(500);
   LR(50, 1024); // go back with the 30cm goal
   servo[servoMvClaws] = 80;// release the 30cm goal
   servo[servoMvClaws3] = 180;
   wait1Msec(500);
   LR(50, 1320); // go back from the 30cm goal
   R(1900, -50); // rotate to 90cm goal
   LR(-50, 1200); // ride to 90cm goal and stop near the 30cm goal
   servo[servoMvClaws2] = 0;
   wait1Msec(500);//capture to 30cm goal
   motion(1200, 1); // ride and capture to 90cm goal
   elevator(8500); // put the ball to 90cm goal
   TakeBall();

   R(3500, 50); // rotate to parking zone
  // wait1Msec(5000);
   motion(11700,-1); // go to the parking zone
   R(7000, 50); // rotate in the parking zone

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

    OFF_power();

    while(true){
    	wait10Msec(10);
    }
}
