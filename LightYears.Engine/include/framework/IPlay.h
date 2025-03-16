#pragma once 

namespace LightYear
{
	class IPlay 
	{
	public:
		virtual void BeginPlay() = 0;

	protected:
		virtual void ExecuteInternalBeginPlay() = 0;
	};
}