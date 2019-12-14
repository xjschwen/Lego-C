int BlackFloor;

task main()
{
	BlackFloor = SensorValue[LightSensor] + 5;
	wait1Msec(5000);

	while(true)
	{
		motor[LeftMotor] = 100;
		motor[RightMotor] = 100;

		if (SensorValue[LightSensor] > BlackFloor)
		{
			motor[LeftMotor] = -50;
			motor[RightMotor] = -50;
			wait1Msec(500);
			motor[LeftMotor] = 50;
			wait1Msec(500);
		}
	}
}
