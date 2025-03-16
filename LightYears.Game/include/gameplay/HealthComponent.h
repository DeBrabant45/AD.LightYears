#pragma once
#include "framework/Delegate.h"

namespace LightYear
{
	class HealthComponent
	{
	public:
		HealthComponent(float initialAmount, float maxAmount);
		void UpdateAmount(float amount);
		float GetAmount() const { return m_currentAmount; }
		float GetMaxAmount() const { return m_maxAmount; }
		Delegate<float, float, float> OnChanged;

	private:
		void RemoveAmount(float amount);
		void RegenAmount(float amount);
		void EmptyAmount();
		void ClampAmount();

	private:
		float m_currentAmount;
		float m_maxAmount;
	};
}