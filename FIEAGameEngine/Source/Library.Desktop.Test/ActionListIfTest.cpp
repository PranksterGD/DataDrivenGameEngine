#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTest;
using namespace std;

namespace LibraryDesktopTest
{
	TEST_CLASS(ActionListIfTest)
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
			ActionListIf a;

			Assert::IsTrue(a.IsPrescribedAttribute("Name"));
			Assert::IsTrue(a.IsPrescribedAttribute("this"));
			Assert::IsTrue(a.IsPrescribedAttribute("condition"));

			Assert::IsTrue(a.Name() == string());

		}

		TEST_METHOD(CopyConstructor)
		{
			ActionListIf actionListIf("MainAction");

			actionListIf.SetCondition(0);

			ActionListIf otherActionListIf(actionListIf);

			Assert::IsTrue(otherActionListIf.IsPrescribedAttribute("Name"));
			Assert::IsTrue(otherActionListIf.IsPrescribedAttribute("this"));
			Assert::IsTrue(otherActionListIf.IsPrescribedAttribute("condition"));

			Assert::IsTrue(otherActionListIf == actionListIf);
		}

		TEST_METHOD(AssignmentOperator)
		{
			ActionListIf actionListIf("MainAction");

			actionListIf.SetCondition(0);

			ActionListIf otherActionListIf;
			otherActionListIf =  actionListIf;

			Assert::IsTrue(otherActionListIf.IsPrescribedAttribute("Name"));
			Assert::IsTrue(otherActionListIf.IsPrescribedAttribute("this"));
			Assert::IsTrue(otherActionListIf.IsPrescribedAttribute("condition"));

			Assert::IsTrue(otherActionListIf == actionListIf);
		}

		TEST_METHOD(MoveConstructor)
		{
			ActionListIf actionListIf("MainAction");

			actionListIf.SetCondition(0);

			ActionListIf otherActionListIf(actionListIf);

			ActionListIf movedActionListIf(move(actionListIf));

			Assert::IsTrue(movedActionListIf.IsPrescribedAttribute("Name"));
			Assert::IsTrue(movedActionListIf.IsPrescribedAttribute("this"));
			Assert::IsTrue(movedActionListIf.IsPrescribedAttribute("condition"));

			Assert::IsTrue(otherActionListIf == movedActionListIf);
		}

		TEST_METHOD(MoveAssignmentOperator)
		{
			ActionListIf actionListIf("MainAction");

			actionListIf.SetCondition(0);

			ActionListIf otherActionListIf(actionListIf);

			ActionListIf movedActionListIf;
			movedActionListIf= move(actionListIf);

			Assert::IsTrue(movedActionListIf.IsPrescribedAttribute("Name"));
			Assert::IsTrue(movedActionListIf.IsPrescribedAttribute("this"));
			Assert::IsTrue(movedActionListIf.IsPrescribedAttribute("condition"));

			Assert::IsTrue(otherActionListIf == movedActionListIf);
		}

		TEST_METHOD(Name)
		{
			ActionListIf a("Thing");

			Assert::IsTrue(a.Name() == "Thing");

			const ActionListIf* b = &a;

			Assert::IsTrue(b->Name() == "Thing");
		}

		TEST_METHOD(SetName)
		{
			ActionListIf a;

			a.SetName("Thing");

			Assert::IsTrue(a.Name() == "Thing");
		}

		TEST_METHOD(SetCondition)
		{
			ActionListIf a;

			a.SetCondition(50);

			Assert::IsTrue(a.GetCondition() == 50);
		}

		TEST_METHOD(GetCreatedClassName)
		{
			ActionListIf a;

			a.SetCondition(50);

			Assert::IsTrue(a.GetCondition() == 50);
		}

		TEST_METHOD(GetThenAction)
		{
			ActionCreateActionFactory f;
			ActionListFactory f2;
			ActionListIf a;
			a.CreateAction("ActionCreateAction", "then");
			
			Action* b = a.GetThenAction();

			Assert::IsTrue(b->Name() == "then");
			Assert::IsTrue(b->Is("ActionCreateAction"));

			const ActionListIf* c = &a;

			const Action* d = c->GetThenAction();

			Assert::IsTrue(d->Name() == "then");
			Assert::IsTrue(d->Is("ActionCreateAction"));
		}

		TEST_METHOD(GetElseAction)
		{
			ActionCreateActionFactory f;
			ActionListFactory f2;
			ActionListIf a;
			a.CreateAction("ActionCreateAction", "else");

			Action* b = a.GetElseAction();

			Assert::IsTrue(b->Name() == "else");
			Assert::IsTrue(b->Is("ActionCreateAction"));

			const ActionListIf* c = &a;

			const Action* d = c->GetElseAction();

			Assert::IsTrue(d->Name() == "else");
			Assert::IsTrue(d->Is("ActionCreateAction"));
		}

		TEST_METHOD(Update)
		{
			WorldState m;
			World world;

			ActionListIfFactory f1;
			ActionListFactory f2;
			ActionCreateActionFactory f3;

			Action* action = world.CreateAction("ActionListIf", "MainList");

			ActionListIf* actionListIf = action->As<ActionListIf>();
			actionListIf->CreateAction("ActionList", "then");
			actionListIf->CreateAction("ActionList", "else");
			actionListIf->SetCondition(10);

			Action* thenAction = actionListIf->GetThenAction();
			Action* elseAction = actionListIf->GetElseAction();

			world.Update(m);

			Assert::IsTrue(m.mCurrentAction == thenAction);
			
			actionListIf->SetCondition(0);

			world.Update(m);

			Assert::IsTrue(m.mCurrentAction == elseAction);
		}

		TEST_METHOD(ActionDestroyActionRTTI)
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
	_CrtMemState ActionListIfTest::sStartMemState;
}