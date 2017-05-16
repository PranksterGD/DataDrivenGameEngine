namespace FieaGameEngine
{
	template<typename T>
	RTTI_DEFINITIONS(Event<T>)

	template<typename T>
	Vector<EventSubscriber*> Event<T>::sSubscribers;

	template<typename T>
	std::mutex Event<T>::sMutex;

	template<typename T>
	Event<T>::Event(const T& message, bool shouldDelete) :
		EventPublisher(sSubscribers, sMutex, shouldDelete), mMessage(message)
	{

	}

	template<typename T>
	Event<T>::Event(Event<T>&& otherEvent):
		Event(otherEvent.mMessage, otherEvent.DeleteAfterPublishing())
	{
		*this = std::move(otherEvent);
	}

	template<typename T>
	Event<T>& Event<T>::operator=(Event<T>&& otherEvent) 
	{
		if (this != &otherEvent)
		{
			EventPublisher::operator=(move(otherEvent));
			mMessage = otherEvent.mMessage;
		}

		return *this;
	}

	template<typename T>
	void Event<T>::Subscribe(EventSubscriber& subscriber)
	{
		lock_guard<mutex> lock(sMutex);

		if (sSubscribers.Find(&subscriber) == sSubscribers.end())
		{
			sSubscribers.PushBack(&subscriber);
		}	
	}

	template<typename T>
	void Event<T>::Unsubscribe(EventSubscriber& subscriber)
	{
		lock_guard<mutex> lock(sMutex);

		sSubscribers.Remove(&subscriber);
	}

	template<typename T>
	void Event<T>::UnsubscribeAll()
	{
		lock_guard<mutex> lock(sMutex);

		sSubscribers.Clear();
	}

	template <typename T>
	const T& Event<T>::Message() const
	{
		return mMessage;
	}
}
