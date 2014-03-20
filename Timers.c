
static int timerMaster;

void inputTimers()
	{
	timerMaster = time1(T3);
	ClearTimer(T3);
	if (autoClockRunning && sysState.curr==AUTONOMOUS)
		timerAuto +=		timerMaster;
	timerLCDScroll +=		timerMaster;
	timerLCDBacklight +=	timerMaster;
	timerEmulateSpeed =		timerMaster; //Yes, it is supposed to be =, not +=

#if (_TARGET=="Robot")
	timerRobotIdle +=		timerMaster;
	if (joystickIsMoved(true) || nLCDButtons>0)	timerRobotIdle = 0;
	if (timerRobotIdle>62000)					timerRobotIdle = 62000; //Prevent wrapping
#endif
	}