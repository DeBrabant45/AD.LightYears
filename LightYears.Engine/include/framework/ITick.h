#pragma once

namespace LightYear
{
	class ITick 
	{
	public:
		virtual void Tick(float deltaTime) = 0;

	protected:
		virtual void ExecuteInternalTick(float deltaTime) = 0;
	};
}