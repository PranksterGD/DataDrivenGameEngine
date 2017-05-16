#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTest;
using namespace std;

namespace LibraryDesktopTest
{
	TEST_CLASS(SectorTest)
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
			Sector a;

			Assert::IsTrue(a.IsPrescribedAttribute("Name"));
			Assert::IsTrue(a.IsPrescribedAttribute("this"));
			Assert::IsTrue(a.IsPrescribedAttribute("Entities"));

			Assert::IsNull(a.GetWorld());
			Assert::IsTrue(a.Name() == string());

			a.ClearPrescribedAttributes();
		}

		TEST_METHOD(CopyConstructor)
		{
			World world;

			Sector sector("Number1");
			sector.CreateEntity("Entity", "ThisEntity");

			sector.SetWorld(world);

			Sector otherSector(sector);

			Assert::IsTrue(otherSector.Name() == sector.Name());
			Assert::IsTrue(otherSector.GetWorld() == sector.GetWorld());

			Assert::IsTrue(otherSector.Entities().Get<Scope*&>()->Is("Entity"));
			Assert::IsTrue(otherSector.Entities() == sector.Entities());

			Assert::IsTrue(otherSector.IsPrescribedAttribute("Name"));
			Assert::IsTrue(otherSector.IsPrescribedAttribute("this"));
			Assert::IsTrue(otherSector.IsPrescribedAttribute("Entities"));

			Datum& datum = otherSector.Entities();
			datum;

			Assert::IsTrue(datum.Get<Scope*&>()->Is("Entity"));

			Attributed::ClearPrescribedAttributes();
		}

		TEST_METHOD(AssignmentOperator)
		{
			World world;

			Sector sector("Number1");

			sector.SetWorld(world);

			Sector otherSector;
			otherSector = sector;

			Assert::IsTrue(otherSector.Name() == sector.Name());
			Assert::IsTrue(otherSector.GetWorld() == sector.GetWorld());

			Assert::IsTrue(otherSector.IsPrescribedAttribute("Name"));
			Assert::IsTrue(otherSector.IsPrescribedAttribute("this"));
			Assert::IsTrue(otherSector.IsPrescribedAttribute("Entities"));

			Attributed::ClearPrescribedAttributes();
		}

		TEST_METHOD(MoveConstructor)
		{
			World world;

			Sector sector("Number1");

			sector.SetWorld(world);

			sector.CreateEntity("Entity", "ThisEntity");

			Sector othersector(move(sector));

			Assert::IsTrue(othersector.Name() == "Number1");
			Assert::IsTrue(othersector.GetWorld() == &world);

			Assert::IsTrue(othersector.IsPrescribedAttribute("Name"));
			Assert::IsTrue(othersector.IsPrescribedAttribute("this"));
			Assert::IsTrue(othersector.IsPrescribedAttribute("Entities"));

			Datum& datum = othersector.Entities();
			datum;

				Assert::IsTrue(datum.Get<Scope*&>()->Is("Entity"));

			Assert::IsTrue(sector.Name() == string());
			Assert::IsNull(sector.GetWorld());

			Attributed::ClearPrescribedAttributes();
		}

		TEST_METHOD(MoveAssignmentOperator)
		{
			World world;

			Sector sector("Number1");

			sector.SetWorld(world);

			Sector othersector;
			othersector = (move(sector));

			Assert::IsTrue(othersector.Name() == "Number1");
			Assert::IsTrue(othersector.GetWorld() == &world);

			Assert::IsTrue(othersector.IsPrescribedAttribute("Name"));
			Assert::IsTrue(othersector.IsPrescribedAttribute("this"));
			Assert::IsTrue(othersector.IsPrescribedAttribute("Entities"));

			Assert::IsTrue(sector.Name() == string());
			Assert::IsNull(sector.GetWorld());

			Attributed::ClearPrescribedAttributes();
		}

		TEST_METHOD(Name)
		{
			Sector a("Thing");

			Assert::IsTrue(a.Name() == "Thing");

			const Sector* b = &a;

			Assert::IsTrue(b->Name() == "Thing");

			a.ClearPrescribedAttributes();
		}

		TEST_METHOD(SetName)
		{
			Sector a;

			a.SetName("Thing");

			Assert::IsTrue(a.Name() == "Thing");

			a.ClearPrescribedAttributes();
		}

		TEST_METHOD(Entities)
		{
			Sector a;
			a.CreateEntity("Entity", "Number1");

			Datum& datum = a.Entities();

			Assert::IsTrue(datum.Type() == DatumType::TABLE);
			Assert::IsTrue(datum.Get<Scope*&>()->Is("Entity"));

			const Sector* b = &a;

			datum = b->Entities();

			Assert::IsTrue(datum.Type() == DatumType::TABLE);
			Assert::IsTrue(datum.Get<Scope*&>()->Is("Entity"));

			a.ClearPrescribedAttributes();
		}

		TEST_METHOD(CreateEntity)
		{
			Sector a;

			Entity* b = a.CreateEntity("Entity", "Number1");

			Assert::IsTrue(b->Is("Entity"));
			Assert::IsTrue(b->Name() == "Number1");
			Assert::IsTrue(b->GetParent() == &a);

			a.ClearPrescribedAttributes();
		}

		TEST_METHOD(SetWorld)
		{
			World s;

			Sector e;

			e.SetWorld(s);

			Assert::IsTrue(e.GetWorld() == &s);

			Assert::IsTrue(s.Sectors().Get<Scope*&>() == &e);
			s.ClearPrescribedAttributes();
			e.ClearPrescribedAttributes();
		}

		TEST_METHOD(GetWorld)
		{
			World s;
			Sector e;

			Assert::IsNull(e.GetWorld());

			e.SetWorld(s);

			const Sector* e2 = &e;

			Assert::IsTrue(e.GetWorld() == &s);
			Assert::IsTrue(e2->GetWorld() == &s);

			e.ClearPrescribedAttributes();
		}

		TEST_METHOD(Update)
		{
			WorldState m;
			Sector s;
			Entity* e = s.CreateEntity("Entity", "thing");

			Assert::IsTrue(m.mCurrentSector == nullptr);
			Assert::IsTrue(m.mCurrentEntity == nullptr);

			s.Update(m);

			Assert::IsTrue(m.mCurrentSector == &s);
			Assert::IsTrue(m.mCurrentEntity == e);

			s.ClearPrescribedAttributes();

		}

		TEST_METHOD(SectorRTTI)
		{
			Sector a;
			RTTI* r = &a;
			Assert::IsTrue(r->Is("Sector"));
			Assert::IsTrue(r->Is(Sector::TypeIdClass()));
			Assert::IsTrue(r->As<Sector>() != nullptr);
			Assert::IsTrue(a.TypeName() == "Sector");
			Assert::IsTrue(a.TypeIdClass() == Sector::TypeIdClass());
			Assert::IsTrue(r->TypeIdInstance() == Sector::TypeIdClass());
			RTTI* r2 = r->QueryInterface(Sector::TypeIdClass());
			Assert::IsTrue(r2->Is("Sector"));

			a.ClearPrescribedAttributes();
		}


	private:
		static _CrtMemState sStartMemState;

	};
	_CrtMemState SectorTest::sStartMemState;
}