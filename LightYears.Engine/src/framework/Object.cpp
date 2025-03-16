#include "framework/Object.h"
#include "framework/Core.h"

namespace LightYear 
{
	Object::Object() :
		m_isPendingDestroyed{ false }
	{

	}

	Object::~Object()
	{
		LOG("Object Destroyed");
	}

	void Object::Destroy()
	{
		OnDestroy.Broadcast(this);
		m_isPendingDestroyed = true;
	}

	Weak<Object> Object::GetWeakReference()
	{
		return weak_from_this();
	}

	Weak<const Object> Object::GetWeakReference() const
	{
		return weak_from_this();
	}
}