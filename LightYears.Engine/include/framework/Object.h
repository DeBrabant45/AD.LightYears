#pragma once
#include "framework/Core.h"
#include "framework/Delegate.h"

#include <memory>

namespace LightYear
{
	class Object : public std::enable_shared_from_this<Object>
	{
	public:
		Object();
		virtual ~Object();
		virtual void Destroy();
		bool IsPendingDestroyed() const { return m_isPendingDestroyed; }
		Weak<Object> GetWeakReference();
		Weak<const Object> GetWeakReference() const;
		Delegate<Object*> OnDestroy;

	private:
		bool m_isPendingDestroyed;
	};
}