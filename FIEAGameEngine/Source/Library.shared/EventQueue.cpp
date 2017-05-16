#include "pch.h"

using namespace std;
using namespace FieaGameEngine;
using namespace std::chrono;

void EventQueue::Enqueue(EventPublisher& eventPublisher, const GameTime& gameTime, const std::chrono::milliseconds& delay)
{
	eventPublisher.SetTime(gameTime.CurrentTime(), delay);

	lock_guard<mutex> lock(mMutex);

	mQueue.emplace_back(&eventPublisher);
}

void EventQueue::Send(const EventPublisher& eventPublisher)
{
	eventPublisher.Deliver();
}

void EventQueue::Update(const GameTime& gameTime)
{
	std::vector<EventPublisher*> expiredQueue;
	vector<future<void>> futures;

	{
		lock_guard<mutex> lock(mMutex);

		auto expiredIt = std::partition(mQueue.begin(), mQueue.end(), [&gameTime](EventPublisher* eventPublisher)
		{
			return !eventPublisher->IsExpired(gameTime.CurrentTime());
		});

		expiredQueue.insert(expiredQueue.begin(), expiredIt, mQueue.end());
		mQueue.erase(expiredIt, mQueue.end());
	}

	for (EventPublisher* publisher : expiredQueue)
	{
		if (publisher->IsExpired(gameTime.CurrentTime()))
		{
			futures.emplace_back(async([publisher]
			{
				publisher->Deliver();

				if (publisher->DeleteAfterPublishing())
				{
					delete publisher;
				}

			}));
		}
	}

	for (auto& f : futures)
	{
		f.get();
	}
}

void EventQueue::Clear()
{
	lock_guard<mutex> lock(mMutex);

	for (EventPublisher* publisher : mQueue)
	{
		if (publisher->DeleteAfterPublishing())
		{
			delete publisher;
		}
	}

	mQueue.clear();
}

size_t EventQueue::Size() const
{
	lock_guard<mutex> lock(mMutex);
	return mQueue.size();
}

bool EventQueue::IsEmpty() const
{
	lock_guard<mutex> lock(mMutex);
	return mQueue.empty();
}

EventQueue::~EventQueue()
{
	Clear();
}