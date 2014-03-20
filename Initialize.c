//Constants

//Functions
void initializeOther()
	{
	//--Sensors--//
	SensorValue[QUAD_LEFT] = 0;
	SensorValue[QUAD_RIGHT] = 0;
	SensorValue[GYRO] = 0;

	//--Timers--//
	ClearTimer(T1);
	ClearTimer(T2);
	ClearTimer(T3);
	ClearTimer(T4);

	//--Other--//
	writeDebugStreamLine("\n================");
#ifdef PHYSICAL_ROBOT_TARGET
	writeDebugStreamLine("-Physical Robot-");
#else
	writeDebugStreamLine("----Emulator----");
#endif
	sysState.curr = DISABLED; //Usually changes to operator later
	autoRoutine.curr = 0;
	}
