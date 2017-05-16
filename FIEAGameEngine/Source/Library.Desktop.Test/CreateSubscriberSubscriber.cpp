#include "pch.h"

using namespace std;
using namespace FieaGameEngine;

namespace UnitTest
{

	CreateSubscriberSubscriber::CreateSubscriberSubscriber()
	{
		mNotified = false;

	}

	void CreateSubscriberSubscriber::Notify(const EventPublisher& eventPublisher)
	{
		if (eventPublisher.Is(Event<Foo>::TypeIdClass()))
		{	
			{
				lock_guard<mutex> lock(mMutex);
				mNotified = true;

				EventSubscriberFoo* sub = new EventSubscriberFoo();
				subs.PushBack(sub);

				Event<Foo>::Subscribe(*sub);
			}
		}
	}

	CreateSubscriberSubscriber::~CreateSubscriberSubscriber()
	{
		for (EventSubscriberFoo* sub : subs)
		{
			delete sub;
		}
	}
}