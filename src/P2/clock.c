#include <clock.h>
#include <intrinsics.h>

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

void SetClockRate(float rt)
{
    g_rtClock = rt;
    SetClockEnabled(&g_clock, rt > 0.0f);
}

void MarkClockTick(CLOCK *pclock)
{
    const TICK currentTick = TickNow();
    const TICK deltaTick = currentTick - pclock->tickFrame;
    float dt = deltaTick * CLOCK_EE_TICK_DURATION;

    // Clamp delta time between one and two frames
    float dtMin = CLOCK_FRAMETIME;
    float dtMax = CLOCK_FRAMETIME * 2;

    if (dt < dtMin)
    {
        dt = dtMin;
    }
    else if (dt > dtMax)
    {
        dt = dtMax;
    }

    // Store unscaled real delta time
    pclock->dtReal = dt;
    float dtScaled = pclock->fEnabled ? dt : 0.0f;
    dtScaled *= g_rtClockPowerUp * g_rtClock;

    // If scaled delta time is at least one frame, store the scaled value
    if (dtScaled >= CLOCK_FRAMETIME)
    {
        pclock->dtReal = dtScaled;
    }

    // Update clock state
    pclock->t += dtScaled;
    pclock->dtPrev = pclock->dt;
    pclock->dt = dtScaled;
    pclock->tReal += pclock->dtReal;
    pclock->tickFrame = currentTick;
}

void MarkClockTickRealOnly(CLOCK *pclock)
{
    const TICK currentTick = TickNow();
    const TICK deltaTick = currentTick - pclock->tickFrame;
    float dt = deltaTick * CLOCK_EE_TICK_DURATION;

    pclock->dtReal = dt;
    pclock->tReal += pclock->dtReal;
    pclock->tickFrame = currentTick;
}

void ResetClock(CLOCK *pclock, float t)
{ 
    pclock->t = t;
}

void SetClockEnabled(CLOCK *pclock, int fEnabled)
{
    pclock->fEnabled = fEnabled;
}

void StartupClock() 
{
    ulong cTick = READ_CP0_COUNT();

    s_tickLastRaw = (TICK)cTick;
    g_clock.tickFrame = TickNow();
}

/**
 * @todo Correct cWrapAround once the bss section of the TU is migrated.
 */
const TICK TickNow()
{
    // Read 32-bit CP0 Count register
    ulong cTick = READ_CP0_COUNT();

    // Mask count to ensure clean 32-bit value (likely not necessary)
    ulong ulMask = 0xFFFFFFFF;
    cTick = cTick & ulMask;

    // Detect wraparound: if count < previous count, the register overflowed
    if (cTick < s_tickLastRaw)
    {
        cWrapAround++;
    }

    // Store current count for next wraparound detection
    s_tickLastRaw = cTick;

    // Combine wraparound count (upper 32 bits) with current count (lower 32 bits)
    return (cWrapAround << 32) | cTick;
}
