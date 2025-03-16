#include "framework/PhysicsContactListener.h"
#include "framework/Actor.h"

#include <box2D/b2_contact.h>

namespace LightYear
{
	Actor* PhysicsContactListener::GetActorFromContact(b2Fixture* fixture) const
	{
		if (!fixture || !fixture->GetBody())
			return nullptr;

		return reinterpret_cast<Actor*>(fixture->GetBody()->GetUserData().pointer);
	}

	void PhysicsContactListener::BeginContact(b2Contact* contact)
	{
		Actor* actorA = GetActorFromContact(contact->GetFixtureA());
		Actor* actorB = GetActorFromContact(contact->GetFixtureB());

		if (actorA && !actorA->IsPendingDestroyed())
			actorA->OnBeginOverlap(actorB);

		if (actorB && !actorB->IsPendingDestroyed())
			actorB->OnBeginOverlap(actorA);
	}

	void PhysicsContactListener::EndContact(b2Contact* contact)
	{
		Actor* actorA = GetActorFromContact(contact->GetFixtureA());
		Actor* actorB = GetActorFromContact(contact->GetFixtureB());

		if (actorA && !actorA->IsPendingDestroyed())
			actorA->OnEndOverlap(actorB);

		if (actorB && !actorB->IsPendingDestroyed())
			actorB->OnEndOverlap(actorA);
	}
}