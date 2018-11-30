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

#include <string.h>
#include <vector>

enum EMATRIXMODE
{
  MM_PROJECTION = 0,
  MM_MODELVIEW,
  MM_TEXTURE,
  MM_MATRIXSIZE  // Must be last! used for size of matrices
};

class CMatrix
{
public:
  CMatrix();
  virtual ~CMatrix();

  GLfloat* GetMatrix(EMATRIXMODE mode);

  void MatrixMode(EMATRIXMODE mode);
  void PushMatrix();
  void PopMatrix();
  void LoadIdentity();
  void Ortho(GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
  void Ortho2D(GLfloat l, GLfloat r, GLfloat b, GLfloat t);
  void Frustum(GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
  void Translatef(GLfloat x, GLfloat y, GLfloat z);
  void Scalef(GLfloat x, GLfloat y, GLfloat z);
  void Rotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
  void MultMatrixf(const GLfloat *matrix);
  void LookAt(GLfloat eyex, GLfloat eyey, GLfloat eyez, GLfloat centerx, GLfloat centery, GLfloat centerz, GLfloat upx, GLfloat upy, GLfloat upz);
  bool Project(GLfloat objx, GLfloat objy, GLfloat objz, const GLfloat modelMatrix[16], const GLfloat projMatrix[16], const GLint viewport[4], GLfloat* winx, GLfloat* winy, GLfloat* winz);

protected:

  struct MatrixWrapper
  {
    MatrixWrapper(){};
    MatrixWrapper( const float values[16]) { memcpy(m_values,values,sizeof(m_values)); }
    MatrixWrapper( const MatrixWrapper &rhs ) { memcpy(m_values, rhs.m_values, sizeof(m_values)); }
    MatrixWrapper &operator=( const MatrixWrapper &rhs ) { memcpy(m_values, rhs.m_values, sizeof(m_values)); return *this;}
    operator float*() { return m_values; }
    operator const float*() const { return m_values; }

    float m_values[16];
  };

  std::vector<struct MatrixWrapper> m_matrices[(int)MM_MATRIXSIZE];
  GLfloat *m_pMatrix;
  EMATRIXMODE m_matrixMode;
};
