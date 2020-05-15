/*
 *  Copyright (C) 2005-2020 Team Kodi (https://kodi.tv)
 *  Copyright (C) 2005 Joakim Eriksson <je@plane9.com>
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
 */

#pragma once

#include "types.h"
#include <chrono>

/***************************** D E F I N E S *******************************/
/****************************** M A C R O S ********************************/
/************************** S T R U C T U R E S ****************************/

////////////////////////////////////////////////////////////////////////////
//
class CTimer
{
public:

  CTimer();
  void Init(void);
  void Update(void);
  f32 GetDeltaTime(void);
  void SetSpeed(f32 speed);

protected:
  double m_OldCount;
  f32 m_DeltaTime;
  f32 m_speed;
};

/***************************** G L O B A L S *******************************/
/***************************** I N L I N E S *******************************/

////////////////////////////////////////////////////////////////////////////
//
inline CTimer::CTimer()
{
  m_DeltaTime = 0.0f;
  m_speed = 1.0f;
}

////////////////////////////////////////////////////////////////////////////
//
inline void CTimer::Init(void)
{
  m_OldCount = std::chrono::duration<double>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

////////////////////////////////////////////////////////////////////////////
//
inline void CTimer::Update(void)
{
  double time = std::chrono::duration<double>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
  m_DeltaTime = (time - m_OldCount) * m_speed;
  m_OldCount = time;
}

////////////////////////////////////////////////////////////////////////////
//
inline f32 CTimer::GetDeltaTime(void)
{
  return m_DeltaTime;
}

////////////////////////////////////////////////////////////////////////////
//
void CTimer::SetSpeed(f32 speed)
{
  m_speed = speed;
}
