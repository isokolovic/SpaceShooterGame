#pragma once
#include <SFML/Graphics.hpp>
#include "framework/Core.h"
#include "framework/Delegate.h"
#include "framework/Object.h"

class b2Body;

namespace ss
{
	class World;

	class Actor : public Object
	{
	public:
		Actor(World* owningWorld, const std::string& texturePath = "");
		virtual ~Actor();
		void BeginPlayInternal();
		void TickInternal(float deltaTime);
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		void SetTexture(const std::string& texturePath);
		virtual void Render(sf::RenderWindow& window);

		void SetActorLocation(const sf::Vector2f& newLoc);
		void SetActorRotation(float newRot);
		void AddActorLocationOffset(const sf::Vector2f& offsetAmt);
		void AddActorRotationOffset(float newRotAmt);

		sf::Vector2f GetActorLocation() const;
		float GetActorRotation() const;

		sf::Vector2f GetActorForwardDirection() const;
		sf::Vector2f GetActorRightDirection() const;
		sf::FloatRect GetActorGlobalBounds() const;

		sf::Vector2u GetWindowSize() const;

		const World* GetWorld() const { return mOwningWorld; }
		World* GetWorld() { return mOwningWorld; }

		bool IsActorOutOfWindowBounds(float allowance = 10.f) const;

		void SetEnablePhysics(bool enable);
		virtual void OnActorBeginOverlap(Actor* other);
		virtual void OnActorEndOverlap(Actor* other);

		virtual void Destroy() override;

		void SetTeamID(uint8 teamID) { mTeamID = teamID; }
		static uint8 GetNeutralTeamID() { return neutralTeamID; }
		uint8 GetTeamID() const { return mTeamID; }
		bool IsOtherHostile(Actor* other) const;

		virtual void ApplyDamage(float amt);

		sf::Sprite& GetSprite() { return mSprite; }
		const sf::Sprite& GetSprite() const { return mSprite; }

		Delegate<Actor*> onActorDestroyed;
		void SetTextureRepeat(bool repeated);
	private:
		void InitializePhysics();
		void UnInitializePhysics();
		void UpdatePhysicsBodyTransform();
		void CenterPivot();

		World* mOwningWorld;
		bool mHasBeganPlay;

		sf::Sprite mSprite;
		shared<sf::Texture> mTexture;

		b2Body* mPhysicsBody;
		bool mPhysicsEnabled;

		uint8 mTeamID;
		const static uint8 neutralTeamID = 255;
	};
}