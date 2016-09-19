#pragma config(Sensor, dgtl1,  Encoder1,       sensorQuadEncoder)
#pragma config(Motor,  port1,           driveBackLeft, tmotorVex393_HBridge, openLoop, driveLeft)
#pragma config(Motor,  port2,           driveBackRight, tmotorVex393_MC29, openLoop, driveRight)
#pragma config(Motor,  port3,           driveFrontLeft, tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port10,          driveFrontRight, tmotorVex393_HBridge, openLoop, driveRight)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define ENCODER_CONVERSION 	0.006 			// Encode Pulses/ms
#define UPDATE_INTERVAL  		25  				// In ms
#define MS_PER_MIN						60000			//
#define REV_PER_ENCODER_TICK  0.00277   // 1 rev / 360 ticks


float encoderVal;

task main()
{
while(true){
motor[driveBackLeft] = 127;
motor[driveBackRight] = vexRT[Ch2];
motor[driveFrontLeft] = vexRT[Ch3];
motor[driveFrontRight] = vexRT[Ch2];
encoderVal= abs(SensorValue[Encoder1]) * REV_PER_ENCODER_TICK * (1/UPDATE_INTERVAL) * MS_PER_MIN;
}
}
