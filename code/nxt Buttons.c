#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Motor,  mtr_S1_C3_1,     UL,            tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     ULT,           tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C4_1,     UR,            tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C4_2,     URT,           tmotorTetrix, openLoop, encoder)

task main()
{

	// right arrow = 1      left arrow = 2
	nMotorEncoder[UL] = 0;
	int enc;
	motor[UR] = 0;
  motor[UL] = 0;
  motor[URT] = 0;
  motor[ULT] = 0;

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

}
