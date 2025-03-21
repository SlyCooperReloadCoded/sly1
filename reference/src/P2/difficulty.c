/**
 * @file difficulty.cpp
 *
 * @brief Implements the difficulty scaling functions.
*/
#include <difficulty.h>
#include <game.h>
#include <cstring>

/* Called when game starts; clears the difficulty struct */
void OnDifficultyGameLoad(DIFFICULTY* pdifficulty)
{
	memset(pdifficulty, 0, sizeof(DIFFICULTY));
}

/* Set the game difficulty props based on current save file */
void OnDifficultyWorldPreLoad(DIFFICULTY* pdifficulty)
{
	const GS* gsCur = g_pgsCur;
	const LS* lsCur = g_plsCur;
	const int gameworld = (int)(gsCur->gameworldCur);
	const int worldlevel = (int)(gsCur->worldlevelCur);

	DIFFICULTYLEVEL* difficultyProps;

	pdifficulty->ccoinRichMin = 4;
	pdifficulty->ccoinRichMax = 6;
	pdifficulty->ccoinPoorMax = 3;
	pdifficulty->ccoinPoorMin = 1;

	if (((gameworld == (int)GAMEWORLD_Intro) || (gameworld == (int)GAMEWORLD_Clockwerk)) || (worldlevel == (int)WORLDLEVEL_Hub))
	{ // Case: Current world is 0 or 5, or current level is a hub
		difficultyProps = &g_difficultyEasy; // Set easy difficulty
	}
	else if (((int)lsCur->fls & (int)FLS_KeyCollected) == 0)
	{ // Case: Key NOT collected on current level
		difficultyProps = &g_difficultyMedium; // set medium difficulty
	}
	else
	{ // Case: Key collected on current level
		difficultyProps = &g_difficultyHard; // set hard difficulty
	}

	pdifficulty->pdifficultyLevel = difficultyProps;

	ChangeSuck(lsCur->uSuck, pdifficulty);
	difficultyProps = pdifficulty->pdifficultyLevel; // redundant?

	// todo: finish function
}

/* Update the player suck and determine the number of suck charms they get */
void OnDifficultyWorldPostLoad(DIFFICULTY* pdifficulty)
{
	DIFFICULTYLEVEL* difficultyProps;
	int csuckCharms;

	// Case: The transition is a quit-game reload
	if (/*(g_transition.load_flags & 8) = 0 */ true) // todo implement g_transition
	{
		const float newSuck = GLimitLm((LM*)&pdifficulty->pdifficultyLevel->unk_lm_0x8, g_plsCur->uSuck);
		ChangeSuck(newSuck, pdifficulty);
	}
	// Case: The ransition is not a quit-game reload
	else {
		difficultyProps = pdifficulty->pdifficultyLevel;

		// Case: Suck value is BELOW charmLow or ABOVE charmHigh
		if ((g_plsCur->uSuck < difficultyProps->uSuckCharmLow) ||
			(difficultyProps->uSuckCharmHigh <= g_plsCur->uSuck))
		{
			// Suck value is lower than both thresholds
			if (g_plsCur->uSuck < difficultyProps->uSuckCharmHigh)
			{
				//RemoveSwExtraneousCharms(g_psw); // todo implement function
				return;
			}

			// Suck value is not below the charmLow, so it must be above charmHigh
			csuckCharms = difficultyProps->ccharmHigh;
		}
		// Case: Suck value is ABOVE charmLow but BELOW charmHigh
		else
		{
			csuckCharms = difficultyProps->ccharmLow;
		}

		if (g_pgsCur->ccharm < csuckCharms)
		{
			SetCcharm(csuckCharms); // todo implement function
			pdifficulty->dps = DPS_GivenCharms;
		}
	}
}

/**
 * @note This funciton is not implemented. It may be leftover from previous versions
 * of the game where there was a teleport powerup.
*/
void OnDifficultyInitialTeleport(DIFFICULTY* pdifficulty)
{
	return;
}

void OnDifficultyPlayerDeath(float scalar, DIFFICULTY* pdifficulty)
{
	DIFFICULTYLEVEL* pdifflevel = pdifficulty->pdifficultyLevel;

	// Get suck values for current level
	float uSuckCur = g_plsCur->uSuck;
	float duSuckDeath = pdifflevel->duSuckDeath;

	// Increase suck value
	ChangeSuck(uSuckCur + scalar * duSuckDeath, pdifficulty);

	// Update suckunknown_0x10
	float result;
	if (g_pgsCur->clife < 0)
	{
		// itgame over
		result = pdifficulty->pdifficultyLevel->field_0x40;
	}
	else
	{
		// not game over
		result = pdifflevel->field_0x3c;
		if (g_pgsCur->clife <= pdifflevel->field_0x4c)
		{
			result = result + pdifflevel->field_0x50;
		}
	}
	result = GLimitLm(&g_lmZeroOne, g_plsCur->unk_suck_0x10 + scalar * result);
	g_plsCur->unk_suck_0x10 = result;
}

/* Reduce player suck upon first triggering a checkpoint */
void OnDifficultyTriggerCheckpoint(DIFFICULTY* pdifficulty, CHKPNT* pchkpnt)
{
	DIFFICULTYLEVEL* pdifflevel;

	if (pchkpnt == NULL)
	{
		pdifflevel = pdifficulty->pdifficultyLevel;
	}

	/* todo: implement CHKPNT struct and finish this function */
	// ...
}

/* Resets some difficulty values upon collecting a key */
void OnDifficultyCollectKey(DIFFICULTY* pdifficulty)
{
	LS* lsCur = g_plsCur;

	ChangeSuck(0.0, pdifficulty);

	lsCur->unk_suck_0x10 = 0.0;
	lsCur->unk_field_0x70 = 0;

	memset(&lsCur->unk_field_0x74, 0, 1);
}

/* Update the suck value on the current level save data */
void ChangeSuck(float nParam, DIFFICULTY* pdifficulty)
{
	const float newSuck = GLimitLm(&pdifficulty->pdifficultyLevel->suckLm, (g_plsCur->uSuck + nParam * 0.1)); // clamp new suck
	g_plsCur->uSuck = newSuck; // set current level suck to clamped value
}
