#pragma once
#include "framework/Actor.h"
#include "gameplay/HealthComponent.h"

namespace LightYear
{
	class Spaceship : public Actor
	{
	public:
		Spaceship(World* world, const std::string& texturePath = "");
		virtual void Tick(float deltaTime) override;
		void SetVelocity(const sf::Vector2f& velocity);
		sf::Vector2f GetVelocity() const { return m_velocity; }
		virtual void Shoot();
		virtual void BeginPlay() override;

	private:
		void OnHealthChanged(float amount, float health, float maxHealth);

	private: 
		sf::Vector2f m_velocity;
		HealthComponent m_healthComponent;
	};
}