#pragma config(Sensor, S1,     RightLight,     sensorLightActive)
#pragma config(Sensor, S2,     FrontLight,     sensorLightActive)
#pragma config(Sensor, S4,     LeftLight,      sensorLightActive)
#pragma config(Motor,  motorA,          RightMotor,    tmotorNXT, openLoop, reversed, encoder)
#pragma config(Motor,  motorB,          CenterMotor,   tmotorNXT, openLoop, encoder)
#pragma config(Motor,  motorC,          LeftMotor,     tmotorNXT, openLoop, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int BlackFloor;
//Drive directions to execute
const int DRIVE_FORWARD = 0;
const int TURN_LEFT = 1;
const int TURN_RIGHT= 2;
const int BACKUP = 3;
/*
const int SPEED_FAST_FORWARD = 100;
const int SPEED_FAST_REVERSE = - 100;
const int SPEED_SLOW_FORWARD = 65;
const int SPEED_SLOW_REVERSE = -65;
*/

const int SPEED_FAST_FORWARD = 0;
const int SPEED_FAST_REVERSE = 0;
const int SPEED_SLOW_FORWARD = 0;
const int SPEED_SLOW_REVERSE = 0;


// Return the value of the sensor plugged into S1 Port

// Determine if the sensor sees the white line

bool isBlack (int value) {
	return (value < BlackFloor);
}

bool isWhite (int value) {
	return (value > BlackFloor);
}

// back the robot up for mSecs
void backup( int mSec) {
	motor[LeftMotor] = SPEED_SLOW_REVERSE;
	motor[RightMotor] = SPEED_SLOW_REVERSE;
	motor[CenterMotor] = SPEED_SLOW_REVERSE;
	wait1Msec(mSec);
}

int findRandom (int minTime, int maxTime) {
	int x = (rand() % (maxTime - minTime)) + minTime;
	return (x);
}


// find a random number and have the robot turn for that amount of time
void randomTurn() {
	motor[LeftMotor] = SPEED_FAST_FORWARD;
	motor[RightMotor] = SPEED_FAST_REVERSE;
	motor[CenterMotor] = 0;
	wait1Msec (findRandom(250,750));
}

// Reads the 3 light sensors and returns the correct action to take
int readSensors() {

	int frontValue= SensorValue [FrontLight];
	int leftValue= SensorValue [LeftLight];
	int rightValue= SensorValue [RightLight];
	int retValue = 0;

	if (isBlack (leftValue) && isBlack(frontValue) && isBlack(rightValue) ) {
		retValue = DRIVE_FORWARD;
	}
	else if (isWhite(leftValue) && isBlack(frontValue) && isBlack(rightValue)) {
		retValue = TURN_LEFT;
	}
	else if (isBlack(leftValue) && isBlack(frontValue) && isWhite(rightValue)) {
		retValue = TURN_RIGHT;
	}
	else if (isBlack (leftValue) && isWhite(frontValue) && isBlack(rightValue)) {
		retValue = BACKUP;
	}

	return (retValue);
}


task main()
{
	srand(nSysTime);  // generate seed for rand() from current system time
	// BlackFloor = SensorValue[FrontLight] + 5;
	wait1Msec(5000);
	int action = 0;
	BlackFloor = SensorValue[FrontLight] + 5;
	while (true) {

		action = readSensors();

		if (action == DRIVE_FORWARD) {
			motor[LeftMotor] = SPEED_FAST_FORWARD;
			motor[RightMotor] = SPEED_FAST_FORWARD;
			motor[CenterMotor] = SPEED_FAST_FORWARD;
		}
		else if (action == BACKUP) {
			motor[LeftMotor] = -1 * findRandom(85,100);
			motor[RightMotor] = -1 * findRandom(85,100);
			motor [CenterMotor] = -1 * findRandom(85,100);
			wait1Msec(findRandom (350,750));
		}
		else if (action == TURN_LEFT){
			motor[LeftMotor] = -1 * findRandom(85,100);
			motor[RightMotor] = 1 * findRandom(85,100);
			motor[CenterMotor] = 0;
			wait1Msec(findRandom (250,500));
		}
		else if (action == TURN_RIGHT){
			motor[LeftMotor] = 1 * findRandom(85,100);
			motor[RightMotor] = -1 * findRandom(85,100);
			motor[CenterMotor] = 0;
			wait1Msec(findRandom (250,500));
		}

	}

}
