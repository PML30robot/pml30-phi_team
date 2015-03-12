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
	#define FR 3
#endif

#ifndef BR
	#define BR 4
#endif

#ifndef FL
	#define FL 5
#endif

#ifndef BL
	#define BL 6
#endif

#ifndef UL
	#define UL 7
#endif

#ifndef ULT
	#define ULT 8
#endif

#ifndef UR
	#define UR 9
#endif

#ifndef URT
	#define URT 10
#endif

#ifndef servoBall
	#define servoBall servo1
#endif

#ifndef servoTube
	#define servoTube servo2
#endif

#ifndef servoMvClaws
	#define servoMvClaws servo3
#endif

#ifndef servoMvClaws2
	#define servoMvClaws2 servo4
#endif

#ifndef servoMvClaws3
	#define servoMvClaws3 servo5
#endif

#ifndef servoBall2
	#define servoBall2 servo6
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
		servo[servoBall] = 230;
		servo[servoBall2] = 0;
		servo[servoTube] = 0;
		servo[servoMvClaws] = 70;
		servo[servoMvClaws2] = 100;
		servo[servoMvClaws3] = 263 - ServoValue[servoMvClaws];
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
