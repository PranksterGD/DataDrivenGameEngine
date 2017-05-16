#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTest;
using namespace std;

namespace LibraryDesktopTest
{
	TEST_CLASS(WorldTest)
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
			World a;

			Assert::IsTrue(a.IsPrescribedAttribute("Name"));
			Assert::IsTrue(a.IsPrescribedAttribute("this"));
			Assert::IsTrue(a.IsPrescribedAttribute("Sectors"));

			Assert::IsTrue(a.Name() == string());

			a.ClearPrescribedAttributes();
		}

		TEST_METHOD(CopyConstructor)
		{

			World world("Number1");
			world.CreateSector("Sector1");

			World otherWorld(world);

			Assert::IsTrue(otherWorld.Name() == world.Name());
			Assert::IsTrue(otherWorld.Sectors() == world.Sectors());

			Assert::IsTrue(otherWorld == world);

			Assert::IsTrue(otherWorld.Sectors().Get<Scope*&>()->Is("Sector"));

			Assert::IsTrue(otherWorld.Sectors().Get<Scope*&>()->As<Sector>()->Name() ==
				world.Sectors().Get<Scope*&>()->As<Sector>()->Name());

			Assert::IsTrue(otherWorld.Sectors().Get<Scope*&>()->As<Sector>()->GetWorld() ==
				world.Sectors().Get<Scope*&>()->As<Sector>()->GetWorld());

			Assert::IsTrue(otherWorld.IsPrescribedAttribute("Name"));
			Assert::IsTrue(otherWorld.IsPrescribedAttribute("this"));
			Assert::IsTrue(otherWorld.IsPrescribedAttribute("Sectors"));

			Attributed::ClearPrescribedAttributes();
		}

		TEST_METHOD(AssignmentOperator)
		{
			World world("Number1");
			world.CreateSector("Sector1");

			World otherWorld;
			otherWorld = world;

			Assert::IsTrue(otherWorld.Name() == world.Name());
			//Assert::IsTrue(otherWorld.Sectors() == world.Sectors());

			Assert::IsTrue(otherWorld.IsPrescribedAttribute("Name"));
			Assert::IsTrue(otherWorld.IsPrescribedAttribute("this"));
			Assert::IsTrue(otherWorld.IsPrescribedAttribute("Sectors"));

			Attributed::ClearPrescribedAttributes();
		}

		TEST_METHOD(MoveConstructor)
		{
			World world("Number1");
			world.CreateSector("Sector1");

			World otherWorld(move(world));

			Assert::IsTrue(otherWorld.Name() == "Number1");

			Assert::IsTrue(otherWorld.IsPrescribedAttribute("Name"));
			Assert::IsTrue(otherWorld.IsPrescribedAttribute("this"));
			Assert::IsTrue(otherWorld.IsPrescribedAttribute("Sectors"));

			Assert::IsTrue(world.Name() == string());

			Attributed::ClearPrescribedAttributes();
		}

		TEST_METHOD(MoveAssignmentOperator)
		{
			World world("Number1");
			world.CreateSector("Sector1");

			World otherWorld;
			otherWorld = move(world);

			Assert::IsTrue(otherWorld.Name() == "Number1");

			Assert::IsTrue(otherWorld.IsPrescribedAttribute("Name"));
			Assert::IsTrue(otherWorld.IsPrescribedAttribute("this"));
			Assert::IsTrue(otherWorld.IsPrescribedAttribute("Sectors"));

			Assert::IsTrue(world.Name() == string());

			Attributed::ClearPrescribedAttributes();
		}

		TEST_METHOD(Name)
		{
			World a("Thing");

			Assert::IsTrue(a.Name() == "Thing");

			const World* b = &a;

			Assert::IsTrue(b->Name() == "Thing");

			a.ClearPrescribedAttributes();
		}

		TEST_METHOD(SetName)
		{
			World a;

			a.SetName("Thing");

			Assert::IsTrue(a.Name() == "Thing");

			a.ClearPrescribedAttributes();
		}

		TEST_METHOD(Sectors)
		{
			World a;
			a.CreateSector("Sector");

			Datum& datum = a.Sectors();

			Assert::IsTrue(datum.Type() == DatumType::TABLE);
			Assert::IsTrue(datum.Get<Scope*&>()->Is("Sector"));

			const World* b = &a;

			datum = b->Sectors();

			Assert::IsTrue(datum.Type() == DatumType::TABLE);
			Assert::IsTrue(datum.Get<Scope*&>()->Is("Sector"));

			a.ClearPrescribedAttributes();
		}

		TEST_METHOD(CreateSector)
		{
			World a;

			Sector* b = a.CreateSector("Sector");

			Assert::IsTrue(b->Is("Sector"));
			Assert::IsTrue(b->Name() == "Sector");
			Assert::IsTrue(b->GetParent() == &a);

			a.ClearPrescribedAttributes();
		}

		TEST_METHOD(Update)
		{
			WorldState m;
			World s;
			Sector* e = s.CreateSector("Sector");

			Assert::IsTrue(m.mCurrentWorld == nullptr);
			Assert::IsTrue(m.mCurrentSector == nullptr);

			s.Update(m);

			Assert::IsTrue(m.mCurrentWorld == &s);
			Assert::IsTrue(m.mCurrentSector == e);

			s.ClearPrescribedAttributes();
		}


	private:
		static _CrtMemState sStartMemState;

	};
	_CrtMemState WorldTest::sStartMemState;
}