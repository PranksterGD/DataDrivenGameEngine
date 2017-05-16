#pragma once

namespace FieaGameEngine
{
	class EventPublisher;

	class  EventSubscriber
	{
	public:

		/*Function that listens for events. On receiving events, performs actions based on the
		type of event received.*/
		virtual void Notify(const EventPublisher& eventPublisher) = 0;

	};
}
