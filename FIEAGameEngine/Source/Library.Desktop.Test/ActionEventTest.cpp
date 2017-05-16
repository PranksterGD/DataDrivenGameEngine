#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTest;
using namespace std;
using namespace std::chrono;

namespace LibraryDesktopTest
{
	TEST_CLASS(ActionEventTest)
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
			ActionEvent a;

			Assert::IsTrue(a.IsPrescribedAttribute("Name"));
			Assert::IsTrue(a.IsPrescribedAttribute("this"));
			Assert::IsTrue(a.IsPrescribedAttribute("Subtype"));
			Assert::IsTrue(a.IsPrescribedAttribute("Delay"));

			Assert::IsTrue(a.Name() == "");
			Assert::IsTrue(a.GetSubtype() == "");
			Assert::IsTrue(a.GetDelay() == 0);

			ActionEvent b("Thing", "OtherThing", 100);

			Assert::IsTrue(b.Name() == "Thing");
			Assert::IsTrue(b.GetSubtype() == "OtherThing");
			Assert::IsTrue(b.GetDelay() == 100);

		}

		TEST_METHOD(CopyConstructor)
		{
			ActionEvent actionEvent("Thing", "OtherThing", 100);

			ActionEvent otherActionEvent = actionEvent;

			Assert::IsTrue(otherActionEvent == actionEvent);
			Assert::IsTrue(otherActionEvent.GetDelay() == actionEvent.GetDelay());
			Assert::IsTrue(otherActionEvent.GetSubtype() == actionEvent.GetSubtype());
		}

		TEST_METHOD(AssignmentOperator)
		{
			ActionEvent actionEvent("Thing", "OtherThing", 100);

			ActionEvent otherActionEvent;
			otherActionEvent = actionEvent;

			Assert::IsTrue(otherActionEvent == actionEvent);
			Assert::IsTrue(otherActionEvent.GetDelay() == actionEvent.GetDelay());
			Assert::IsTrue(otherActionEvent.GetSubtype() == actionEvent.GetSubtype());
		}

		TEST_METHOD(MoveConstructor)
		{
			ActionEvent actionEvent("Thing", "OtherThing", 100);

			ActionEvent otherActionEvent = actionEvent;

			ActionEvent movedActionEvent = move(actionEvent);

			Assert::IsTrue(otherActionEvent == movedActionEvent);
			Assert::IsTrue(otherActionEvent.GetDelay() == movedActionEvent.GetDelay());
			Assert::IsTrue(otherActionEvent.GetSubtype() == movedActionEvent.GetSubtype());

			Assert::IsTrue(actionEvent.GetDelay() == 0);
			Assert::IsTrue(actionEvent.GetSubtype() == "");
			Assert::IsTrue(actionEvent.Name() == "");
		}

		TEST_METHOD(MoveAssignmentOperator)
		{
			ActionEvent actionEvent("Thing", "OtherThing", 100);

			ActionEvent otherActionEvent = actionEvent;

			ActionEvent movedActionEvent;
			movedActionEvent = move(actionEvent);

			Assert::IsTrue(otherActionEvent == movedActionEvent);
			Assert::IsTrue(otherActionEvent.GetDelay() == movedActionEvent.GetDelay());
			Assert::IsTrue(otherActionEvent.GetSubtype() == movedActionEvent.GetSubtype());

			Assert::IsTrue(actionEvent.GetDelay() == 0);
			Assert::IsTrue(actionEvent.GetSubtype() == "");
			Assert::IsTrue(actionEvent.Name() == "");
		}

		TEST_METHOD(GetSetDelay)
		{
			ActionEvent a;
			
			Assert::IsTrue(a.GetDelay() == 0);

			a.SetDelay(10);

			Assert::IsTrue(a.GetDelay() == 10);
		}

		TEST_METHOD(GetSetSubtype)
		{
			ActionEvent a;
			Assert::IsTrue(a.GetSubtype() == "");

			a.SetSubtype("Thing");

			Assert::IsTrue(a.GetSubtype() == "Thing");
		}

		TEST_METHOD(Update)
		{
			WorldState s;

			World world;

			ActionEventFactory f;

			Action* action = world.CreateAction("ActionEvent", "event");

			Assert::IsNotNull(action);

			ActionEvent* eventAction = action->As<ActionEvent>();
			eventAction->SetSubtype("Thing");
			eventAction->SetDelay(10);
			eventAction->Append("NewStuff");

			Assert::IsTrue(world.GetEventQueue().IsEmpty());

			ReactionAttributed* reaction = new ReactionAttributed("SomeName");

			Datum* subtypesDatum = reaction->Find("Subtype");

			subtypesDatum->PushBack("Thing");

			world.Adopt(*reaction, "Reactions");

			Assert::IsNull(reaction->Find("NewStuff"));

			world.Update(s);

			Assert::IsTrue(world.GetEventQueue().Size() == 1U);

			delete(eventAction);

			s.mGameTime.SetCurrentTime(s.mGameTime.CurrentTime() + milliseconds(15));

			world.Update(s);

			Assert::IsTrue(world.GetEventQueue().IsEmpty());

			Assert::IsNotNull(reaction->Find("NewStuff"));
		}

		TEST_METHOD(Copy)
		{
			ActionEvent a;

			Scope* s = a.Copy();

			Assert::IsTrue(s->Is("ActionEvent"));

			delete s;
		}

		TEST_METHOD(ActionEventRTTI)
		{
			ActionEvent a;
			RTTI* r = &a;

			Assert::IsTrue(r->Is("ActionEvent"));
			Assert::IsTrue(r->Is(ActionEvent::TypeIdClass()));
			Assert::IsTrue(r->As<ActionEvent>() != nullptr);
			Assert::IsTrue(a.TypeName() == "ActionEvent");
			Assert::IsTrue(a.TypeIdClass() == ActionEvent::TypeIdClass());
			Assert::IsTrue(r->TypeIdInstance() == ActionEvent::TypeIdClass());
			RTTI* r2 = r->QueryInterface(ActionEvent::TypeIdClass());
			Assert::IsTrue(r2->Is("ActionEvent"));

			a.ClearPrescribedAttributes();
		}


	private:
		static _CrtMemState sStartMemState;

	};
	_CrtMemState ActionEventTest::sStartMemState;
}