//State.c

//Functions
//This function decides if the robot is in disabled, autonomous, or operator
//depending on what the competition switch is on (if plugged in) or what the
//robot thinks it is in. This allows us to test autonomous without a competition
//switch by changing variables. These variables can be modified on the LCD.
void inputProcessState()
	{
	setLastInt(&sysState);

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

	if (changedInt(sysState))
		{
		//--Execute whenever the state changes--//
		timerLCDScroll=0;
		timerLCDBacklight=0;

		liftPresetIndex = BAR;

		zeroMotors();

		//--Execute depending on which state changing from--//
		switch (sysState.last)
			{
			case AUTONOMOUS:	sysDisableLift = true;	break;
			case DISABLED:		break;
			case OPERATOR:		break;
			}

		//--Execute depending on which state changing to--//
		switch (sysState.curr)
			{
			case AUTONOMOUS:
				writeDebugStreamLine("***Autonomous***");
				stateSwitchToAutonomous();
				sysLCDBacklight = LCD_ALWAYS_ON;
				break;
			case DISABLED:
				writeDebugStreamLine("****Disabled****");
				sysLCDBacklight = LCD_ALWAYS_ON; //LCD_TIMEOUT;
				break;
			case OPERATOR:
				writeDebugStreamLine("****Operator****");
				sysLCDBacklight = LCD_ALWAYS_ON;
				break;
			}
		}
	}
