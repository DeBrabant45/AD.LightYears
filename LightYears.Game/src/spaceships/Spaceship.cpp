#include "spaceships/Spaceship.h"

namespace LightYear
{
	Spaceship::Spaceship(World* world, const std::string& texturePath) 
		:Actor(world, texturePath),
		m_healthComponent{ 100.f, 100.f}
	{

	}

	void Spaceship::BeginPlay()
	{
		Actor::BeginPlay();

		SetPhysics(true);
		m_healthComponent.OnChanged.BindAction(GetWeakReference(), &Spaceship::OnHealthChanged);
		m_healthComponent.OnChanged.Broadcast(11, 89, 100);
	}

	void Spaceship::OnHealthChanged(float amount, float health, float maxHealth)
	{
		LOG("Health changed by: %f, and is now: %f/%f", amount, health, maxHealth);
	}

	void Spaceship::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		auto offset = GetVelocity() * deltaTime;
		AddLocationOffset(offset);
	}

	void Spaceship::SetVelocity(const sf::Vector2f& velocity)
	{
		m_velocity = velocity;
	}

	void Spaceship::Shoot()
	{

	}
}