#include "pch.h"

using namespace std;
using namespace FieaGameEngine;

WorldState::WorldState() :
	mCurrentEntity(nullptr), mCurrentSector(nullptr), mCurrentWorld(nullptr), mCurrentAction(nullptr)
{

}

const std::chrono::high_resolution_clock::time_point& WorldState::GetGameTime() const
{
	return mGameTime.CurrentTime();
}

void WorldState::SetGameTime(const std::chrono::high_resolution_clock::time_point& totalGameTime)
{
	mGameTime.SetCurrentTime(totalGameTime);
}