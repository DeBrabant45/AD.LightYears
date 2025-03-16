#include "player/PlayerSpaceship.h"
#include "SFML/System.hpp"
#include "framework/MathUtility.h"
#include "weapons/BulletShooter.h"

namespace LightYear
{
	PlayerSpaceship::PlayerSpaceship(World* world, const std::string& path)
		: Spaceship{ world, path },
		m_moveInput { },
		m_speed { 200.f },
		m_bulletShooter{ new BulletShooter{this, 0.3f} }
	{

	}

	void PlayerSpaceship::Tick(float deltaTime)
	{
		Spaceship::Tick(deltaTime);
		HandleInput();
		ConsumeInput(deltaTime);
	}

	void PlayerSpaceship::Shoot()
	{
		if (m_bulletShooter)
		{
			m_bulletShooter->Shoot();
		}
	}

	void PlayerSpaceship::HandleInput()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			m_moveInput.y = -1.f;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			m_moveInput.y = 1.f;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			m_moveInput.x = -1.f;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			m_moveInput.x = 1.f;
		}
		ClampBoundaries();
		NormalizeInput();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			Shoot();
		}
	}

	void PlayerSpaceship::ClampBoundaries()
	{
		auto location = GetLocation();
		auto windowSize = GetWindowSize();

		if (IsBoundariesMet(location.x, windowSize.x, m_moveInput.x))
		{
			m_moveInput.x = 0.f;
		}

		if (IsBoundariesMet(location.y, windowSize.y, m_moveInput.y))
		{
			m_moveInput.y = 0.f;
		}
	}

	bool PlayerSpaceship::IsBoundariesMet(float position, float boundary, float input)
	{
		return (position < 0 && input < 0) || (position > boundary && input > 0);
	}

	void PlayerSpaceship::NormalizeInput()
	{
		Normalize(m_moveInput);
	}

	void PlayerSpaceship::ConsumeInput(float deltaTime)
	{
		auto velocity = m_moveInput * m_speed;
		SetVelocity(velocity);
		m_moveInput.x = m_moveInput.y = 0.f;
	}
}