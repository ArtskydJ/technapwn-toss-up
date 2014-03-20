//Variables
unsigned int timerLCDScroll		= 0;
unsigned int timerLCDBacklight	= 0;
unsigned int timerAuto			= 0;
unsigned int timerRobotIdle		= 0;
unsigned int timerEmulateSpeed	= 0;

//Functions
void inputTimers()
	{
	int tTimerMaster = time1(T3);
	ClearTimer(T3);
	if (autoClockRunning && sysState.curr==AUTONOMOUS)
		timerAuto +=		tTimerMaster;
	timerLCDScroll +=		tTimerMaster;
	timerLCDBacklight +=	tTimerMaster;
	timerEmulateSpeed =		tTimerMaster; //Yes, it is supposed to be =, not +=

	if (timerLCDScroll>62000)					timerLCDScroll = 62000; //Prevent wrapping
	if (timerLCDBacklight>62000)				timerLCDBacklight = 62000; //Prevent wrapping
	if (joystickIsMoved(true))					timerLCDBacklight = 0;
#if (_TARGET=="Robot")
	timerRobotIdle +=		tTimerMaster;
	if (joystickIsMoved(true) || nLCDButtons>0)	timerRobotIdle = 0;
	if (timerRobotIdle>62000)					timerRobotIdle = 62000; //Prevent wrapping
#endif
	}
