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

#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

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
bool CMatrixTrails::RestoreDevice(const std::string& path)
{
  m_CharSize.x = 2.0 / (f32)m_NumColumns;
  m_CharSize.y = 2.0 / (f32)m_NumRows;
  m_CharSize.z = 0.0f;

  m_shader = new CGUIShader("vert.glsl", "frag.glsl");
  if (!m_shader->CompileAndLink())
  {
    delete m_shader;
    m_shader = nullptr;
    return false;
  }

  glGenBuffers(1, &m_vertexVBO);
  glGenBuffers(1, &m_indexVBO);

  m_Texture = SOIL_load_OGL_texture(path.c_str(), SOIL_LOAD_RGB, 0, 0);

  return true;
}

////////////////////////////////////////////////////////////////////////////
//
void CMatrixTrails::InvalidateDevice()
{
  glDeleteBuffers(1, &m_vertexVBO);
  m_vertexVBO = 0;
  glDeleteBuffers(1, &m_indexVBO);
  m_indexVBO = 0;

  delete(m_shader);
  m_shader = nullptr;
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
bool CMatrixTrails::Draw()
{
  // Fill in the vertex buffers with the quads
  size_t nVSize = m_NumRows * m_NumColumns * 4;
  std::vector<TRenderVertex> vert(nVSize);

  f32 posX = -1.0, posY = 1.0;
  TRenderVertex* vert2=&vert[0];
  for (int cNr=0; cNr<m_NumColumns; cNr++)
  {
    vert2 = m_Columns[cNr].UpdateVertexBuffer(vert2, posX, posY, m_CharSize, m_config->m_CharSizeTex);
    posX += m_CharSize.x;
  }

  GLint posLoc = m_shader->GetPosLoc();
  GLint colLoc = m_shader->GetColLoc();
  GLint texCoord = m_shader->GetTexCoord();

  m_shader->PushMatrix();
  m_shader->Enable();

  glBindBuffer(GL_ARRAY_BUFFER, m_vertexVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(TRenderVertex)*nVSize, &vert[0], GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindTexture(GL_TEXTURE_2D, m_Texture);

  glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, sizeof(TRenderVertex), BUFFER_OFFSET(offsetof(TRenderVertex, pos)));
  glEnableVertexAttribArray(posLoc);

  glVertexAttribPointer(colLoc, 4, GL_FLOAT, GL_FALSE, sizeof(TRenderVertex), BUFFER_OFFSET(offsetof(TRenderVertex, col)));
  glEnableVertexAttribArray(colLoc);

  glVertexAttribPointer(texCoord, 2, GL_FLOAT, GL_FALSE, sizeof(TRenderVertex), BUFFER_OFFSET(offsetof(TRenderVertex, u)));
  glEnableVertexAttribArray(texCoord);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glEnable(GL_BLEND);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, nVSize);

  glDisableVertexAttribArray(posLoc);
  glDisableVertexAttribArray(colLoc);
  glDisableVertexAttribArray(texCoord);

  m_shader->Disable();
  m_shader->PopMatrix();

  return true;
}
