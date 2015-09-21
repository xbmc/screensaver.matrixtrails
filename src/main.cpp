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

#include "xbmc_scr_dll.h"
#include "libXBMC_addon.h"
#include <GL/gl.h>
#include "main.h"
#include "matrixtrails.h"
#include "timer.h"
#include <time.h>
#include <iostream>

CMatrixTrails*	gMatrixTrails = null;
CRenderD3D		gRender;
CTimer*			gTimer = null;
CConfig			gConfig;

ADDON::CHelper_libXBMC_addon *XBMC           = NULL;

#include <string.h>

#define TEXTURESIZE		256				// Width & height of the texture we are using

////////////////////////////////////////////////////////////////////////////
// XBMC has loaded us into memory, we should set our core values
// here and load any settings we may have from our config file
//
ADDON_STATUS ADDON_Create(void* hdl, void* props)
{
  if (!props)
    return ADDON_STATUS_UNKNOWN;

  if (!XBMC)
    XBMC = new ADDON::CHelper_libXBMC_addon;

  if (!XBMC->RegisterMe(hdl))
  {
    delete XBMC, XBMC=NULL;
    return ADDON_STATUS_PERMANENT_FAILURE;
  }

  SCR_PROPS* scrprops = (SCR_PROPS*)props;

  gConfig.SetDefaults();
  gRender.m_Width = scrprops->width;
  gRender.m_Height = scrprops->height;

  return ADDON_STATUS_OK;
}

////////////////////////////////////////////////////////////////////////////
// XBMC tells us we should get ready to start rendering. This function
// is called once when the screensaver is activated by XBMC.
//
extern "C" void Start()
{
	srand((u32)time(null));
	gMatrixTrails = new CMatrixTrails();
	if (!gMatrixTrails)
		return;
	gTimer = new CTimer();
	gTimer->Init();
        char path[1024];
        XBMC->GetSetting("__addonpath__", path);
        std::string p2(path);
        p2 += "/resources/MatrixTrails.tga";

	if (!gMatrixTrails->RestoreDevice(&gRender, p2.c_str()))
		ADDON_Stop();
}

////////////////////////////////////////////////////////////////////////////
// XBMC tells us to render a frame of our screensaver. This is called on
// each frame render in XBMC, you should render a single frame only - the DX
// device will already have been cleared.
//
extern "C" void Render()
{
	if (!gMatrixTrails)
		return;
	gTimer->Update();
	gMatrixTrails->Update(gTimer->GetDeltaTime());
	gMatrixTrails->Draw(&gRender);
}

////////////////////////////////////////////////////////////////////////////
// XBMC tells us to stop the screensaver we should free any memory and release
// any resources we have created.
//
extern "C" void ADDON_Stop()
{
	if (!gMatrixTrails)
		return;
	gMatrixTrails->InvalidateDevice(&gRender);
	SAFE_DELETE(gMatrixTrails);
	SAFE_DELETE(gTimer);
}

void ADDON_Destroy()
{
}

ADDON_STATUS ADDON_GetStatus()
{
  return ADDON_STATUS_OK;
}

bool ADDON_HasSettings()
{
  return false;
}

unsigned int ADDON_GetSettings(ADDON_StructSetting ***sSet)
{
  return 0;
}

ADDON_STATUS ADDON_SetSetting(const char *strSetting, const void *value)
{
  if (strcmp(strSetting, "columns") == 0)
    gConfig.m_NumColumns = *(int*)value;
  if (strcmp(strSetting, "rows") == 0)
    gConfig.m_NumColumns = *(int*)value;
  if (strcmp(strSetting, "chars") == 0)
    gConfig.m_NumChars = *(int*)value;
  if (strcmp(strSetting,"charsizex") == 0)
     gConfig.m_CharSizeTex.x = (*(float*)value)/TEXTURESIZE;
  if (strcmp(strSetting,"charsizey") == 0)
     gConfig.m_CharSizeTex.y = (*(float*)value)/TEXTURESIZE;

  return ADDON_STATUS_OK;
}

void ADDON_FreeSettings()
{
}

void ADDON_Announce(const char *flag, const char *sender, const char *message, const void *data)
{
}

void GetInfo(SCR_INFO *info)
{
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
//
void	CConfig::SetDefaults()
{
	m_CharDelayMin	= 0.015f;
	m_CharDelayMax	= 0.060f;
	m_FadeSpeedMin	= 1.0f;
	m_FadeSpeedMax	= 1.5f;
	m_NumColumns	= 200;
	m_NumRows		= 40;
	m_CharCol.Set(0.0f, 1.0f, 0.0f, 1.0f);

	m_NumChars		= 64;
	m_CharSizeTex.x = 32.0/TEXTURESIZE;
	m_CharSizeTex.y = 26.0f/TEXTURESIZE;
}
