#pragma once
#include <cstdint>
#include "EventSubscriber.h"
#include "Foo.h"
#include <mutex>

namespace UnitTest
{
	class EventSubscriberFoo : public FieaGameEngine::EventSubscriber
	{
	public:

		Foo mFoo;

		bool mNotified;

		int mCount;

		EventSubscriberFoo();

		virtual void Notify(const class FieaGameEngine::EventPublisher& eventPublisher) override;

	private:

		std::mutex mMutex;

	};
}