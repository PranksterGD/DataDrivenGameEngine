#pragma once
#include "EventSubscriber.h"
#include <exception>
namespace UnitTest
{
	class ExceptionSubscriber : public FieaGameEngine::EventSubscriber
	{
	public:

		virtual void Notify(const FieaGameEngine::EventPublisher& eventPublisher) override { delete(&eventPublisher); throw std::exception("Blah"); }
	};
}
