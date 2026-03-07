#ifndef SMARTGUARD_H
#define SMARTGUARD_H

#include "common.h"
#include <stepguard.h>
#include <actseg.h>
#include <cid.h>
#include <mq.h>
#include <so.h>

struct SGFT
{
    /* 0x00 */ OID oidTarget;
    /* 0x04 */ ALO *paloTarget;
};

/**
 * @class SMART_GUARD
 * @brief non-flashlight guard.
 */
struct SMARTGUARD : public STEPGUARD
{
    // ...
    /* 0xc38 */ SGFT mpsgssgft[SGS_Max];
    // ...
};

void InitSmartguard(SMARTGUARD *psmartguard);

void PostSmartguardLoadFlashlight(SMARTGUARD *psmartguard);

void UseSmartguardFlashlightTarget(SMARTGUARD *psmartguard, SGS sgs, OID oidTarget);

/**
 * @todo Figure out what this function does, determine the right types and rename.
 */
void FUN_001B7100(SMARTGUARD *psmartguard, int unk);

void PostSmartguardLoad(SMARTGUARD *psmartguard);

int FFilterSmartguardDetect(SMARTGUARD *psmartguard, SO *pso);

int FDetectSmartguard(SMARTGUARD *psmartguard);

void UpdateSmartguard(SMARTGUARD *psmartguard, float dt);

void UpdateSmartguardFlashlight(SMARTGUARD *psmartguard);

void OnSmartguardEnteringSgs(SMARTGUARD *psmartguard, SGS sgsPrev, ASEG *pasegOverride);

int FCanSmartguardAttack(SMARTGUARD *psmartguard);

SGAS SgasGetSmartguard(SMARTGUARD *psmartguard);

void HandleSmartguardMessage(SMARTGUARD *psmartguard, MSGID msgid, void *pv);

void FreezeSmartguard(SMARTGUARD *psmartguard, int fFreeze);

#endif // SMARTGUARD_H
