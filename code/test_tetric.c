#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,      ,             tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,      ,             tmotorTetrix, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	motor[3] = 50;
 while(true){
   wait10Msec(10);
 }

};
