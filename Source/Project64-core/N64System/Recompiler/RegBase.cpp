/****************************************************************************
*                                                                           *
* Project64 - A Nintendo 64 emulator.                                      *
* http://www.pj64-emu.com/                                                  *
* Copyright (C) 2012 Project64. All rights reserved.                        *
*                                                                           *
* License:                                                                  *
* GNU/GPLv2 http://www.gnu.org/licenses/gpl-2.0.html                        *
*                                                                           *
****************************************************************************/
#include "stdafx.h"
#include <Project64-core/N64System/Recompiler/RegBase.h>

CRegBase::CRegBase() :
m_CycleCount(0),
m_Fpu_Used(false)
{
    for (int32_t i = 0; i < 32; i++)
    {
        m_MIPS_RegState[i] = STATE_UNKNOWN;
        m_MIPS_RegVal[i].DW = 0;
    }
    m_MIPS_RegState[0] = STATE_CONST_32_SIGN;
}

bool CRegBase::operator==(const CRegBase& right) const
{
    for (uint32_t count = 0; count < 32; count++)
    {
        if (m_MIPS_RegState[count] != right.m_MIPS_RegState[count])
        {
            return false;
        }
        if (m_MIPS_RegState[count] == STATE_UNKNOWN)
        {
            continue;
        }
        if (m_MIPS_RegVal[count].DW != right.m_MIPS_RegVal[count].DW)
        {
            return false;
        }
    }
    if (m_CycleCount != right.m_CycleCount) { return false; }
    if (m_Fpu_Used != right.m_Fpu_Used) { return false; }
    return true;
}

bool CRegBase::operator!=(const CRegBase& right) const
{
    return !(right == *this);
}

CRegBase& CRegBase::operator=(const CRegBase& right)
{
    memcpy(&m_MIPS_RegState, &right.m_MIPS_RegState, sizeof(m_MIPS_RegState));
    memcpy(&m_MIPS_RegVal, &right.m_MIPS_RegVal, sizeof(m_MIPS_RegVal));
    m_CycleCount = right.m_CycleCount;
    m_Fpu_Used = right.m_Fpu_Used;
#ifdef _DEBUG
    if (*this != right)
    {
        g_Notify->BreakPoint(__FILE__, __LINE__);
    }
#endif
    return *this;
}