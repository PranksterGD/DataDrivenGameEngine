#pragma once
#include <cstdint>
#include "EventSubscriber.h"
#include "EventQueue.h"
#include "GameTime.h"

namespace UnitTest
{
	class CreateEventSubscriber : public FieaGameEngine::EventSubscriber
	{
	public:

		FieaGameEngine::EventQueue* queue;

		FieaGameEngine::GameTime* time;

		bool mNotified;

		CreateEventSubscriber();

		virtual void Notify(const class FieaGameEngine::EventPublisher& eventPublisher) override;


	};
}