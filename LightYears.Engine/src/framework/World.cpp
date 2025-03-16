#include "framework/World.h"
#include "framework/Core.h"
#include "framework/Actor.h"
#include "framework/Application.h"

namespace LightYear 
{
	World::World(Application* application) :
		m_application{ application },
		m_beginPlay{ false },
		m_actors{},
		m_pendingActors{}
	{

	}

	World::~World()
	{

	}

	void World::BeginPlay()
	{
		if (m_beginPlay)
			return;

		m_beginPlay = true;
		ExecuteInternalBeginPlay();
	}

	void World::ExecuteInternalBeginPlay()
	{
		LOG("Begin play");
	}

	void World::Tick(float deltaTime)
	{
		AddPendingActors();
		TickActors(deltaTime);
		ExecuteInternalTick(deltaTime);
	}

	void World::AddPendingActors()
	{
		if (m_pendingActors.empty())
			return;

		for (auto pendingActor : m_pendingActors)
		{
			m_actors.push_back(pendingActor);
			pendingActor->BeginPlay();
		}
		m_pendingActors.clear();
	}

	void World::TickActors(float deltaTime)
	{
		for (auto actor = m_actors.begin(); actor != m_actors.end();)
		{
			actor->get()->Tick(deltaTime);
			++actor;
		}
	}

	void World::ExecuteInternalTick(float deltaTime)
	{
		//LOG("Ticking at framerate: %f", 1.f / deltaTime);
	}

	void World::Render(sf::RenderWindow& window)
	{
		for (auto& actor : m_actors)
		{
			actor->Render(window);
		}
	}

	sf::Vector2u World::GetWindowSize() const
	{
		return m_application->GetWindowSize();
	}

	void World::CleanCycle()
	{
		for (auto actor = m_actors.begin(); actor != m_actors.end();)
		{
			if (actor->get()->IsPendingDestroyed())
			{
				actor = m_actors.erase(actor);
				continue;
			}

			++actor;
		}
	}
}