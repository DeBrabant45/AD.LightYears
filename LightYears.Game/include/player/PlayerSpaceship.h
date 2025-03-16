#pragma once
#include "spaceships/Spaceship.h"

namespace LightYear 
{
	class BulletShooter;

	class PlayerSpaceship : public Spaceship
	{
	public:
		PlayerSpaceship(World* world, const std::string& path = "SpaceShooterRedux/PNG/playerShip1_blue.png");
		virtual void Tick(float deltaTime) override;
		void SetSpeed(float speed) { m_speed = speed; }
		float GetSpeed() { return m_speed; }
		virtual void Shoot() override;

	private:
		void HandleInput();
		void ConsumeInput(float deltaTime);
		void NormalizeInput();
		void ClampBoundaries();
		bool IsBoundariesMet(float value, float clampSize, float input);

	private:
		sf::Vector2f m_moveInput;
		float m_speed;
		Unique<BulletShooter> m_bulletShooter;
	};
}