void stateControl()
	{
#ifdef PRACTICE //Practice
	if (sysDisabledMode)					sysState.curr = DISABLED;	//0
	else if (sysAutoMode || sysVirtualAuto)	sysState.curr = AUTONOMOUS;	//2
	else									sysState.curr = OPERATOR;	//1
#else			//Competition
	if (bIfiRobotDisabled)			sysState.curr = DISABLED;
	else if (bIfiAutonomousMode)	sysState.curr = AUTONOMOUS;
	else							sysState.curr = OPERATOR;
#endif
	if (changed(sysState))
		{
		menuScrStr = 0;
		menuScrChar = 0;
		timerLCDScroll=0;
		timerLCDBacklight=0;
		switch (sysState.last)
			{
			case AUTONOMOUS:
				break;
			case DISABLED:
				break;
			case OPERATOR:
				break;
			}
		switch (sysState.curr)
			{
			case AUTONOMOUS:
				writeDebugStreamLine("***Autonomous***");
				autoStep = 0;
				autoStepCheck = 0;
				sysLCDBacklight=LCD_ALWAYS_ON;
				break;
			case DISABLED:
				writeDebugStreamLine("****Disabled****");
				sysLCDBacklight=LCD_TIMEOUT;
				break;
			case OPERATOR:
				writeDebugStreamLine("****Operator****");
				sysLCDBacklight=LCD_ALWAYS_ON;
				break;
			}
		}
	}
