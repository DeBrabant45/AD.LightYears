#pragma once

#include <string>

std::string GetResourceDirectory()
{
#ifdef NDEBUG // release build
	return "assets/";
#else
	return "C:/AaronsProjects/LightYears/LightYears.Game/assets/";
#endif
}
