#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTest;
using namespace std;

namespace LibraryDesktopTest
{
	TEST_CLASS(ActionListTest)
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
			ActionList a;

			Assert::IsTrue(a.IsPrescribedAttribute("Name"));
			Assert::IsTrue(a.IsPrescribedAttribute("this"));
			Assert::IsTrue(a.IsPrescribedAttribute("Actions"));

			Assert::IsTrue(a.Name() == string());

		}

		TEST_METHOD(CopyConstructor)
		{
			ActionList actionList("RealList");

			ActionListFactory a;
			actionList.CreateAction("ActionList", "ChildList");

			ActionList otherActionList(actionList);

			Assert::IsTrue(otherActionList.IsPrescribedAttribute("Name"));
			Assert::IsTrue(otherActionList.IsPrescribedAttribute("this"));
			Assert::IsTrue(otherActionList.IsPrescribedAttribute("Actions"));

			Assert::IsTrue(otherActionList == actionList);
		}

		TEST_METHOD(AssignmentOperator)
		{
			ActionList actionList("RealList");

			ActionListFactory a;
			actionList.CreateAction("ActionList", "ChildList");

			ActionList otherActionList;
			otherActionList = actionList;

			Assert::IsTrue(otherActionList.IsPrescribedAttribute("Name"));
			Assert::IsTrue(otherActionList.IsPrescribedAttribute("this"));
			Assert::IsTrue(otherActionList.IsPrescribedAttribute("Actions"));

			Assert::IsTrue(otherActionList == actionList);

		}

		TEST_METHOD(MoveConstructor)
		{
			ActionList actionList("RealList");

			ActionListFactory a;
			actionList.CreateAction("ActionList", "ChildList");

			ActionList otherActionList(actionList);

			ActionList movedActionList(move(actionList));

			Assert::IsTrue(movedActionList.IsPrescribedAttribute("Name"));
			Assert::IsTrue(movedActionList.IsPrescribedAttribute("this"));
			Assert::IsTrue(movedActionList.IsPrescribedAttribute("Actions"));

			Assert::IsTrue(movedActionList == otherActionList);

			Assert::IsTrue(actionList.Name() == string());
		}

		TEST_METHOD(MoveAssignmentOperator)
		{
			ActionList actionList("RealList");

			ActionListFactory a;
			actionList.CreateAction("ActionList", "ChildList");

			ActionList otherActionList(actionList);

			ActionList movedActionList;
			movedActionList = (move(actionList));

			Assert::IsTrue(movedActionList.IsPrescribedAttribute("Name"));
			Assert::IsTrue(movedActionList.IsPrescribedAttribute("this"));
			Assert::IsTrue(movedActionList.IsPrescribedAttribute("Actions"));

			Assert::IsTrue(movedActionList == otherActionList);

			Assert::IsTrue(actionList.Name() == string());
		}

		TEST_METHOD(Name)
		{
			ActionList a("Thing");

			Assert::IsTrue(a.Name() == "Thing");

			const ActionList* b = &a;

			Assert::IsTrue(b->Name() == "Thing");
		}

		TEST_METHOD(SetName)
		{
			ActionList a;

			a.SetName("Thing");

			Assert::IsTrue(a.Name() == "Thing");
		}

		TEST_METHOD(Actions)
		{
			ActionList a;
			ActionListFactory f;

			a.CreateAction("ActionList", "Number1");

			Datum& datum = a.Actions();

			Assert::IsTrue(datum.Type() == DatumType::TABLE);
			Assert::IsTrue(datum.Get<Scope*&>()->Is("Action"));

			const ActionList* b = &a;

			datum = b->Actions();

			Assert::IsTrue(datum.Type() == DatumType::TABLE);
			Assert::IsTrue(datum.Get<Scope*&>()->Is("Action"));
		}

		TEST_METHOD(Update)
		{
			WorldState m;
			ActionList e;

			ActionListFactory f;

			Action* a = e.CreateAction("ActionList", "ChildList");

			e.Update(m);

			Assert::IsTrue(m.mCurrentAction == a);
		}

		TEST_METHOD(CreateAction)
		{
			ActionList a;
			ActionListFactory f;

			Action* b = a.CreateAction("ActionList", "ChildList");

			Datum& d = a.Actions();
			Assert::IsTrue(d == *b);
		}

		TEST_METHOD(ActionListRTTI)
		{
			ActionList a;
			RTTI* r = &a;

			Assert::IsTrue(r->Is("ActionList"));
			Assert::IsTrue(r->Is(ActionList::TypeIdClass()));
			Assert::IsTrue(r->As<ActionList>() != nullptr);
			Assert::IsTrue(a.TypeName() == "ActionList");
			Assert::IsTrue(a.TypeIdClass() == ActionList::TypeIdClass());
			Assert::IsTrue(r->TypeIdInstance() == ActionList::TypeIdClass());
			RTTI* r2 = r->QueryInterface(ActionList::TypeIdClass());
			Assert::IsTrue(r2->Is("ActionList"));

			a.ClearPrescribedAttributes();
		}


	private:
		static _CrtMemState sStartMemState;

	};
	_CrtMemState ActionListTest::sStartMemState;
}