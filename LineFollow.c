#pragma config(Sensor, S1,     LineLight,      sensorLightActive)
#pragma config(Motor,  motorA,          Left,          tmotorNXT, PIDControl, reversed, encoder)
#pragma config(Motor,  motorB,          Right,         tmotorNXT, PIDControl, reversed, encoder)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	int lowPower=35;
	int highPower=65;

	while (true) {
		if (SensorValue [LineLight] > 50) {
			motor[Left] = lowPower;
			motor[Right] = highPower;
		}
		else {
			motor[Left]=highPower;
			motor[Right]=lowPower;
		}
		Sleep(0);
	}
	motor[Left] = 0;
	motor[Right] = 0;
}
