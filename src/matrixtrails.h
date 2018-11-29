////////////////////////////////////////////////////////////////////////////
//
// Author:
//   Joakim Eriksson
//
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "shaders/GUIShader.h"
#include "column.h"
#include "Texture.h"

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
class ATTRIBUTE_HIDDEN CMatrixTrails
{
public:
  CMatrixTrails(CConfig* config);
  ~CMatrixTrails();
  bool RestoreDevice(const std::string& path);
  void InvalidateDevice();
  void Update(f32 dt);
  bool Draw();

protected:
  int m_NumColumns;
  int m_NumRows;
  CColumn* m_Columns;
  CVector m_CharSize, m_CharSizeTex;

  GLuint m_Texture;

private:
  CGUIShader* m_shader = nullptr;
  unsigned int m_vertexVBO = -1;
  unsigned int m_vertexVAO = -1;
  unsigned int m_indexVBO = -1;
  CConfig* m_config;
};

/***************************** I N L I N E S *******************************/
