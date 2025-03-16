#pragma once

#include <SFML/Graphics.hpp>
#include "framework/Core.h"
#include "framework/ITick.h"
#include "framework/ICleanCycle.h"
#include "framework/CycleClock.h"

namespace LightYear 
{
	class World;

	class Application : public ITick, public ICleanCycle
	{
	public:
		Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, sf::Uint32 style);
		void Run();
		template<typename WorldType>
		Weak<WorldType> LoadWorld();
		sf::Vector2u GetWindowSize() const;
		void Tick(float deltaTime) override;

	protected:
		virtual void Render();
		virtual void ExecuteInternalTick(float deltaTime) override;

	private:
		void RenderInternal();
		void CleanCycle();

	private:
		sf::RenderWindow m_window;
		sf::Clock m_tickClock;
		float m_targetFrameRate;
		Shared<World> m_world;
		CycleClock m_cycleClock;
	};

	template<typename WorldType>
	inline Weak<WorldType> Application::LoadWorld()
	{
		Shared<WorldType> world{ new WorldType{ this } };
		m_world = world;
		m_world->BeginPlay();

		return world;
	}
}