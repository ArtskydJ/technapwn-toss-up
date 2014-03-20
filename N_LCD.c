void updateScrollingText(string *INStrs, int INNOStrs)
	{
	if (changed(autoRoutine)) //If we change autonomous routines
		{
		menuScrStr = 0;
		menuScrChar = 0;
		}
	if(timerLCDScroll >= NEXT_CHAR_MS) //If it is time to scroll message
		{
		string tString = (INStrs[menuScrStr]);
		if (menuScrChar >= strlen(tString))
			{
			menuScrChar=0;
			menuScrStr = ((menuScrStr+1) % INNOStrs);
			}
		string temp1,temp2,temp3;
		temp1 = (INStrs[menuScrStr]);
		temp2 = (INStrs[(menuScrStr+1)%INNOStrs]);
		temp3 = (INStrs[(menuScrStr+2)%INNOStrs]);
		StringDelete(temp1,0,menuScrChar);	//Delete the beginning
		sprintf(tString,"%s%s%s",temp1,temp2,temp3);
		strcpy(bottomLCDLine.curr,tString);
		menuScrChar++; 									//Scroll the message
		timerLCDScroll = 0;								//Reset Timer
		}
	}


void updateBacklight()
	{
	switch (sysLCDBacklight)
		{
		case 0:
		case 1:
			bLCDBacklight = (bool)sysLCDBacklight;
			timerLCDBacklight=0;
		break;

		case LCD_BLINK_SLOW:
			if (timerLCDBacklight > LCD_BLINK_SLOW_MS)
				{
				bLCDBacklight = !bLCDBacklight;
				timerLCDBacklight=0;
				}
		break;

		case LCD_BLINK_FAST:
			if (timerLCDBacklight > LCD_BLINK_FAST_MS)
				{
				bLCDBacklight = !bLCDBacklight;
				timerLCDBacklight=0;
				}
		break;

		case LCD_TIMEOUT:
			if (nLCDButtons != 0)
				timerLCDBacklight=0;
			bLCDBacklight = (timerLCDBacklight<LCD_TIMEOUT_MS);
		break;
		}
	}


void menuExecuteActivated()
	{
	menuItemActivated = false;
	switch (menuItem.curr)
		{
		case 00: {sysAutoMode = true;} break; //sysDisabledMode = false; (2013-05-13)
		case 01: {menuChecklistItem = (menuChecklistItem+1)%NO_CHECKLIST_ITEMS;} break;
		case 02: {sysMotorsEnabled = !sysMotorsEnabled;} break; //Enable / Disable motors
		case 03: break; //View battery Levels
		case 04: {sysMotorTest = !sysMotorTest;} break; //Run Motor Test/choose speed
		case 05: {mtrTestEnabled[potPosition(10)] = (( mtrTestEnabled[potPosition(10)]+2 )%3)-1;} break; //Toggle Motors between -1, 0 and 1
		case 06: break; //View Analog Value
		case 07: break; //View Digital Value
	/*	case 08: {LeftLineFolTile  = SenLeftLine;}  break;
		case 09: {LeftLineFolLine  = SenLeftLine;}  break;
		case 10: {RightLineFolTile = SenRightLine;} break;
		case 11: {RightLineFolLine = SenRightLine;} break;	*/
		default: break; //Execute nothing
		}
	}


void menuViewName()
	{
	string tString="";
	strcpy(tString,menuItemName[menuItem.curr]);
	switch(menuItem.curr)
		{
		case 0:
			switch (potCentered(NO_AUTO_ROUTINES))
				{
				case 0: StringFormat(tString,"%s %.1f |>%d ",menuItemName[menuItem.curr],((float)timerAuto/1000),autoRoutine.curr); break;
				case 1: StringFormat(tString,"%s %.1f | %d ",menuItemName[menuItem.curr],((float)timerAuto/1000),autoRoutine.curr); break;
				case 2: StringFormat(tString,"%s %.1f | %d<",menuItemName[menuItem.curr],((float)timerAuto/1000),autoRoutine.curr); break;
				}
			break;
		case 1: {strcat(tString, menuChecklist[menuChecklistItem*2]);} break;
		}
	strcpy(topLCDLine.curr,tString);
	}


void menuViewValue()
	{
	string tString1="",tString2="";
	bool scrollingValue=false;
	switch (menuItem.curr) //BOTTOM LINE
		{
		case 00: {string temp[NO_AUTO_NAME_STRS];
					for (int j=0; j<NO_AUTO_NAME_STRS; j++) temp[j]=autoName[autoRoutine.curr-1][j];
					updateScrollingText(temp,NO_AUTO_NAME_STRS); scrollingValue=true;} break; //Scrolling Autonomous Name
					
		case 01: {tString1 = menuChecklist[menuChecklistItem*2+1];} break;
		case 02: {tString1 = (sysMotorsEnabled)?"Enabled":"Disabled";} break;
		case 03: {updateScrollingText(batteryLevel,3); scrollingValue=true;} break; //Scrolling Battery Levels
		
		case 04: {tString1 = sysMotorTest?"On":"Off";
					StringFormat(tString2,"|Speed:%1d",stkMtrTest);} break;
					
		case 05: {int temp1=potPosition(10); int temp2=mtrTestEnabled[temp1];
					strcpy(tString1,motorName[temp1]);
					tString2=(temp2==-1)?"|Rev": (temp2==1)?"|Fwd":"|Off"; } break;// -1 Rev    1 Fwd    0 Off
					
		case 06: StringFormat(tString1, "anlg %1d:%1d", potPosition(8)+1,  SensorValue[potPosition(8)   ]); break; //View Analog Value
		case 07: StringFormat(tString1, "dgtl %1d:%1d", potPosition(12)+1, SensorValue[potPosition(12)+8]); break; //View Digital Value
		/*case 08: StringFormat(tString1,"%0004d-%0004d",LeftLineFolTile, SenLeftLine);  break;
		case 09: StringFormat(tString1,"%0004d-%0004d",LeftLineFolLine, SenLeftLine);  break;
		case 10: StringFormat(tString1,"%0004d-%0004d",RightLineFolTile,SenRightLine); break;
		case 11: StringFormat(tString1,"%0004d-%0004d",RightLineFolLine,SenRightLine); break;*/
		default: break;
		}
	if (scrollingValue)
		{
		if (menuItem.curr==0)	menuDisplayPos=LEFT0; //No   "<" at the beginning
		else					menuDisplayPos=LEFT1; //With "<" at the beginning
		}
	else
		{
		menuDisplayPos=CENTER;
		strcat(tString1,tString2);
		bottomLCDLine.curr = tString1;
		}
	}


void outputLCD()
	{
	updateBacklight();
	if (topLCDLine.curr != topLCDLine.last)
		{
		clearLCDLine(0);
		displayLCDCenteredString(0,topLCDLine.curr);
		}
	if (bottomLCDLine.curr != bottomLCDLine.last)
		{
		clearLCDLine(1);
		if (sysState.curr == AUTONOMOUS)
			displayLCDCenteredString(1,bottomLCDLine.curr);
		else if (sysState.curr == DISABLED || sysState.curr == OPERATOR)
			{
			switch (menuDisplayPos)
				{
				case LEFT0:  displayLCDString(1,0,bottomLCDLine.curr);			break;
				case LEFT1:  displayLCDString(1,1,bottomLCDLine.curr);			break;
				case CENTER: displayLCDCenteredString(1,bottomLCDLine.curr);	break;
				}
			}
		}
	if ((sysState.curr == DISABLED || sysState.curr == OPERATOR) && sysError==ERR_NONE)
		{
		if (menuItem.curr>0)				displayLCDString(1,0, "<");
		if (menuItem.curr<NO_MENU_ITEMS-1)	displayLCDString(1,15,">");
		}
	}


void processLCD()
	{
	if (sysError!=ERR_NONE)
		{
		sysLCDBacklight=LCD_BLINK_SLOW;
		switch(sysError)
			{
			case ERR_LOW_CORTEX:
				topLCDLine.curr=	"ERROR--Low";
				bottomLCDLine.curr=	"Cortex Battery";
				break;
			case ERR_LOW_POW_EX:
				topLCDLine.curr=	"ERROR--Low Power";
				bottomLCDLine.curr=	"Expander Battery";
				break;
			case ERR_ROBOT_IDLE:
				topLCDLine.curr =    "3018  Techna PWN";
				bottomLCDLine.curr = " Robotics  Nora ";
				break;
			}
		}
	else
		{
		sysLCDBacklight=LCD_ALWAYS_ON;
		if (sysState.curr == DISABLED || sysState.curr == OPERATOR) //Show the menu
			{
			if (pressed(btnScreenLeft))		menuItem.curr--;
			if (pressed(btnScreenRight))	menuItem.curr++;
			capValue(0, (menuItem.curr), (NO_MENU_ITEMS-1));

			if (pressed(btnScreenCenter))	menuItemActivated = !menuItemActivated;
			if (menuItemActivated)
				menuExecuteActivated();

			menuViewName();  //TOP LINE
			menuViewValue(); //BOTTOM LINE
			if (changed(menuItem))
				{
				menuScrStr = 0;
				menuScrChar = 0;
				}
			}
		else if (sysState.curr == AUTONOMOUS)
			{
			/*if (sysVirtualAuto)
				{
				if (joystickIsMoved(true) || pressed(btnScreenRight) || pressed(btnScreenLeft))
					{
					//sysVirtualAuto=false;
					autoResetEnd();
					}
				}*/
			StringFormat(topLCDLine.curr,"Time:%.1f | %d ",((float)timerAuto/1000),autoRoutine.curr);
			StringFormat(bottomLCDLine.curr, "Step: %d", autoStep);	//Show step
			}
		}
	}
