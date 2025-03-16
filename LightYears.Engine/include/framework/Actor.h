#pragma once

#include "framework/Object.h"
#include "framework/Core.h"
#include <SFML/Graphics.hpp>
#include "framework/IActor.h"

class b2Body;

namespace LightYear
{
	class World;

	class Actor : public Object, public IActor
	{
	public:
		Actor(World* world, const std::string& texturePath = "");
		virtual ~Actor();
		virtual void BeginPlay() override;
		void Tick(float deltaTime) override;
		virtual void Render(sf::RenderWindow& window) override;
		void SetTexture(const std::string& texturePath);
		void SetLocation(const sf::Vector2f& location);
		void AddLocationOffset(const sf::Vector2f& offset);
		sf::Vector2f GetLocation() const;
		void SetRotation(float rotation);
		void AddRotationOffset(float offset);
		float GetRotation() const;
		sf::Vector2f GetForwardDirection() const;
		sf::Vector2f GetRightDirection() const;
		sf::Vector2u GetWindowSize() const;
		sf::FloatRect GetGlobalBounds() const;
		World* GetWorld() const { return m_world; }
		bool IsOutOfBounds() const;
		void SetPhysics(bool isEnabled);
		void OnBeginOverlap(Actor* other);
		void OnEndOverlap(Actor* other);
		virtual void Destroy() override;

	protected:
		virtual void ExecuteInternalTick(float deltaTime) override;
		virtual void ExecuteInternalBeginPlay() override;

	private:
		void CenterPivot();
		void EnablePhysics();
		void DisablePhysics();
		void UpdatePhysicsBodyTransform();

	private:
		World* m_world;
		bool m_hasBeganPlay;
		sf::Sprite m_sprite;
		Shared<sf::Texture> m_texture;
		b2Body* m_physicsBody;
		bool m_isPhysicsEnabled;
	};
}