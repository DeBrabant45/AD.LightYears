#include "framework/Application.h"
#include "framework/Core.h"
#include "framework/World.h"
#include "framework/AssetManager.h"
#include "framework/PhysicsSystem.h"

namespace LightYear 
{
	Application::Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, sf::Uint32 style) : 
		m_window{ sf::VideoMode(windowWidth, windowHeight), title, style },
		m_tickClock{ },
		m_targetFrameRate{ 60.f },
		m_world{ nullptr },
		m_cycleClock{ 0.3f }
	{

	}

	void Application::Run()
	{
		m_tickClock.restart();
		auto accumulatedTime = 0.f;
		auto targetDeltaTime = 1.f / m_targetFrameRate;
		while (m_window.isOpen())
		{
			sf::Event windowEvent;
			while (m_window.pollEvent(windowEvent))
			{
				if (windowEvent.type != sf::Event::EventType::Closed)
					continue;

				m_window.close();
			}

			accumulatedTime += m_tickClock.restart().asSeconds();
			while (accumulatedTime > targetDeltaTime)
			{
				accumulatedTime -= targetDeltaTime;
				Tick(targetDeltaTime);
				Render();
			}
		}
	}

	sf::Vector2u Application::GetWindowSize() const
	{
		return m_window.getSize();
	}

	void Application::Tick(float deltaTime)
	{
		ExecuteInternalTick(deltaTime);

		if (!m_world)
			return;

		m_world->Tick(deltaTime);
		PhysicsSystem::Get().Step(deltaTime);
		CleanCycle();
	}

	void Application::ExecuteInternalTick(float deltaTime)
	{

	}

	void Application::CleanCycle()
	{
		if (!m_cycleClock.HasElapsed())
			return;

		m_cycleClock.Reset();
		AssetManager::Get().CleanCycle();
		m_world->CleanCycle();
	}

	void Application::Render()
	{
		m_window.clear();
		RenderInternal();
		m_window.display();
	}

	void Application::RenderInternal()
	{
		if (!m_world)
			return;

		m_world->Render(m_window);
	}
}