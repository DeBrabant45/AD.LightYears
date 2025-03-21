#pragma once

namespace LightYear
{
	class Actor;

	class Shooter
	{
	public:
		void Shoot();
		virtual bool CanShoot() const { return true; }
		virtual bool IsOnCooldown() const { return false; }
		Actor* GetOwner() const { return m_owner; }

	protected:
		Shooter(Actor* owner);

	private:
		virtual void ShootAction() = 0;
		Actor* m_owner;
	};
}