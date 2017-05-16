#pragma once
#include <cstdint>
#include "EventSubscriber.h"
#include "EventQueue.h"
#include "GameTime.h"
#include "Vector.h"
#include <mutex>

namespace UnitTest
{
	class CreateSubscriberSubscriber : public FieaGameEngine::EventSubscriber
	{
	public:

		bool mNotified;

		CreateSubscriberSubscriber();
		~CreateSubscriberSubscriber();

		virtual void Notify(const class FieaGameEngine::EventPublisher& eventPublisher) override;

	private:

		FieaGameEngine::Vector<EventSubscriberFoo*> subs;
		std::mutex mMutex;

	};
}