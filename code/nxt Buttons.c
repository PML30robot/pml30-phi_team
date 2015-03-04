#include "power.h"
#include "inicializate_motors.h"

task main()
{
	inicializete_motors();
	inicializate_resetPower();
	ON_power();

	// right arrow = 1      left arrow = 2
	nMotorEncoder[UL] = 0;
	int enc;

	while(true)
	{
		enc = nMotorEncoder[UL];
		nxtDisplayBigTextLine(1 , "%i" , enc);
	 if(nNxtButtonPressed == 2)  // down
	 {
	   motor[UR] = -100;
	   motor[UL] = 100;
	   motor[URT] = -100;
	   motor[ULT] = 100;
	 }
	 if(nNxtButtonPressed == 1)  // up
	 {
	   motor[UR] = 100;
	   motor[UL] = -100;
	   motor[URT] = 100;
	   motor[ULT] = -100;
	 }
	 if(nNxtButtonPressed != 2 && nNxtButtonPressed != 1)
	 {
	   motor[UR] = 0;
	   motor[UL] = 0;
	   motor[URT] = 0;
	   motor[ULT] = 0;
	 }
	}

	ON_power();
}
