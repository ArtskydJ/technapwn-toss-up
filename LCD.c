//Constants
static const int NO_AUTO_ROUTINES =		12;
static const int NO_CHECKLIST_ITEMS =	9;
static const int NEXT_CHAR_MS =			175;
static const int LCD_BLINK_SLOW_MS =	500;
static const int LCD_BLINK_FAST_MS =	200;
static const int LCD_TIMEOUT_MS =		5000;
static const int M_AUTON =				0;
static const int M_CHECKLIST =			1;
static const int M_DIS_ENABLE_MTRS =	2;
static const int M_BATT_LEVELS =		3;
static const int M_MTR_TEST =			4;
static const int M_ANALOG_LEVELS =		5;
static const int M_DIGITAL_LEVELS =		6;
static const int M_EIGHTEEN =			7;
static const int NO_MENU_ITEMS =		8;

//Variables
static T_LC_BOOL btnScreenLeft;//LCD Buttons
static T_LC_BOOL btnScreenCenter;
static T_LC_BOOL btnScreenRight;
static T_LC_INT  menuItem;//LCD Menu
static int menuScrStr = 0;
static int menuScrChar = 0;
static bool menuItemActivated=false;
static int menuChecklistItem = 0;
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
	"NONE",
	"NONE",
	"NONE"};
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
	menuItemName[M_DIS_ENABLE_MTRS] = "Dis/Enable Mtrs";
	menuItemName[M_BATT_LEVELS] = "Battery Levels:";
	menuItemName[M_MTR_TEST] = "Motor Test:";
	menuItemName[M_ANALOG_LEVELS] = "Analog Value:";
	menuItemName[M_DIGITAL_LEVELS] = "Digital Value:";
	}


void setLCDLasts(void)
	{
	setLastBool(btnScreenLeft);
	setLastBool(btnScreenCenter);
	setLastBool(btnScreenRight);
	setLastInt(menuItem);
	setLastString(topLCDLine);
	setLastString(bottomLCDLine);
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
	int n=(float)INMaxVal*senSelectorPot/4096;
	capIntValue(0, n, INMaxVal-1);
	return n;
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
	btnScreenLeft.curr =	(bool)(nLCDButtons & 1);
	btnScreenCenter.curr =	(bool)(nLCDButtons & 2);
	btnScreenRight.curr =	(bool)(nLCDButtons & 4);
	if (sysState.curr != AUTONOMOUS)	//If not in autonomous
		autoRoutine.curr = potPosition(NO_AUTO_ROUTINES)+1;
	}


void stateChangeLCD(void)
	{
	menuScrStr = 0;
	menuScrChar = 0;
	}


/*void updateScrollingText(string &INapply, string INstr1, string INstr2, string INstr3) //3 input strings
	{
	string tStrs[3]={INstr1, INstr2, INstr3};
	bool tScroll = timerLCDScroll >= NEXT_CHAR_MS;
	if (changedInt(autoRoutine)) //If we change autonomous routines
		{
		menuScrStr = 0;
		menuScrChar = 0;
		}
	string result;
	strcpy(result,tStrs[menuScrStr]);
	if(tScroll)
		{
		if (menuScrChar >= strlen(result))
			{
			menuScrChar=0;
			menuScrStr = ((menuScrStr+1) % 3); //3 input strings
			}
		}
	StringDelete(result,0,menuScrChar); //Delete the beginning
	for (int t=menuScrStr+1; strlen(result)<20; t++)
		strcat(result,tStrs[t%3]);
	strcpy(INapply,result);
	if (tScroll)
		{
		menuScrChar++; //Scroll the message
		timerLCDScroll = 0; //Reset Timer
		}
	}

void updateScrollingText2(char *INstr)
	{
	if (changedInt(autoRoutine)) //If we change autonomous routines
		menuScrChar = 0;

	if(timerLCDScroll >= NEXT_CHAR_MS) //If it is time to scroll message
		{
		string tString = "";
		if (menuScrChar >= strlen(INstr))
			menuScrChar=0;

		StringFromChars(tString, INstr);
		StringDelete(tString, 0, menuScrChar);	//Delete the beginning
		while(strlen(tString)<20)				//While message is too short
			strcat(tString, INstr);					//Add to the message
		strcpy(bottomLCDLine.curr,tString);		//Assign message to bottomLCDLine
		menuScrChar++; 							//Scroll the message
		timerLCDScroll = 0;						//Reset Timer
		}
	}*/


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
		case M_AUTON:
			sysAutoMode = true;
			break; //sysDisabledMode = false; (2013-05-13)
		case M_CHECKLIST:
			menuChecklistItem = (menuChecklistItem+1)%NO_CHECKLIST_ITEMS;
			break;
		case M_DIS_ENABLE_MTRS:
			sysMotorsEnabled = !sysMotorsEnabled;
			break; //Enable / Disable motors
		case M_BATT_LEVELS: break; //View battery Levels
		case M_MTR_TEST:
			mtrTestEnabled[potPosition(10)] = (( mtrTestEnabled[potPosition(10)]+2 )%3)-1;
			break; //Toggle Motors between -1, 0 and 1
		case M_EIGHTEEN:
			if (outLift==LIFT_EIGHTEEN)
				outLift = 0;
			else
				outLift=LIFT_EIGHTEEN;
			break; //View Analog Value
		default: break; //Execute nothing
		}
	}


void menuView()
	{
	string tString0="";				//Top Line
	string tString1="",tString2="";	//Bottom Line
	bool tScrollingValue=false;

	sysMotorTest=false;

	strcpy(tString0,menuItemName[menuItem.curr]);
	switch (menuItem.curr) //BOTTOM LINE
		{
		case M_AUTON:
			switch (potCentered(NO_AUTO_ROUTINES))
				{
				case 0: StringFormat(tString0,"%s %.1f |>%d ",menuItemName[menuItem.curr],((float)timerAuto/1000),autoRoutine.curr); break;
				case 1: StringFormat(tString0,"%s %.1f | %d ",menuItemName[menuItem.curr],((float)timerAuto/1000),autoRoutine.curr); break;
				case 2: StringFormat(tString0,"%s %.1f | %d<",menuItemName[menuItem.curr],((float)timerAuto/1000),autoRoutine.curr); break;
				}
			int temp = autoRoutine.curr-1;
			strcpy(tString1,autoNames[temp]);
			//updateScrollingText(tString1,autoNames[temp][0],autoNames[temp][1],autoNames[temp][2]);
			break; //Scrolling Autonomous Name

		case M_CHECKLIST:
			strcat(tString0, menuChecklist[menuChecklistItem*2]);
			tString1 = menuChecklist[menuChecklistItem*2+1];
			break;
		case M_DIS_ENABLE_MTRS:
			tString1 = (sysMotorsEnabled)?"Enabled":"Disabled";
			break;
		case M_BATT_LEVELS:
			sprintf(tString1,"C%1.1f P%1.1f B%1.1f", (float)nAvgBatteryLevel/1000,
					(float)senPwrExpVoltage/70,(float)BackupBatteryLevel/1000);
			//updateScrollingText(tString1,batteryLevel[0],batteryLevel[1],"");
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

	strcat(tString1,tString2);
	strcpy(bottomLCDLine.curr,tString1);
	strcpy(topLCDLine.curr,tString0);
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
			sysLCDBacklight=LCD_TIMEOUT;

			if (pressed(btnScreenLeft))		menuItem.curr--;
			if (pressed(btnScreenRight))	menuItem.curr++;
			capIntValue(0, menuItem.curr, NO_MENU_ITEMS-1);
			//menuItem.curr = (menuItem.curr + (NO_MENU_ITEMS)) % (NO_MENU_ITEMS); //ITEM = (ITEM + NUM) % NUM

			if (pressed(btnScreenCenter))	menuItemActivated = !menuItemActivated;
			if (menuItemActivated)			menuExecuteActivated();

			menuView();
			if (changedInt(menuItem))
				{
				menuScrStr = 0;
				menuScrChar = 0;
				}
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
			if (menuItem.curr==0)
				displayLCDString(1,0,bottomLCDLine.curr);
			else
				displayLCDString(1,1,bottomLCDLine.curr);
			}
		}
	if (sysState.curr != AUTONOMOUS && sysError==ERR_NONE)
		{
		if (menuItem.curr>0)				displayLCDString(1,0, "<"); //If not at the first item, show prev arrow
		if (menuItem.curr<NO_MENU_ITEMS-1)	displayLCDString(1,15,">"); //If not at the last item, show next arrow
		}
	}
