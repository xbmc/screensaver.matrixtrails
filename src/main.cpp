/*
 *  Copyright (C) 2005-2020 Team Kodi (https://kodi.tv)
 *  Copyright (C) 2005 Joakim Eriksson <je@plane9.com>
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSE.md for more information.
 */

#include "main.h"
#include "matrixtrails.h"
#include "timer.h"

#include <kodi/addon-instance/Screensaver.h>
#include <kodi/gui/gl/GL.h>

#include <time.h>
#include <string.h>

#define TEXTURESIZE 256  // Width & height of the texture we are using

class ATTRIBUTE_HIDDEN CScreensaverMatrixTrails
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
  m_config.SetDefaults();
  m_config.m_NumColumns = kodi::GetSettingInt("columns");
  m_config.m_NumRows = kodi::GetSettingInt("rows");
  m_config.m_CharCol.r = float(kodi::GetSettingInt("rain-red")) / 100.0f;
  m_config.m_CharCol.g = float(kodi::GetSettingInt("rain-green")) / 100.0f;
  m_config.m_CharCol.b = float(kodi::GetSettingInt("rain-blue")) / 100.0f;
  m_config.m_CharEventCol.r = float(kodi::GetSettingInt("event-red")) / 100.0f;
  m_config.m_CharEventCol.g = float(kodi::GetSettingInt("event-green")) / 100.0f;
  m_config.m_CharEventCol.b = float(kodi::GetSettingInt("event-blue")) / 100.0f;
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
  m_timer->SetSpeed(static_cast<f32>(kodi::GetSettingInt("speed")));
  std::string path = kodi::GetAddonPath() + "/resources/MatrixTrails.tga";
  if (!m_matrixTrails->RestoreDevice(path))
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
  m_matrixTrails->InvalidateDevice();
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
  m_matrixTrails->Draw();
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
//
void CConfig::SetDefaults()
{
  m_CharDelayMin = 0.030f;
  m_CharDelayMax = 0.120f;
  m_FadeSpeedMin = 0.25f;
  m_FadeSpeedMax = 0.70f;
  m_NumColumns = 200;
  m_NumRows = 40;
  m_CharCol.Set(0.0f, 1.0f, 0.0f, 1.0f);
  m_CharEventCol.Set(0.8f, 1.0f, 0.9f, 1.0f);

  m_NumChars = 32;
  m_CharSizeTex.x = 32.0f/TEXTURESIZE;
  m_CharSizeTex.y = 26.0f/TEXTURESIZE;
}

ADDONCREATOR(CScreensaverMatrixTrails);
