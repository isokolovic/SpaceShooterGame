#include "player/Player.h"
#include "framework/World.h"
#include "player/PlayerSpaceship.h"

namespace ss
{
	Player::Player()
		: mLifeCount{ 3 },
		mScore{ 0 },
		mCurrentPlayerSpaceship{}
	{
	}

	weak<PlayerSpaceship> Player::SpawnSpaceship(World* world)
	{
		if (mLifeCount > 0)
		{
			--mLifeCount;
			auto windowSize = world->GetWindowSize();

			/*newWorld.lock()->SpawnActor<Actor>();*/ //Because it's a weak reference, must be locked first to get a pointer. 
			mCurrentPlayerSpaceship = world->SpawnActor<PlayerSpaceship>();
			mCurrentPlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(windowSize.x / 2.f, windowSize.y / 2 - 100.f));
			mCurrentPlayerSpaceship.lock()->SetActorRotation(-90.f);
			onLifeChange.Broadcast(mLifeCount);

			return mCurrentPlayerSpaceship;
		}
		else
		{
			onLifeExhausted.Broadcast();
		}

		return weak<PlayerSpaceship>{};
	}

	void Player::AddLifeCount(unsigned int count)
	{
		if (count > 0)
		{
			mLifeCount += count;
			onLifeChange.Broadcast(mLifeCount);
		}
	}

	void Player::AddScore(unsigned int amt)
	{
		if (amt > 0)
		{
			mScore = amt;
			onScoreChange.Broadcast(mScore);
		}
	}
}