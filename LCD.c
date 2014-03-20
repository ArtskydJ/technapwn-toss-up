//LCD.c

//Constants
static const int NO_CHECKLIST_ITEMS =	10;
static const int LCD_BLINK_SLOW_MS =	500;
static const int LCD_BLINK_FAST_MS =	200;
static const int LCD_TIMEOUT_MS =		5000;
static const string autoNames[NO_AUTO_ROUTINES] = {
	"Red Mid 1  N  12",
	"Blu Mid 1  N  12",
	"Red Hng 1  S  11",
	"Blu Hng 1  S  11",
	"Red Mid 2  N  15",
	"Blu Mid 2  N  15",
	"NONE",
	"NONE",
	"Test Things",
	"Test Drive-Time",
	"Test Gyro-Turn",
	"Red-Mid Skills 1"};
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
	menuItemName[M_VOLUME] =     "Sound Volume";
	}


/* This function checks how far the potentiometer is turned and compares it to
the max number allowed. Then it returns the corresponding value. For example, if
you want 10 numbers, then you input 10 and it will return a number from 0 - 9,
depending on how far the potentiometer is turned.
*/
int potPosition(int INMaxVal)
	{ return capIntValue(0, (float)INMaxVal*senSelectorPot/4096, INMaxVal-1); }


/* This function is similar to potPosition, but it returns 0, 1 or 2, relative
to the distance from a "border". 0, 2 are left and right borders, 1 is centered.
*/
int potCentered(int INMaxVal)
	{ return ((float)3*INMaxVal*senSelectorPot/4096)%3; }


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


void menuExecuteActivated()
	{
	menuItemActivated = false;
	switch (menuItemIndex)
		{
		case M_AUTON:
			sysAutoMode = true;
			break; //sysDisabledMode = false; (2013-05-13)
		case M_CHECKLIST:
			menuChecklistItem = (menuChecklistItem+1)%NO_CHECKLIST_ITEMS;
			break;
		case M_ENABLE_OUT:
			sysOutputsEnabled = !sysOutputsEnabled;
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
		case M_VOLUME:
			nVolume = potPosition(101);
			break;
		default: break; //Execute nothing
		}
	}


void menuView()
	{
	string tString0="";				//Top Line
	string tString1="",tString2="";	//Bottom Line

	sysMotorTest=false;

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
			tString1 = (sysOutputsEnabled)?"Enabled":"Disabled";
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
		case M_VOLUME:
			StringFormat(tString1, "Is:%d Set:%1d", nVolume, potPosition(101)); //Set Volume Level
			break;
		}

	strcpy(topLCDLine.curr,tString0);
	strcat(tString1,tString2);
	strcpy(bottomLCDLine.curr,tString1);
	}


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
			menuItemIndex = (T_MENU_ITEMS)capIntValue(0, menuItemIndex, M_NO_ITEMS-1);
			//menuItemIndex = (menuItemIndex + (NO_MENU_ITEMS)) % (NO_MENU_ITEMS); //ITEM = (ITEM + NUM) % NUM

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
	if (sysState.curr != AUTONOMOUS && sysError==ERR_NONE)
		{
		if (menuItemIndex>0)                 displayLCDString(0,0, "<"); //If not at the first item, show prev arrow
		if (menuItemIndex<(int)M_NO_ITEMS-1) displayLCDString(0,15,">"); //If not at the last item, show next arrow
		}

	setLastString(&topLCDLine);
	setLastString(&bottomLCDLine);
	}
