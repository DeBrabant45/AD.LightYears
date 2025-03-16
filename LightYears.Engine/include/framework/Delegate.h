#pragma once
#include "framework/Core.h"

#include <functional>

namespace LightYear
{
	class Object;

	template<typename... Args>
	class Delegate
	{
	public:
		template<typename ClassName>
		void BindAction(Weak<Object> object, void(ClassName::* callback)(Args ...));
		void Broadcast(Args... args);

	private:
		List<std::function<bool(Args...)>> m_callBacks;
	};

	template<typename ...Args>
	template<typename ClassName>
	inline void Delegate<Args...>::BindAction(
		Weak<Object> object, 
		void(ClassName::* callback)(Args...))
	{
		auto callbackFunction = [object, callback](Args... args)->bool
			{
				if (!object.expired())
				{
					(static_cast<ClassName*>(object.lock().get())->*callback)(args...);
					return true;
				}

				return false;
			};

		m_callBacks.push_back(callbackFunction);
	}

	template<typename ...Args>
	inline void Delegate<Args...>::Broadcast(Args ...args)
	{
		for (auto iter = m_callBacks.begin(); iter != m_callBacks.end();)
		{
			if ((*iter)(args...))
			{
				++iter;
			}
			else
			{
				iter = m_callBacks.erase(iter);
			}
		}
	}
}