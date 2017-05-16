#include "pch.h"

using namespace std;
using namespace FieaGameEngine;

namespace UnitTest
{

	ClearEventSubscriber::ClearEventSubscriber()
	{
		mNotified = false;
		queue = nullptr;
	}

	void ClearEventSubscriber::Notify(const EventPublisher& eventPublisher)
	{
		if (eventPublisher.Is(Event<Foo>::TypeIdClass()))
		{
			mNotified = true;

			if (queue != nullptr)
			{
				queue->Clear();
			}
		}
	}
}