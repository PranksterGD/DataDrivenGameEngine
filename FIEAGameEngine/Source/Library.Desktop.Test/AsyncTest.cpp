#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTest;
using namespace std;
using namespace std::chrono;

namespace LibraryDesktopTest
{
	TEST_CLASS(AsyncTest)
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
			Event<Foo>::UnsubscribeAll();
			Event<int>::UnsubscribeAll();
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

		TEST_METHOD(StressTest)
		{
			EventSubscriberFoo a;
			Foo foo(10, 10);
			EventQueue queue;
			GameTime time;
			Event<Foo>::Subscribe(a);

			for (uint32_t i = 0; i < 5000; ++i)
			{
				Event<Foo>* event = new Event<Foo>(foo, true);
				queue.Enqueue(*event, time);
			}

			queue.Update(time);		

			Assert::AreEqual(5000, a.mCount);
		}

		TEST_METHOD(TestEventCreation)
		{
			CreateEventSubscriber a;
			Foo foo(10, 10);
			EventQueue queue;
			GameTime time;
			Event<Foo>::Subscribe(a);

			a.queue = &queue;
			a.time = &time;

			for (uint32_t i = 0; i < 5000; ++i)
			{
				Event<Foo>* event = new Event<Foo>(foo, true);
				queue.Enqueue(*event, time);
			}

			queue.Update(time);

			Assert::IsTrue(queue.Size() == 5000);
		}

		TEST_METHOD(ClearEventTest)
		{
			ClearEventSubscriber a;
			Foo foo(10, 10);
			EventQueue queue;
			GameTime time;
			Event<Foo>::Subscribe(a);

			a.queue = &queue;

			for (uint32_t i = 0; i < 5000; ++i)
			{
				Event<Foo>* event = new Event<Foo>(foo, true);
				queue.Enqueue(*event, time);
			}

			queue.Update(time);

			Assert::IsTrue(queue.Size() == 0);
		}

		TEST_METHOD(MultipleSubscribers)
		{
			EventSubscriberFoo a;
			Foo foo(10, 10);
			EventQueue queue;
			GameTime time;
			Event<Foo>::Subscribe(a);
			Vector<EventSubscriberFoo*> subs;

			Event<Foo>::UnsubscribeAll();

			for (uint32_t i = 0; i < 100; ++i)
			{
				Event<Foo>* event = new Event<Foo>(foo, true);
				queue.Enqueue(*event, time);
			}

			for (uint32_t i = 0; i < 100; ++i)
			{
				EventSubscriberFoo* sub = new EventSubscriberFoo();
				Event<Foo>::Subscribe(*sub);
				subs.PushBack(sub);
			}

			queue.Update(time);

			for (EventSubscriberFoo* sub : subs)
			{
				Assert::AreEqual(100, sub->mCount);
			}

			for (EventSubscriberFoo* sub : subs)
			{
				delete sub;
			}
		}

		TEST_METHOD(TestSubscriberCreation)
		{
			CreateSubscriberSubscriber a;
			Foo foo(10, 10);
			EventQueue queue;
			GameTime time;
			Event<Foo>::Subscribe(a);

			uint32_t subs = 500;
			Event<Foo> event(foo);

			Assert::AreEqual(event.Subscribers().Size(), 1U);

			for (uint32_t i = 0; i < subs; ++i)
			{
				Event<Foo>* e = new Event<Foo>(foo, true);
				queue.Enqueue(*e, time);
			}

			queue.Update(time);

			Assert::AreEqual(event.Subscribers().Size(), subs+1);

			Event<Foo>::UnsubscribeAll();

		}

		TEST_METHOD(TestSubscriberRemove)
		{
			RemoveSubscriberSubscriber a;
			RemoveSubscriberSubscriber b;
			RemoveSubscriberSubscriber c;
			RemoveSubscriberSubscriber d;
			RemoveSubscriberSubscriber e;
			Foo foo(10, 10);
			EventQueue queue;
			GameTime time;
			Event<Foo>::Subscribe(a);
			Event<Foo>::Subscribe(b);
			Event<Foo>::Subscribe(c);
			Event<Foo>::Subscribe(d);
			Event<Foo>::Subscribe(e);

			uint32_t subs = 500;

			Event<Foo> event(foo);

			Assert::AreEqual(event.Subscribers().Size(), 5U);

			for (uint32_t i = 0; i < subs; ++i)
			{
				Event<Foo>* eve = new Event<Foo>(foo, true);
				queue.Enqueue(*eve, time);
			}

			queue.Update(time);

			Assert::AreEqual(event.Subscribers().Size(), 0U);

			Event<Foo>::UnsubscribeAll();

		}

		TEST_METHOD(TestException)
		{
			ExceptionSubscriber a;

			Foo foo(10, 10);
			Event<Foo>* event = new Event<Foo>(foo, true);

			EventQueue queue;

			Event<Foo>::Subscribe(a);

			GameTime time;

			queue.Enqueue(*event, time);

			auto expression = [&queue, &time] {queue.Update(time); };

			Assert::ExpectException<exception>(expression);

			Event<Foo>::UnsubscribeAll();
		}

	private:
		static _CrtMemState sStartMemState;

	};
	_CrtMemState AsyncTest::sStartMemState;
}