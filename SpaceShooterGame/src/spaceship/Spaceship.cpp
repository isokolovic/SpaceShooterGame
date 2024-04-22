#include "spaceship/Spaceship.h"
#include <functional>

namespace ss {

	Spaceship::Spaceship(World* owningWorld, const std::string& texturePath)
		: Actor{ owningWorld, texturePath },
		mVelocity{},
		mHealthComponent{ 100.f, 100.f }
	{
	}

	void Spaceship::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		AddActorLocationOffset(GetVelocity() * deltaTime);
	}

	void Spaceship::SetVelocity(const sf::Vector2f& newVelocity)
	{
		mVelocity = newVelocity;
	}

	void Spaceship::Shoot()
	{
	}

	void Spaceship::BeginPlay()
	{
		Actor::BeginPlay();
		SetEnablePhysics(true);

		mHealthComponent.onHealthChanged.BindAction(GetWeakRef(), &Spaceship::OnHealthChanged);
	}

	void Spaceship::OnHealthChanged(float amt, float health, float maxHealth)
	{

	}
}