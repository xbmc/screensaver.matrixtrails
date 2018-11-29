////////////////////////////////////////////////////////////////////////////
//
// Matrix Trails Screensaver for XBox Media Center
// Copyright (c) 2005 Joakim Eriksson <je@plane9.com>
//
////////////////////////////////////////////////////////////////////////////
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
////////////////////////////////////////////////////////////////////////////

#include "main.h"
#include "matrixtrails.h"
#include "SOIL2/SOIL2.h"

#include <vector>
#include <iostream>

////////////////////////////////////////////////////////////////////////////
//
CMatrixTrails::CMatrixTrails(CConfig* config)
  : m_config(config)
{
  m_NumColumns = m_config->m_NumColumns;
  m_NumRows = m_config->m_NumRows;

  m_Columns = new CColumn[m_NumColumns];
  for (int cNr=0; cNr<m_NumColumns; cNr++)
  {
    m_Columns[cNr].Init(m_config, m_NumRows);
  }
}

////////////////////////////////////////////////////////////////////////////
//
CMatrixTrails::~CMatrixTrails()
{
  SAFE_DELETE_ARRAY(m_Columns);
}

////////////////////////////////////////////////////////////////////////////
//
bool CMatrixTrails::RestoreDevice(CRenderD3D* render, const char* path)
{
  int numQuads = m_NumRows*m_NumColumns;

  int channels;

  m_CharSize.x = (f32)render->m_Width  / (f32)m_NumColumns;
  m_CharSize.y = (f32)render->m_Height / (f32)m_NumRows;
  m_CharSize.z = 0.0f;

  m_Texture = SOIL_load_OGL_texture(path, SOIL_LOAD_RGB, 0, 0);

  return true;
}

////////////////////////////////////////////////////////////////////////////
//
void CMatrixTrails::InvalidateDevice(CRenderD3D* render)
{
}

////////////////////////////////////////////////////////////////////////////
//
void CMatrixTrails::Update(f32 dt)
{
  for (int cNr=0; cNr<m_NumColumns; cNr++)
  {
    m_Columns[cNr].Update(dt);
  }
}

////////////////////////////////////////////////////////////////////////////
//
bool CMatrixTrails::Draw(CRenderD3D* render)
{
  // Fill in the vertex buffers with the quads
  std::vector<TRenderVertex> vert(m_NumRows*m_NumColumns*4);

  f32 posX = 0, posY = 0;
  TRenderVertex* vert2=&vert[0];
  for (int cNr=0; cNr<m_NumColumns; cNr++)
  {
    vert2 = m_Columns[cNr].UpdateVertexBuffer(vert2, posX, posY, m_CharSize, m_config->m_CharSizeTex);
    posX += m_CharSize.x;
  }

  glEnable(GL_BLEND);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, m_Texture);

  int index = 0;
  glBegin(GL_TRIANGLE_STRIP);
  for (int rNr=0; rNr<m_NumRows; rNr++)
  {
    for (int cNr=0; cNr<m_NumColumns*4; cNr++, index++)
    {
      glColor4f(vert[index].col[0], vert[index].col[1],
                vert[index].col[2], vert[index].col[3]);
      glTexCoord2f(vert[index].u, vert[index].v);
      glVertex2f(vert[index].pos.x, vert[index].pos.y);
    }
  }
  glEnd();

  return true;
}
