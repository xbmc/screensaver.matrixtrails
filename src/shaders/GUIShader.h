/*
 *  Copyright (C) 2005-2018 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Kodi; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#pragma once

#include "Shader.h"
#include "Matrix.h"

class ATTRIBUTE_HIDDEN CGUIShader : public CShaderProgram, public CMatrix
{
public:
  CGUIShader(std::string vert, std::string frag);

  void OnCompiledAndLinked() override;
  bool OnEnabled() override;
  void Free();

  GLint GetPosLoc() { return m_hPos; }
  GLint GetColLoc() { return m_hCol; }
  GLint GetTexCoord() { return m_hTexCoord; }

protected:
  GLint m_hTex = -1;
  GLint m_hProj = -1;
  GLint m_hModel = -1;
  GLint m_hPos = -1;
  GLint m_hCol = -1;
  GLint m_hTexCoord = -1;

  GLfloat *m_proj = nullptr;
  GLfloat *m_model = nullptr;
};
