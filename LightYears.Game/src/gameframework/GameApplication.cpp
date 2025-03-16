#include "gameframework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "framework/AssetManager.h"
#include "spaceships/Spaceship.h"
#include "player/PlayerSpaceship.h"
#include "config.h"

LightYear::Application* GetApplication()
{
	return new LightYear::GameApplication{};
}

namespace LightYear 
{
	GameApplication::GameApplication() 
		: Application{ 600, 900, "Light Years", sf::Style::Titlebar | sf::Style::Close }
	{
		AssetManager::Get().SetRootDirectory(GetResourceDirectory());
		auto world = LoadWorld<World>();
		//auto actorOne = world.lock()->SpawnActor<Actor>();
		m_testPlayer = world.lock()->SpawnActor<PlayerSpaceship>();
		//m_testPlayer.lock()->SetTexture("SpaceShooterRedux/PNG/playerShip1_blue.png");
		m_testPlayer.lock()->SetLocation(sf::Vector2f(300.f, 490.f));
		m_testPlayer.lock()->SetRotation(0);
		//m_testPlayer.lock()->SetVelocity(sf::Vector2f(0.f, -200.f));
		m_counter = 0;
		Weak<Spaceship> testSpaceship = world.lock()->SpawnActor<Spaceship>();
		testSpaceship.lock()->SetTexture("SpaceShooterRedux/PNG/playerShip1_blue.png");
		testSpaceship.lock()->SetLocation(sf::Vector2f{ 100.f, 50.f });
	}

	void GameApplication::ExecuteInternalTick(float deltaTime)
	{
		m_counter += deltaTime;

		if (m_counter > 10.f)
		{
			if (!m_testPlayer.expired())
			{
				m_testPlayer.lock()->Destroy();
			}
		}
		//m_counter += deltaTime;
		//if (m_counter < 2.f)
		//	return;

		//if (m_actorToDestroy.expired())
		//	return;

		//m_actorToDestroy.lock()->Destroy();
	}
}