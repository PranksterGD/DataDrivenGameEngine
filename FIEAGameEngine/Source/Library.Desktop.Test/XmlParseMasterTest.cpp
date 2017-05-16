#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTest;
using namespace std;

namespace LibraryDesktopTest
{
	TEST_CLASS(XmlParseMasterTest)
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

#pragma region MasterTesting

		TEST_METHOD(DefaultConstructor)
		{
			XmlParseMaster a;

			Assert::IsTrue(a.GetSharedData() == nullptr);
			Assert::IsTrue(a.GetFileName() == "");
		}

		TEST_METHOD(Clone)
		{
			XmlParseMaster a;
			
			XmlParseHelperFoo h;

			a.AddHelper(h);

			XmlParseMaster* b = a.Clone();
			delete(b);
		}

		TEST_METHOD(AddHelper)
		{
			XmlParseMaster a;
			XmlParseHelperFoo h;
		
			a.AddHelper(h);

			XmlParseMaster* b = a.Clone();

			auto expression = [b, &h] {b->AddHelper(h); };

			Assert::ExpectException<exception>(expression);

			delete(b);
		}

		TEST_METHOD(RemoveHelper)
		{
			XmlParseMaster a;
			XmlParseHelperFoo h;

			a.AddHelper(h);

			XmlParseMaster* b = a.Clone();

			a.RemoveHelper(h);

			auto expression = [b, &h] {b->RemoveHelper(h); };

			Assert::ExpectException<exception>(expression);

			delete(b);
		}

		TEST_METHOD(TestParsing)
		{
			XmlParseMaster a;

			XmlParseHelperFoo::SharedData b;
			a.SetSharedData(&b);

			const char* xml = "<Soldier name = 'Soldier:76' Health = '300'><Weapon Type = 'Shotgun' Ammo = '500' /><Position><X>200</X><Y>300</Y><Z>400</Z></Position></Soldier>";

			XmlParseHelperFoo h;
			a.AddHelper(h);

			a.Parse(xml, strlen(xml));

			Assert::AreEqual(h.MaxDepth(), 3U);

			Assert::AreEqual(h.StartElementHandlerCount(), 6U);

			Assert::AreEqual(h.EndElementHandlerCount(), 6U);
			
			Assert::AreEqual(h.CharDataHandlerCount(), 3U);

			Assert::IsTrue(h.IsInitialized());

			Assert::IsTrue(b.mHealth == 300);

			Assert::IsTrue(b.mAmmo == 500);

			Assert::AreEqual(b.mXPositon, 200);
			
			Assert::AreEqual(b.mYPosition, 300);

			Assert::AreEqual(b.mZPosition, 400);

			a.ParseFromFile("../../../Test.xml");

			Assert::AreEqual(h.MaxDepth(), 3U);

			Assert::IsTrue(h.IsInitialized());

			Assert::IsTrue(b.mHealth == 30);

			Assert::IsTrue(b.mAmmo == 50);

			Assert::AreEqual(b.mXPositon, 20);

			Assert::AreEqual(b.mYPosition, 30);

			Assert::AreEqual(b.mZPosition, 40);

			auto expression = [&a] {a.ParseFromFile("C:\\Users\\ssuresh\\Desktop\\Test2.xml"); };
			Assert::ExpectException<exception>(expression);

			const char* xml2 = "<Student>";

			auto expression2 = [&a, xml2] {a.Parse(xml2, strlen(xml2)); };
			Assert::ExpectException<exception>(expression2);
		}

		TEST_METHOD(GetFileName)
		{
			XmlParseMaster a;

			Assert::IsTrue(a.GetFileName() == "");

			XmlParseHelperFoo::SharedData b;
			a.SetSharedData(&b);

			XmlParseHelperFoo h;
			a.AddHelper(h);

			a.ParseFromFile("../../../Test.xml");

			Assert::IsTrue(a.GetFileName() == "../../../Test.xml");
		}

		TEST_METHOD(GetSharedData)
		{
			XmlParseMaster a;
			Assert::IsTrue(a.GetSharedData() == nullptr);

			XmlParseHelperFoo::SharedData b;
			XmlParseMaster c(&b);
			Assert::IsTrue(c.GetSharedData() == &b);
		}

		TEST_METHOD(SetSharedData)
		{
			XmlParseMaster a;
			Assert::IsTrue(a.GetSharedData() == nullptr);

			XmlParseHelperFoo::SharedData b;
			a.SetSharedData(&b);
			Assert::IsTrue(a.GetSharedData() == &b);
		}

#pragma  endregion MasterTesting

#pragma region SharedDataTesting
		
		TEST_METHOD(SharedDataDefaultConstructor)
		{
			XmlParseHelperFoo::SharedData a;

			Assert::IsTrue(a.mHealth == 0);
			Assert::IsTrue(a.mXPositon == 0);
			Assert::IsTrue(a.mYPosition == 0);
			Assert::IsTrue(a.mZPosition == 0);
			Assert::IsTrue(a.mAmmo == 0);
			Assert::IsTrue(a.Depth() == 0);

			Assert::IsTrue(a.GetXmlParseMaster() == nullptr);
		}

		TEST_METHOD(SharedDataIncrementDepth)
		{
			XmlParseHelperFoo::SharedData a;
			Assert::IsTrue(a.Depth() == 0);

			a.IncrementDepth();
			Assert::IsTrue(a.Depth() == 1);
		}

		TEST_METHOD(SharedDataDecrementDepth)
		{
			XmlParseHelperFoo::SharedData a;
			Assert::IsTrue(a.Depth() == 0);

			a.IncrementDepth();
			Assert::IsTrue(a.Depth() == 1);

			a.DecrementDepth();
			Assert::IsTrue(a.Depth() == 0);

			auto expression = [&a] {a.DecrementDepth(); };
			Assert::ExpectException<exception>(expression);
		}

		TEST_METHOD(SharedDataGetXmlParseMaster)
		{
			XmlParseHelperFoo::SharedData a;

			XmlParseMaster m(&a);

			Assert::IsTrue(a.GetXmlParseMaster() == &m);

			XmlParseHelperFoo::SharedData b;

			Assert::IsTrue(b.GetXmlParseMaster() == nullptr);
		}

		TEST_METHOD(SharedDataSetXmlParseMaster)
		{
			XmlParseMaster m;
			XmlParseHelperFoo::SharedData a;

			a.SetXmlParseMaster(&m);
			Assert::IsTrue(a.GetXmlParseMaster() == &m);
		}

		TEST_METHOD(SharedDataInitialize)
		{
			XmlParseMaster a;

			XmlParseHelperFoo::SharedData b;
			a.SetSharedData(&b);

			const char* xml = "<Soldier name = 'Soldier:76' Health = '300'><Weapon Type = 'Shotgun' Ammo = '500' /><Position><X>200</X><Y>300</Y><Z>400</Z></Position></Soldier>";

			XmlParseHelperFoo h;
			a.AddHelper(h);

			a.Parse(xml, strlen(xml));

			b.Initialize();

			Assert::IsTrue(b.mHealth == 0);

			Assert::IsTrue(b.mAmmo == 0);

			Assert::AreEqual(b.mXPositon, 0);

			Assert::AreEqual(b.mYPosition, 0);

			Assert::AreEqual(b.mZPosition, 0);

			Assert::AreEqual(b.Depth(), 0U);

		}

		TEST_METHOD(SharedDataClone)
		{
			XmlParseMaster a;

			XmlParseHelperFoo::SharedData b;
			a.SetSharedData(&b);

			const char* xml = "<Soldier name = 'Soldier:76' Health = '300'><Weapon Type = 'Shotgun' Ammo = '500' /><Position><X>200</X><Y>300</Y><Z>400</Z></Position></Soldier>";

			XmlParseHelperFoo h;
			a.AddHelper(h);

			a.Parse(xml, strlen(xml));

			XmlParseMaster::SharedData* c = b.Clone();

			XmlParseHelperFoo::SharedData* d = c->As<XmlParseHelperFoo::SharedData>();

			Assert::IsTrue(d != nullptr);

			delete(c);
		}

#pragma  endregion SharedDataTesting

#pragma region HelperTesting

		TEST_METHOD(HelperDefaultConstructor)
		{
			XmlParseHelperFoo a;

			Assert::AreEqual(a.MaxDepth(), 0U);

			Assert::AreEqual(a.StartElementHandlerCount(), 0U);

			Assert::AreEqual(a.EndElementHandlerCount(), 0U);

			Assert::AreEqual(a.CharDataHandlerCount(), 0U);

			Assert::IsFalse(a.IsInitialized());
		}

		TEST_METHOD(HelperInitialize)
		{
			XmlParseMaster a;

			XmlParseHelperFoo::SharedData b;
			a.SetSharedData(&b);

			const char* xml = "<Soldier name = 'Soldier:76' Health = '300'><Weapon Type = 'Shotgun' Ammo = '500' /><Position><X>200</X><Y>300</Y><Z>400</Z></Position></Soldier>";

			XmlParseHelperFoo h;
			a.AddHelper(h);

			a.Parse(xml, strlen(xml));

			h.Initialize(&a);

			Assert::AreEqual(h.MaxDepth(), 0U);

			Assert::AreEqual(h.StartElementHandlerCount(), 0U);

			Assert::AreEqual(h.EndElementHandlerCount(), 0U);

			Assert::AreEqual(h.CharDataHandlerCount(), 0U);

			Assert::IsTrue(h.IsInitialized());
		}

		TEST_METHOD(HelperStartElementHandler)
		{
			XmlParseHelperFoo h;

			XmlParseMaster a;

			h.Initialize(&a);

			Assert::IsFalse(h.StartElementHandler(string(), Hashmap<string, string>()));

			XmlParseMaster::SharedData b;
			a.SetSharedData(&b);
			Assert::IsFalse(h.StartElementHandler(string(), Hashmap<string, string>()));

			XmlParseHelperFoo::SharedData c;
			a.SetSharedData(&c);
			Assert::IsTrue(h.StartElementHandler(string(), Hashmap<string, string>()));
		}

		TEST_METHOD(HelperEndElementHandler)
		{
			XmlParseHelperFoo h;

			XmlParseMaster a;

			h.Initialize(&a);

			Assert::IsFalse(h.EndElementHandler(string()));

			XmlParseMaster::SharedData b;
			a.SetSharedData(&b);
			Assert::IsFalse(h.EndElementHandler(string()));

			XmlParseHelperFoo::SharedData c;
			a.SetSharedData(&c);
			Assert::IsTrue(h.EndElementHandler(string()));
		}

		TEST_METHOD(HelperCharElementHandler)
		{
			XmlParseHelperFoo h;

			XmlParseMaster a;

			h.Initialize(&a);

			Assert::IsFalse(h.CharDataHandler(string(), 0));

			XmlParseMaster::SharedData b;
			a.SetSharedData(&b);
			Assert::IsFalse(h.CharDataHandler(string(), 0));

			XmlParseHelperFoo::SharedData c;
			a.SetSharedData(&c);
			Assert::IsTrue(h.CharDataHandler(string(), 0));
		}

		TEST_METHOD(HelperClone)
		{
			XmlParseHelperFoo h;

			IXmlParseHelper* i = h.Clone();

			XmlParseHelperFoo* d = dynamic_cast<XmlParseHelperFoo*>(i);

			Assert::IsTrue(d != nullptr);

			delete(i);
		}


#pragma endregion HelperTesting

	private:
		static _CrtMemState sStartMemState;

	};
	_CrtMemState XmlParseMasterTest::sStartMemState;
}