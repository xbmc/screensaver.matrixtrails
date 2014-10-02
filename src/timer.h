////////////////////////////////////////////////////////////////////////////
//
// Author:
//   Joakim Eriksson
//
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "types.h"
#include <sys/time.h>

/***************************** D E F I N E S *******************************/
/****************************** M A C R O S ********************************/
/************************** S T R U C T U R E S ****************************/

////////////////////////////////////////////////////////////////////////////
//
class CTimer
{
public:

				CTimer();
	void		Init(void);
	void		Update(void);
	f32			GetDeltaTime(void);

protected:
	double m_OldCount;
	f32				m_DeltaTime;

        static double WallTime ()
        {
          timeval tmpTime;
          gettimeofday(&tmpTime,NULL);
          return tmpTime.tv_sec + tmpTime.tv_usec/1.0e6;
        }
};

/***************************** G L O B A L S *******************************/
/***************************** I N L I N E S *******************************/

////////////////////////////////////////////////////////////////////////////
//
inline CTimer::CTimer()
{
	m_DeltaTime		= 0.0f;
}

////////////////////////////////////////////////////////////////////////////
//
inline void	CTimer::Init(void)
{
  m_OldCount = WallTime();
}

////////////////////////////////////////////////////////////////////////////
//
inline void	CTimer::Update(void)
{
  m_DeltaTime = WallTime()-m_OldCount;
  m_OldCount = WallTime();
}

////////////////////////////////////////////////////////////////////////////
//
inline f32		CTimer::GetDeltaTime(void)
{
	return m_DeltaTime;
}
