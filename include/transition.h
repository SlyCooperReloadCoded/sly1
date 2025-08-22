/**
 * @file transition.h
 *
 * @brief Level transitions.
 */
#ifndef TRANSITION_H
#define TRANSITION_H

#include "common.h"
#include <oid.h>
#include <cat.h>
#include <game.h>

class CTransition;
extern CTransition g_transition;

/**
 * @brief Level Table Struct
 *
 * Holds data about the level file.
 *
 * @note Name is not official.
*/
struct LevelTableStruct
{
    CFileLocation fileLocation; /* Ciphers for lsn and size */
    uint search_val;
    uint for_lsn;
    uint search_cipher; /* Cipher for search val */
    uint for_size;
    uint level_id; /* Level ID */
    uint level_name;  /* Pointer to level name string */
    FLS tasks;         /* Tasks to complete (visited, key, vault, mts) */
};

/**
 * @brief Transition flags.
 */
enum FTRANS
{
    FTRANS_None = 0,
    FTRANS_Checkpoint = 1,
    FTRANS_RetryWorld = 2,
    FTRANS_ClearGame = 4,
    FTRANS_SameWorld = 8,
    FTRANS_ShowLives = 16
};

/**
 * @brief Transition flags integer type.
 */
typedef int GRFTRANS;

/**
 * @brief Transition data
 *
 * Responsible for holding data bout a level transition.
 */
struct TRANS
{
    uint fSet;
    LevelTableStruct *pchzWorld; // Current file thats loading struct
    OID oidWarp;                        // Checkpoint Warps
    OID oidWarpContet;
    GRFTRANS grftrans; // Lost all lives flags
};

/**
 * @brief Transition
 */
class CTransition
{
public:
    int m_fPending;    // Basically like a level pending flag.
    char *m_pchzWorld; // This is the ptr to enc level sector offset and size in memory
    OID m_oidWarp;     // Which checkpoint you spawn at when you start a level
    OID m_oidWarpContext;

    GRFTRANS grftrans;       // Flags that affect level loading, one of them checks if you lost all lives when you die.
    char m_achzWorldCur[64]; // File description contents.

    /**
     * @brief Constructor.
     */
    CTransition();

    /**
     * @brief Sets the conditions on the level if you died or loading a level.
     */
    void Set(char *pchzWorld, OID oidWarp, OID oidWarpContext, GRFTRANS grftrans);

    /**
     * @brief  Executes the conditions from CTransition::Set by setting some engine vaules to default and loading the level file.
     */
    void Execute();
};

/**
 * @brief Reloads the current level. The value of FTRANS affects the load.
 *
 * @param ftrans Transition flags.
 */
void ResetWorld(FTRANS ftrans);

#endif // TRANSITION_H
