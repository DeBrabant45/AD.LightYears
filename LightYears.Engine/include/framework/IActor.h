#pragma once
#include "framework/ITick.h"
#include "framework/IPlay.h"
#include "framework/IRender.h"

namespace LightYear
{
	class IActor : public ITick, public IPlay, public IRender
	{

	};
}