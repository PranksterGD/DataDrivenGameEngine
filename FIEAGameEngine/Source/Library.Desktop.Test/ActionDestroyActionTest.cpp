#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTest;
using namespace std;

namespace LibraryDesktopTest
{
	TEST_CLASS(ActionDestroyActionTest)
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
			ActionDestroyAction a;

			Assert::IsTrue(a.IsPrescribedAttribute("Name"));
			Assert::IsTrue(a.IsPrescribedAttribute("this"));
			Assert::IsTrue(a.IsPrescribedAttribute("InstanceName"));

			Assert::IsTrue(a.Name() == string());

		}

		TEST_METHOD(CopyConstructor)
		{
			ActionDestroyAction actionDestroyAction("MainAction");

			actionDestroyAction.SetDestroyedInstanceName("SomeName");

			ActionDestroyAction otherActionDestroyAction(actionDestroyAction);

			Assert::IsTrue(otherActionDestroyAction.IsPrescribedAttribute("Name"));
			Assert::IsTrue(otherActionDestroyAction.IsPrescribedAttribute("this"));
			Assert::IsTrue(otherActionDestroyAction.IsPrescribedAttribute("InstanceName"));

			Assert::IsTrue(otherActionDestroyAction == actionDestroyAction);
		}

		TEST_METHOD(AssignmentOperator)
		{
			ActionDestroyAction actionDestroyAction("MainAction");

			actionDestroyAction.SetDestroyedInstanceName("SomeName");

			ActionDestroyAction otherActionDestroyAction;
			otherActionDestroyAction = actionDestroyAction;

			Assert::IsTrue(otherActionDestroyAction.IsPrescribedAttribute("Name"));
			Assert::IsTrue(otherActionDestroyAction.IsPrescribedAttribute("this"));
			Assert::IsTrue(otherActionDestroyAction.IsPrescribedAttribute("InstanceName"));

			Assert::IsTrue(otherActionDestroyAction == actionDestroyAction);
		}

		TEST_METHOD(MoveConstructor)
		{
			ActionDestroyAction actionDestroyAction("MainAction");

			actionDestroyAction.SetDestroyedInstanceName("SomeName");

			ActionDestroyAction otherActionDestroyAction(actionDestroyAction);

			ActionDestroyAction movedActionDestroyAction(move(actionDestroyAction));

			Assert::IsTrue(movedActionDestroyAction.IsPrescribedAttribute("Name"));
			Assert::IsTrue(movedActionDestroyAction.IsPrescribedAttribute("this"));
			Assert::IsTrue(movedActionDestroyAction.IsPrescribedAttribute("InstanceName"));

			Assert::IsTrue(movedActionDestroyAction == otherActionDestroyAction);
		}

		TEST_METHOD(MoveAssignmentOperator)
		{
			ActionDestroyAction actionDestroyAction("MainAction");

			actionDestroyAction.SetDestroyedInstanceName("SomeName");

			ActionDestroyAction otherActionDestroyAction(actionDestroyAction);

			ActionDestroyAction movedActionDestroyAction;
			movedActionDestroyAction = (move(actionDestroyAction));

			Assert::IsTrue(movedActionDestroyAction.IsPrescribedAttribute("Name"));
			Assert::IsTrue(movedActionDestroyAction.IsPrescribedAttribute("this"));
			Assert::IsTrue(movedActionDestroyAction.IsPrescribedAttribute("InstanceName"));

			Assert::IsTrue(movedActionDestroyAction == otherActionDestroyAction);
		}

		TEST_METHOD(Name)
		{
			ActionDestroyAction a("Thing");

			Assert::IsTrue(a.Name() == "Thing");

			const ActionDestroyAction* b = &a;

			Assert::IsTrue(b->Name() == "Thing");
		}

		TEST_METHOD(SetName)
		{
			ActionDestroyAction a;

			a.SetName("Thing");

			Assert::IsTrue(a.Name() == "Thing");
		}

		TEST_METHOD(SetDestroyedInstanceName)
		{
			ActionDestroyAction a;

			a.SetDestroyedInstanceName("Thing");

			Assert::IsTrue(a.GetDestroyedInstanceName() == "Thing");
		}

		TEST_METHOD(GetCreatedClassName)
		{
			ActionDestroyAction a;

			a.SetDestroyedInstanceName("Thing");

			Assert::IsTrue(a.GetDestroyedInstanceName() == "Thing");

			const ActionDestroyAction* b = &a;

			Assert::IsTrue(b->GetDestroyedInstanceName() == "Thing");
		}

		TEST_METHOD(Update)
		{
			WorldState m;
			ActionList e;

			ActionListFactory f;
			ActionCreateActionFactory g;
			ActionDestroyActionFactory h;

			World world;

			Action* action = world.CreateAction("ActionList", "MainList");

			ActionList* actionList = action->As<ActionList>();

			Action* a = actionList->CreateAction("ActionCreateAction", "ChildList");
			Action* d = actionList->CreateAction("ActionDestroyAction", "DestroyAction");
			a;
			d;

			ActionDestroyAction* destroy = d->As<ActionDestroyAction>();

			destroy->SetDestroyedInstanceName("ChildList");

			Assert::IsTrue(actionList->Actions().Size() == 2);

			world.Update(m);

			Assert::IsTrue(m.mCurrentAction == d);

			Assert::IsTrue(actionList->Actions().Size() == 1);
		}

		TEST_METHOD(ActionDestroyActionRTTI)
		{
			ActionDestroyAction a;
			RTTI* r = &a;

			Assert::IsTrue(r->Is("ActionDestroyAction"));
			Assert::IsTrue(r->Is(ActionDestroyAction::TypeIdClass()));
			Assert::IsTrue(r->As<ActionDestroyAction>() != nullptr);
			Assert::IsTrue(a.TypeName() == "ActionDestroyAction");
			Assert::IsTrue(a.TypeIdClass() == ActionDestroyAction::TypeIdClass());
			Assert::IsTrue(r->TypeIdInstance() == ActionDestroyAction::TypeIdClass());
			RTTI* r2 = r->QueryInterface(ActionDestroyAction::TypeIdClass());
			Assert::IsTrue(r2->Is("ActionDestroyAction"));
		}


	private:
		static _CrtMemState sStartMemState;

	};
	_CrtMemState ActionDestroyActionTest::sStartMemState;
}