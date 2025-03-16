#include "framework/Actor.h"
#include "framework/Core.h"
#include "framework/AssetManager.h"
#include "framework/MathUtility.h"
#include "framework/World.h"
#include "framework/PhysicsSystem.h"

namespace LightYear
{
	Actor::Actor(World* world, const std::string& texturePath) :
		m_world{ world },
		m_hasBeganPlay{ false },
		m_sprite{},
		m_texture{},
		m_physicsBody{ nullptr },
		m_isPhysicsEnabled{ false }
	{
		SetTexture(texturePath);
	}

	Actor::~Actor()
	{
		LOG("Actor destroyed");
	}

	void Actor::SetTexture(const std::string& texturePath)
	{
		m_texture = AssetManager::Get().LoadTexture(texturePath);
		if (!m_texture)
			return;

		m_sprite.setTexture(*m_texture);
		int textureWidth = m_texture->getSize().x;
		int textureHeight = m_texture->getSize().y;
		m_sprite.setTextureRect(sf::IntRect{ sf::Vector2i{ }, sf::Vector2i{ textureWidth, textureHeight } });
		CenterPivot();
	}

	void Actor::SetLocation(const sf::Vector2f& location)
	{
		m_sprite.setPosition(location);
		UpdatePhysicsBodyTransform();
	}

	void Actor::SetRotation(float rotation)
	{
		m_sprite.setRotation(rotation);
		UpdatePhysicsBodyTransform();
	}

	void Actor::AddLocationOffset(const sf::Vector2f& offset)
	{
		SetLocation(GetLocation() + offset);
	}

	sf::Vector2f Actor::GetLocation() const
	{
		return m_sprite.getPosition();
	}

	void Actor::AddRotationOffset(float offset)
	{
		SetRotation(GetRotation() + offset);
	}

	float Actor::GetRotation() const
	{
		return m_sprite.getRotation();
	}

	void Actor::BeginPlay()
	{
		if (m_hasBeganPlay)
			return;

		m_hasBeganPlay = true;
		ExecuteInternalBeginPlay();
	}

	void Actor::ExecuteInternalBeginPlay()
	{

	}

	void Actor::Tick(float deltaTime)
	{
		if (IsPendingDestroyed())
			return;

		ExecuteInternalTick(deltaTime);
	}

	void Actor::ExecuteInternalTick(float delaTime)
	{

	}

	void Actor::Render(sf::RenderWindow& window)
	{
		if (IsPendingDestroyed())
			return;

		window.draw(m_sprite);
	}

	sf::Vector2f Actor::GetForwardDirection() const
	{
		return RotationToVector(GetRotation() + -90.f);
	}

	sf::Vector2f Actor::GetRightDirection() const
	{
		return RotationToVector(GetRotation());
	}

	sf::Vector2u Actor::GetWindowSize() const
	{
		return m_world->GetWindowSize();
	}

	bool Actor::IsOutOfBounds() const
	{
		auto windowWidth = GetWorld()->GetWindowSize().x;
		auto windowHeight = GetWorld()->GetWindowSize().y;
		auto width = GetGlobalBounds().width;
		auto height = GetGlobalBounds().height;
		auto actorposition = GetLocation();
		return ((actorposition.x < -width)
			|| (actorposition.x > windowWidth + width)
			|| (actorposition.y < -height)
			|| (actorposition.y > windowHeight + height)) ? true : false;
	}

	sf::FloatRect Actor::GetGlobalBounds() const
	{
		return m_sprite.getGlobalBounds();
	}

	void Actor::CenterPivot()
	{
		auto bound = m_sprite.getGlobalBounds();
		m_sprite.setOrigin(bound.width / 2.f, bound.height / 2.f);
	}

	void Actor::SetPhysics(bool isEnabled)
	{
		m_isPhysicsEnabled = isEnabled;
		if (m_isPhysicsEnabled)
		{
			EnablePhysics();
			return;
		}

		DisablePhysics();
	}

	void Actor::OnBeginOverlap(Actor* other)
	{
		LOG("Begin overlap");
	}

	void Actor::OnEndOverlap(Actor* other)
	{
		LOG("End overlap");
	}

	void Actor::Destroy()
	{
		DisablePhysics();
		Object::Destroy();
	}

	void Actor::EnablePhysics()
	{
		if (m_physicsBody)
			return;

		m_physicsBody = PhysicsSystem::Get().AddListener(this);
	}

	void Actor::DisablePhysics()
	{
		if (!m_physicsBody)
			return;

		PhysicsSystem::Get().RemoveListener(m_physicsBody);
		m_physicsBody = nullptr;
	}

	void Actor::UpdatePhysicsBodyTransform()
	{
		if (!m_physicsBody)
			return;

		auto physicsScale = PhysicsSystem::Get().GetPhysicsScale();
		b2Vec2 position{ GetLocation().x * physicsScale, GetLocation().y * physicsScale };
		auto rotation = DegreesToRadians(GetRotation());

		m_physicsBody->SetTransform(position, rotation);
	}
}