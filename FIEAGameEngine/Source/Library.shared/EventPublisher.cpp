#include "pch.h"

using namespace std;
using namespace FieaGameEngine;
using namespace std::chrono;

RTTI_DEFINITIONS(EventPublisher)

EventPublisher::EventPublisher(const Vector<EventSubscriber *>& subscribers, mutex& mutex, bool shouldDelete) :
	mShouldDelete(shouldDelete), mSubscribers(&subscribers), mMutex(&mutex), mDelay(milliseconds::zero())
{

}

EventPublisher::EventPublisher(EventPublisher&& otherEventPublisher)
{
	*this = move(otherEventPublisher);
}

EventPublisher& EventPublisher::operator=(EventPublisher&& otherEventPublisher)
{
	if (this != &otherEventPublisher)
	{
		mEnqueueTime = otherEventPublisher.mEnqueueTime;
		mDelay = otherEventPublisher.mDelay;
		mSubscribers = otherEventPublisher.mSubscribers;
		mMutex = otherEventPublisher.mMutex;
		mShouldDelete = otherEventPublisher.mShouldDelete;

		otherEventPublisher.mEnqueueTime = high_resolution_clock::time_point();
		otherEventPublisher.mDelay = milliseconds::zero();
		otherEventPublisher.mShouldDelete = false;
		otherEventPublisher.mSubscribers = nullptr;
		otherEventPublisher.mMutex = nullptr;
	}


	return *this;
}

void EventPublisher::SetTime(const high_resolution_clock::time_point& enqueueTime, const std::chrono::milliseconds& delay)
{
	mEnqueueTime = enqueueTime;
	mDelay = delay;
}

const high_resolution_clock::time_point& EventPublisher::TimeEnqueued() const
{
	return mEnqueueTime;
}

const milliseconds& EventPublisher::Delay() const
{
	return mDelay;
}

bool EventPublisher::IsExpired(const high_resolution_clock::time_point& currentTime) const
{
	return currentTime >= (mEnqueueTime + mDelay);
}

void EventPublisher::Deliver() const
{
	Vector<EventSubscriber*> workerVector;
	vector<future<void>> futures;

	{
		lock_guard<mutex> lock(*mMutex);
		workerVector = *mSubscribers;
	}

	for (EventSubscriber* subscriber : workerVector)
	{
		futures.emplace_back(async([subscriber, this] {subscriber->Notify(*this); }));
	}

	for (auto& f : futures)
	{
		f.get();
	}
}

bool EventPublisher::DeleteAfterPublishing() const
{
	return mShouldDelete;
}


const Vector<EventSubscriber*>&EventPublisher::Subscribers() const
{
	lock_guard<mutex> lock(*mMutex);
	return *mSubscribers;
}




