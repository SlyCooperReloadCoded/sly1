#include <dialog.h>
#include <asega.h>
#include <screen.h>
#include <wipe.h>
#include <sound.h>

void InitDialog(DIALOG *pdialog)
{
    InitAlo(pdialog);
    STRUCT_OFFSET(pdialog, 0x2c8, ulong) = STRUCT_OFFSET(pdialog, 0x2c8, ulong) | 0x100000000;
    STRUCT_OFFSET(pdialog, 0x300, OID) = OID_Nil;
    STRUCT_OFFSET(pdialog, 0x30c, OID) = OID_Nil;
}

void LoadDialogFromBrx(DIALOG *pdialog, CBinaryInputStream *pbis)
{
    LoadAloFromBrx(pdialog, pbis);
    // pdialog->cde & pdialog->ade
    LoadDialogEventsFromBrx(pdialog, pbis, &STRUCT_OFFSET(pdialog, 0x2dc, int), &STRUCT_OFFSET(pdialog, 0x2e0, DE *));
}

INCLUDE_ASM("asm/nonmatchings/P2/dialog", LoadDialogEventsFromBrx__FP6DIALOGP18CBinaryInputStreamPiPP2DE);

INCLUDE_ASM("asm/nonmatchings/P2/dialog", PostDialogLoad__FP6DIALOG);

void SetDialogInstruct(DIALOG *pdialog)
{
    // pdialog->dialogk
    STRUCT_OFFSET(pdialog, 0x2d0, DIALOGK) = DIALOGK_Instruct;
}

void SetDialogConfront(DIALOG *pdialog)
{
    // pdialog->dialogk
    STRUCT_OFFSET(pdialog, 0x2d0, DIALOGK) = DIALOGK_Confront;
}

void GetDialogPlayed(DIALOG *pdialog, int *pfPlayed)
{
    // pdialog->pfPlayed
    *pfPlayed = *STRUCT_OFFSET(pdialog, 0x304, int *);
}

void SetDialogPlayed(DIALOG *pdialog, int fPlayed)
{
    // pdialog->pfPlayed
    *STRUCT_OFFSET(pdialog, 0x304, int *) = fPlayed;
}

INCLUDE_ASM("asm/nonmatchings/P2/dialog", SetDialogDialogs__FP6DIALOG7DIALOGS);

INCLUDE_ASM("asm/nonmatchings/P2/dialog", UpdateDialog__FP6DIALOGf);

INCLUDE_ASM("asm/nonmatchings/P2/dialog", HandleDialogEvent__FP6DIALOGP2DE);

void HandleDialogMessage(DIALOG *pdialog, MSGID msgid, void *pv)
{
    HandleAloMessage(pdialog, msgid, pv);
    // pdialog->dp
    if (msgid == MSGID_asega_retracted && (ASEGA *)pv == STRUCT_OFFSET(pdialog, 0x2e8, DP).pasegaLipsync)
    {
        STRUCT_OFFSET(pdialog, 0x2e8, DP).pasegaLipsync = NULL;
    }
}

INCLUDE_ASM("asm/nonmatchings/P2/dialog", FPauseDialog__FP6DIALOG);

INCLUDE_ASM("asm/nonmatchings/P2/dialog", FUN_001516c0);

INCLUDE_ASM("asm/nonmatchings/P2/dialog", HandleDialogEvents__FP6DIALOG);

INCLUDE_ASM("asm/nonmatchings/P2/dialog", FUN_00151860);

void TriggerDialog(DIALOG *pdialog)
{
    NOTE *pnote = &g_note;

    if (STRUCT_OFFSET(pnote, 0x260, int) >= 2)
        return;

    if (STRUCT_OFFSET(pnote, 0x26c, int) != 0)
        return;

    if (SetVagUnpaused())
        return;

    if (g_wipe.wipes == WIPES_WipingOut)
        return;

    if (pdialog == g_pdialogPlaying)
        return;

    DIALOGS dialogs = DIALOGS_Triggered;

    if (*STRUCT_OFFSET(pdialog, 0x304, int *) != 0) // pdialog->pfPlayed
    {
        if (STRUCT_OFFSET(pdialog, 0x2d0, DIALOGK) != DIALOGK_Confront) // pdialog->dialogk
        {
            dialogs = DIALOGS_UnableToCall;
        }
        else
        {
            dialogs = STRUCT_OFFSET(pdialog, 0x2d4, DIALOGS); // pdialog->dialogs
        }
    }
    else
    {
        int cpfEquivalence = STRUCT_OFFSET(pdialog, 0x310, int); // pdialog->cpfEquivalence

        if (cpfEquivalence > 0)
        {
            for (int i = 0; i < cpfEquivalence; i++)
            {
                if (*STRUCT_OFFSET_INDEX(pdialog, 0x314, int *, i) != 0)
                // pdialog->cpfEquivalenceArray[i]
                {
                    dialogs = DIALOGS_UnableToCall;
                    break;
                }
            }
        }
    }

    SetDialogDialogs(pdialog, dialogs);
}

void UntriggerDialog(DIALOG *pdialog)
{
    // pdialog->dialogs
    if (STRUCT_OFFSET(pdialog, 0x2d4, DIALOGS) != DIALOGS_Triggered && STRUCT_OFFSET(pdialog, 0x2d4, DIALOGS) != DIALOGS_Playing)
    {
        SetDialogDialogs(pdialog, DIALOGS_Enabled);
    }
}

