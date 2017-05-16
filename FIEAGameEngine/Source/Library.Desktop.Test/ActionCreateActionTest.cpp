#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTest;
using namespace std;

namespace LibraryDesktopTest
{
	TEST_CLASS(ActionCreateActionTest)
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
			ActionCreateAction a;

			Assert::IsTrue(a.IsPrescribedAttribute("Name"));
			Assert::IsTrue(a.IsPrescribedAttribute("this"));
			Assert::IsTrue(a.IsPrescribedAttribute("ClassName"));
			Assert::IsTrue(a.IsPrescribedAttribute("InstanceName"));

			Assert::IsTrue(a.Name() == string());

		}

		TEST_METHOD(CopyConstructor)
		{
			ActionCreateAction actionCreateAction("RealList");

			actionCreateAction.SetCreatedClassName("ActionList");
			actionCreateAction.SetCreatedInstanceName("SomeName");

			ActionCreateAction otherActionCreateAction(actionCreateAction);

			Assert::IsTrue(otherActionCreateAction.IsPrescribedAttribute("Name"));
			Assert::IsTrue(otherActionCreateAction.IsPrescribedAttribute("this"));
			Assert::IsTrue(otherActionCreateAction.IsPrescribedAttribute("ClassName"));
			Assert::IsTrue(otherActionCreateAction.IsPrescribedAttribute("InstanceName"));

			Assert::IsTrue(otherActionCreateAction == actionCreateAction);
		}

		TEST_METHOD(AssignmentOperator)
		{
			ActionCreateAction actionCreateAction("RealList");

			actionCreateAction.SetCreatedClassName("ActionList");
			actionCreateAction.SetCreatedInstanceName("SomeName");

			ActionCreateAction otherActionCreateAction;
			otherActionCreateAction= actionCreateAction;

			Assert::IsTrue(otherActionCreateAction.IsPrescribedAttribute("Name"));
			Assert::IsTrue(otherActionCreateAction.IsPrescribedAttribute("this"));
			Assert::IsTrue(otherActionCreateAction.IsPrescribedAttribute("ClassName"));
			Assert::IsTrue(otherActionCreateAction.IsPrescribedAttribute("InstanceName"));

			Assert::IsTrue(otherActionCreateAction == actionCreateAction);

		}

		TEST_METHOD(MoveConstructor)
		{
			ActionCreateAction actionCreateAction("RealList");

			actionCreateAction.SetCreatedClassName("ActionList");
			actionCreateAction.SetCreatedInstanceName("SomeName");

			ActionCreateAction otherActionCreateAction(actionCreateAction);

			ActionCreateAction movedActionCreateAction(move(actionCreateAction));

			Assert::IsTrue(movedActionCreateAction.IsPrescribedAttribute("Name"));
			Assert::IsTrue(movedActionCreateAction.IsPrescribedAttribute("this"));
			Assert::IsTrue(movedActionCreateAction.IsPrescribedAttribute("ClassName"));
			Assert::IsTrue(movedActionCreateAction.IsPrescribedAttribute("InstanceName"));

			Assert::IsTrue(otherActionCreateAction == movedActionCreateAction);
		}

		TEST_METHOD(MoveAssignmentOperator)
		{
			ActionCreateAction actionCreateAction("RealList");

			actionCreateAction.SetCreatedClassName("ActionList");
			actionCreateAction.SetCreatedInstanceName("SomeName");

			ActionCreateAction otherActionCreateAction(actionCreateAction);

			ActionCreateAction movedActionCreateAction;
			movedActionCreateAction = (move(actionCreateAction));

			Assert::IsTrue(movedActionCreateAction.IsPrescribedAttribute("Name"));
			Assert::IsTrue(movedActionCreateAction.IsPrescribedAttribute("this"));
			Assert::IsTrue(movedActionCreateAction.IsPrescribedAttribute("ClassName"));
			Assert::IsTrue(movedActionCreateAction.IsPrescribedAttribute("InstanceName"));

			Assert::IsTrue(otherActionCreateAction == movedActionCreateAction);
		}

		TEST_METHOD(Name)
		{
			ActionCreateAction a("Thing");

			Assert::IsTrue(a.Name() == "Thing");

			const ActionCreateAction* b = &a;

			Assert::IsTrue(b->Name() == "Thing");
		}

		TEST_METHOD(SetName)
		{
			ActionCreateAction a;

			a.SetName("Thing");

			Assert::IsTrue(a.Name() == "Thing");
		}

		TEST_METHOD(SetCreatedClassName)
		{
			ActionCreateAction a;

			a.SetCreatedClassName("Thing");

			Assert::IsTrue(a.GetCreatedClassName() == "Thing");
		}

		TEST_METHOD(Update)
		{
			WorldState m;
			ActionList e;

			ActionListFactory f;
			ActionCreateActionFactory g;

			Action* a = e.CreateAction("ActionCreateAction", "ChildList");

			ActionCreateAction* create = a->As<ActionCreateAction>();

			create->SetCreatedClassName("ActionList");
			create->SetCreatedInstanceName("CreatedList");

			e.Update(m);

			Assert::IsTrue(m.mCurrentAction == a);

			Datum& datum = e.Actions();

			Assert::IsTrue(datum.Size() == 2);
			Assert::IsTrue(datum.Get<Scope*&>(1)->Is("ActionList"));
			Assert::IsTrue(datum.Get<Scope*&>(1)->As<ActionList>()->Name() == "CreatedList");
		}

		TEST_METHOD(ActionListIfRTTI)
		{
			ActionListIf a;
			RTTI* r = &a;

			Assert::IsTrue(r->Is("ActionListIf"));
			Assert::IsTrue(r->Is(ActionListIf::TypeIdClass()));
			Assert::IsTrue(r->As<ActionListIf>() != nullptr);
			Assert::IsTrue(a.TypeName() == "ActionListIf");
			Assert::IsTrue(a.TypeIdClass() == ActionListIf::TypeIdClass());
			Assert::IsTrue(r->TypeIdInstance() == ActionListIf::TypeIdClass());
			RTTI* r2 = r->QueryInterface(ActionListIf::TypeIdClass());
			Assert::IsTrue(r2->Is("ActionListIf"));
		}


	private:
		static _CrtMemState sStartMemState;

	};
	_CrtMemState ActionCreateActionTest::sStartMemState;
}