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

#ifdef HAS_GL
  // always define GL_GLEXT_PROTOTYPES before include gl headers
  #if !defined(GL_GLEXT_PROTOTYPES)
    #define GL_GLEXT_PROTOTYPES
  #endif
  #if defined(TARGET_LINUX)
    #include <GL/gl.h>
    #include <GL/glext.h>
  #elif defined(TARGET_FREEBSD)
    #include <GL/gl.h>
  #elif defined(TARGET_DARWIN)
    #include <OpenGL/gl3.h>
    #include <OpenGL/gl3ext.h>
  #endif
#elif HAS_GLES >= 2
  #if defined(TARGET_DARWIN)
    #include <OpenGLES/ES2/gl.h>
    #include <OpenGLES/ES2/glext.h>
  #else
    #include <GLES2/gl2.h>
    #include <GLES2/gl2ext.h>
  #endif
  #if HAS_GLES == 3
    #include <GLES3/gl3.h>
  #endif
#endif

#include <vector>
#include <string>

#include "kodi/AddonBase.h"

//////////////////////////////////////////////////////////////////////
// CShader - base class
//////////////////////////////////////////////////////////////////////
class ATTRIBUTE_HIDDEN CShader
{
public:
  CShader() = default;
  virtual ~CShader() = default;
  virtual bool Compile() = 0;
  virtual void Free() = 0;
  virtual GLuint Handle() = 0;

  bool LoadSource(std::string &file);
  bool OK() { return m_compiled; }

protected:
  std::string m_source;
  std::string m_lastLog;
  std::vector<std::string> m_attr;
  bool m_compiled = false;
};


//////////////////////////////////////////////////////////////////////
// CVertexShader
//////////////////////////////////////////////////////////////////////
class ATTRIBUTE_HIDDEN CVertexShader : public CShader
{
public:
  CVertexShader() = default;
  ~CVertexShader() override { Free(); }
  void Free() override;
  bool Compile() override;
  GLuint Handle() override { return m_vertexShader; }

protected:
  GLuint m_vertexShader = 0;
};

//////////////////////////////////////////////////////////////////////
// CPixelShader
//////////////////////////////////////////////////////////////////////
class ATTRIBUTE_HIDDEN CPixelShader : public CShader
{
public:
  CPixelShader() = default;
  ~CPixelShader() { Free(); }
  void Free() override;
  bool Compile() override;
  GLuint Handle() override { return m_pixelShader; }

protected:
  GLuint m_pixelShader = 0;
};

//////////////////////////////////////////////////////////////////////
// CShaderProgram
//////////////////////////////////////////////////////////////////////
class ATTRIBUTE_HIDDEN CShaderProgram
{
public:
  CShaderProgram(std::string &vert, std::string &frag);

  virtual ~CShaderProgram()
  {
    Free();
    delete m_pFP;
    delete m_pVP;
  }

  bool Enable();
  void Disable();
  bool OK() { return m_ok; }
  void Free();

  CVertexShader* VertexShader() { return m_pVP; }
  CPixelShader* PixelShader() { return m_pFP; }
  bool CompileAndLink();

  virtual void OnCompiledAndLinked() {};
  virtual bool OnEnabled() { return false; };
  virtual void OnDisabled() {};

  GLuint ProgramHandle() { return m_shaderProgram; }

protected:
  CVertexShader* m_pVP = nullptr;
  CPixelShader* m_pFP = nullptr;
  GLuint m_shaderProgram = 0;
  bool m_ok = false;
  bool m_validated = false;
};
