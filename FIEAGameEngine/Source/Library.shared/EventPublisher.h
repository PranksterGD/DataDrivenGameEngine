#pragma once
#include "RTTI.h"
#include "EventSubscriber.h"
#include "Vector.h"
#include <chrono>
#include <mutex>
namespace FieaGameEngine
{
	class EventPublisher: public RTTI
	{
		RTTI_DECLARATIONS(EventPublisher, RTTI)

	public:

		/**Function that is used to set the time data of the EventPublisher.
		* @param enqueueTime - The time point when the EventPublisher was enqueued.
		* @param delay - The delay after which the EventPublisher should fire.*/
		void SetTime(const std::chrono::high_resolution_clock::time_point& enqueueTime, const std::chrono::milliseconds& delay = std::chrono::milliseconds(0));

		/**Function that is used to retrieve the enqueued time of the EventPublisher.
		* @return - A const time point reference to the enqueued time of the EventPublisher.*/
		const std::chrono::high_resolution_clock::time_point& TimeEnqueued() const;

		/**Function that is used to retrieve the delay time of the EventPublisher.
		* @return - A const milliseconds reference to the delay time of the EventPublisher.*/
		const std::chrono::milliseconds& Delay() const;

		/**Function that is used to tell if an event has expired or not.
		* @param currentTime - The current time.
		* @return A boolean - True if the event has expired, false otherwise.*/
		bool IsExpired(const std::chrono::high_resolution_clock::time_point& currentTime) const;

		/**Function that fires the event and calls notify on all of its subscribers. */
		void Deliver() const;

		/**Function that is used to tell if the event queue will delete the EventPublisher after firing it.
		* @return A boolean - True if the event queue should delete it, false otherwise.*/
		bool DeleteAfterPublishing() const;

		/**Function that is used to get the list of subscribers.
		* @return A const reference to the vector that contains the list of subscribers.*/
		 const Vector<EventSubscriber*>& Subscribers() const;

		/**Destructor for the EventPublisher that is defaulted. */
		virtual ~EventPublisher() = default;

	protected:

		/**Constructor for the EventPublisher.
		* @param subscribers - The subscriber list of the EventPublisher
		* @param shouldDelete - If true, the event queue will delete the event after firing it.*/
		EventPublisher(const Vector<EventSubscriber*>& subscribers, std::mutex& Mutex , bool shouldDelete);

		/**Copy constructor for the EventPublisher.
		* @param otherEventPublisher- The other EventPublisher that is to be copied from.*/
		EventPublisher(const EventPublisher& otherEventPublisher) = default;

		/**Assignment operator for the EventPublisher.
		* @param otherEventPublisher- The other EventPublisher that is to be assigned to.
		* @return- A reference to the EventPublisher after assignment.*/
		EventPublisher& operator=(const EventPublisher& otherEventPublisher) = default;

		/**Move constructor for the EventPublisher.
		* @param otherEventPublisher- The other EventPublisher that is to be moved from.*/
		EventPublisher(EventPublisher&& otherEventPublisher);

		/**Move assignment operator for the EventPublisher.
		* @param otherEventPublisher - The other EventPublisher that is to be moved to.
		* @return- A reference to the EventPublisher after moving.*/
		EventPublisher& operator=(EventPublisher&& otherEventPublisher);

	private:

		std::chrono::time_point<std::chrono::steady_clock> mEnqueueTime;

		std::chrono::milliseconds mDelay;

		bool mShouldDelete;

		const Vector<EventSubscriber*>* mSubscribers;

		std::mutex* mMutex;
	};
}