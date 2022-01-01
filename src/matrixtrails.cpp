/*
 *  Copyright (C) 2005-2021 Team Kodi (https://kodi.tv)
 *  Copyright (C) 2005 Joakim Eriksson <je@plane9.com>
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
 */

#include "main.h"
#include "matrixtrails.h"
#include "SOIL2/SOIL2.h"

#include <stddef.h>
#include <vector>

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

  std::string fraqShader = kodi::addon::GetAddonPath("resources/shaders/" GL_TYPE_STRING "/frag.glsl");
  std::string vertShader = kodi::addon::GetAddonPath("resources/shaders/" GL_TYPE_STRING "/vert.glsl");
  if (!LoadShaderFiles(vertShader, fraqShader) || !CompileAndLink())
    return false;

  glGenBuffers(1, &m_vertexVBO);

  m_Texture = SOIL_load_OGL_texture(path.c_str(), SOIL_LOAD_RGB, 0, 0);

  return true;
}

////////////////////////////////////////////////////////////////////////////
//
void CMatrixTrails::InvalidateDevice()
{
  glDeleteBuffers(1, &m_vertexVBO);
  m_vertexVBO = 0;
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

  EnableShader();

  glBindBuffer(GL_ARRAY_BUFFER, m_vertexVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(TRenderVertex)*nVSize, &vert[0], GL_STATIC_DRAW);

  glBindTexture(GL_TEXTURE_2D, m_Texture);

  glVertexAttribPointer(m_aPosition, 3, GL_FLOAT, GL_FALSE, sizeof(TRenderVertex), BUFFER_OFFSET(offsetof(TRenderVertex, pos)));
  glEnableVertexAttribArray(m_aPosition);

  glVertexAttribPointer(m_aColor, 4, GL_FLOAT, GL_FALSE, sizeof(TRenderVertex), BUFFER_OFFSET(offsetof(TRenderVertex, col)));
  glEnableVertexAttribArray(m_aColor);

  glVertexAttribPointer(m_aCoord, 2, GL_FLOAT, GL_FALSE, sizeof(TRenderVertex), BUFFER_OFFSET(offsetof(TRenderVertex, u)));
  glEnableVertexAttribArray(m_aCoord);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glEnable(GL_BLEND);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, nVSize);

  glDisableVertexAttribArray(m_aPosition);
  glDisableVertexAttribArray(m_aColor);
  glDisableVertexAttribArray(m_aCoord);

  DisableShader();

  return true;
}

void CMatrixTrails::OnCompiledAndLinked()
{
  // Variables passed directly to the Vertex shader
  m_aPosition = glGetAttribLocation(ProgramHandle(), "a_pos");
  m_aColor = glGetAttribLocation(ProgramHandle(), "a_color");
  m_aCoord = glGetAttribLocation(ProgramHandle(), "a_coord");
}
