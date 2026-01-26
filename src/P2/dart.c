#include <dart.h>
#include <emitter.h>
#include <jt.h>

extern SNIP s_asnipDart[];

void InitDart(DART *pdart)
{
    InitSo(pdart);
    SetDartDarts(pdart, DARTS_Nil);
}

INCLUDE_ASM("asm/nonmatchings/P2/dart", OnDartAdd__FP4DART);

void RemoveDart(DART *pdart)
{
    RemoveLo(pdart);
    AppendDlEntry(&pdart->psw->dlDartFree, pdart);
    SetDartDarts(pdart, DARTS_AvailToFire);
}

void CloneDart(DART *pdart, DART *pdartBase)
{
    DLE dleDartFree = STRUCT_OFFSET(pdart, 0x56c, DLE); // pdart->dleDartFree
    CloneSo(pdart, pdartBase);
    STRUCT_OFFSET(pdart, 0x56c, DLE) = dleDartFree; // pdart->dleDartFree
}

void LoadDartFromBrx(DART *pdart, CBinaryInputStream *pbis)
{
    LoadSoFromBrx(pdart, pbis);
    InferExpl(&STRUCT_OFFSET(pdart, 0x58c, EXPL *), pdart); // pdart->pexpl
}

void HandleDartMessage(DART *pdart, MSGID msgid, void *pv)
{
    HandleAloMessage(pdart, msgid, pv);
    // pdart->pasegaSticking
    if (msgid == MSGID_asega_retracted && (ASEGA *)pv == STRUCT_OFFSET(pdart, 0x578, ASEGA *))
    {
        STRUCT_OFFSET(pdart, 0x578, ASEGA *) = NULL;
        SetDartDarts(pdart, DARTS_Stuck);
    }
}

void PostDartLoad(DART *pdart)
{
    PostAloLoad(pdart);
    SnipAloObjects(pdart, 1, s_asnipDart);
}

void UpdateDart(DART *pdart, float dt)
{
    UpdateSo(pdart, dt);

    switch (STRUCT_OFFSET(pdart, 0x550, DARTS))
    {
        case DARTS_AvailToFire:
        case DARTS_ReadyToFire:
        case DARTS_Sticking:
        case DARTS_Fading:
        default:
        {
            break;
        }
        case DARTS_Airborne:
        {
            UpdateDartAirborne(pdart, dt);
            break;
        }
        case DARTS_Stuck:
        {
            // pdart->dtMaxStuck, pdart->tDarts, g_pjt->phbsk
            if (STRUCT_OFFSET(pdart, 0x568, float) < g_clock.t - STRUCT_OFFSET(pdart, 0x554, float) &&
               (!g_pjt || (HBSK *)pdart->paloParent != STRUCT_OFFSET(g_pjt, 0x23b0, HBSK *)))
            {
                SetDartDarts(pdart, DARTS_Fading);
            }
            break;
        }
    }
}

void SetDartDarts(DART *pdart, DARTS darts)
{
    // pdart->darts
    if (STRUCT_OFFSET(pdart, 0x550, DARTS) == darts)
    {
        return;
    }

    if (STRUCT_OFFSET(pdart, 0x550, DARTS) == DARTS_Airborne)
    {
        STRUCT_OFFSET(pdart, 0x57c, ALO *) = NULL; // pdart->paloTarget
        STRUCT_OFFSET(pdart, 0x580, float) = 0.0f; // pdart->dtLaunchToTarget
        STRUCT_OFFSET(pdart, 0x584, float) = 0.0f; // pdart->dzTarget
        STRUCT_OFFSET(pdart, 0x588, DARTGUN *) = NULL; // pdart->pdartgunFiredFrom
    }

    STRUCT_OFFSET(pdart, 0x550, DARTS) = darts; // pdart->darts
    STRUCT_OFFSET(pdart, 0x554, float) = g_clock.t; // pdart->tDarts

    if (darts == DARTS_Fading)
    {
        FadeAloOut(pdart, STRUCT_OFFSET(pdart, 0x564, float)); // pdart->dtFade
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/dart", ApplyDartThrow__FP4DARTP2PO);

INCLUDE_ASM("asm/nonmatchings/P2/dart", UpdateDartAirborne__FP4DARTf);
