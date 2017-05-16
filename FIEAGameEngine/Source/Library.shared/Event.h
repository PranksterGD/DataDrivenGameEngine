#pragma once
#include "EventPublisher.h"
#include "EventSubscriber.h"
#include <mutex>

namespace FieaGameEngine
{
	template <typename T>
	class Event final : public EventPublisher
	{
		RTTI_DECLARATIONS(Event, EventPublisher)

	public:
		/**Constructor for the Event.
		* @param message - The payload of the event.
		* @param shouldDelete - If true, the event queue will delete the event after firing it.*/
		Event(const T& message, bool shouldDelete = true);

		/**Copy constructor for the Event.
		* @param otherEvent- The other Event that is to be copied from.*/
		Event(const Event& otherEvent) = default;

		/**Move constructor for the Event.
		* @param otherEvent- The other Event that is to be moved from.*/
		Event(Event&& otherEvent);

		/**Assignment operator for the Event.
		* @param otherEvent- The other Event that is to be assigned to.
		* @return- A reference to the Event after assignment.*/
		Event& operator=(const Event& otherEvent) = default;

		/**Move assignment operator for the Event.
		* @param otherEvent - The other Event that is to be moved to.
		* @return- A reference to the Event after moving.*/
		Event& operator=(Event&& otherEvent);

		/**Function that is used to add a subscriber to the subscriber list.
		* @param subscriber- The new subscriber.*/
		static void Subscribe(EventSubscriber& subscriber);

		/**Function that is used to remove a subscriber to the subscriber list.
		* @param subscriber- The subscriber to remove.*/
		static void Unsubscribe(EventSubscriber& subscriber);

		/**Function that is used to remove all subscribers to the subscriber list. */
		static void UnsubscribeAll();

		/**Function that is used to retrieve the message that the event carries.
		* @return - A const reference to the message of the event.*/
		const T& Message() const;

		/**Destructor for the Event that is defaulted. */
		~Event() = default;

	private:

		T mMessage;

		static Vector<EventSubscriber*> sSubscribers;

		static std::mutex sMutex;
	};
}

#include "Event.Inl"