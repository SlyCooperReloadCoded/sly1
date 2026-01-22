#include <aseg.h>
#include <blend.h>

// 96% Match
INCLUDE_ASM("asm/nonmatchings/P2/blend", VerifyAeaEquivalence__FiP2EAiT1);
#ifdef SKIP_ASM
void VerifyAeaEquivalence(int cea0, EA *aea0, int cea1, EA *aea1)
{
    int fLess = (cea0 < cea1);
    int ceaMin = cea0;

    if (cea0 >= cea1)
    {
        ceaMin = cea1;
    }

    int i;

    if (0 < ceaMin)
    {
        if (fLess)
        {
            i = cea0;
        }
        else
        {
            i = cea1;
        }

        do
        {
            i--;
        } while (i != 0);
    }
}
#endif

INCLUDE_ASM("asm/nonmatchings/P2/blend", EnsureAsegBlendDynamic__FP3ALOiiPviPiT5PP6ASEGBL);

INCLUDE_ASM("asm/nonmatchings/P2/blend", FillBlAmrsg__FiiPviiP3OID);

INCLUDE_ASM("asm/nonmatchings/P2/blend", CalculateBlendAmrsg__FiiPviiP4MRSGPf);

INCLUDE_ASM("asm/nonmatchings/P2/blend", ImrsgLookUp__FffiP4MRSGPf);

JUNK_ADDIU(90);

INCLUDE_ASM("asm/nonmatchings/P2/blend", ReblendAsegbl__FP6ASEGBLiiPv);

void SetAsegblSlerp(ASEGBL *pasegbl, ALO *palo)
{
    CHN *pchn = PchnFindAseg(pasegbl, palo);
    if (!pchn)
        return;
    if (!STRUCT_OFFSET(pchn, 0x8, void *))
        return;
    STRUCT_OFFSET(STRUCT_OFFSET(pchn, 0x8, void *), 0x18, int) = 1;
}
