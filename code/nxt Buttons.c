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

#ifndef UL
	#define UL 9
#endif

#ifndef ULT
	#define ULT 10
#endif

#ifndef UR
	#define UR 3
#endif

#ifndef URT
	#define URT 4
#endif

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
