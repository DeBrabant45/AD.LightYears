#include "gameplay/HealthComponent.h"
#include "framework/Core.h"

namespace LightYear
{
	HealthComponent::HealthComponent(float initialAmount, float maxAmount) :
		m_currentAmount{ initialAmount },
		m_maxAmount{ maxAmount }
	{

	}

	void HealthComponent::UpdateAmount(float amount)
	{
		if (amount == 0 || m_currentAmount == 0)
			return;

		m_currentAmount += amount;

		ClampAmount();

		if (amount < 0)
		{
			RemoveAmount(-amount);
			if (m_currentAmount <= 0)
				EmptyAmount();
		}
		else
		{
			RegenAmount(amount);
		}
	}

	void HealthComponent::RemoveAmount(float amount)
	{
		// should handle the logic for remove amount
		LOG("Removed amount: %f, current amount is: %f/%f", amount, m_currentAmount, m_maxAmount);
	}

	void HealthComponent::RegenAmount(float amount)
	{
		// Should handle it's own logic for regen
		LOG("Health regen amount: %f, current amount is: %f/%f", amount, m_currentAmount, m_maxAmount);
	}

	void HealthComponent::EmptyAmount()
	{
		// Should handle the Empty amount on it's own
		LOG("Amount is Empty");
	}

	void HealthComponent::ClampAmount()
	{
		if (m_currentAmount < 0)
			m_currentAmount = 0;

		if (m_currentAmount > m_maxAmount)
			m_currentAmount = m_maxAmount;
	}
}