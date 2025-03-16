#pragma

#include "framework/Core.h"
#include <SFML/Graphics.hpp>
#include "framework/ITick.h"
#include "framework/IPlay.h"
#include "framework/ICleanCycle.h"

namespace LightYear
{
	class Application;
	class Actor;

	class World : public ITick, public IPlay, public ICleanCycle
	{
	public:
		World(Application* application);
		virtual ~World();
		void BeginPlay() override;
		void Tick(float deltaTime) override;
		template<typename ActorType, typename... Args>
		Weak<ActorType> SpawnActor(Args... args);
		void Render(sf::RenderWindow& window);
		sf::Vector2u GetWindowSize() const;
		void CleanCycle();

	protected:
		virtual void ExecuteInternalBeginPlay() override;
		virtual void ExecuteInternalTick(float deltaTime) override;

	private:
		void TickActors(float deltaTime);
		void AddPendingActors();

	private:
		Application* m_application;
		bool m_beginPlay;
		List<Shared<Actor>> m_actors;
		List<Shared<Actor>> m_pendingActors;
	};

	template<typename ActorType, typename... Args>
	inline Weak<ActorType> World::SpawnActor(Args... args)
	{
		Shared<ActorType> actor{ new ActorType(this, args...) };
		m_pendingActors.push_back(actor);

		return actor;
	}
}