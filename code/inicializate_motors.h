																///////////////////////////////////////
																///// 				 Library 						/////
																///// 			to inicilizate        /////
																///// 		 motors and servos 			/////
																/////															/////
																/////         version 1.0					/////
																/////				from 04.03.2015       /////
																/////															/////
																/////    			created by					/////
																/////				KRYLOV GEORGII				/////
																/////															/////
																/////				 for FTC Team					/////
																/////					PML30-phi 					/////
																///////////////////////////////////////

#pragma once

#ifndef resetPowerMotor
	#define resetPowerMotor 0
#endif

#ifndef L_BLADE
	#define L_BLADE 1
#endif

#ifndef R_BLADE
	#define R_BLADE 2
#endif

#ifndef FR
	#define FR 5
#endif

#ifndef BR
	#define BR 6
#endif

#ifndef FL
	#define FL 7
#endif

#ifndef BL
	#define BL 8
#endif

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

#ifndef servoBall
	#define servoBall servo11
#endif

#ifndef servoTubeRight
	#define servoTubeRight servo7
#endif

#ifndef servoTubeLeft
	#define servoTubeLeft servo8
#endif

#ifndef servoMvClawsRight
	#define servoMvClawsRight servo1
#endif

#ifndef servoMvClawsLeft
	#define servoMvClawsLeft servo6
#endif

#ifndef servoMvClaws2
	#define servoMvClaws2 servo2
#endif

#ifndef servoBall2
	#define servoBall2 servo12
#endif

#define Goal_Captured 251
#define Goal_Released 210
#define Goal_Side_Captured 70
#define Goal_Side_Released 230
#define Bucket_Vertical 15
#define Bucket_Overturned 200
#define Blade_Open 35
#define Blade2_Open 185

#define difference 256

#ifdef teleop
	#define servoMvClawsStartValue Goal_Captured
	#define servoBlade Blade_Open
	#define servoBlade2 Blade2_Open
#endif

#ifdef autonom
	#define servoMvClawsStartValue 70
	#define servoBlade 235
	#define servoBlade2 0
#endif


bool isMotorsInicializete = false;

bool inicializete_motors(const bool requirement = false){
	if (!isMotorsInicializete || requirement){
		motor[resetPowerMotor] = 0;
		motor[L_BLADE] = 0;
		motor[R_BLADE] = 0;
		motor[FR] = 0;
		motor[BR] = 0;
		motor[FL] = 0;
		motor[BL] = 0;
		motor[UR] = 0;
	  motor[UL] = 0;
	  motor[URT] = 0;
	  motor[ULT] = 0;
		servo[servoBall2] = servoBlade2;
		servo[servoBall] = servoBlade;
		servo[servoTubeRight] = Bucket_Vertical;
		servo[servoTubeLeft] = Bucket_Vertical;
		servo[servoMvClawsRight] = servoMvClawsStartValue;
		servo[servoMvClawsLeft] = difference - servoValue[servoMvClawsRight];
		servo[servoMvClaws2] = 230;
		nMotorEncoder[FR] = 0;
		nMotorEncoder[FL] = 0;
		nMotorEncoder[BR] = 0;
		nMotorEncoder[BL] = 0;
		nMotorEncoder[UR] = 0;
		nMotorEncoder[UL] = 0;
		nMotorEncoder[URT] = 0;
		nMotorEncoder[ULT] = 0;

		isMotorsInicializete = true;

		return true;
	}else{
		return false;
	}
}
