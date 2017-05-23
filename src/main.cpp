////////////////////////////////////////////////////////////////////////////
//
// Matrix Trails Screensaver for XBox Media Center
// Copyright (c) 2005 Joakim Eriksson <je@plane9.com>
//
// Thanks goes to Warren for his 'TestXBS' program!
// Matrix Symbol Font by Lexandr (mCode 1.5 - http://www.deviantart.com/deviation/2040700/)
//
// To run the screensaver copy over the MatrixTrails.xbs, MatrixTrails.tga
// and MatrixTrails.xml to the screensaver dir in xbmc
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
#include "timer.h"

#include <kodi/addon-instance/Screensaver.h>
#include <GL/gl.h>
#include <time.h>
#include <iostream>
#include <string.h>

#define TEXTURESIZE 256  // Width & height of the texture we are using

class CScreensaverMatrixTrails
  : public kodi::addon::CAddonBase,
    public kodi::addon::CInstanceScreensaver
{
public:
  CScreensaverMatrixTrails();

  virtual bool Start() override;
  virtual void Stop() override;
  virtual void Render() override;

private:
  CMatrixTrails* m_matrixTrails;
  CTimer* m_timer;
  CRenderD3D m_render;
  CConfig m_config;
};

////////////////////////////////////////////////////////////////////////////
// Kodi has loaded us into memory, we should set our core values
// here and load any settings we may have from our config file
//
CScreensaverMatrixTrails::CScreensaverMatrixTrails()
  : m_matrixTrails(nullptr),
    m_timer(nullptr)
{
  m_render.m_Width = Width();
  m_render.m_Height = Height();

  m_config.SetDefaults();
  m_config.m_NumColumns = kodi::GetSettingInt("columns");
  m_config.m_NumRows = kodi::GetSettingInt("rows");
}

////////////////////////////////////////////////////////////////////////////
// Kodi tells us we should get ready to start rendering. This function
// is called once when the screensaver is activated by Kodi.
//
bool CScreensaverMatrixTrails::Start()
{
  srand((u32)time(null));
  m_matrixTrails = new CMatrixTrails(&m_config);
  if (!m_matrixTrails)
    return false;
  m_timer = new CTimer();
  m_timer->Init();
  std::string path = kodi::GetAddonPath() + "/resources/MatrixTrails.tga";
  if (!m_matrixTrails->RestoreDevice(&m_render, path.c_str()))
  {
    Stop();
    return false;
  }
  return true;
}

////////////////////////////////////////////////////////////////////////////
// Kodi tells us to stop the screensaver we should free any memory and release
// any resources we have created.
//
void CScreensaverMatrixTrails::Stop()
{
  if (!m_matrixTrails)
    return;
  m_matrixTrails->InvalidateDevice(&m_render);
  SAFE_DELETE(m_matrixTrails);
  SAFE_DELETE(m_timer);
}

////////////////////////////////////////////////////////////////////////////
// Kodi tells us to render a frame of our screensaver. This is called on
// each frame render in Kodi, you should render a single frame only - the DX
// device will already have been cleared.
//
void CScreensaverMatrixTrails::Render()
{
  if (!m_matrixTrails)
    return;
  m_timer->Update();
  m_matrixTrails->Update(m_timer->GetDeltaTime());
  m_matrixTrails->Draw(&m_render);
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
//
void CConfig::SetDefaults()
{
  m_CharDelayMin = 0.015f;
  m_CharDelayMax = 0.060f;
  m_FadeSpeedMin = 1.0f;
  m_FadeSpeedMax = 1.5f;
  m_NumColumns = 200;
  m_NumRows = 40;
  m_CharCol.Set(0.0f, 1.0f, 0.0f, 1.0f);

  m_NumChars = 32;
  m_CharSizeTex.x = 32.0/TEXTURESIZE;
  m_CharSizeTex.y = 26.0f/TEXTURESIZE;
}

ADDONCREATOR(CScreensaverMatrixTrails);
