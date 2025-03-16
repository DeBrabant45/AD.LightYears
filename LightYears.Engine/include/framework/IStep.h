#pragma once

namespace LightYear
{
	class IStep
	{
	public:
		virtual void Step(float deltaTime) = 0;
	};
}