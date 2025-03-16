#pragma once
#include <box2d/b2_world.h>

namespace LightYear
{
	class Actor;

	class PhysicsContactListener : public b2ContactListener
	{
		Actor* GetActorFromContact(b2Fixture* fixture) const;
		virtual void BeginContact(b2Contact* contact) override;
		virtual void EndContact(b2Contact* contact) override;
	};
}