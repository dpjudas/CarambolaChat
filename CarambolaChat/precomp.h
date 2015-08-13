
#pragma once

#include <ClanLib/core.h>
#include <ClanLib/application.h>
#include <ClanLib/display.h>
#ifdef WIN32
#include <ClanLib/d3d.h>
#else
#include <ClanLib/gl.h>
#endif
#include <ClanLib/ui.h>
#include <ClanLib/sound.h>
#include <ClanLib/network.h>
#include <algorithm>

#pragma warning(disable: 4267) // warning C4267: 'argument' : conversion from 'size_t' to 'int', possible loss of data
