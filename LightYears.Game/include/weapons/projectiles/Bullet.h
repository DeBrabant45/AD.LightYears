#pragma once

#include "framework/Actor.h"

namespace LightYear
{
	class Bullet : public Actor
	{
	public:
		Bullet(World* world, Actor* owner, const std::string& texturePath, float speed = 600.f, float damage = 10.f);
		virtual void BeginPlay() override;
		void SetSpeed(float speed);
		void SetDamage(float damage);
		virtual void Tick(float deltaTime) override;

	private:
		void Move(float deltaTime);

	private:
		Actor* m_owner;
		float m_speed;
		float m_damage;
	};
}