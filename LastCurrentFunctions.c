//Functions
/* These functions are for the LC types.
(Last-Current types.)
*/
bool changedBool(T_LC_BOOL INLC)
	{ //Returns true if the boolean changed
	return (INLC.last != INLC.curr);
	}

bool changedInt(T_LC_INT INLC)
	{ //Returns true if the integer changed
	return (INLC.last != INLC.curr);
	}

bool pressed(T_LC_BOOL INLC)
	{ //Returns true if it was just pressed
	return (!INLC.last && INLC.curr);
	}

int diffLastInt(T_LC_BOOL INLC)
	{ //Returns the difference of last and current value
	return (INLC.curr - INLC.last);
	}

int diffStepInt(T_LC_INT INLC)
	{ //Returns the difference of step starting and current value
	return (INLC.stepStart - INLC.last);
	}

void setLastBool(T_LC_BOOL *INLC)
	{ //Sets the last value to the current value
	INLC->last = INLC->curr;
	}

void setLastInt(T_LC_INT *INLC)
	{ //Sets the last value to the current value
	INLC->last = INLC->curr;
	}

void setLastString(T_LC_STRING *INLC)
	{ //Sets the last value to the current value
	INLC->last = INLC->curr;
	}

void setStepInt(T_LC_INT *INLC)
	{ //Sets the step start value to the current value
	INLC->stepStart = INLC->curr;
	}

/*void setToZeroBool(T_LC_BOOL *INLC)
	{ //Sets the step start value to the current value
	INLC->last = false;
	INLC->curr = false;
	}*/

void setToZeroInt(T_LC_INT *INLC)
	{ //Sets the step start value to the current value
	INLC->last = 0;
	INLC->curr = 0;
	}

void slewLCInt(T_LC_INT *INLC, int INnum)
	{
	int diff = INLC->curr - INLC->last;
	if		(diff > INnum) diff = INnum;
	else if (diff < -INnum) diff = -INnum;
	
	INLC->curr += diff;
	}
