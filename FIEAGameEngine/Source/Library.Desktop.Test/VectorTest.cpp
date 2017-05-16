#include "pch.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace FieaGameEngine;
using namespace UnitTest;
using namespace std;

namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			template<>
			wstring ToString<UnitTest::Foo>(const UnitTest::Foo& t)
			{
				RETURN_WIDE_STRING(t.GetData());
			}
		}
	}
}

namespace LibraryDesktopTest
{
	TEST_CLASS(VectorTest)
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

		//Creates empty lists of ints and strings and checks that their size is zero
		TEST_METHOD(VectorDefaultConstructor)
		{
			Vector<int32_t> intVector;
			Vector<int32_t*> pointerVector;
			Vector<Foo> fooVector;

			Assert::AreEqual(intVector.Size(), defaultSize);
			Assert::AreEqual(intVector.Capacity(), defaultCapacity);
			Assert::AreEqual(pointerVector.Size(), defaultSize);
			Assert::AreEqual(pointerVector.Capacity(), defaultCapacity);
			Assert::AreEqual(fooVector.Size(), defaultSize);
			Assert::AreEqual(fooVector.Capacity(), defaultCapacity);
		}

		TEST_METHOD(VectorIndexOperator)
		{
			
			Vector<int32_t> intVector;
			Vector<int32_t*> pointerVector;
			Vector<Foo> fooVector;

			auto intIndexException = [&intVector] {intVector[0]; };
			auto pointerIndexException = [&pointerVector] {pointerVector[0]; };
			auto fooIndexException = [&fooVector] {fooVector[0]; };

			Assert::ExpectException<exception>(intIndexException);
			Assert::ExpectException<exception>(pointerIndexException);
			Assert::ExpectException<exception>(fooIndexException);
	
			for (int i = 0; i < maxNumberOfElements; ++i)
			{
				intVector.PushBack(intTestVariableArray1[i]);
				pointerVector.PushBack(pointerTestVariableArray1[i]);
				fooVector.PushBack(fooTestVariableArray1[i]);

				Assert::AreEqual(intVector[i], intTestVariableArray1[i]);
				Assert::AreEqual(pointerVector[i], pointerTestVariableArray1[i]);
				Assert::AreEqual(fooVector[i], fooTestVariableArray1[i]);
			}

			const Vector<int32_t> &constIntVector = intVector;
			const Vector<int32_t*> &constPointerVector = pointerVector;
			const Vector<Foo> &constFooVector = fooVector;

			for (int i = 0; i < maxNumberOfElements; ++i)
			{
				Assert::AreEqual(constIntVector[i], intTestVariableArray1[i]);
				Assert::AreEqual(constPointerVector[i], pointerTestVariableArray1[i]);
				Assert::AreEqual(constFooVector[i], fooTestVariableArray1[i]);
			}
		}

		TEST_METHOD(VectorPopBack)
		{
			Vector<int32_t> intVector;
			Vector<int32_t*> pointerVector;
			Vector<Foo> fooVector;

			intVector.PopBack();
			pointerVector.PopBack();
			fooVector.PopBack();

			for (int i = 0; i < maxNumberOfElements; ++i)
			{
				intVector.PushBack(intTestVariableArray1[i]);
				pointerVector.PushBack(pointerTestVariableArray1[i]);
				fooVector.PushBack(fooTestVariableArray1[i]);
			}

			uint32_t intVectorSizeAfterPushes = intVector.Size();
			uint32_t pointerVectorSizeAfterPushes = pointerVector.Size();
			uint32_t fooVectorSizeAfterPushes = fooVector.Size();
			for (int i = 0; i < maxNumberOfElements; ++i)
			{
				intVector.PopBack();
				pointerVector.PopBack();
				fooVector.PopBack();

				Assert::AreEqual(intVector.Size(), intVectorSizeAfterPushes - i - 1);
				Assert::AreEqual(pointerVector.Size(), pointerVectorSizeAfterPushes - i - 1);
				Assert::AreEqual(fooVector.Size(), fooVectorSizeAfterPushes - i - 1);
			}
		}

		TEST_METHOD(VectorIsEmpty)
		{
			Vector<int32_t> intVector;
			Vector<int32_t*> pointerVector;
			Vector<Foo> fooVector;

			Assert::IsTrue(intVector.IsEmpty());
			Assert::IsTrue(pointerVector.IsEmpty());
			Assert::IsTrue(fooVector.IsEmpty());

			intVector.PushBack(intTestVariable1);
			pointerVector.PushBack(pointerTestVariable1);
			fooVector.PushBack(fooTestVariable1);

			Assert::IsFalse(intVector.IsEmpty());
			Assert::IsFalse(pointerVector.IsEmpty());
			Assert::IsFalse(fooVector.IsEmpty());
		}

		TEST_METHOD(VectorFront)
		{
			Vector<int32_t> intVector;
			Vector<int32_t*> pointerVector;
			Vector<Foo> fooVector;

			auto intFrontException = [&intVector] {intVector.Front(); };
			auto pointerFrontException = [&pointerVector] {pointerVector.Front(); };
			auto fooFrontException = [&fooVector] {fooVector.Front(); };

			Assert::ExpectException<exception>(intFrontException);
			Assert::ExpectException<exception>(pointerFrontException);
			Assert::ExpectException<exception>(fooFrontException);

			for (int i = 0; i < maxNumberOfElements; ++i)
			{
				intVector.PushBack(intTestVariableArray1[i]);
				pointerVector.PushBack(pointerTestVariableArray1[i]);
				fooVector.PushBack(fooTestVariableArray1[i]);

				Assert::AreEqual(intVector.Front(), intTestVariableArray1[0]);
				Assert::AreEqual(pointerVector.Front(), pointerTestVariableArray1[0]);
				Assert::AreEqual(fooVector.Front(), fooTestVariableArray1[0]);
			}

			const Vector<int32_t> &constIntVector = intVector;
			const Vector<int32_t*> &constPointerVector = pointerVector;
			const Vector<Foo> &constFooVector = fooVector;

			Assert::AreEqual(constIntVector.Front(), intTestVariable1);
			Assert::AreEqual(constPointerVector.Front(), pointerTestVariable1);
			Assert::AreEqual(constFooVector.Front(), fooTestVariable1);
		}

		TEST_METHOD(VectorBack)
		{
			Vector<int32_t> intVector;
			Vector<int32_t*> pointerVector;
			Vector<Foo> fooVector;

			auto intBackException = [&intVector] {intVector.Back(); };
			auto pointerBackException = [&pointerVector] {pointerVector.Back(); };
			auto fooBackException = [&fooVector] {fooVector.Back(); };

			Assert::ExpectException<exception>(intBackException);
			Assert::ExpectException<exception>(pointerBackException);
			Assert::ExpectException<exception>(fooBackException);

			for (int i = 0; i < maxNumberOfElements; ++i)
			{
				intVector.PushBack(intTestVariableArray1[i]);
				pointerVector.PushBack(pointerTestVariableArray1[i]);
				fooVector.PushBack(fooTestVariableArray1[i]);

				Assert::AreEqual(intVector.Back(), intTestVariableArray1[i]);
				Assert::AreEqual(pointerVector.Back(), pointerTestVariableArray1[i]);
				Assert::AreEqual(fooVector.Back(), fooTestVariableArray1[i]);
			}

			const Vector<int32_t> &constIntVector = intVector;
			const Vector<int32_t*> &constPointerVector = pointerVector;
			const Vector<Foo> &constFooVector = fooVector;

			Assert::AreEqual(constIntVector.Back(), intTestVariable3);
			Assert::AreEqual(constPointerVector.Back(), pointerTestVariable3);
			Assert::AreEqual(constFooVector.Back(), fooTestVariable3);
		}

		TEST_METHOD(VectorSize)
		{
			Vector<int32_t> intVector;
			Vector<int32_t*> pointerVector;
			Vector<Foo> fooVector;

			Assert::AreEqual(intVector.Size(), defaultSize);
			Assert::AreEqual(pointerVector.Size(), defaultSize);
			Assert::AreEqual(fooVector.Size(), defaultSize);

			for (int i = 0; i < maxNumberOfElements; ++i)
			{
				intVector.PushBack(intTestVariableArray1[i]);
				pointerVector.PushBack(pointerTestVariableArray1[i]);
				fooVector.PushBack(fooTestVariableArray1[i]);

				Assert::AreEqual(intVector.Size(),(uint32_t) i + 1);
				Assert::AreEqual(pointerVector.Size(), (uint32_t) i + 1);
				Assert::AreEqual(fooVector.Size(), i + (uint32_t) 1);
			}
		}

		TEST_METHOD(VectorCapacity)
		{
			Vector<int32_t> intVector;
			Vector<int32_t*> pointerVector;
			Vector<Foo> fooVector;

			Assert::AreEqual(intVector.Capacity(), defaultCapacity);
			Assert::AreEqual(pointerVector.Capacity(), defaultCapacity);
			Assert::AreEqual(fooVector.Capacity(), defaultCapacity);

			for (int i = 0; i < maxNumberOfElements; ++i)
			{
				intVector.PushBack(intTestVariableArray1[i]);
				pointerVector.PushBack(pointerTestVariableArray1[i]);
				fooVector.PushBack(fooTestVariableArray1[i]);

				Assert::AreEqual(intVector.Capacity(), defaultCapacity);
				Assert::AreEqual(pointerVector.Capacity(), defaultCapacity);
				Assert::AreEqual(fooVector.Capacity(), defaultCapacity);
			}

			uint32_t newCapacity = 1;
			intVector.Reserve(newCapacity);
			pointerVector.Reserve(newCapacity);
			pointerVector.Reserve(newCapacity);

			Assert::AreEqual(intVector.Capacity(), defaultCapacity);
			Assert::AreEqual(pointerVector.Capacity(), defaultCapacity);
			Assert::AreEqual(fooVector.Capacity(), defaultCapacity);

			newCapacity = 5;

			intVector.Reserve(newCapacity);
			pointerVector.Reserve(newCapacity);
			fooVector.Reserve(newCapacity);

			Assert::AreEqual(intVector.Capacity(), newCapacity);
			Assert::AreEqual(pointerVector.Capacity(), newCapacity);
			Assert::AreEqual(fooVector.Capacity(), newCapacity);
		}

		TEST_METHOD(VectorBegin)
		{
			Vector<int32_t> intVector;
			Vector<int32_t*> pointerVector;
			Vector<Foo> fooVector;
			Vector<int32_t>::Iterator intIt;
			Vector<int32_t*>::Iterator pointerIt;
			Vector<Foo>::Iterator fooIt;

			intIt = intVector.begin();
			pointerIt = pointerVector.begin();
			fooIt = fooVector.begin();

			Assert::IsTrue(intIt == intVector.end());
			Assert::IsTrue(pointerIt == pointerVector.end());
			Assert::IsTrue(fooIt == fooVector.end());

			for (int i = 0; i < maxNumberOfElements; ++i)
			{
				intVector.PushBack(intTestVariableArray1[i]);
				pointerVector.PushBack(pointerTestVariableArray1[i]);
				fooVector.PushBack(fooTestVariableArray1[i]);

				intIt = intVector.begin();
				pointerIt = pointerVector.begin();
				fooIt = fooVector.begin();

				Assert::IsTrue(*intIt == intVector[0]);
				Assert::IsTrue(*pointerIt == pointerVector[0]);
				Assert::IsTrue(*fooIt == fooVector[0]);
			}
		}

		TEST_METHOD(VectorEnd)
		{
			Vector<int32_t> intVector;
			Vector<int32_t*> pointerVector;
			Vector<Foo> fooVector;
			Vector<int32_t>::Iterator intIt;
			Vector<int32_t*>::Iterator pointerIt;
			Vector<Foo>::Iterator fooIt;

			intIt = intVector.end();
			pointerIt = pointerVector.end();
			fooIt = fooVector.end();

			Assert::IsTrue(intIt == intVector.begin());
			Assert::IsTrue(pointerIt == pointerVector.begin());
			Assert::IsTrue(fooIt == fooVector.begin());

			auto intEndException = [&intIt] {*intIt; };
			auto pointerEndException = [&pointerIt] {*pointerIt; };
			auto fooEndException = [&fooIt] {*fooIt; };

			for (int i = 0; i < maxNumberOfElements; ++i)
			{
				intVector.PushBack(intTestVariableArray1[i]);
				pointerVector.PushBack(pointerTestVariableArray1[i]);
				fooVector.PushBack(fooTestVariableArray1[i]);

				intIt = intVector.end();
				pointerIt = pointerVector.end();
				fooIt = fooVector.end();

				Assert::ExpectException<exception>(intEndException);
				Assert::ExpectException<exception>(pointerEndException);
				Assert::ExpectException<exception>(fooEndException);
			}
		}

		TEST_METHOD(VectorPushBack)
		{
			Vector<int32_t> intVector;
			Vector<int32_t*> pointerVector;
			Vector<Foo> fooVector;
			Vector<int32_t>::Iterator intIt;
			Vector<int32_t*>::Iterator pointerIt;
			Vector<Foo>::Iterator fooIt;

			for (int i = 0; i < maxNumberOfElements; ++i)
			{
				intVector.PushBack(intTestVariableArray1[i]);
				pointerVector.PushBack(pointerTestVariableArray1[i]);
				fooVector.PushBack(fooTestVariableArray1[i]);

				Assert::AreEqual(intVector[i], intTestVariableArray1[i]);
				Assert::AreEqual(pointerVector[i], pointerTestVariableArray1[i]);
				Assert::AreEqual(fooVector[i], fooTestVariableArray1[i]);

				Assert::AreEqual(intVector.Size(), (uint32_t) i + 1);
				Assert::AreEqual(pointerVector.Size(), (uint32_t)i + 1);
				Assert::AreEqual(fooVector.Size(), (uint32_t)i + 1);
			}
			intVector.PushBack(intTestVariable1);
			pointerVector.PushBack(pointerTestVariable1);
			fooVector.PushBack(fooTestVariable1);

			Assert::AreEqual(intVector[maxNumberOfElements], intTestVariable1);
			Assert::AreEqual(pointerVector[maxNumberOfElements], pointerTestVariable1);
			Assert::AreEqual(fooVector[maxNumberOfElements], fooTestVariable1);

			Assert::AreEqual(intVector.Size(), (uint32_t)maxNumberOfElements + 1);
			Assert::AreEqual(pointerVector.Size(), (uint32_t)maxNumberOfElements + 1);
			Assert::AreEqual(fooVector.Size(), (uint32_t)maxNumberOfElements + 1);
		};

		TEST_METHOD(VectorCopyConstructor)
		{
			Vector<int32_t> intVector;
			Vector<int32_t*> pointerVector;
			Vector<Foo> fooVector;

			for (int i = 0; i < maxNumberOfElements; ++i)
			{
				intVector.PushBack(intTestVariableArray1[i]);
				pointerVector.PushBack(pointerTestVariableArray1[i]);
				fooVector.PushBack(fooTestVariableArray1[i]);
			}

			Vector<int32_t> intVector2 = intVector;
			Vector<int32_t*> pointerVector2 = pointerVector;
			Vector<Foo> fooVector2 = fooVector;

			Assert::AreEqual(intVector.Size(), intVector2.Size());
			Assert::AreEqual(pointerVector.Size(), pointerVector2.Size());
			Assert::AreEqual(fooVector.Size(), fooVector2.Size());

			Assert::AreEqual(intVector.Capacity(), intVector2.Capacity());
			Assert::AreEqual(pointerVector.Capacity(), pointerVector2.Capacity());
			Assert::AreEqual(fooVector.Capacity(), fooVector2.Capacity());	

			int i = 0;
			for (int32_t data : intVector)
			{
				Assert::AreEqual(data, intVector2[i++]);
			}

			i = 0;
			for (int32_t* data : pointerVector)
			{
				Assert::AreEqual(data, pointerVector2[i++]);
			}

			i = 0;
			for (Foo data : fooVector)
			{
				Assert::AreEqual(data, fooVector2[i++]);
			}
		}

		TEST_METHOD(VectorMoveCopyConstructor)
		{
			Vector<int32_t> intVector;
			Vector<int32_t*> pointerVector;
			Vector<Foo> fooVector;

			for (int i = 0; i < maxNumberOfElements; ++i)
			{
				intVector.PushBack(intTestVariableArray1[i]);
				pointerVector.PushBack(pointerTestVariableArray1[i]);
				fooVector.PushBack(fooTestVariableArray1[i]);
			}

			Vector<int32_t> intVector2 = move(intVector);
			Vector<int32_t*> pointerVector2 = move(pointerVector);
			Vector<Foo> fooVector2 = move(fooVector);

			Assert::IsTrue(intVector.IsEmpty());
			Assert::IsTrue(pointerVector.IsEmpty());
			Assert::IsTrue(fooVector.IsEmpty());

			int i = 0;
			for (int32_t data : intVector2)
			{
				Assert::AreEqual(intTestVariableArray1[i++], data);
				data;
			}

			i = 0;
			for (int32_t* data : pointerVector2)
			{
				Assert::AreEqual(pointerTestVariableArray1[i++], data);
			}

			i = 0;
			for (Foo data : fooVector2)
			{
				Assert::AreEqual(fooTestVariableArray1[i++], data);
			}
		}

		TEST_METHOD(VectorAssignmentOperator)
		{
			Vector<int32_t> intVector;
			Vector<int32_t*> pointerVector;
			Vector<Foo> fooVector;
			Vector<int32_t> intVector2;
			Vector<int32_t*> pointerVector2;
			Vector<Foo> fooVector2;

			for (int i = 0; i < maxNumberOfElements; ++i)
			{
				intVector.PushBack(intTestVariableArray1[i]);
				pointerVector.PushBack(pointerTestVariableArray1[i]);
				fooVector.PushBack(fooTestVariableArray1[i]);
			}

			intVector2 = intVector;
			pointerVector2 = pointerVector;
			fooVector2 = fooVector;

			Assert::AreEqual(intVector.Size(), intVector2.Size());
			Assert::AreEqual(pointerVector.Size(), pointerVector2.Size());
			Assert::AreEqual(fooVector.Size(), fooVector2.Size());

			Assert::AreEqual(intVector.Capacity(), intVector2.Capacity());
			Assert::AreEqual(pointerVector.Capacity(), pointerVector2.Capacity());
			Assert::AreEqual(fooVector.Capacity(), fooVector2.Capacity());

			int i = 0;
			for (int32_t data : intVector)
			{
				Assert::AreEqual(data, intVector2[i++]);
			}

			i = 0;
			for (int32_t* data : pointerVector)
			{
				Assert::AreEqual(data, pointerVector2[i++]);
			}

			i = 0;
			for (Foo data : fooVector)
			{
				Assert::AreEqual(data, fooVector2[i++]);
			}
		}

		TEST_METHOD(VectorMoveAssignmentConstructor)
		{
			Vector<int32_t> intVector;
			Vector<int32_t*> pointerVector;
			Vector<Foo> fooVector;

			for (int i = 0; i < maxNumberOfElements; ++i)
			{
				intVector.PushBack(intTestVariableArray1[i]);
				pointerVector.PushBack(pointerTestVariableArray1[i]);
				fooVector.PushBack(fooTestVariableArray1[i]);
			}

			Vector<int32_t> intVector2;
			Vector<int32_t*> pointerVector2;
			Vector<Foo> fooVector2;

			intVector2 = move(intVector);
			pointerVector2 = move(pointerVector);
			fooVector2 = move(fooVector);


			Assert::IsTrue(intVector.IsEmpty());
			Assert::IsTrue(pointerVector.IsEmpty());
			Assert::IsTrue(fooVector.IsEmpty());

			int i = 0;
			for (int32_t data : intVector2)
			{
				Assert::AreEqual(intTestVariableArray1[i++], data);
				data;
			}

			i = 0;
			for (int32_t* data : pointerVector2)
			{
				Assert::AreEqual(pointerTestVariableArray1[i++], data);
			}

			i = 0;
			for (Foo data : fooVector2)
			{
				Assert::AreEqual(fooTestVariableArray1[i++], data);
			}
		}

		TEST_METHOD(VectorAt)
		{

			Vector<int32_t> intVector;
			Vector<int32_t*> pointerVector;
			Vector<Foo> fooVector;

			auto intIndexException = [&intVector] {intVector.At(0); };
			auto pointerIndexException = [&pointerVector] {pointerVector.At(0); };
			auto fooIndexException = [&fooVector] {fooVector.At(0); };

			Assert::ExpectException<exception>(intIndexException);
			Assert::ExpectException<exception>(pointerIndexException);
			Assert::ExpectException<exception>(fooIndexException);

			for (int i = 0; i < maxNumberOfElements; ++i)
			{
				intVector.PushBack(intTestVariableArray1[i]);
				pointerVector.PushBack(pointerTestVariableArray1[i]);
				fooVector.PushBack(fooTestVariableArray1[i]);

				Assert::AreEqual(intVector.At(i), intTestVariableArray1[i]);
				Assert::AreEqual(pointerVector.At(i), pointerTestVariableArray1[i]);
				Assert::AreEqual(fooVector.At(i), fooTestVariableArray1[i]);
			}

			const Vector<int32_t> &constIntVector = intVector;
			const Vector<int32_t*> &constPointerVector = pointerVector;
			const Vector<Foo> &constFooVector = fooVector;

			Assert::AreEqual(constIntVector.At(0), intTestVariableArray1[0]);
			Assert::AreEqual(constPointerVector.At(0), pointerTestVariableArray1[0]);
			Assert::AreEqual(constFooVector.At(0), fooTestVariableArray1[0]);
		}

		TEST_METHOD(VectorReserve)
		{
			
				Vector<int32_t> intVector;
				Vector<int32_t*> pointerVector;
				Vector<Foo> fooVector;

				for (int i = 0; i < maxNumberOfElements; ++i)
				{
					intVector.PushBack(intTestVariableArray1[i]);
					pointerVector.PushBack(pointerTestVariableArray1[i]);
					fooVector.PushBack(fooTestVariableArray1[i]);
				}

				uint32_t newCapacity = 1;
				intVector.Reserve(newCapacity);
				pointerVector.Reserve(newCapacity);
				pointerVector.Reserve(newCapacity);

				Assert::AreEqual(intVector.Capacity(), defaultCapacity);
				Assert::AreEqual(pointerVector.Capacity(), defaultCapacity);
				Assert::AreEqual(fooVector.Capacity(), defaultCapacity);

				newCapacity = 5;

				intVector.Reserve(newCapacity);
				pointerVector.Reserve(newCapacity);
				fooVector.Reserve(newCapacity);

				Assert::AreEqual(intVector.Capacity(), newCapacity);
				Assert::AreEqual(pointerVector.Capacity(), newCapacity);
				Assert::AreEqual(fooVector.Capacity(), newCapacity);
			}

		TEST_METHOD(VectorFind)
		{
			Vector<int32_t> intVector;
			Vector<int32_t*> pointerVector;
			Vector<Foo> fooVector;
			Vector<int32_t>::Iterator intIt;
			Vector<int32_t*>::Iterator pointerIt;
			Vector<Foo>::Iterator fooIt;

			intIt = intVector.Find(intTestVariable1);
			pointerIt = pointerVector.Find(pointerTestVariable1);
			fooIt = fooVector.Find(fooTestVariable1);

			Assert::IsTrue(intIt == intVector.end());
			Assert::IsTrue(pointerIt == pointerVector.end());
			Assert::IsTrue(fooIt == fooVector.end());

			for (int i = 0; i < maxNumberOfElements; ++i)
			{
				intVector.PushBack(intTestVariableArray1[i]);
				pointerVector.PushBack(pointerTestVariableArray1[i]);
				fooVector.PushBack(fooTestVariableArray1[i]);

				intIt = intVector.Find(intTestVariableArray1[i]);
				pointerIt = pointerVector.Find(pointerTestVariableArray1[i]);
				fooIt = fooVector.Find(fooTestVariableArray1[i]);

				Assert::AreEqual(*intIt, intTestVariableArray1[i]);
				Assert::AreEqual(*pointerIt, pointerTestVariableArray1[i]);
				Assert::AreEqual(*fooIt, fooTestVariableArray1[i]);
			}
		}

		TEST_METHOD(VectorRemove)
		{
			Vector<int32_t> intVector;
			Vector<int32_t*> pointerVector;
			Vector<Foo> fooVector;

			intVector.Remove(intTestVariable1);
			pointerVector.Remove(pointerTestVariable1);
			fooVector.Remove(fooTestVariable1);

			for (int i = 0; i < maxNumberOfElements; ++i)
			{
				intVector.PushBack(intTestVariableArray1[i]);
				pointerVector.PushBack(pointerTestVariableArray1[i]);
				fooVector.PushBack(fooTestVariableArray1[i]);
			}

			Assert::AreEqual(intVector.Size(), maxNumberOfElements) ;
			Assert::AreEqual(pointerVector.Size(), maxNumberOfElements );
			Assert::AreEqual(fooVector.Size(), maxNumberOfElements );

			for (int i = 0; i < maxNumberOfElements; ++i)
			{
				intVector.Remove(intTestVariableArray1[i]);
				pointerVector.Remove(pointerTestVariableArray1[i]);
				fooVector.Remove(fooTestVariableArray1[i]);

				Assert::AreEqual(intVector.Size(), maxNumberOfElements - i - 1);
				Assert::AreEqual(pointerVector.Size(), maxNumberOfElements - i - 1);
				Assert::AreEqual(fooVector.Size(), maxNumberOfElements - i - 1);
			}
		}

		TEST_METHOD(VectorRangeRemove)
		{
			Vector<int32_t> intVector;
			Vector<int32_t*> pointerVector;
			Vector<Foo> fooVector;
			Vector<int32_t> intVector2;
			Vector<int32_t*> pointerVector2;
			Vector<Foo> fooVector2;

			for (int i = 0; i < maxNumberOfElements; ++i)
			{
				intVector.PushBack(intTestVariableArray1[i]);
				pointerVector.PushBack(pointerTestVariableArray1[i]);
				fooVector.PushBack(fooTestVariableArray1[i]);
			}

			intVector2 = intVector;
			pointerVector2 = pointerVector;
			fooVector2 = fooVector;

			Vector<int32_t>::Iterator intIt;
			Vector<int32_t*>::Iterator pointerIt;
			Vector<Foo>::Iterator fooIt;
			Vector<int32_t>::Iterator intIt2;
			Vector<int32_t*>::Iterator pointerIt2;
			Vector<Foo>::Iterator fooIt2;

			intIt2 = intVector.begin();
			pointerIt2 = pointerVector.begin();
			fooIt2 = fooVector.begin();

			intIt = intIt2++;
			pointerIt = pointerIt2++;
			fooIt = fooIt2++;

			intVector.Remove(intIt, intIt2);
			pointerVector.Remove(pointerIt, pointerIt2);
			fooVector.Remove(fooIt, fooIt2);

			Assert::AreEqual((uint32_t)1, intVector.Size());
			Assert::AreEqual((uint32_t)1, pointerVector.Size());
			Assert::AreEqual((uint32_t)1, fooVector.Size());

			intVector = intVector2;
			pointerVector = pointerVector2;
			fooVector = fooVector2;

			intIt2 = intVector.begin();
			pointerIt2 = pointerVector.begin();
			fooIt2 = fooVector.begin();

			intIt = intIt2++;
			pointerIt = pointerIt2++;
			fooIt = fooIt2++;

			++intIt2;
			++pointerIt2;
			++fooIt2;

			intVector.Remove(intIt, intIt2);
			pointerVector.Remove(pointerIt, pointerIt2);
			fooVector.Remove(fooIt, fooIt2);

			Assert::AreEqual((uint32_t)0, intVector.Size());
			Assert::AreEqual((uint32_t)0, pointerVector.Size());
			Assert::AreEqual((uint32_t)0, fooVector.Size());

			intVector = intVector2;
			pointerVector = pointerVector2;
			fooVector = fooVector2;

			intIt2 = intVector.begin();
			pointerIt2 = pointerVector.begin();
			fooIt2 = fooVector.begin();

			intIt = intIt2++;
			pointerIt = pointerIt2++;
			fooIt = fooIt2++;

			intVector.Remove(intIt2, intIt);
			pointerVector.Remove(pointerIt2, pointerIt);
			fooVector.Remove(fooIt2, fooIt);

			Assert::AreEqual((uint32_t)3, intVector.Size());
			Assert::AreEqual((uint32_t)3, pointerVector.Size());
			Assert::AreEqual((uint32_t)3, fooVector.Size());

		}

		TEST_METHOD(VectorShrinkToFit)
		{
			Vector<int32_t> intVector;
			Vector<int32_t*> pointerVector;
			Vector<Foo> fooVector;

			intVector.ShrinkToFit();
			pointerVector.ShrinkToFit();
			fooVector.ShrinkToFit();

			Assert::AreEqual(intVector.Capacity(), (uint32_t)0);
			Assert::AreEqual(pointerVector.Capacity(), (uint32_t)0);
			Assert::AreEqual(fooVector.Capacity(), (uint32_t)0);
		}

		TEST_METHOD(IteratorDefaultConstructor)
		{
			Vector<int32_t>::Iterator intIt;
			Vector<int32_t*>::Iterator pointerIt;
			Vector<Foo>::Iterator fooIt;
			Vector<int32_t>::Iterator intIt2;
			Vector<int32_t*>::Iterator pointerIt2;
			Vector<Foo>::Iterator fooIt2;

			Vector<int32_t> intVector;
			Vector<int32_t*> pointerVector;
			Vector<Foo> fooVector;

			Assert::IsTrue(intIt == intIt2);
			Assert::IsTrue(pointerIt == pointerIt2);
			Assert::IsTrue(fooIt ==fooIt2);

			intIt2 = intVector.begin();
			pointerIt2 = pointerVector.begin();
			fooIt2 = fooVector.begin();

			Assert::IsFalse(intIt == intIt2);
			Assert::IsFalse(pointerIt == pointerIt2);
			Assert::IsFalse(fooIt == fooIt2);
		}

		TEST_METHOD(IteratorCopyConstructor)
		{
			Vector<int32_t>::Iterator intIt;
			Vector<int32_t*>::Iterator pointerIt;
			Vector<Foo>::Iterator fooIt;

			Vector<int32_t> intVector;
			Vector<int32_t*> pointerVector;
			Vector<Foo> fooVector;

			intVector.PushBack(intTestVariable1);
			pointerVector.PushBack(pointerTestVariable1);
			fooVector.PushBack(fooTestVariable1);

			intIt = intVector.begin();
			pointerIt = pointerVector.begin();
			fooIt = fooVector.begin();

			Vector<int32_t>::Iterator intIt2(intIt);
			Vector<int32_t*>::Iterator pointerIt2(pointerIt);
			Vector<Foo>::Iterator fooIt2(fooIt);

			Assert::IsTrue(intIt == intIt2);
			Assert::IsTrue(pointerIt == pointerIt2);
			Assert::IsTrue(fooIt == fooIt2);
		}

		TEST_METHOD(IteratorAssignment)
		{
			Vector<int32_t>::Iterator intIt;
			Vector<int32_t*>::Iterator pointerIt;
			Vector<Foo>::Iterator fooIt;
			Vector<int32_t>::Iterator intIt2;
			Vector<int32_t*>::Iterator pointerIt2;
			Vector<Foo>::Iterator fooIt2;

			Vector<int32_t> intVector;
			Vector<int32_t*> pointerVector;
			Vector<Foo> fooVector;

			intVector.PushBack(intTestVariable1);
			pointerVector.PushBack(pointerTestVariable1);
			fooVector.PushBack(fooTestVariable1);

			intIt = intVector.begin();
			pointerIt = pointerVector.begin();
			fooIt = fooVector.begin();

			intIt2 = intIt;
			pointerIt2 = pointerIt;
			fooIt2 = fooIt;

			Assert::IsTrue(intIt == intIt2);
			Assert::IsTrue(pointerIt == pointerIt2);
			Assert::IsTrue(fooIt == fooIt2);
		}

		TEST_METHOD(IteratorEquality)
		{
			Vector<int32_t>::Iterator intIt;
			Vector<int32_t*>::Iterator pointerIt;
			Vector<Foo>::Iterator fooIt;
			Vector<int32_t>::Iterator intIt2;
			Vector<int32_t*>::Iterator pointerIt2;
			Vector<Foo>::Iterator fooIt2;

			Vector<int32_t> intVector;
			Vector<int32_t*> pointerVector;
			Vector<Foo> fooVector;

			Assert::IsTrue(intIt == intIt2);
			Assert::IsTrue(pointerIt == pointerIt2);
			Assert::IsTrue(fooIt == fooIt2);

			intVector.PushBack(intTestVariable1);
			pointerVector.PushBack(pointerTestVariable1);
			fooVector.PushBack(fooTestVariable1);

			intIt = intVector.begin();
			pointerIt = pointerVector.begin();
			fooIt = fooVector.begin();

			Assert::IsFalse(intIt == intIt2);
			Assert::IsFalse(pointerIt == pointerIt2);
			Assert::IsFalse(fooIt == fooIt2);

			intIt2 = intVector.begin();
			pointerIt2 = pointerVector.begin();
			fooIt2 = fooVector.begin();

			Assert::IsTrue(intIt == intIt2);
			Assert::IsTrue(pointerIt == pointerIt2);
			Assert::IsTrue(fooIt == fooIt2);
		}

		TEST_METHOD(VectorInequality)
		{
			Vector<int32_t>::Iterator intIt;
			Vector<int32_t*>::Iterator pointerIt;
			Vector<Foo>::Iterator fooIt;
			Vector<int32_t>::Iterator intIt2;
			Vector<int32_t*>::Iterator pointerIt2;
			Vector<Foo>::Iterator fooIt2;

			Vector<int32_t> intVector;
			Vector<int32_t*> pointerVector;
			Vector<Foo> fooVector;

			intIt = intVector.begin();
			pointerIt = pointerVector.begin();
			fooIt = fooVector.begin();

			Assert::IsTrue(intIt != intIt2);
			Assert::IsTrue(pointerIt != pointerIt2);
			Assert::IsTrue(fooIt != fooIt2);

			intIt2 = intVector.begin();
			pointerIt2 = pointerVector.begin();
			fooIt2 = fooVector.begin();

			Assert::IsFalse(intIt != intIt2);
			Assert::IsFalse(pointerIt != pointerIt2);
			Assert::IsFalse(fooIt != fooIt2);

			intVector.PushBack(intTestVariable1);
			pointerVector.PushBack(pointerTestVariable1);
			fooVector.PushBack(fooTestVariable1);

			intIt = intVector.begin();
			pointerIt = pointerVector.begin();
			fooIt = fooVector.begin();

			Assert::IsFalse(intIt != intIt2);
			Assert::IsFalse(pointerIt != pointerIt2);
			Assert::IsFalse(fooIt != fooIt2);
		}

		TEST_METHOD(IteratorPreIncrement)
		{
			Vector<int32_t>::Iterator intIt;
			Vector<int32_t*>::Iterator pointerIt;
			Vector<Foo>::Iterator fooIt;
			Vector<int32_t>::Iterator intIt2;
			Vector<int32_t*>::Iterator pointerIt2;
			Vector<Foo>::Iterator fooIt2;

			Vector<int32_t> intVector;
			Vector<int32_t*> pointerVector;
			Vector<Foo> fooVector;

			for (int i = 0; i < maxNumberOfElements; ++i)
			{
				intVector.PushBack(intTestVariableArray1[i]);
				pointerVector.PushBack(pointerTestVariableArray1[i]);
				fooVector.PushBack(fooTestVariableArray1[i]);
			}

			intIt = intVector.begin();
			intIt2 = ++intIt;
			pointerIt = pointerVector.begin();
			pointerIt2 = ++pointerIt;
			fooIt = fooVector.begin();
			fooIt2 = ++fooIt;

			Assert::IsTrue(intIt == intIt2);
			Assert::IsTrue(pointerIt == pointerIt2);
			Assert::IsTrue(fooIt == fooIt2);

			Assert::AreEqual(*intIt, intTestVariable2);
			Assert::AreEqual(*pointerIt, pointerTestVariable2);
			Assert::AreEqual(*fooIt, fooTestVariable2);
		}

		TEST_METHOD(IteratorPostIncrement)
		{
			Vector<int32_t>::Iterator intIt;
			Vector<int32_t*>::Iterator pointerIt;
			Vector<Foo>::Iterator fooIt;
			Vector<int32_t>::Iterator intIt2;
			Vector<int32_t*>::Iterator pointerIt2;
			Vector<Foo>::Iterator fooIt2;

			Vector<int32_t> intVector;
			Vector<int32_t*> pointerVector;
			Vector<Foo> fooVector;

			for (int32_t i = 0; i < maxNumberOfElements; ++i)
			{
				intVector.PushBack(intTestVariableArray1[i]);
				pointerVector.PushBack(pointerTestVariableArray1[i]);
				fooVector.PushBack(fooTestVariableArray1[i]);
			}

			intIt = intVector.begin();
			intIt2 = intIt++;
			pointerIt = pointerVector.begin();
			pointerIt2 = pointerIt++;
			fooIt = fooVector.begin();
			fooIt2 = fooIt++;

			Assert::IsFalse(intIt == intIt2);
			Assert::IsFalse(pointerIt == pointerIt2);
			Assert::IsFalse(fooIt == fooIt2);

			Assert::AreEqual(*intIt, intTestVariable2);
			Assert::AreEqual(*pointerIt, pointerTestVariable2);
			Assert::AreEqual(*fooIt, fooTestVariable2);
		}

		TEST_METHOD(IteratorDeference)
		{
			Vector<int32_t>::Iterator intIt;
			Vector<int32_t*>::Iterator pointerIt;
			Vector<Foo>::Iterator fooIt;

			Vector<int32_t> intVector;
			Vector<int32_t*> pointerVector;
			Vector<Foo> fooVector;

			auto intDeferenceExpection = [&intIt] {*intIt; };
			auto pointerDeferenceExpection = [&pointerIt] {*pointerIt; };
			auto fooDeferenceExpection = [&fooIt] {*fooIt; };

			Assert::ExpectException<exception>(intDeferenceExpection);
			Assert::ExpectException<exception>(pointerDeferenceExpection);
			Assert::ExpectException<exception>(fooDeferenceExpection);

			int32_t i = 0;
			for ( i = 0; i < maxNumberOfElements; ++i)
			{
				intVector.PushBack(intTestVariableArray1[i]);
				pointerVector.PushBack(pointerTestVariableArray1[i]);
				fooVector.PushBack(fooTestVariableArray1[i]);
			}

			i = 0;
			for (int32_t data : intVector)
			{
				Assert::AreEqual(data, intTestVariableArray1[i++]);
			}

			i = 0;
			for (int32_t* data : pointerVector)
			{
				Assert::AreEqual(data, pointerTestVariableArray1[i++]);
			}

			i = 0;
			for (Foo data : fooVector)
			{
				Assert::AreEqual(data, fooTestVariableArray1[i++]);
			}

			i = 0;
			for (int32_t data : intVector)
			{
				Assert::AreEqual(data, intTestVariableArray1[i++]);
			}

			i = 0;
			for (int32_t* data : pointerVector)
			{
				Assert::AreEqual(data, pointerTestVariableArray1[i++]);
			}

			i = 0;
			for (Foo data : fooVector)
			{
				Assert::AreEqual(data, fooTestVariableArray1[i++]);
			}

			intIt = intVector.begin();
			pointerIt = pointerVector.begin();
			fooIt = fooVector.begin();

			const Vector<int32_t>::Iterator &constIntIt = intIt;
			const Vector<int32_t*>::Iterator &constPointerIt = pointerIt;
			const Vector<Foo>::Iterator &constFooIt = fooIt;

			Assert::AreEqual(*constIntIt, *intIt);
			Assert::AreEqual(*constPointerIt, *pointerIt);
			Assert::AreEqual(*constFooIt, *fooIt);
		}

		

	private:
		_CrtMemState VectorTest::sStartMemState;
		static const  uint32_t maxNumberOfElements = 3;
		static const uint32_t defaultCapacity = 3;
		static const uint32_t defaultSize= 0;
		int32_t intTestVariable1 = 10;
		int32_t intTestVariable2 = 20;
		int32_t intTestVariable3 = 30;

		int32_t intTestVariableArray1[maxNumberOfElements] = { 10,20,30 };
		int32_t intTestVariableArray2[maxNumberOfElements] = { 30,20,10 };

		Foo fooTestVariable1 = Foo(1, 10);
		Foo fooTestVariable2 = Foo(2, 30);
		Foo fooTestVariable3 = Foo(2, 30);

		Foo fooTestVariableArray1[maxNumberOfElements] = { fooTestVariable1, fooTestVariable2, fooTestVariable3 };
		Foo fooTestVariableArray2[maxNumberOfElements] = { fooTestVariable3, fooTestVariable2, fooTestVariable1 };

		std::int32_t* pointerTestVariable1 = &intTestVariable1;
		std::int32_t* pointerTestVariable2 = &intTestVariable2;
		std::int32_t* pointerTestVariable3 = &intTestVariable3;

		std::int32_t* pointerTestVariableArray1[maxNumberOfElements] = { pointerTestVariable1, pointerTestVariable2,
			pointerTestVariable3 };

		std::int32_t* pointerTestVariableArray2[maxNumberOfElements] = { pointerTestVariable3, pointerTestVariable2,
			pointerTestVariable1 };
		
	};
}
