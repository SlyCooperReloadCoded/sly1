#include <tv.h>
#include <clock.h>

INCLUDE_ASM("asm/nonmatchings/P2/tv", InitTv__FP2TV5BLOTK);

INCLUDE_ASM("asm/nonmatchings/P2/tv", PostTvLoad__FP2TV);

void GetTvItvbMinMax(TV *ptv, int *pitvbDrawMin, int *pitvbDrawMax)
{
    // ptv->uUnwind
    int max = (int)(STRUCT_OFFSET(ptv, 0xc70, float) * 57.0f);
    *pitvbDrawMin = (0x39 - max) / 2;
    *pitvbDrawMax = *pitvbDrawMin + max;
}

INCLUDE_ASM("asm/nonmatchings/P2/tv", DrawTvArea__FP2TVR4GIFSi);

INCLUDE_ASM("asm/nonmatchings/P2/tv", DrawTvBands__FP2TVR4GIFS);

INCLUDE_ASM("asm/nonmatchings/P2/tv", DrawTvOutline__FP2TVR4GIFS);

INCLUDE_ASM("asm/nonmatchings/P2/tv", DrawTv__FP2TV);

void SetTvTvs(TV *ptv, TVS tvs)
{
    // ptv->tvs
    if (tvs == STRUCT_OFFSET(ptv, 0x260, TVS))
    {
        return;
    }

    STRUCT_OFFSET(ptv, 0x260, TVS) = tvs; // ptv->tvs
    STRUCT_OFFSET(ptv, 0x264, float) = g_clock.tReal; // ptv->tTvs
}

INCLUDE_ASM("asm/nonmatchings/P2/tv", AcceptTvSpeaker__FP2TV);

INCLUDE_ASM("asm/nonmatchings/P2/tv", SetTvTvgs__FP2TV4TVGS);

INCLUDE_ASM("asm/nonmatchings/P2/tv", SetTvBlots__FP2TV5BLOTS);

INCLUDE_ASM("asm/nonmatchings/P2/tv", UpdateTv__FP2TV);

INCLUDE_ASM("asm/nonmatchings/P2/tv", RenderTv__FP2TV);

INCLUDE_ASM("asm/nonmatchings/P2/tv", PreTvContext__FP3RPL);

INCLUDE_ASM("asm/nonmatchings/P2/tv", PostTvContext__FP3RPL);

INCLUDE_ASM("asm/nonmatchings/P2/tv", SetTvSpeaker__FP2TVP7SPEAKER);

INCLUDE_ASM("asm/nonmatchings/P2/tv", SetTvReplace__FP2TVP3ALO);

INCLUDE_ASM("asm/nonmatchings/P2/tv", OnTvReset__FP2TV);

INCLUDE_ASM("asm/nonmatchings/P2/tv", tv__static_initialization_and_destruction_0);

INCLUDE_ASM("asm/nonmatchings/P2/tv", _GLOBAL_$I$RGBA_Distortion);
