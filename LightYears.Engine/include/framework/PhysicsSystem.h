#pragma once
#include "framework/Core.h"
#include "framework/IStep.h"
#include "framework/PhysicsContactListener.h"

#include <box2d/b2_world.h>
#include <box2d/b2_body.h>

namespace LightYear
{
	class Actor;

	class PhysicsSystem : public IStep
	{
	public:
		static PhysicsSystem& Get();
		virtual void Step(float deltaTime);
		b2Body* AddListener(Actor* listener);
		void RemoveListener(b2Body* listener);
		float GetPhysicsScale() const { return m_physicsScale; }
		static void CleanUp();

	protected:
		PhysicsSystem();
		b2PolygonShape CreateShape(Actor* listener);
		b2FixtureDef CreateFixtureDefinition(b2PolygonShape& shape);
		float ConvertToPhysicsUnits(float value);
		b2BodyDef CreateBodyDefinition(Actor* listener);

	private:
		void DestroyPendingListeners();

	private:
		static Unique<PhysicsSystem> m_physicsSystem;
		b2World m_physicsWorld;
		float m_physicsScale;
		int m_velocityIteration;
		int m_positionIteration;
		PhysicsContactListener m_physicsContactListener;
		Set<b2Body*> m_pendingRemovalListeners;
	};
}