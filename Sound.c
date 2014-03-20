//Sound.c

//Constants
#define NO_SOUNDS_LIFT 1
#define NO_SOUNDS_INTK 2
//Variables
static int sndIndexLift = 0;
static int sndIndexIntk = 0;

//Functions
void outputSound()
	{
	if (sysError!=ERR_NONE && sysError!=ERR_ROBOT_IDLE) //If there is an error (not including idling)
		{
		if (timerLCDBacklight<MIN_LOOP_MS*2)
			PlayImmediateTone(784, 15);
		}
#ifdef SOUND_EFFECTS
	else //No errors!
		{
		if (sgn(outLift) == sgn(UP) && bSoundActive==false) //If the lift is going up
			{
			switch (sndIndexLift)
				{
				case 0: PlaySoundFile("Inception.wav"); break;
				}
			sndIndexLift = (sndIndexLift+1)%NO_SOUNDS_LIFT;
			}
		
		if (sgn(outIntk) == sgn(IN) && bSoundActive==false) //If the intake is intaking
			{
			switch (sndIndexIntk)
				{
				case 0: PlaySoundFile("LaserFire.wav"); break;
				case 1: PlaySoundFile("GearClicking4.wav"); break;
				}
			sndIndexLift = (sndIndexLift+1)%NO_SOUNDS_INTK;
			}
		}
#endif
	}
