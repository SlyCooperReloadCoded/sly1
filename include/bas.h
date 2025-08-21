/**
 * @file bas.h
 *
 * @brief Binary Async Stream.
*/
#ifndef BAS_H
#define BAS_H

#include "common.h"
#include <util.h>

/**
 * @brief Binary Async Stream Kind
*/
enum BASK
{
    BASK_Nil = -1,
    BASK_Cd = 1,
    BASK_Host = 0,
    BASK_Max = 2
};

/**
 * @brief Binary Async Stream.
 */
class CBinaryAsyncStream
{
public:
    BASK m_bask;
    int m_fd;
    uint32_t m_isector;
    int m_cbSpooling;
    byte* m_pbSpooling;
    byte* m_abSpool;
    int m_cb;
    byte* m_pb;
    int m_ibCur;
    int m_cbUnspooled;
    int m_cbFile;

    /**
     * @brief Constructs a new CBinaryAsyncStream.
     *
     * @param pvSpool Pointer to the spool
     */
    CBinaryAsyncStream(void* pvSpool);

    /**
     * @brief Destroys the CBinaryAsyncStream.
     */
    ~CBinaryAsyncStream();

    /**
     * @brief Closes the stream.
     */
    void Close();
};

#endif // BAS_H
