//Constants
static const int NO_CHECKLIST_ITEMS =	9;
static const int LCD_BLINK_SLOW_MS =	500;
static const int LCD_BLINK_FAST_MS =	200;
static const int LCD_TIMEOUT_MS =		5000;

//Variables
static T_LC_BOOL btnScreenLeft; //LCD Buttons
static T_LC_BOOL btnScreenCenter;
static T_LC_BOOL btnScreenRight;
static T_MENU_ITEMS menuItemIndex; //LCD Menu
static bool menuItemActivated=false;
static int menuChecklistItem = 0;
static int menuBatteryItem = 0;
static T_LC_STRING topLCDLine = "";//LCD Screen
static T_LC_STRING bottomLCDLine = "";

static string motorName[10];
//static string autoString[NO_AUTO_NAME_STRS];
static string autoNames[NO_AUTO_ROUTINES] = { //make const? (gives error with scroll func)
	"B M | P 2L | 12",
	"R M | P 2L | 12",
	"B H | P 2B | 9",
	"R H | P 2B | 9",
	"B M | Prog",
	"NONE",
	"NONE",
	"NONE",
	"NONE",
	"Test Things",
	"Test Drive Time",
	"Test Gyro Turn"};
//static const char autonName[]="NONE | ";
static string menuChecklist[NO_CHECKLIST_ITEMS*2] =
	{
	"      ",	"Batteries in",
	"      ",	"Batts charged",
	" Power",	"Ex + Cortex on",
	"      ",	"Joy plugged in",
	"  Joy ",	"lights green",
	"      ",	"Robot aligned",
	"      ",	"Correct auton",
	"      ",	"Preload in",
	" Robot",	"fits in 18\""
	};

static string menuItemName[NO_MENU_ITEMS];

//Functions
void initializeLCD(void)
	{
	motorName[DRIVE_FL]  = "Frnt L Dr";
	motorName[DRIVE_BL1] = "Back L Dr1";
	motorName[DRIVE_BL2] = "Back L Dr2";
	motorName[DRIVE_FR]  = "Frnt R Dr1";
	motorName[DRIVE_BR1] = "Back R Dr1";
	motorName[DRIVE_BR2] = "Back R Dr2";
	motorName[LIFT_L]    = "L Lift";
	motorName[LIFT_R]    = "R Lift";
	motorName[INTK_L]    = "Intake";
	//motorName[INTK_R]    = "R Intake";

	menuItemName[M_AUTON] = "Time:";
	menuItemName[M_CHECKLIST] = "Checklist:";
	menuItemName[M_DIS_ENABLE_MTRS] = "Disable Outputs";
	menuItemName[M_BATT_LEVELS] = "Battery Levels:";
	menuItemName[M_MTR_TEST] = "Motor Test:";
	menuItemName[M_ANALOG_LEVELS] = "Analog Value:";
	menuItemName[M_DIGITAL_LEVELS] = "Digital Value:";
	}


/* This function checks how far the potentiometer
is turned and compares it to the max number
allowed. Then it returns the corresponding value.
 For example, if you want 10 numbers, then you
input 10 and it will return a number from 0 - 9,
depending on how far the potentiometer is turned.
*/
int potPosition(int INMaxVal)
	{
	return capIntValue(0, (float)INMaxVal*senSelectorPot/4096, INMaxVal-1);
	}


/* This function is similar to potPosition, but
it returns 0, 1 or 2 depending on how close the
potentiometer is to a "border". 0 and 2 are
borders, while 1 is centered.
*/
int potCentered(int INMaxVal)
	{
	int n=(float)3*INMaxVal*senSelectorPot/4096;
	return n%3;
	}


void inputLCD(void)
	{
	//--Set Lasts--//
	setLastBool(&btnScreenLeft);
	setLastBool(&btnScreenCenter);
	setLastBool(&btnScreenRight);
	setLastString(&topLCDLine);
	setLastString(&bottomLCDLine);

	btnScreenLeft.curr =	(bool)(nLCDButtons & 1);
	btnScreenCenter.curr =	(bool)(nLCDButtons & 2);
	btnScreenRight.curr =	(bool)(nLCDButtons & 4);
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
	switch (menuItemIndex)
		{
		case M_AUTON:
			sysAutoMode = true;
			break; //sysDisabledMode = false; (2013-05-13)
		case M_CHECKLIST:
			menuChecklistItem = (menuChecklistItem+1)%NO_CHECKLIST_ITEMS;
			break;
		case M_DIS_ENABLE_MTRS:
			sysMotorsEnabled = !sysMotorsEnabled;
			break; //Enable / Disable motors
		case M_BATT_LEVELS:
			menuBatteryItem = (menuBatteryItem+1)%3;
			break; //View battery Levels
		case M_MTR_TEST:
			mtrTestEnabled[potPosition(10)] = (( mtrTestEnabled[potPosition(10)]+2 )%3)-1;
			break; //Toggle Motors between -1, 0 and 1
		case M_ANALOG_LEVELS: break; //View Analog Value
		case M_DIGITAL_LEVELS: break; //View Digital Value
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
			switch (potCentered(NO_AUTO_ROUTINES))
				{
				case 0: StringFormat(tString0,"%s %.1f |>%d ",menuItemName[menuItemIndex],((float)timerAuto/1000),autoRoutine.curr); break;
				case 1: StringFormat(tString0,"%s %.1f | %d ",menuItemName[menuItemIndex],((float)timerAuto/1000),autoRoutine.curr); break;
				case 2: StringFormat(tString0,"%s %.1f | %d<",menuItemName[menuItemIndex],((float)timerAuto/1000),autoRoutine.curr); break;
				}
			int temp = autoRoutine.curr-1;
			strcpy(tString1,autoNames[temp]);
			break; //Scrolling Autonomous Name

		case M_CHECKLIST:
			strcat(tString0, menuChecklist[menuChecklistItem*2]);
			tString1 = menuChecklist[menuChecklistItem*2+1];
			break;
		case M_DIS_ENABLE_MTRS:
			tString1 = (sysMotorsEnabled)?"Enabled":"Disabled";
			break;
		case M_BATT_LEVELS:
			switch (menuBatteryItem)
				{
				case 0: sprintf(tString1,"Cortex: %1.3f", (float)nAvgBatteryLevel/1000);   break;
				case 1: sprintf(tString1,"Pow Ex: %1.3f", (float)senPwrExpVoltage/70);     break;
				case 2: sprintf(tString1,"Backup: %1.3f", (float)BackupBatteryLevel/1000); break;
				}
			break; //Scrolling Battery Levels
		case M_MTR_TEST:
			sysMotorTest = true;
			StringFormat(tString2,"%5d",stkMtrTest);
			strcat(tString0, tString2);
			int temp1 = potPosition(10);
			int temp2 = mtrTestEnabled[temp1];
			strcpy(tString1,motorName[temp1]);
			tString2 = (temp2==-1)?"|Rev": (temp2==1)?"|Fwd":"|Off"; // -1 Rev    1 Fwd    0 Off
			break;
		case M_ANALOG_LEVELS:
			StringFormat(tString1, "anlg %1d:%1d", potPosition(8)+1,  SensorValue[potPosition(8)   ]);//View Analog Value
			break;
		case M_DIGITAL_LEVELS:
			StringFormat(tString1, "dgtl %1d:%1d", potPosition(12)+1, SensorValue[potPosition(12)+8]); //View Digital Value
			break;
		}

	strcpy(topLCDLine.curr,tString0);
	strcat(tString1,tString2);
	strcpy(bottomLCDLine.curr,tString1);
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
		if (sysState.curr == DISABLED || sysState.curr == OPERATOR) //Show the menu
			{
			sysLCDBacklight=LCD_ALWAYS_ON;

			if (pressed(btnScreenLeft))		menuItemIndex--;
			if (pressed(btnScreenRight))	menuItemIndex++;
			menuItemIndex = (T_MENU_ITEMS)capIntValue(0, menuItemIndex, NO_MENU_ITEMS-1);
			//menuItemIndex = (menuItemIndex + (NO_MENU_ITEMS)) % (NO_MENU_ITEMS); //ITEM = (ITEM + NUM) % NUM

			if (pressed(btnScreenCenter))	menuItemActivated = !menuItemActivated;
			if (menuItemActivated)			menuExecuteActivated();

			menuView();
			}
		else if (sysState.curr == AUTONOMOUS)
			{
			sysLCDBacklight=LCD_ALWAYS_ON;
			StringFormat(topLCDLine.curr,"Time:%.1f | %d ",((float)timerAuto/1000),autoRoutine.curr);
			StringFormat(bottomLCDLine.curr, "Step: %d", autoStep);	//Show step
			}
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
		if (sysState.curr==AUTONOMOUS || strlen(bottomLCDLine.curr)<16)
			displayLCDCenteredString(1,bottomLCDLine.curr);
		else
			{
			if (menuItemIndex==0)
				displayLCDString(1,0,bottomLCDLine.curr);
			else
				displayLCDString(1,1,bottomLCDLine.curr);
			}
		}
	if (sysState.curr != AUTONOMOUS && sysError==ERR_NONE)
		{
		if (menuItemIndex>0)                    displayLCDString(1,0, "<"); //If not at the first item, show prev arrow
		if (menuItemIndex<(int)NO_MENU_ITEMS-1) displayLCDString(1,15,">"); //If not at the last item, show next arrow
		}
	}
