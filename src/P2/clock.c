#include <clock.h>

// constants
static const int CLOCK_FRAMERATE = 60; // 60 FPS
static const float CLOCK_FRAMETIME = 1.f / CLOCK_FRAMERATE; // 1/60th of a second

static const int CLOCK_EE_TICK_RATE = 294912000; // 294.912 MHz
static const float CLOCK_EE_TICK_DURATION = 1.f / CLOCK_EE_TICK_RATE; // 1/294.912 MHz

// data
float g_rtClock = 1.0f;
float g_rtClockPowerUp = 1.0f;
CLOCK g_clock = { 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0 };
TICK s_tickLastRaw; // Should be static?

// text
void SetClockRate(float rt) {
    g_rtClock = rt;
    SetClockEnabled(&g_clock, rt > 0.0f);
}

void MarkClockTick(CLOCK* pclock)
{
	float dt;
	float t1;

	const TICK tickFrame = TickNow();
	const TICK deltaTick = tickFrame - pclock->tickFrame;

	dt = deltaTick * CLOCK_EE_TICK_DURATION;

    t1 = CLOCK_FRAMETIME * 2;

	if (dt < CLOCK_FRAMETIME) {
		dt = CLOCK_FRAMETIME;
	}
	else if (t1 < dt) {
		dt = t1;
	}

	pclock->dtReal = dt;

	float dtFinal = 0.0f;

	if (pclock->fEnabled) {
		dtFinal = dt;
	}

	dtFinal *= g_rtClockPowerUp * g_rtClock;

	if (CLOCK_FRAMETIME <= dtFinal) {
		pclock->dtReal = dtFinal;
	}

	pclock->t += dtFinal;
	pclock->dtPrev = pclock->dt;
	pclock->dt = dtFinal;
	pclock->tReal += pclock->dtReal;
	pclock->tickFrame = tickFrame;
}

void MarkClockTickRealOnly(CLOCK *pclock)
{
	const TICK tickFrame = TickNow();
	const TICK deltaTick = tickFrame - pclock->tickFrame;
	float dt = deltaTick * CLOCK_EE_TICK_DURATION;

	pclock->dtReal = dt;
	pclock->tReal += pclock->dtReal;
	pclock->tickFrame = tickFrame;
}

void ResetClock(CLOCK *pclock, float t)
{
	pclock->t = t;
}

void SetClockEnabled(CLOCK *pclock, int fEnabled)
{
	pclock->fEnabled = fEnabled;
}

INCLUDE_ASM(const s32, "P2/clock", StartupClock__Fv);
#ifdef SKIP_ASM
/**
 * @todo 69.58% matched.
 */
void StartupClock()
{
	// todo: what is count?
	// s_tickLastRaw = (long)Count;
	g_clock.tickFrame = TickNow();
}
#endif

INCLUDE_ASM(const s32, "P2/clock", TickNow__Fv);
INCLUDE_ASM(const s32, "P2/clock", func_00143140); // empty, not really a function
#ifdef SKIP_ASM
/**
 * @todo 7.78% matched.
 */
const TICK TickNow()
{
	// todo: what is Count?
	// TICK countLow = (long)Count & 0xffffffff;
	// if (countLow < s_tickLastRaw) {
	// 	cWrapAround.1014 += 1;
	// }
	// s_tickLastRaw = countLow;
	// return cWrapAround.1014 << 0x20 | countLow;
	return (TICK)1.0; // temp
}
#endif
