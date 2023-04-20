/*
 *  Copyright (C) 2005-2021 Team Kodi (https://kodi.tv)
 *  Copyright (C) 2005 Joakim Eriksson <je@plane9.com>
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
 */

#pragma once

#include <kodi/gui/gl/Shader.h>

#include "column.h"

/***************************** D E F I N E S *******************************/
/****************************** M A C R O S ********************************/
/***************************** C L A S S E S *******************************/

////////////////////////////////////////////////////////////////////////////
//
typedef struct TRenderVertex
{
  CVector pos;
  float col[4];
  f32 u, v;
} TRenderVertex;

////////////////////////////////////////////////////////////////////////////
//
class ATTR_DLL_LOCAL CMatrixTrails : public kodi::gui::gl::CShaderProgram
{
public:
  CMatrixTrails(CConfig* config);
  ~CMatrixTrails();

  bool RestoreDevice(const std::string& path);
  void InvalidateDevice();
  void Update(f32 dt);
  bool Draw();

  // override functions for kodi::gui::gl::CShaderProgram
  void OnCompiledAndLinked() override;
  bool OnEnabled() override { return true; }
  
protected:
  int m_NumColumns;
  int m_NumRows;
  CColumn* m_Columns;
  CVector m_CharSize, m_CharSizeTex;

  GLuint m_Texture;

private:
  GLuint m_vao = -1;
  GLuint m_vertexVBO = -1;
 
  GLint m_aPosition = -1;
  GLint m_aColor = -1;
  GLint m_aCoord = -1;

  CConfig* m_config;
};

/***************************** I N L I N E S *******************************/
