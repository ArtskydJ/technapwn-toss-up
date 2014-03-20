void stateControl()
	{
	//--Decide what state the robot is in--//
	if (nVexRCReceiveState & vrCompetitionSwitch)	//If the Competition switch is plugged in...
		{
		if (bIfiRobotDisabled)			sysState.curr = DISABLED;	//...base the state on comp switch settings
		else if (bIfiAutonomousMode)	sysState.curr = AUTONOMOUS;
		else							sysState.curr = OPERATOR;
		}
	else											//If the Competition switch is not plugged in...
		{
		if (sysDisabledMode)	sysState.curr = DISABLED;	//...base the state on variables
		else if (sysAutoMode)	sysState.curr = AUTONOMOUS;
		else					sysState.curr = OPERATOR;
		}

	if (changed(sysState))
		{
		//--Execute whenever the state changes--//
		menuScrStr = 0;
		menuScrChar = 0;
		timerLCDScroll=0;
		timerLCDBacklight=0;
		
		//--Execute depending on which state changing from--//
		switch (sysState.last)
			{
			case AUTONOMOUS:	break;
			case DISABLED:		break;
			case OPERATOR:		break;
			}
			
		//--Execute depending on which state changing to--//
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
