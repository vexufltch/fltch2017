#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    armLeftE,       sensorPotentiometer)
#pragma config(Sensor, in2,    backWheelE,     sensorPotentiometer)
#pragma config(Sensor, in3,    backFlipPot,    sensorPotentiometer)
#pragma config(Sensor, in4,    autoSelect,     sensorPotentiometer)
#pragma config(Sensor, in5,    memoryPot,      sensorPotentiometer)
#pragma config(Sensor, in8,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  backLimit,      sensorTouch)
#pragma config(Sensor, dgtl2,  autoBumper,     sensorTouch)
#pragma config(Sensor, dgtl12, autoOverride,   sensorTouch)
#pragma config(Sensor, I2C_1,  frontRightE,    sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  backRightE,     sensorNone)
#pragma config(Sensor, I2C_3,  frontLeftE,     sensorNone)
#pragma config(Sensor, I2C_4,  backleftE,      sensorNone)
#pragma config(Motor,  port1,           armLeft,       tmotorVex393, openLoop)
#pragma config(Motor,  port2,           backLeft,      tmotorVex393, openLoop)
#pragma config(Motor,  port3,           frontLeft,     tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port4,           intake,        tmotorVex393HighSpeed, openLoop, reversed)
#pragma config(Motor,  port5,           winch,         tmotorServoStandard, openLoop)
#pragma config(Motor,  port7,           memoryMtr,     tmotorVex269, openLoop)
#pragma config(Motor,  port8,           frontRight,    tmotorVex393, openLoop, encoder, encoderPort, I2C_1, 1000)
#pragma config(Motor,  port9,           backRight,     tmotorVex393, openLoop, reversed)
#pragma config(Motor,  port10,          armRight,      tmotorVex393, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


#pragma platform(VEX)

#define spinJoy Ch1
#define crabJoy Ch4
#define fwdJoy Ch3

task main()
{
	const int maxPower = 127; //max power of vex motors 
	float powerPercent = 1; //var to set power to the bot
	float power = 0; //power to write to motors

	int armMotor;
	int crabVal;
	int spinVal;
	int forwardVal;

	bool fwd = false;
	bool bwd = false;

	char encoderVal[15];
	char powerVal[15];

	bool fwdJoyTog = false;

	bool spinJoyTog = false;
	bool leftSpin = false;
	bool rightSpin = false;

	bool crabJoyTog = false;
	bool crabLeft = false;
	bool crabRight = false;

	bool armTog = false;
	bool upArm = false;
	bool downArm = false;

	bool intakeTog = false;
	bool intakeIn = false;
	bool intakeOut = false;
	bool intakeOff = false;
	bool intakePrintTog = false;

	bool fwdNotCrab = true;

	int intakeVal;

	clearDebugStream();

	while (true)
	{
		if (vexRT[Btn7UXmtr2] == 1)
		{
			powerPercent = 0.1;
		}
		if (vexRT[Btn7LXmtr2] == 1)
		{
			powerPercent = 0.2;
		}
		if (vexRT[Btn7DXmtr2] == 1)
		{
			powerPercent = 0.3;
		}
		if (vexRT[Btn7RXmtr2] == 1)
		{
			powerPercent = 0.4;
		}
		if (vexRT[Btn8UXmtr2] == 1)
		{
			powerPercent = 0.5;
		}
		if (vexRT[Btn8LXmtr2] == 1)
		{
			powerPercent = 0.6;
		}
		if (vexRT[Btn8DXmtr2] == 1)
		{
			powerPercent = 0.7;
		}
		if (vexRT[Btn8RXmtr2] == 1)
		{
			powerPercent = 0.8;
		}
		if (vexRT[Btn5UXmtr2] == 1)
		{
			powerPercent = 0.9;
		}
		if (vexRT[Btn6UXmtr2] == 1)
		{
			powerPercent = 1.0;
		}
		if (vexRT[Btn7U] == 1)
		{
			clearDebugStream();
		}

		if (vexRT[Btn8U] == 1)
		{
			fwdNotCrab = true;
		}

		if (vexRT[Btn8R] == 1)
		{
			fwdNotCrab = false;
		}

		//controls

		if (fwdNotCrab == true) {
			if (vexRT[fwdJoy] >= 10)//Adds a threshold of +10 to set values
			{
				fwdJoyTog = true;
				fwd = true;

				forwardVal = power; //sets + joy values to variables
			}
			else if (vexRT[fwdJoy] <= -10)//Adds a threshold of -10 to set values
			{
				fwdJoyTog = true;
				bwd = true;
				forwardVal = -power; //sets - joy values to variables
			}
			else
			{
				if (fwdJoyTog == false)
				{
					if (crabJoyTog == false)
					{
						if(spinJoyTog == false)
						{
							SensorValue[frontRightE] = 0; 
						}
					}
				}

				else {

					if (fwd == true)// meaning the bot went forward
					{
						sprintf(encoderVal, "%d", abs(SensorValue[frontRightE]));
						sprintf(powerVal, "%d", power);

						writeDebugStream("forwardFour(");
						writeDebugStream(powerVal);
						writeDebugStream(",");
						writeDebugStream(encoderVal);
						writeDebugStreamLine(");");

						fwd = false;
						fwdJoyTog = false;
					}

					else {

						sprintf(encoderVal, "%d", abs(SensorValue[frontRightE]));
						sprintf(powerVal, "%d", power);

						writeDebugStream("backwardFour(");
						writeDebugStream(powerVal);
						writeDebugStream(",");
						writeDebugStream(encoderVal);
						writeDebugStreamLine(");");

						bwd = false;
						fwdJoyTog = false;
					}
				}
				forwardVal = 0;
			}
		}

	//the rest of the code is the same except coded for crabbing and spinning. Ill add comments were necisary but for the most part is the same
	//concept.


		if(fwdNotCrab == false) {
		
			if (vexRT[crabJoy] >= 10 )//Adds a thershhold of +10 to set values
			{
				crabJoyTog = true;
				crabRight = true;
				crabVal = power; //sets + joy values to varibles
			}
			else if (vexRT[crabJoy] <= -10 )//Adds a thershhold of -10 to set values
			{
				crabJoyTog = true;
				crabLeft = true;
				crabVal = -power; //sets - joy values to varibles
			}
			else
			{
				if (crabJoyTog == false)
				{
					if(spinJoyTog == false)
					{
						SensorValue[frontRightE] = 0;
					}
				}
			else {
					if (crabRight == true)
					{
						sprintf(encoderVal, "%d", abs(SensorValue[frontRightE]));
						sprintf(powerVal, "%d", power);

						writeDebugStream("crabRight(");
						writeDebugStream(powerVal);
						writeDebugStream(",");
						writeDebugStream(encoderVal);
						writeDebugStreamLine(");");

						crabRight = false;
						crabJoyTog = false;
					}
					else {
						sprintf(encoderVal, "%d", abs(SensorValue[frontRightE]));
						sprintf(powerVal, "%d", power);

						writeDebugStream("crabLeft(");
						writeDebugStream(powerVal);
						writeDebugStream(",");
						writeDebugStream(encoderVal);
						writeDebugStreamLine(");");

						crabLeft = false;
						crabJoyTog = false;

					}
				}
			crabVal = 0;
			}
		}

		if (vexRT[spinJoy] >= 10)
		{
			spinJoyTog = true;
			rightSpin = true;
			spinVal = power; //sets + joy values to varibles
		}
		else if(vexRT[spinJoy] <= -10)
		{
			spinJoyTog = true;
			leftSpin = true;
			spinVal = -power;
		}
		else
		{
			if (spinJoyTog == false)
			{
				if (crabJoyTog == false)
				{
					if(fwdJoyTog == false)
					{
						SensorValue[gyro] = 0;
					}
				}
			}
			
			else {
				if (rightSpin == true)
				{
					sprintf(encoderVal, "%d", abs(SensorValue[gyro]));
					sprintf(powerVal, "%d", power);

					writeDebugStream("rightSpin(");
					writeDebugStream(powerVal);
					writeDebugStream(",");
					writeDebugStream(encoderVal);
					writeDebugStreamLine(");");

					rightSpin = false;
					spinJoyTog = false;
				}
				else {
					sprintf(encoderVal, "%d", abs(SensorValue[gyro]));
					sprintf(powerVal, "%d", power);

					writeDebugStream("leftSpin(");
					writeDebugStream(powerVal);
					writeDebugStream(",");
					writeDebugStream(encoderVal);
					writeDebugStreamLine(");");

					leftSpin = false;
					spinJoyTog = false;
				}
			}
			spinVal = 0;
		}


		if (vexRT[Btn6U]== 1 && vexRT[Btn6D]== 0 )
		{
			armTog = true;
			upArm = true;
			armMotor = power;
		}
		else if (vexRT[Btn6U]== 0 && vexRT[Btn6D]== 1  )
		{
			armTog = true;
			downArm = true;
			armMotor = -power;
		}
		else {
			if(armTog == false)
			{
				//SensorValue[armRightE] = 0;
				//this is incase you have an encoder on your arm system instead of a potentionmeter like we used.
				//so with a little tweaking to this section and to the armUp and armDown functions in MechWheelFunctions.c
				//you could get this to work with an encoder instead of a pot.
			}
			else {
				if(upArm == true)
				{
					sprintf(encoderVal, "%d", abs(SensorValue[armLeftE]));
					sprintf(powerVal, "%d", power);

					writeDebugStream("armUp(");
					writeDebugStream(powerVal);
					writeDebugStream(",");
					writeDebugStream(encoderVal);
					writeDebugStreamLine(");");

					upArm = false;
					armTog = false;
				}
				else {
					sprintf(encoderVal, "%d", abs(SensorValue[armLeftE]));
					sprintf(powerVal, "%d", power);

					writeDebugStream("armDown(");								writeDebugStream(powerVal);
					writeDebugStream(",");
					writeDebugStream(encoderVal);
					writeDebugStreamLine(");");

					downArm = false;
					armTog = false;
				}
			}
			armMotor = 0;
		}


		//this next code is for an intake

		if (vexRT[Btn5U]== 1 && vexRT[Btn5D]== 0 )
		{
			intakeTog = true;
			intakeIn = true;
			intakeVal = power;

			if(intakePrintTog == false)
			{
				sprintf(powerVal, "%d", power);

				writeDebugStream("motor[intake]= ");
				writeDebugStream(powerVal);
				writeDebugStreamLine(";");

				intakePrintTog = true;
			}
		}
		else if (vexRT[Btn5U]== 0 && vexRT[Btn5D]== 1  )
		{
			intakeTog = true;
			intakeOut = true;
			intakeVal = -power;

			if(intakePrintTog == false)
			{
				sprintf(powerVal, "%d", power);

				writeDebugStream("motor[intake]= -");
				writeDebugStream(powerVal);
				writeDebugStreamLine(";");

				intakePrintTog = true;
			}
		}
		else {
			if(intakeTog == false)
			{
				if(intakeOff == true)
				{
					writeDebugStreamLine("motor[intake]= 0;");

					intakeOff = false;
				}
			}
			else {
				if(intakeIn == true)
				{
						intakeIn = false;
						intakeTog = false;
						intakeOff = true;
						intakePrintTog = false;

				}
				else {
						intakeOut = false;
						intakeTog = false;
						intakeOff = true;
						intakePrintTog = false;
				}
			}
			intakeVal = 0;
		}


		motor[frontRight] = forwardVal - spinVal - crabVal;
		motor[backRight] = forwardVal - spinVal + crabVal;
		motor[frontLeft] = forwardVal + spinVal + crabVal;
		motor[backLeft] = forwardVal + spinVal - crabVal;
		motor[armRight] = armMotor + 20 ;
		motor[armLeft] = armMotor + 20;
		motor[intake] = intakeVal;


		/*	if(SensorValue[armLeftE] < SensorValue[memoryPot])
		{
			motor[armRight] = armMotor - 30 ;
			motor[armLeft] = armMotor - 30;
		}*/

	}

}

