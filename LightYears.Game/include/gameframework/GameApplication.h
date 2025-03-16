#pragma once	

#include <framework/Application.h>
#include <framework/Core.h>

namespace LightYear 
{
	class Actor;
	class Spaceship;
	class PlayerSpaceship;

	class GameApplication : public Application
	{
	public:
		GameApplication();

	protected:
		virtual void ExecuteInternalTick(float deltaTime) override;

	private:
		float m_counter;
		Weak<PlayerSpaceship> m_testPlayer;
	};
}