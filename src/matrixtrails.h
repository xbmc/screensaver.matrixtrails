////////////////////////////////////////////////////////////////////////////
//
// Author:
//   Joakim Eriksson
//
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "column.h"
#include "Texture.h"

/***************************** D E F I N E S *******************************/
/****************************** M A C R O S ********************************/
/***************************** C L A S S E S *******************************/

////////////////////////////////////////////////////////////////////////////
//
typedef	struct	TRenderVertex
{
	CVector		pos;
	f32			w;
	float col[4];
	f32			u, v;
} TRenderVertex;

////////////////////////////////////////////////////////////////////////////
//
class CMatrixTrails
{
public:
					CMatrixTrails();
					~CMatrixTrails();
	bool			RestoreDevice(CRenderD3D* render, const char* path);
	void			InvalidateDevice(CRenderD3D* render);
	void			Update(f32 dt);
	bool			Draw(CRenderD3D* render);

protected:
	int				m_NumColumns;
	int				m_NumRows;
	CColumn*		m_Columns;
	CVector			m_CharSize, m_CharSizeTex;

        GLuint m_Texture;
};

/***************************** I N L I N E S *******************************/
