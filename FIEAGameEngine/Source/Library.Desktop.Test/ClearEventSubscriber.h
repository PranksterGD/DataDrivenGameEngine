#pragma once
#include <cstdint>
#include "EventSubscriber.h"
#include "EventQueue.h"
#include "GameTime.h"

namespace UnitTest
{
	class ClearEventSubscriber : public FieaGameEngine::EventSubscriber
	{
	public:

		FieaGameEngine::EventQueue* queue;

		bool mNotified;

		ClearEventSubscriber();

		virtual void Notify(const class FieaGameEngine::EventPublisher& eventPublisher) override;

	};
}