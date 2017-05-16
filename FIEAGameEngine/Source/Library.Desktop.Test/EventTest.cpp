#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTest;
using namespace std;
using namespace std::chrono;

namespace LibraryDesktopTest
{
	TEST_CLASS(EventTest)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
#if defined (_DEBUG)

			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
#endif
		}

		TEST_METHOD_CLEANUP(Cleanup)
		{
			Attributed::ClearPrescribedAttributes();
#if defined (_DEBUG)
			_CrtMemState endMemState, diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &sStartMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
#endif
		}

		TEST_METHOD(DefaultConstructor)
		{
			Foo*  foo = new Foo(10, 10);
			Event<Foo>* event = new Event<Foo>(*foo, true);

			Assert::IsTrue(event->DeleteAfterPublishing());
			Assert::IsTrue(event->Message() == *foo);

			delete(foo);
			delete(event);

			Event<Foo>::UnsubscribeAll();
		}

		TEST_METHOD(MoveConstructor)
		{
			WorldState state;

			Foo*  foo = new Foo(10, 10);
			Event<Foo>* event = new Event<Foo>(*foo, true);


			EventSubscriberFoo eventFoo;
			EventSubscriberFoo eventFoo2;
			EventSubscriberFoo eventFoo3;
			EventSubscriberFoo eventFoo4;
			Event<Foo>::Subscribe(eventFoo);
			Event<Foo>::Subscribe(eventFoo2);
			Event<Foo>::Subscribe(eventFoo3);
			Event<Foo>::Subscribe(eventFoo4);

			event->SetTime(state.GetGameTime(), milliseconds(10));

			Event<Foo> copyEvent(*event);
			Event<Foo> moveEvent(move(*event));

			Assert::IsTrue(moveEvent.Message() == copyEvent.Message());
			Assert::IsTrue(moveEvent.TimeEnqueued() == copyEvent.TimeEnqueued());
			Assert::IsTrue(moveEvent.DeleteAfterPublishing() == copyEvent.DeleteAfterPublishing());
			Assert::IsTrue(moveEvent.Delay() == copyEvent.Delay());

			delete(foo);
			delete(event);

			Event<Foo>::UnsubscribeAll();

		}

		TEST_METHOD(MoveAssignmentOperator)
		{
			WorldState state;

			Foo*  foo = new Foo(10, 10);
			Foo foo2(20, 20);
			Event<Foo>* event = new Event<Foo>(*foo, true);


			EventSubscriberFoo eventFoo;
			Event<Foo>::Subscribe(eventFoo);

			event->SetTime(state.GetGameTime(), milliseconds(10));

			Event<Foo> copyEvent(foo2, false);
			copyEvent = *event;

			Event<Foo> moveEvent(foo2, false);
			moveEvent = move(*event);

			Assert::IsTrue(moveEvent.Message() == copyEvent.Message());
			Assert::IsTrue(moveEvent.TimeEnqueued() == copyEvent.TimeEnqueued());
			Assert::IsTrue(moveEvent.DeleteAfterPublishing() == copyEvent.DeleteAfterPublishing());
			Assert::IsTrue(moveEvent.Delay() == copyEvent.Delay());

			delete(foo);
			delete(event);

			Event<Foo>::UnsubscribeAll();

		}

		TEST_METHOD(Subscribe)
		{
			Foo*  foo = new Foo(10, 10);
			Event<Foo>* event = new Event<Foo>(*foo, true);

			EventSubscriberFoo eventFoo;

			Event<Foo>::Subscribe(eventFoo);

			Vector<EventSubscriber*> list = event->Subscribers();

			Assert::IsTrue(list.Find(&eventFoo) != list.end());
			Assert::IsTrue(list.Size() == 1U);

			Event<Foo>::Subscribe(eventFoo);

			Assert::IsTrue(list.Size() == 1U);

			delete(foo);
			delete(event);

			Event<Foo>::UnsubscribeAll();
		}

		TEST_METHOD(UnSubscribe)
		{
			Foo*  foo = new Foo(10, 10);
			Event<Foo>* event = new Event<Foo>(*foo, true);

			EventSubscriberFoo eventFoo;

			Event<Foo>::Subscribe(eventFoo);

			const Vector<EventSubscriber*>& list = event->Subscribers();

			Assert::IsTrue(list.Find(&eventFoo) != list.end());
			Assert::IsTrue(list.Size() == 1U);

			Event<Foo>::Unsubscribe(eventFoo);

			Assert::IsTrue(list.Size() == 0);
			Assert::IsTrue(list.Find(&eventFoo) == list.end());

			delete(foo);
			delete(event);

			Event<Foo>::UnsubscribeAll();
		}

		TEST_METHOD(UnSubscribeAll)
		{
			Foo*  foo = new Foo(10, 10);
			Event<Foo>* event = new Event<Foo>(*foo, true);

			EventSubscriberFoo eventFoo;
			EventSubscriberFoo eventFoo2;

			Event<Foo>::Subscribe(eventFoo);
			Event<Foo>::Subscribe(eventFoo2);

			Event<Foo>::UnsubscribeAll();

			const Vector<EventSubscriber*>& list = event->Subscribers();

			Assert::IsTrue(list.Size() == 0);
			Assert::IsTrue(list.Find(&eventFoo) == list.end());
			Assert::IsTrue(list.Find(&eventFoo2) == list.end());

			delete(foo);
			delete(event);

			Event<Foo>::UnsubscribeAll();
		}

		TEST_METHOD(Message)
		{
			Foo*  foo = new Foo(10, 10);
			Event<Foo>* event = new Event<Foo>(*foo, true);

			Assert::IsTrue(event->Message() == *foo);

			delete(foo);
			delete(event);

			Event<Foo>::UnsubscribeAll();
		}

		TEST_METHOD(SetTime)
		{
			WorldState state;

			Foo*  foo = new Foo(10, 10);
			Event<Foo>* event = new Event<Foo>(*foo, true);

			event->SetTime(state.GetGameTime(),milliseconds(10));

			Assert::IsTrue(event->TimeEnqueued() == state.GetGameTime());
			Assert::IsTrue(event->Delay() == milliseconds(10));

			delete(foo);
			delete(event);

			Event<Foo>::UnsubscribeAll();
		}

		TEST_METHOD(TimeEnqueued)
		{
			WorldState state;

			Foo*  foo = new Foo(10, 10);
			Event<Foo>* event = new Event<Foo>(*foo, true);

			event->SetTime(state.GetGameTime(), milliseconds(10));

			Assert::IsTrue(event->TimeEnqueued() == state.GetGameTime());

			delete(foo);
			delete(event);

			Event<Foo>::UnsubscribeAll();
		}

		TEST_METHOD(Delay)
		{
			WorldState state;

			Foo*  foo = new Foo(10, 10);
			Event<Foo>* event = new Event<Foo>(*foo, true);

			Assert::IsTrue(event->Delay() == milliseconds::zero());

			event->SetTime(state.GetGameTime(), milliseconds(10));

			Assert::IsTrue(event->Delay() == milliseconds(10));

			delete(foo);
			delete(event);

			Event<Foo>::UnsubscribeAll();
		}

		TEST_METHOD(IsExpired)
		{
			WorldState state;

			Foo*  foo = new Foo(10, 10);
			Event<Foo>* event = new Event<Foo>(*foo, true);

			event->SetTime(state.GetGameTime(), milliseconds(10));

			Assert::IsFalse(event->IsExpired(state.GetGameTime()));

			Assert::IsTrue(event->IsExpired(state.GetGameTime() + milliseconds(10)));

			Assert::IsTrue(event->IsExpired(state.GetGameTime() + milliseconds(11)));

			delete(foo);
			delete(event);

			Event<Foo>::UnsubscribeAll();
		}

		TEST_METHOD(DeleteAfterPublishing)
		{
			Foo*  foo = new Foo(10, 10);
			Event<Foo>* event = new Event<Foo>(*foo, true);

			Assert::IsTrue(event->DeleteAfterPublishing());

			Event<Foo>* event2 = new Event<Foo>(*foo, false);

			Assert::IsFalse(event2->DeleteAfterPublishing());

			delete(foo);
			delete(event);
			delete(event2);

			Event<Foo>::UnsubscribeAll();
		}

		TEST_METHOD(Deliver)
		{
			Foo  foo(10, 10);
			Event<Foo> event(foo);

			EventSubscriberFoo eventFoo;

			Event<Foo>::Subscribe(eventFoo);

			Assert::IsFalse(eventFoo.mNotified);

			event.Deliver();

			Assert::IsTrue(eventFoo.mNotified);

			Event<Foo>::UnsubscribeAll();
		}

		TEST_METHOD(Enqueue)
		{
			WorldState state;

			World world;

			Foo*  foo = new Foo(10, 10);
			Event<Foo>* event = new Event<Foo>(*foo, true);

			EventSubscriberFoo eventFoo;

			world.GetEventQueue().Enqueue(*event, state.mGameTime, milliseconds(10));

			Assert::IsTrue(world.GetEventQueue().Size() == 1U);

			delete(foo);
		}

		TEST_METHOD(Update)
		{
			WorldState state;

			World world;

			Foo*  foo = new Foo(10, 10);
			Event<Foo>* event = new Event<Foo>(*foo, false);
			Event<Foo> *event2 = new Event<Foo>(*foo, true);

			EventSubscriberFoo eventFoo;

			world.GetEventQueue().Enqueue(*event, state.mGameTime, milliseconds(10));
			world.GetEventQueue().Enqueue(*event2, state.mGameTime, milliseconds(5));

			Assert::IsTrue(world.GetEventQueue().Size() == 2U);

			Event<Foo>::Subscribe(eventFoo);

			Assert::IsFalse(eventFoo.mNotified);

			state.mGameTime.SetCurrentTime(state.mGameTime.CurrentTime() + milliseconds(3));

			world.Update(state);

			Assert::IsFalse(eventFoo.mNotified);

			Assert::IsTrue(world.GetEventQueue().Size() == 2U);

			state.mGameTime.SetCurrentTime(state.mGameTime.CurrentTime() + milliseconds(3));

			world.Update(state);

			Assert::IsTrue(eventFoo.mNotified);

			Assert::IsTrue(world.GetEventQueue().Size() == 1U);

			state.mGameTime.SetCurrentTime(state.mGameTime.CurrentTime() + milliseconds(5));

			world.Update(state);

			Assert::IsTrue(world.GetEventQueue().Size() == 0U);

			delete(foo);
			delete(event);
		}

		TEST_METHOD(Clear)
		{
			WorldState state;

			World world;

			Foo*  foo = new Foo(10, 10);
			Event<Foo>* event = new Event<Foo>(*foo, false);
			Event<Foo> *event2 = new Event<Foo>(*foo, true);

			EventSubscriberFoo eventFoo;

			world.GetEventQueue().Enqueue(*event, state.mGameTime, milliseconds(10));
			world.GetEventQueue().Enqueue(*event2, state.mGameTime, milliseconds(5));

			Assert::IsTrue(world.GetEventQueue().Size() == 2U);

			Event<Foo>::Subscribe(eventFoo);

			Assert::IsFalse(eventFoo.mNotified);

			state.mGameTime.SetCurrentTime(state.mGameTime.CurrentTime() + milliseconds(3));

			world.Update(state);

			Assert::IsFalse(eventFoo.mNotified);

			Assert::IsTrue(world.GetEventQueue().Size() == 2U);

			state.mGameTime.SetCurrentTime(state.mGameTime.CurrentTime() + milliseconds(3));

			world.GetEventQueue().Clear();

			Assert::IsTrue(world.GetEventQueue().Size() == 0U);

			delete(foo);
			delete(event);
		}

		TEST_METHOD(Size)
		{
			WorldState state;

			World world;

			Foo*  foo = new Foo(10, 10);
			Event<Foo>* event = new Event<Foo>(*foo, true);
			Event<Foo> *event2 = new Event<Foo>(*foo, true);

			Assert::IsTrue(world.GetEventQueue().Size() == 0U);

			world.GetEventQueue().Enqueue(*event, state.mGameTime, milliseconds(10));

			Assert::IsTrue(world.GetEventQueue().Size() == 1U);

			world.GetEventQueue().Enqueue(*event2, state.mGameTime, milliseconds(5));

			Assert::IsTrue(world.GetEventQueue().Size() == 2U);

			delete(foo);
		}

		TEST_METHOD(IsEmpty)
		{
			WorldState state;

			World world;

			Foo*  foo = new Foo(10, 10);
			Event<Foo>* event = new Event<Foo>(*foo, true);
			Event<Foo> *event2 = new Event<Foo>(*foo, true);

			Assert::IsTrue(world.GetEventQueue().IsEmpty());

			world.GetEventQueue().Enqueue(*event, state.mGameTime, milliseconds(10));

			Assert::IsFalse(world.GetEventQueue().IsEmpty());

			world.GetEventQueue().Enqueue(*event2, state.mGameTime, milliseconds(5));

			Assert::IsFalse(world.GetEventQueue().IsEmpty());

			delete(foo);
			Event<Foo>::UnsubscribeAll();
		}

		TEST_METHOD(Send)
		{
			Foo*  foo = new Foo(10, 10);
			Event<Foo>* event = new Event<Foo>(*foo, true);

			EventSubscriberFoo eventFoo;

			Event<Foo>::Subscribe(eventFoo);

			Assert::IsFalse(eventFoo.mNotified);

			World world;
			world.GetEventQueue().Send(*event);

			Assert::IsTrue(eventFoo.mNotified);

			delete(foo);
			delete(event);

			Event<Foo>::UnsubscribeAll();
		}



	private:
		static _CrtMemState sStartMemState;

	};
	_CrtMemState EventTest::sStartMemState;
}