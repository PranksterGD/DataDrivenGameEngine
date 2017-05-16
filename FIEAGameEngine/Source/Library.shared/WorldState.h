#pragma once
#include "GameTime.h"

namespace FieaGameEngine
{
	class WorldState final
	{
	public:
		WorldState();

		~WorldState() = default;

		WorldState(const WorldState& otherWorldState) = delete;

		WorldState& operator=(const WorldState& otherWorldState) = delete;

		const std::chrono::high_resolution_clock::time_point&  GetGameTime() const;

		void SetGameTime(const std::chrono::high_resolution_clock::time_point& totalGameTime);
		
		class World* mCurrentWorld;
		class Sector* mCurrentSector;
		class Entity* mCurrentEntity;
		class Action* mCurrentAction;

		GameClock mGameClock;
		GameTime mGameTime;

	};
}