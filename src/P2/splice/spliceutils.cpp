#include <splice/spliceutils.h>
#include <splice/frame.h>
#include <splice/gc.h>
#include <splice/pair.h>
#include <splice/splotheap.h>
#include <splice/vecmat.h>

extern CGc g_gc;

// todo: match and fix blocked references
INCLUDE_ASM("asm/nonmatchings/P2/splice/spliceutils", StartupSplice__Fv);
#ifdef SKIP_ASM
void StartupSplice()
{
    g_gc.Startup();

    g_splotheapPair.Startup(0xc, 0x2000);
    g_splotheapPair.m_pfndelete = reinterpret_cast<PFNDELETE>(DeletePair);

    g_splotheapFrame.Startup(0x1c, 0x190);
    g_splotheapFrame.m_pfndelete = reinterpret_cast<PFNDELETE>(DeleteFrame);

    g_splotheapUnk1.Startup(0x10, 0x800);
    g_splotheapUnk1.m_pfndelete = reinterpret_cast<PFNDELETE>(0x11C4E8);

    g_splotheapProc.Startup(0x14, 0x800);
    StartupSpliceStructuredTypeFactories();

    g_splotheapMethod.Startup(0xc, 0x80);
}
#endif // SKIP_ASM

void ShutdownSplice()
{
    g_splotheapPair.Shutdown();
    g_splotheapFrame.Shutdown();
    g_splotheapUnk1.Shutdown();
    g_splotheapProc.Shutdown();
    ShutdownSpliceStructuredTypeFactories();
    g_splotheapMethod.Shutdown();
    g_gc.Shutdown();
}

INCLUDE_ASM("asm/nonmatchings/P2/splice/spliceutils", spliceutils__static_initialization_and_destruction_0);

INCLUDE_ASM("asm/nonmatchings/P2/splice/spliceutils", _GLOBAL_$I$g_splotheapPair);

INCLUDE_ASM("asm/nonmatchings/P2/splice/spliceutils", _GLOBAL_$D$g_splotheapPair);
