#include <aseg.h>
#include <blend.h>

INCLUDE_ASM("asm/nonmatchings/P2/blend", VerifyAeaEquivalence__FiP2EAiT1);

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
