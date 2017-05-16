#pragma once
#include <cstdint>
#include "EventSubscriber.h"
#include "EventQueue.h"
#include "GameTime.h"
#include "Vector.h"

namespace UnitTest
{
	class RemoveSubscriberSubscriber : public FieaGameEngine::EventSubscriber
	{
	public:

		bool mNotified;

		RemoveSubscriberSubscriber();

		virtual void Notify(const class FieaGameEngine::EventPublisher& eventPublisher) override;

	private:

	};
}