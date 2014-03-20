//LCD.c

//Constants
static const int NO_CHECKLIST_ITEMS =	10;
static const int LCD_BLINK_SLOW_MS =	500;
static const int LCD_BLINK_FAST_MS =	200;
static const int LCD_TIMEOUT_MS =		5000;
static const string autoNames[NO_AUTO_ROUTINES] = {
	"L Red Mid 1 12pt",
	"R Blu Mid 1 12pt",
	"L Red Hng 1 17pt",
	"R Blu Hng 1 17pt",
	"L Red Mid 2 15pt",
	"R Blu Mid 2 15pt",
	"L Red Hng 2 21pt",
	"None",
	"None",
	"None",
	"Current Test",
	"L Red Hng Prog 1"};
static const string menuChecklist[NO_CHECKLIST_ITEMS] = {
	"Cortex on",
	"Power Expandr on",
	"Batteries in",
	"Batteries chargd",
	"Joy plugged in",
	"Joy lights green",
	"Robot aligned",
	"Correct auton",
	"Preload in",
	"Robot fits in 18"};

//Variables
static T_MENU_ITEMS menuItemIndex; //LCD Menu
static bool menuItemActivated=false;
static int menuChecklistItem = 0;
static int menuBatteryItem = 0;
static T_LC_STRING topLCDLine; //LCD Screen
static T_LC_STRING bottomLCDLine;
static string motorName[10];
static string menuItemName[M_NO_ITEMS];

//Functions
//This function sets string variables for use in the menu.
void initializeLCD(void)
	{
	motorName[DRIVE_FL]  = "L Drv Front";
	motorName[DRIVE_BL1] = "L Drv Back 1";
	motorName[DRIVE_BL2] = "L Drv Back 2";
	motorName[DRIVE_FR]  = "R Drv Front";
	motorName[DRIVE_BR1] = "R Drv Back 1";
	motorName[DRIVE_BR2] = "R Drv Back 2";
	motorName[LIFT_L]    = "L Lift 1";
	motorName[LIFT_L2]   = "L Lift 2";
	motorName[LIFT_R]    = "R Lift";
	motorName[INTK_L]    = "Intake";
	menuItemName[M_AUTON] =      "Time:";
	menuItemName[M_CHECKLIST] =  "Checklist:";
	menuItemName[M_ENABLE_OUT] = "Outputs are:";
	menuItemName[M_BATTERY] =    "Battery Volts";
	menuItemName[M_MTR_TEST] =   "Motor Test:";
	menuItemName[M_ANALOG] =     "Analog Values";
	menuItemName[M_DIGITAL] =    "Digital Values";
	menuItemName[M_MOTOR] =      "Motor Values";
	}


//This function checks how far the dial is turned compared to how many options
//number allowed. E.g. potPosition(100) returns a number between 0 and 99,
//proportional to how far the dial is turned.
int potPosition(int INMaxVal)
	{ return capIntValue(0, (float)INMaxVal*senSelectorPot/4096, INMaxVal-1); }


//This function updates the backlight. It allows the backlight to stay off/on,
//blink slow/fast, or to light up whenever a button is pressed.
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
			bLCDBacklight = (timerLCDBacklight<LCD_TIMEOUT_MS);
		break;
		}
	}


//This function runs when the center LCD button is pressed. If menuItemActivated
//was set to true in a switch case, then this function would repeat until the
//center LCD button was pressed again.
void menuExecuteActivated()
	{
	menuItemActivated = false;
	switch (menuItemIndex)
		{
		case M_AUTON:
			sysAutoMode = true;
			break;
		case M_CHECKLIST:
			menuChecklistItem = (menuChecklistItem+1)%NO_CHECKLIST_ITEMS;
			break;
		case M_ENABLE_OUT:
			sysDisabledMode = !sysDisabledMode;
			break; //Enable / Disable motors
		case M_BATTERY:
			menuBatteryItem = (menuBatteryItem+1)%2; //2 should be 3 with pow ex
			break; //View battery Levels
		case M_MTR_TEST:
			mtrTestEnabled[potPosition(10)] = (( mtrTestEnabled[potPosition(10)]+2 )%3)-1;
			break; //Toggle Motors between -1, 0 and 1
		case M_ANALOG: break; //View Analog Values
		case M_DIGITAL: break; //View Digital Values
		case M_MOTOR: break; //View Motor Values
		default: break; //Execute nothing
		}
	}


//This function analyzes variables and prepares text to print to the LCD. It
//checks which menu item it is on, and creates a string, which will be printed.
void menuView()
	{
	string tString0="";				//Top Line
	string tString1="",tString2="";	//Bottom Line

	sysMotorTest=false; //This gets set to true in case M_MTR_TEST
	strcpy(tString0,menuItemName[menuItemIndex]);
	switch (menuItemIndex) //BOTTOM LINE
		{
		case M_AUTON:
			StringFormat(tString0,"%s %3.1f | %d ",menuItemName[menuItemIndex],(float)timerAuto/1000,autoRoutine.curr);
			int temp = autoRoutine.curr-1;
			strcpy(tString1,autoNames[temp]);
			break; //Autonomous Name

		case M_CHECKLIST:
			tString1 = menuChecklist[menuChecklistItem];
			break;
		case M_ENABLE_OUT:
			tString1 = (sysDisabledMode)?"Disabled":"Enabled";
			break;
		case M_BATTERY:
			switch (menuBatteryItem)
				{
				case 0: sprintf(tString1,"Cortex:    %1.3f", (float)nAvgBatteryLevel/1000);   break;
				//case 1: sprintf(tString1,"Power Exp: %1.3f", (float)senPwrExpVoltage/70);     break;
				case 1: sprintf(tString1,"Backup 9v: %1.3f", (float)BackupBatteryLevel/1000); break;
				}
			break; //Battery Levels
		case M_MTR_TEST:
			sysMotorTest = true;
			StringFormat(tString2,"%3d",abs(stkMtrTest1)); //negative sign will not fit; using abs()
			strcat(tString0, tString2);
			int temp1 = potPosition(10);
			int temp2 = mtrTestEnabled[temp1];
			strcpy(tString1,motorName[temp1]);
			tString2 = (temp2==-1)?"|Rev": (temp2==1)?"|Fwd":"|Off"; // -1 Rev    1 Fwd    0 Off
			break;
		case M_ANALOG:
			StringFormat(tString1, "anlg %1d:%1d", potPosition(8)+1,  SensorValue[potPosition(8)   ]); //View Analog Value
			break;
		case M_DIGITAL:
			StringFormat(tString1, "dgtl %1d:%1d", potPosition(12)+1, SensorValue[potPosition(12)+8]); //View Digital Value
			break;
		case M_MOTOR:
			StringFormat(tString1, "motor %1d:%1d", potPosition(10)+1,  motor[potPosition(10)]); //View Motor Value
			break;
		}

	strcpy(topLCDLine.curr,tString0);
	strcat(tString1,tString2);
	strcpy(bottomLCDLine.curr,tString1);
	}


//This function checks for errors, and prints them to the screen if any exist.
//Otherwise, it checks for button presses, shows the menu or autonomous stats.
void processLCD()
	{
	static bool errorDismissed=false;
	if (sysError!=ERR_NONE && errorDismissed==false)
		{
		sysLCDBacklight=LCD_BLINK_SLOW;
		switch(sysError)
			{
			case ERR_LOW_CORTEX:
				topLCDLine.curr =    "ERROR--Low";
				bottomLCDLine.curr = "Cortex Battery";
				break;
			case ERR_LOW_POW_EX:
				topLCDLine.curr =    "ERROR--Low Power";
				bottomLCDLine.curr = "Expander Battery";
				break;
			case ERR_ROBOT_IDLE:
				topLCDLine.curr =    "3018  Techna PWN";
				bottomLCDLine.curr = " Robotics  Nora ";
				break;
			}
		if (nLCDButtons != 0)
			errorDismissed = true;
		}
	else
		{
		if (sysState.curr == DISABLED || sysState.curr == OPERATOR) //Show the menu
			{
			sysLCDBacklight=LCD_ALWAYS_ON;

			if (pressed(btnScreenLeft))		menuItemIndex--;
			if (pressed(btnScreenRight))	menuItemIndex++;
#ifdef MENU_WRAP
			menuItemIndex = (menuItemIndex + (NO_MENU_ITEMS)) % (NO_MENU_ITEMS); //ITEM = (ITEM + NUM) % NUM   |   (Wrap)
#else
			menuItemIndex = (T_MENU_ITEMS)capIntValue(0, menuItemIndex, M_NO_ITEMS-1); //(Don't wrap)
#endif
			if (pressed(btnScreenCenter))	menuItemActivated = !menuItemActivated;
			if (menuItemActivated)			menuExecuteActivated();

			menuView();
			}
		else if (sysState.curr == AUTONOMOUS)
			{
			if (btnScreenLeft.curr || btnScreenRight.curr)
				sysAutoMode = false; //Only works when competition switch is unplugged (see State.c)

			sysLCDBacklight=LCD_ALWAYS_ON;
			StringFormat(topLCDLine.curr,"Time: %3.1f | %d ",((float)timerAuto/1000),autoRoutine.curr);
			StringFormat(bottomLCDLine.curr, "Step: %d", autoStep);	//Show step
			}
		}
	}


//This function updates the backlight, applies screen strings if they have
//changed, and applies menu hints. Up to now, variables topLCDLine and
//bottomLCDLine have been set to the desired strings. This keeps the LCD from
//being cleared and set excessively (which causes ugly blinking).
void outputLCD()
	{
	updateBacklight();
	if (changedString(topLCDLine))
		{
		clearLCDLine(0);
		displayLCDCenteredString(0,topLCDLine.curr);
		}
	if (changedString(bottomLCDLine))
		{
		clearLCDLine(1);
		displayLCDCenteredString(1,bottomLCDLine.curr);
		}
#ifndef MENU_WRAP //No wrap
	if (sysState.curr != AUTONOMOUS && sysError==ERR_NONE)
		{
		if (menuItemIndex>0)                 displayLCDString(0,0, "<"); //If not at the first item, show prev arrow
		if (menuItemIndex<(int)M_NO_ITEMS-1) displayLCDString(0,15,">"); //If not at the last item, show next arrow
		}
#endif

	setLastString(&topLCDLine);
	setLastString(&bottomLCDLine);
	}
