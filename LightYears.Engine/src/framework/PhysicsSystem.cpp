#include "framework/PhysicsSystem.h"
#include "framework/Core.h"
#include <framework/Actor.h>
#include "framework/MathUtility.h"

#include <box2D/b2_contact.h>
#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>

namespace LightYear
{
	Unique<PhysicsSystem> PhysicsSystem::m_physicsSystem{ nullptr };

	PhysicsSystem::PhysicsSystem() : 
		m_physicsWorld{ b2Vec2{ 0.f, 0.f } },
		m_physicsScale{ 0.01f },
		m_velocityIteration{ 8 },
		m_positionIteration{ 3 },
		m_physicsContactListener{},
		m_pendingRemovalListeners{}
	{
		m_physicsWorld.SetContactListener(&m_physicsContactListener);
		m_physicsWorld.SetAllowSleeping(false);
	}

	PhysicsSystem& PhysicsSystem::Get()
	{
		if (!m_physicsSystem)
			m_physicsSystem = std::move(Unique<PhysicsSystem>(new PhysicsSystem));

		return *m_physicsSystem;
	}

	void PhysicsSystem::Step(float deltaTime)
	{
		DestroyPendingListeners();
		m_physicsWorld.Step(deltaTime, m_velocityIteration, m_positionIteration);
	}

	b2Body* PhysicsSystem::AddListener(Actor* listener)
	{
		if (listener->IsPendingDestroyed())
			return nullptr;

		auto bodyDefinition = CreateBodyDefinition(listener);
		auto body = m_physicsWorld.CreateBody(&bodyDefinition);
		auto shape = CreateShape(listener);
		auto fixtureDefinition = CreateFixtureDefinition(shape);
		body->CreateFixture(&fixtureDefinition);

		return body;
	}

	b2BodyDef PhysicsSystem::CreateBodyDefinition(Actor* listener)
	{
		b2BodyDef bodyDef; 
		bodyDef.type = b2_dynamicBody;
		bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(listener);
		bodyDef.position.Set(
			ConvertToPhysicsUnits(listener->GetLocation().x),
			ConvertToPhysicsUnits(listener->GetLocation().y)
		);
		bodyDef.angle = DegreesToRadians(listener->GetRotation());

		return bodyDef;
	}

	void PhysicsSystem::DestroyPendingListeners()
	{
		for (auto listener : m_pendingRemovalListeners)
		{
			m_physicsWorld.DestroyBody(listener);
		}

		m_pendingRemovalListeners.clear();
	}

	b2PolygonShape PhysicsSystem::CreateShape(Actor* listener)
	{
		auto divisor = 2.f;
		b2PolygonShape shape;
		auto listenerBounds = listener->GetGlobalBounds();
		shape.SetAsBox(
			ConvertToPhysicsUnits(listenerBounds.width / divisor),
			ConvertToPhysicsUnits(listenerBounds.height / divisor)
		);
		return shape;
	}

	float PhysicsSystem::ConvertToPhysicsUnits(float value)
	{
		return value * GetPhysicsScale();
	}

	b2FixtureDef PhysicsSystem::CreateFixtureDefinition(b2PolygonShape& shape)
	{
		b2FixtureDef fixtureDefinition;
		fixtureDefinition.shape = &shape;
		fixtureDefinition.density = 1.0f;
		fixtureDefinition.friction = 0.3f;
		fixtureDefinition.isSensor = true;

		return fixtureDefinition;
	}

	void PhysicsSystem::RemoveListener(b2Body* listener)
	{
		m_pendingRemovalListeners.insert(listener);
	}

	void PhysicsSystem::CleanUp()
	{
		m_physicsSystem = std::move(Unique<PhysicsSystem>{new PhysicsSystem});
	}
}
 