//Constants

//Functions
void initializeOther()
	{
	//--Encoders--//
	SensorValue[QUAD_LEFT] = 0;
	SensorValue[QUAD_RIGHT] = 0;

	//--Timers--//
	ClearTimer(T1);
	ClearTimer(T2);
	ClearTimer(T3);
	ClearTimer(T4);

	//--Other--//
	writeDebugStreamLine("================");
	sysState.curr=DISABLED; //Should change to operator later
	}
