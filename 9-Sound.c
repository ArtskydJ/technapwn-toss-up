//Sound.c

//Constants
#define NO_SOUNDS_INTK 2
//Variables
static int sndIndexIntk = 0;

//Functions
//This function plays sound effects (if enabled) and plays beeps if the robot
//has an error (for example, low battery).
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
		if (bSoundActive==false)
			{
			if (sgn(outLift) == sgn(UP)) //If the lift is going up
				{
				PlaySoundFile("Inception.wav");
				}
			
			if (sgn(outIntk) == sgn(IN)) //If the intake is intaking
				{
				switch (sndIndexIntk)
					{
					case 0: PlaySoundFile("LaserFire.wav"); break;
					case 1: PlaySoundFile("GearClicking4.wav"); break;
					}
				sndIndexLift = (sndIndexLift+1)%NO_SOUNDS_INTK;
				}
			
			if (outCata)
				{
				PlaySoundFile("Smash.wav");
				}
			}
		}
#endif
	}
