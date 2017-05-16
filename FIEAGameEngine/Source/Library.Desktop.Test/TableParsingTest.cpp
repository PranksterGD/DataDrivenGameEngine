#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTest;
using namespace std;

namespace LibraryDesktopTest
{
	TEST_CLASS(TableParsingTest)
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

#pragma region ParseTesting

		TEST_METHOD(TestParsing)
		{
			XmlParseMaster master;

			XmlParseHelperTable::SharedData data;
			master.SetSharedData(&data);

			XmlParseHelperTable tableHelper;
			master.AddHelper(tableHelper);
			
			XmlParseHelperInteger intHelper;
			master.AddHelper(intHelper);

			XmlParseHelperFloat floatHelper;
			master.AddHelper(floatHelper);
			
			XmlParseHelperString stringHelper;
			master.AddHelper(stringHelper);

			XmlParseHelperVector vectorHelper;
			master.AddHelper(vectorHelper);

			XmlParseHelperMatrix matrixHelper;
			master.AddHelper(matrixHelper);

			master.ParseFromFile("../../../Scope.xml");

			Assert::IsTrue(data.Depth() == 0);

			Assert::IsTrue(data.mScope != nullptr);

			 Datum* datum =data.mScope->Find("Health");
			 Assert::IsTrue(datum != nullptr);
			 Assert::IsTrue(datum->Type() == DatumType::INTEGER);
			 Assert::IsTrue(datum->Get<int32_t&>(0) == 200);
			 Assert::IsTrue(datum->Get<int32_t&>(1) == 300);

			 datum = data.mScope->Find("Dps");
			 Assert::IsTrue(datum != nullptr);
			 Assert::IsTrue(datum->Type() == DatumType::FLOAT);
			 Assert::IsTrue(datum->Get<float&>(0) == 20.0f);

			 datum = data.mScope->Find("Name");
			 Assert::IsTrue(datum != nullptr);
			 Assert::IsTrue(datum->Type() == DatumType::STRING);
			 Assert::IsTrue(datum->Get<string&>(0) == "Soldier:76");

			 datum = data.mScope->Find("level2");
			 Assert::IsTrue(datum != nullptr);
			 Assert::IsTrue(datum->Type() == DatumType::TABLE);
			 Scope* scope = datum->Get<Scope*&>();

			 datum =scope->Find("Position");
			 Assert::IsTrue(datum != nullptr);
			 Assert::IsTrue(datum->Type() == DatumType::VECTOR);
			 Assert::IsTrue(datum->Get<glm::vec4&>(0) == glm::vec4(10.0f));

			 datum = scope->Search("thing");
			 Assert::IsTrue(datum != nullptr);
			 Assert::IsTrue(datum->Type() == DatumType::MATRIX);
			 Assert::IsTrue(datum->Get<glm::mat4&>(0) == glm::mat4(10.0f));
		}

		TEST_METHOD(TestExceptions)
		{
			XmlParseMaster master;

			XmlParseHelperTable::SharedData data;
			master.SetSharedData(&data);

			XmlParseHelperTable tableHelper;
			master.AddHelper(tableHelper);

			XmlParseHelperInteger intHelper;
			master.AddHelper(intHelper);

			XmlParseHelperFloat floatHelper;
			master.AddHelper(floatHelper);

			XmlParseHelperString stringHelper;
			master.AddHelper(stringHelper);

			XmlParseHelperVector vectorHelper;
			master.AddHelper(vectorHelper);

			XmlParseHelperMatrix matrixHelper;
			master.AddHelper(matrixHelper);
			
			const char* intText = "<integer name ='Health' value ='10' />";
			auto intException = [&master, intText] {master.Parse(intText, sizeof(intText)); };
			Assert::ExpectException<exception>(intException);

			const char* floatText = "<float name ='Health' value ='10.0' />";
			auto floatException = [&master, floatText] {master.Parse(floatText, sizeof(floatText)); };
			Assert::ExpectException<exception>(floatException);

			const char* stringText = "<string name ='Health' value ='Ten' />";
			auto stringException = [&master, stringText] {master.Parse(stringText, sizeof(stringText)); };
			Assert::ExpectException<exception>(stringException);

			const char* vectorText = "<string name ='Health' value ='10.0, 10.0, 10.0, 10.0' />";
			auto vectorException = [&master, vectorText] {master.Parse(vectorText, sizeof(vectorText)); };
			Assert::ExpectException<exception>(stringException);

			const char* matrixText = "<string name ='Health' value ='10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0' />";
			auto matrixException = [&master, matrixText] {master.Parse(matrixText, sizeof(matrixText)); };
			Assert::ExpectException<exception>(matrixException);
		}

#pragma  endregion ParseTesting

#pragma region HelperTesting

		TEST_METHOD(TestClones)
		{
			IXmlParseHelper* helper;

			XmlParseHelperInteger intHelper;
			helper = intHelper.Clone();
			XmlParseHelperInteger* intHelper2 = dynamic_cast<XmlParseHelperInteger*>(helper);
			Assert::IsTrue(intHelper2 != nullptr);
			delete(helper);

			XmlParseHelperFloat floatHelper;
			helper = floatHelper.Clone();
			XmlParseHelperFloat* floatHelper2 = dynamic_cast<XmlParseHelperFloat*>(helper);
			Assert::IsTrue(floatHelper2 != nullptr);
			delete(helper);

			XmlParseHelperString stringHelper;
			helper = stringHelper.Clone();
			XmlParseHelperString* stringHelper2 = dynamic_cast<XmlParseHelperString*>(helper);
			Assert::IsTrue(stringHelper2 != nullptr);
			delete(helper);

			XmlParseHelperVector vectorHelper;
			helper = vectorHelper.Clone();
			XmlParseHelperVector* vectorHelper2 = dynamic_cast<XmlParseHelperVector*>(helper);
			Assert::IsTrue(vectorHelper2 != nullptr);
			delete(helper);

			XmlParseHelperMatrix matrixHelper;
			helper = matrixHelper.Clone();
			XmlParseHelperMatrix* matrixHelper2 = dynamic_cast<XmlParseHelperMatrix*>(helper);
			Assert::IsTrue(matrixHelper2 != nullptr);
			delete(helper);
		}

#pragma endregion HelperTesting

#pragma region SharedDataTesting

		TEST_METHOD(SharedDataRTTI)
		{
			XmlParseHelperTable::SharedData data;
			RTTI* r = &data;

			Assert::IsTrue(r->Is("SharedData"));
			Assert::IsTrue(r->Is(XmlParseHelperTable::SharedData::TypeIdClass()));
			Assert::IsTrue(r->As<XmlParseHelperTable::SharedData >() != nullptr);
			Assert::IsTrue(data.TypeName() == "SharedData");
			Assert::IsTrue(data.TypeIdClass() == XmlParseHelperTable::SharedData::TypeIdClass());
			Assert::IsTrue(r->TypeIdInstance() == XmlParseHelperTable::SharedData::TypeIdClass());
			RTTI* r2 = r->QueryInterface(XmlParseHelperTable::SharedData::TypeIdClass());
			Assert::IsTrue(r2->Is("SharedData"));
		}

		TEST_METHOD(SharedDataInitialize)
		{
			XmlParseMaster master;

			XmlParseHelperTable::SharedData data;
			master.SetSharedData(&data);

			XmlParseHelperTable tableHelper;
			master.AddHelper(tableHelper);

			master.ParseFromFile("../../../Scope.xml");

			data.Initialize();

			Assert::IsTrue(data.mScope == nullptr);
		}

		TEST_METHOD(SharedDataClone)
		{
			XmlParseMaster master;

			XmlParseHelperTable::SharedData data;
			master.SetSharedData(&data);

			XmlParseHelperTable tableHelper;
			master.AddHelper(tableHelper);

			master.ParseFromFile("../../../Scope.xml");

			XmlParseMaster::SharedData* cloneData = data.Clone();

			XmlParseHelperTable::SharedData* otherData = cloneData->As<XmlParseHelperTable::SharedData>();

			Assert::IsTrue(otherData != nullptr);

			delete(cloneData);
		}


#pragma  endregion SharedDataTesting








	private:
		static _CrtMemState sStartMemState;

	};
	_CrtMemState TableParsingTest::sStartMemState;
}