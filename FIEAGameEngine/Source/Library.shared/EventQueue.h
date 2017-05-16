#pragma once
#include <chrono>
#include "EventPublisher.h"
#include "GameTime.h"
#include "Vector.h"
#include <mutex>
#include <vector>

namespace FieaGameEngine
{
	class EventQueue final
	{

	public:

		/**Default constructor for the Event Queue that is defaulted. */
		EventQueue() = default;

		/**Destructor for the Event Queue that is defaulted. */
		~EventQueue();

		EventQueue(const EventQueue& otherEventQueue) = delete;

		EventQueue(EventQueue&& otherEventQueue) = delete;

		EventQueue& operator=(const EventQueue& otherEventQueue) = delete;

		EventQueue& operator=(EventQueue&& otherEventQueue) = delete;

		/**Function that adds an event to the event queue
		* @param eventPublisher - The event to be added.
		* @param gameTime - A game time reference that is used to get the current time.
		* @param delay - The delay after which the event should fire.*/
		void Enqueue(EventPublisher& eventPublisher, const GameTime& gameTime, const std::chrono::milliseconds& delay = std::chrono::milliseconds::zero());

		/**Function that is used to immediately fire an event.
		* @param eventPublisher - The event to fire.*/
		void Send(const EventPublisher& eventPublisher);

		/**Function that checks if any event in the event queue has expired and if so, fires the event.
		* @param gameTime - A game time reference that is used to get the current time. */
		void Update(const GameTime& gameTime);

		/**Function that removes all the elements from the event queue. Calls update once first before clearing
		* @param gameTime - A game time reference that is used to get the current time. */
		void Clear();

		/**Function that is used to check if the event queue is empty.
		* @return- A boolean: true if the queue is empty, false otherwise.*/
		bool IsEmpty() const;

		/**Function that is used to get the number of elements in the queue.
		* @return - An integer that is the size of the queue.*/
		size_t Size() const;

	private:

		std::vector<EventPublisher*> mQueue;
		mutable std::mutex mMutex;
	};
}
