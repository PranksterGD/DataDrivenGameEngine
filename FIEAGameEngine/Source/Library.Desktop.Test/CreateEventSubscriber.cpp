#include "pch.h"

using namespace std;
using namespace FieaGameEngine;

namespace UnitTest
{

	CreateEventSubscriber::CreateEventSubscriber()
	{
		mNotified = false;
		queue = nullptr;
		time = nullptr;

	}

	void CreateEventSubscriber::Notify(const EventPublisher& eventPublisher)
	{
		if (eventPublisher.Is(Event<Foo>::TypeIdClass()))
		{
			Event<Foo>* event = new Event<Foo>(*eventPublisher.As<Event<Foo>>());
			
			if (queue != nullptr && time != nullptr)
			{
				queue->Enqueue(*event, *time);
			}
		}
	}
}