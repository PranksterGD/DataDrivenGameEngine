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
	TEST_CLASS(SListTest)
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
		TEST_METHOD(TestDefaultConstructor)
		{
			SList<std::int32_t> list;
			Assert::AreEqual((std::int32_t)list.Size(), 0);

			SList<Foo> fooList;
			Assert::AreEqual((std::int32_t)fooList.Size(), 0);

			SList<std::int32_t*> pointerList;
			Assert::AreEqual((std::int32_t)pointerList.Size(), 0);
		}

		/*Creates lists of ints and strings. First pushes one value to them and ensures that the value
		pushed is equal to the front of the list, and that the front and back of the list are the same.
		Then pushes another value to the front of the list and ensures that the new front of the list
		matches the second value pushed*/
		TEST_METHOD(TestPushFront)
		{
			SList<std::int32_t> list;
			SList<Foo> fooList;
			SList<std::int32_t*> pointerList;
			list.PushFront(testVariable1);
			fooList.PushFront(fooTestVariable1);
			pointerList.PushFront(pointerTestVariable1);

			Assert::AreEqual(list.Front(), testVariable1);
			Assert::AreEqual(fooList.Front(), fooTestVariable1);
			Assert::AreEqual(pointerList.Front(), pointerTestVariable1);
			Assert::AreEqual(list.Front(), list.Back());
			Assert::AreEqual(fooList.Front(), fooList.Back());
			Assert::AreEqual(pointerList.Front(), pointerList.Back());

			list.PushFront(testVariable2);
			fooList.PushFront(fooTestVariable2);
			pointerList.PushFront(pointerTestVariable2);

			Assert::AreEqual(list.Front(), testVariable2);
			Assert::AreEqual(fooList.Front(), fooTestVariable2);
			Assert::AreEqual(pointerList.Front(), pointerTestVariable2);
		}

		/*Pushes 3 elements into the front of lists of ints and strings.
		Pops the elements from the front one by one, and checks that the value that is popped matches
		the value that was pushed in, and that the size of the lists reduce by one for each pop*/
		TEST_METHOD(TestPopFront)
		{
			SList<std::int32_t> list;
			SList<Foo> fooList;
			SList<std::int32_t*> pointerList;

			auto intPopFrontException = [&list] {list.PopFront(); };
			auto pointerPopFrontExcepton = [&pointerList] {pointerList.PopFront(); };
			auto fooPopFrontException = [&fooList] {fooList.PopFront(); };

			Assert::ExpectException<exception>(intPopFrontException);
			Assert::ExpectException<exception>(pointerPopFrontExcepton);
			Assert::ExpectException<exception>(fooPopFrontException);

			for (std::int32_t i = 1; i < maxNumberOfElements+1; i++)
			{
				list.PushFront(testVariableArray[i - 1]);
				fooList.PushFront(fooTestVariableArray[i - 1]);
				pointerList.PushFront(pointerTestVariableArray[i - 1]);
			}

			std::int32_t size = 3;

			for (std::int32_t i = 1; i < maxNumberOfElements+1; i++)
			{
				std::int32_t value =list.PopFront();
				Foo stringValue = fooList.PopFront();
				std::int32_t* pointerValue = pointerList.PopFront();
				size--;
				Assert::AreEqual(value, testVariableArray2[i - 1]);
				Assert::AreEqual(stringValue, fooTestVariableArray2[i - 1]);
				Assert::AreEqual(pointerValue, pointerTestVariableArray2[i - 1]);
				Assert::AreEqual(size, (std::int32_t)list.Size());
				Assert::AreEqual(size, (std::int32_t)fooList.Size());
				Assert::AreEqual(size, (std::int32_t)pointerList.Size());
			}
		}

		/*Creates lists of ints and strings. First pushes one value to the back and ensures that the value
		pushed is equal to the back of the list, and that the front and back of the list are the same.
		Then pushes another value to the back of the list and ensures that the new back of the list
		matches the second value pushed*/
		TEST_METHOD(TestPushBack)
		{
			SList<std::int32_t> list;
			SList<Foo> fooList;
			SList<std::int32_t*> pointerList;
			list.PushBack(testVariable1);
			fooList.PushBack(fooTestVariable1);
			pointerList.PushBack(pointerTestVariable1);

			Assert::AreEqual(list.Back(), testVariable1);
			Assert::AreEqual(fooList.Back(), fooTestVariable1);
			Assert::AreEqual(pointerList.Back(), pointerTestVariable1);
			Assert::AreEqual(list.Back(), list.Front());
			Assert::AreEqual(fooList.Back(), fooList.Front());
			Assert::AreEqual(pointerList.Back(), pointerList.Front());

			list.PushBack(testVariable2);
			fooList.PushBack(fooTestVariable2);
			pointerList.PushBack(pointerTestVariable2);
			Assert::AreEqual(list.Back(), testVariable2);
			Assert::AreEqual(fooList.Back(), fooTestVariable2);
			Assert::AreEqual(pointerList.Back(), pointerTestVariable2);
		}

		/*Creates empty lists of ints and strings and ensures that their IsEmpty methods
		return true*/
		TEST_METHOD(TestIsEmpty)
		{
			SList<std::int32_t> list;
			Assert::AreEqual(true, list.IsEmpty());
			list.PushFront(testVariable1);
			Assert::AreEqual(false, list.IsEmpty());

			SList<Foo> fooList;
			Assert::AreEqual(true, fooList.IsEmpty());
			fooList.PushFront(fooTestVariable1);
			Assert::AreEqual(false, fooList.IsEmpty());

			SList<std::int32_t*> pointerList;
			Assert::AreEqual(true, pointerList.IsEmpty());

			pointerList.PushFront(pointerTestVariable1);
			Assert::AreEqual(false, pointerList.IsEmpty());
		
		}

		/*Pushes 3 elements to the front of lists of ints and strings and each time checks that
		the new front of the lists match the value that is being pushed in*/
		TEST_METHOD(TestFront)
		{
			SList<std::int32_t> list;
			SList<Foo> fooList;
			SList<std::int32_t*> pointerList;

			auto intFrontException = [&list] {list.Front(); };
			auto pointerFrontException = [&pointerList] {pointerList.Front(); };
			auto fooFrontException = [&fooList] {fooList.Front(); };

			Assert::ExpectException<exception>(intFrontException);
			Assert::ExpectException<exception>(pointerFrontException);
			Assert::ExpectException<exception>(fooFrontException);

			for (std::int32_t i = 1; i < maxNumberOfElements+1; i++)
			{
				list.PushFront(testVariableArray[i - 1]);
				fooList.PushFront(fooTestVariableArray[i - 1]);
				pointerList.PushFront(pointerTestVariableArray[i - 1]);
				Assert::AreEqual(list.Front(), testVariableArray[i - 1]);
				Assert::AreEqual(fooList.Front(), fooTestVariableArray[i - 1]);
				Assert::AreEqual(pointerList.Front(), pointerTestVariableArray[i - 1]);
			}

			for (std::int32_t i = 1; i < maxNumberOfElements+1; i++)
			{
				list.PushBack(testVariableArray[i - 1]);
				fooList.PushBack(fooTestVariableArray[i - 1]);
				pointerList.PushBack(pointerTestVariableArray[i - 1]);
				Assert::AreEqual(list.Front(), testVariableArray[maxNumberOfElements]);
				Assert::AreEqual(fooList.Front(), fooTestVariableArray[maxNumberOfElements]);
				Assert::AreEqual(pointerList.Front(), pointerTestVariableArray[maxNumberOfElements]);
			}
		}

		/*Pushes 3 elements to the back of lists of ints and strings and each time checks that
		the new back of the lists match the value that is being pushed in*/
		TEST_METHOD(TestBack)
		{
			SList<std::int32_t> list;
			SList<Foo> fooList;
			SList<std::int32_t*> pointerList;

			auto intBackException = [&list] {list.Front(); };
			auto pointerBackException = [&pointerList] {pointerList.Front(); };
			auto fooBackException = [&fooList] {fooList.Front(); };

			Assert::ExpectException<exception>(intBackException);
			Assert::ExpectException<exception>(pointerBackException);
			Assert::ExpectException<exception>(fooBackException);
			for (std::int32_t i = 1; i < maxNumberOfElements+1; i++)
			{
				list.PushBack(testVariableArray[i - 1]);
				fooList.PushBack(fooTestVariableArray[i - 1]);
				pointerList.PushBack(pointerTestVariableArray[i - 1]);
				Assert::AreEqual(list.Back(), testVariableArray[i - 1]);
				Assert::AreEqual(fooList.Back(), fooTestVariableArray[i - 1]);
				Assert::AreEqual(pointerList.Back(), pointerTestVariableArray[i - 1]);
			}

			for (std::int32_t i = 1; i < maxNumberOfElements+1; i++)
			{
				list.PushFront(testVariableArray[i - 1]);
				fooList.PushFront(fooTestVariableArray[i - 1]);
				pointerList.PushFront(pointerTestVariableArray[i - 1]);
				Assert::AreEqual(list.Back(), testVariableArray[maxNumberOfElements]);
				Assert::AreEqual(fooList.Back(), fooTestVariableArray[maxNumberOfElements]);
				Assert::AreEqual(pointerList.Back(), pointerTestVariableArray[maxNumberOfElements]);
			}
		}

		/*Pushes 3 elements into lists of strings and ints and ensures that the size gets 
		incremented by one each time*/
		TEST_METHOD(TestSize)
		{
			SList<std::int32_t> list;
			SList<Foo> fooList;
			SList <std::int32_t*> pointerList;
			for (std::int32_t i = 1; i < maxNumberOfElements+1; i++)
			{
				list.PushBack(testVariableArray[i - 1]);
				fooList.PushBack(fooTestVariableArray[i - 1]);
				pointerList.PushBack(pointerTestVariableArray[i - 1]);
				Assert::AreEqual((std::int32_t) list.Size(), i);
				Assert::AreEqual((std::int_fast32_t)fooList.Size(), i);
				Assert::AreEqual((std::int32_t)pointerList.Size(), i);
			}
		}

		/*Pushes 3 elements into lists of ints and strings and then clears them.
		Checks that after clearing, their sizes are zero and their IsEmpty methods return true*/
		TEST_METHOD(TestClear)
		{
			SList<std::int32_t> list;
			SList<Foo> fooList;
			SList<std::int32_t*> pointerList;
			for (std::int32_t i = 1; i < maxNumberOfElements+1; i++)
			{
				list.PushBack(testVariableArray[i - 1]);
				fooList.PushBack(fooTestVariableArray[i - 1]);
				pointerList.PushBack(pointerTestVariableArray[i - 1]);
			}
			list.Clear();
			fooList.Clear();
			pointerList.Clear();
			Assert::AreEqual(0,(std::int32_t)list.Size());
			Assert::AreEqual(0, (std::int32_t)fooList.Size());
			Assert::AreEqual(0, (std::int32_t)pointerList.Size());
			Assert::AreEqual(true, fooList.IsEmpty());
			Assert::AreEqual(true, list.IsEmpty());
			Assert::AreEqual(true, pointerList.IsEmpty());
		}


		/*Pushes 3 elements into lists of strings and ints, and then creates new lists of ints and
		strings, by using the copy constructor. 
		Checks that the fronts and backs of the both pairs of lists are the same, and then pops 
		elements one by one, each time rechecking that fronts and backs still match.*/
		TEST_METHOD(TestCopyConstructor)
		{
			SList<std::int32_t> list;
			SList<Foo> fooList;
			SList<std::int32_t*> pointerList;
			for (std::int32_t i = 1; i < maxNumberOfElements+1; i++)
			{
				list.PushBack(testVariableArray[i - 1]);
				fooList.PushBack(fooTestVariableArray[i - 1]);
				pointerList.PushBack(pointerTestVariableArray[i - 1]);
			}
			SList <std::int32_t> otherlist(list);
			SList<Foo> otherfooList(fooList);
			SList <std::int32_t*> otherPointerList(pointerList);
			
			for (std::int32_t i = 1; i < maxNumberOfElements+1; i++)
			{
				Assert::AreEqual(list.Front(), otherlist.Front());
				Assert::AreEqual(fooList.Front(), otherfooList.Front());
				Assert::AreEqual(pointerList.Front(), otherPointerList.Front());
				Assert::AreEqual(list.Back(), otherlist.Back());
				Assert::AreEqual(fooList.Back(), otherfooList.Back());
				Assert::AreEqual(pointerList.Back(), otherPointerList.Back());
				list.PopFront();
				fooList.PopFront();
				pointerList.PopFront();
				otherlist.PopFront();
				otherfooList.PopFront();
				otherPointerList.PopFront();
			}
		}

		TEST_METHOD(TestMoveCopyConstructor)
		{
			SList<std::int32_t> list;
			SList<Foo> fooList;
			SList<std::int32_t*> pointerList;
			for (std::int32_t i = 1; i < maxNumberOfElements + 1; i++)
			{
				list.PushBack(testVariableArray[i - 1]);
				fooList.PushBack(fooTestVariableArray[i - 1]);
				pointerList.PushBack(pointerTestVariableArray[i - 1]);
			}
			SList <std::int32_t> otherlist = move(list);
			SList<Foo> otherfooList = move(fooList);
			SList <std::int32_t*> otherPointerList = move(pointerList);

			Assert::IsTrue(list.IsEmpty());
			Assert::IsTrue(fooList.IsEmpty());
			Assert::IsTrue(pointerList.IsEmpty());

			Assert::IsTrue(otherlist.Back() == testVariableArray[3]);
			Assert::IsTrue(otherlist.Front() == testVariableArray[0]);

			Assert::IsTrue(otherfooList.Back() == fooTestVariableArray[3]);
			Assert::IsTrue(otherfooList.Front() == fooTestVariableArray[0]);

			Assert::IsTrue(otherPointerList.Back() == pointerTestVariableArray[3]);
			Assert::IsTrue(otherPointerList.Front() == pointerTestVariableArray[0]);
		}

		/*Pushes 3 elements into lists of strings and ints, and then assigns these lists to
		a new pair of lists of ints and strings.
		Checks that the fronts and backs of the both pairs of lists are the same, and then pops
		elements one by one, each time rechecking that fronts and backs still match.*/
		TEST_METHOD(TestAssigmentOperator)
		{
			SList<int32_t>::Iterator intIt;
			SList<int32_t>::Iterator intIt2;
			SList<int32_t*>::Iterator pointerIt;
			SList<int32_t*>::Iterator pointerIt2;
			SList<Foo>::Iterator fooIt;
			SList<Foo>::Iterator fooIt2;

			SList<std::int32_t> list;
			SList<Foo> fooList;
			SList<std::int32_t*> pointerList;
			for (std::int32_t i = 1; i < maxNumberOfElements+1; i++)
			{
				list.PushBack(testVariableArray[i - 1]);
				fooList.PushBack(fooTestVariableArray[i - 1]);
				pointerList.PushBack(pointerTestVariableArray[i - 1]);
			}
			SList <std::int32_t> otherlist;
			SList <Foo> otherfooList;
			SList <std::int32_t*> otherPointerList;
			otherlist =list;
			otherfooList = fooList;
			otherPointerList = pointerList;
		
			for (intIt = list.begin(), intIt2 =otherlist.begin(); intIt != list.end()
				&& intIt2!=otherlist.end(); ++intIt, ++intIt2)
			{
				Assert::AreEqual(*intIt, *intIt2);
			}

			for (pointerIt = pointerList.begin(), pointerIt2 = otherPointerList.begin(); pointerIt != pointerList.end()
				&& pointerIt2 != otherPointerList.end(); ++pointerIt, ++pointerIt2)
			{
				Assert::AreEqual(*pointerIt, *pointerIt2);
			}

			for (fooIt = fooList.begin(), fooIt2 = otherfooList.begin(); fooIt != fooList.end() &&
				fooIt2 != otherfooList.end();	++fooIt, ++fooIt2)
			{
				Assert::AreEqual(*fooIt, *fooIt2);
			}

			intIt = list.Find(20);
			Assert::AreEqual(*intIt, 20);

			list.InsertAfter(50, list.begin());
			intIt = list.begin();
			++intIt;
			Assert::AreEqual(*intIt, 50);

			list.Remove(20);
		//	list.Remove(10);
		}

		TEST_METHOD(TestIteratorDefaultConstuctor)
		{
			SList<int32_t>::Iterator intIt;
			SList<int32_t>::Iterator intIt2;
			SList<int32_t> intList;
			SList<int32_t*>::Iterator pointerIt;
			SList<int32_t*>::Iterator pointerIt2;
			SList<int32_t*> pointerList;
			SList<Foo>::Iterator FooIt;
			SList<Foo>::Iterator FooIt2;
			SList<Foo> fooList;

			Assert::IsTrue(intIt == intIt2);
			Assert::IsTrue(pointerIt == pointerIt2);
			Assert::IsTrue(FooIt == FooIt2);
			
			intIt2= intList.begin();
			pointerIt2 = pointerList.begin();
			FooIt2 = fooList.begin();
			Assert::IsTrue(intIt != intIt2);
			Assert::IsTrue(pointerIt != pointerIt2);
			Assert::IsTrue(FooIt != FooIt2);
		}

		TEST_METHOD(TestIteratorEqualityOperator)
		{
			SList<int32_t> intList;
			SList<int32_t> otherIntList;
			SList<int32_t>::Iterator intIt;
			SList<int32_t>::Iterator otherIntIt;
			SList<int32_t*> pointerList;
			SList<int32_t*> otherPointerList;
			SList<int32_t*>::Iterator pointerIt;
			SList<int32_t*>::Iterator otherPointerIt;
			SList<Foo> fooList;
			SList<Foo> otherFooList;
			SList<Foo>::Iterator fooIt;
			SList<Foo>::Iterator otherFooIt;

			Assert::IsTrue(intIt == otherIntIt);
			Assert::IsTrue(pointerIt == otherPointerIt);
			Assert::IsTrue(fooIt == otherFooIt);

			intIt = intList.begin();
			otherIntIt = otherIntList.begin();
			pointerIt = pointerList.begin();
			otherPointerIt = otherPointerList.begin();
			fooIt = fooList.begin();
			fooIt = otherFooList.begin();

			Assert::IsFalse(intIt == otherIntIt);
			Assert::IsFalse(pointerIt == otherPointerIt);
			Assert::IsFalse(fooIt == otherFooIt);

			intList.PushFront(testVariable1);
			pointerList.PushFront(pointerTestVariable1);
			fooList.PushFront(fooTestVariable1);
			otherIntIt = intList.begin();
			otherPointerIt = pointerList.begin();
			otherFooIt = fooList.begin();

			Assert::IsFalse(intIt == otherIntIt);
			Assert::IsFalse(pointerIt == otherPointerIt);
			Assert::IsFalse(fooIt == otherFooIt);
		}

		TEST_METHOD(TestIteratorNotEqualOperator)
		{
			SList<int32_t> intList;
			SList<int32_t> otherIntList;
			SList<int32_t>::Iterator intIt;
			SList<int32_t>::Iterator otherIntIt;
			SList<int32_t*> pointerList;
			SList<int32_t*> otherPointerList;
			SList<int32_t*>::Iterator pointerIt;
			SList<int32_t*>::Iterator otherPointerIt;
			SList<Foo> fooList;
			SList<Foo> otherFooList;
			SList<Foo>::Iterator fooIt;
			SList<Foo>::Iterator otherFooIt;

			Assert::IsFalse(intIt != otherIntIt);
			Assert::IsFalse(pointerIt != otherPointerIt);
			Assert::IsFalse(fooIt != otherFooIt);

			intIt = intList.begin();
			otherIntIt = otherIntList.begin();
			pointerIt = pointerList.begin();
			otherPointerIt = otherPointerList.begin();
			fooIt = fooList.begin();
			fooIt = otherFooList.begin();

			Assert::IsTrue(intIt != otherIntIt);
			Assert::IsTrue(pointerIt != otherPointerIt);
			Assert::IsTrue(fooIt != otherFooIt);

			intList.PushFront(testVariable1);
			pointerList.PushFront(pointerTestVariable1);
			fooList.PushFront(fooTestVariable1);
			otherIntIt = intList.begin();
			otherPointerIt = pointerList.begin();
			otherFooIt = fooList.begin();

			Assert::IsTrue(intIt != otherIntIt);
			Assert::IsTrue(pointerIt != otherPointerIt);
			Assert::IsTrue(fooIt != otherFooIt);
		}

		TEST_METHOD(TestIteratorPreIncrementOperator)
		{
			SList<int32_t>::Iterator intIt;
			SList<int32_t>::Iterator intIt2;
			SList<int32_t> intList;
			SList<int32_t*>::Iterator pointerIt;
			SList<int32_t*>::Iterator pointerIt2;
			SList<int32_t*> pointerList;
			SList<Foo>::Iterator FooIt;
			SList<Foo>::Iterator FooIt2;
			SList<Foo> fooList;

			for (std::int32_t i = 1; i < maxNumberOfElements+1; i++)
			{
				intList.PushFront(testVariableArray[i - 1]);
				fooList.PushFront(fooTestVariableArray[i - 1]);
				pointerList.PushFront(pointerTestVariableArray[i - 1]);
			}

			intIt = intList.begin();
			intIt2 = ++intIt;
			pointerIt = pointerList.begin();
			pointerIt2 = ++pointerIt;
			FooIt = fooList.begin();
			FooIt2 = ++FooIt;

			Assert::IsTrue(intIt == intIt2);
			Assert::IsTrue(pointerIt == pointerIt2);
			Assert::IsTrue(FooIt == FooIt2);

			Assert::AreEqual(*intIt, testVariable2);
			Assert::AreEqual(*pointerIt, pointerTestVariable2);
			Assert::AreEqual(*FooIt, fooTestVariable2);
		}

		TEST_METHOD(TestIteratorPostIncrementOperator)
		{
			SList<int32_t>::Iterator intIt;
			SList<int32_t>::Iterator intIt2;
			SList<int32_t> intList;
			SList<int32_t*>::Iterator pointerIt;
			SList<int32_t*>::Iterator pointerIt2;
			SList<int32_t*> pointerList;
			SList<Foo>::Iterator FooIt;
			SList<Foo>::Iterator FooIt2;
			SList<Foo> fooList;

			for (std::int32_t i = 1; i < maxNumberOfElements+1; i++)
			{
				intList.PushFront(testVariableArray[i - 1]);
				fooList.PushFront(fooTestVariableArray[i - 1]);
				pointerList.PushFront(pointerTestVariableArray[i - 1]);
			}

			intIt = intList.begin();
			intIt2 = intIt++;
			pointerIt = pointerList.begin();
			pointerIt2 = pointerIt++;
			FooIt = fooList.begin();
			FooIt2 = FooIt++;

			Assert::IsFalse(intIt == intIt2);
			Assert::IsFalse(pointerIt == pointerIt2);
			Assert::IsFalse(FooIt == FooIt2);

			Assert::AreEqual(*intIt, testVariable2);
			Assert::AreEqual(*pointerIt, pointerTestVariable2);
			Assert::AreEqual(*FooIt, fooTestVariable2);
		}

		TEST_METHOD(TestIteratorDeferenceOperator)
		{
			SList<int32_t>::Iterator intIt;
			SList<int32_t> intList;
			SList<int32_t*>::Iterator pointerIt;
			SList<int32_t*> pointerList;
			SList<Foo>::Iterator FooIt;
			SList<Foo> fooList;

			auto intDeferenceExpection = [&intIt] {*intIt; };
			auto pointerDeferenceExpection = [&pointerIt] {*pointerIt; };
			auto fooDeferenceExpection = [&FooIt] {*FooIt; };

			Assert::ExpectException<exception>(intDeferenceExpection);
			Assert::ExpectException<exception>(pointerDeferenceExpection);
			Assert::ExpectException<exception>(fooDeferenceExpection);

			for (std::int32_t i = 1; i < maxNumberOfElements+1; i++)
			{
				intList.PushFront(testVariableArray[i - 1]);
				fooList.PushFront(fooTestVariableArray[i - 1]);
				pointerList.PushFront(pointerTestVariableArray[i - 1]);
			}
			
			int i = 0;
			for (intIt = intList.begin(); intIt != intList.end(); ++intIt)
			{
				Assert::AreEqual(*intIt, testVariableArray2[i++]);
			}

			i = 0;
			for (pointerIt = pointerList.begin(); pointerIt != pointerList.end(); ++pointerIt)
			{
				Assert::AreEqual(*pointerIt , pointerTestVariableArray2[i++]);
			}

			i = 0;
			for (FooIt = fooList.begin(); FooIt != fooList.end(); ++FooIt)
			{
				Assert::AreEqual(*FooIt, fooTestVariableArray2[i++]);
			}
		}

		TEST_METHOD(TestIteratorBegin)
		{
			SList<int32_t>::Iterator intIt;
			SList<int32_t> intList;
			SList<int32_t*>::Iterator pointerIt;
			SList<int32_t*> pointerList;
			SList<Foo>::Iterator fooIt;
			SList<Foo> fooList;

			intIt = intList.begin();
			pointerIt = pointerList.begin();
			fooIt = fooList.begin();

			auto intDeferenceExpection = [&intIt] {*intIt; };
			auto pointerDeferenceExpection = [&pointerIt] {*pointerIt; };
			auto fooDeferenceExpection = [&fooIt] {*fooIt; };

			Assert::ExpectException<exception>(intDeferenceExpection);
			Assert::ExpectException<exception>(pointerDeferenceExpection);
			Assert::ExpectException<exception>(fooDeferenceExpection);

			for (int i = 0; i < maxNumberOfElements; i++)
			{
				intList.PushFront(testVariableArray[i]);
				pointerList.PushFront(pointerTestVariableArray[i]);
				fooList.PushFront(fooTestVariableArray[i]);

				intIt = intList.begin();
				pointerIt = pointerList.begin();
				fooIt = fooList.begin();

				Assert::AreEqual(*intIt, testVariableArray[i]);
				Assert::AreEqual(*pointerIt, pointerTestVariableArray[i]);
				Assert::AreEqual(*fooIt, fooTestVariableArray[i]);
			}
		}

		TEST_METHOD(TestIteratorEnd)
		{
			SList<int32_t>::Iterator intIt;
			SList<int32_t> intList;
			SList<int32_t*>::Iterator pointerIt;
			SList<int32_t*> pointerList;
			SList<Foo>::Iterator fooIt;
			SList<Foo> fooList;

			intIt = intList.end();
			pointerIt = pointerList.end();
			fooIt = fooList.end();

			auto intDeferenceExpection = [&intIt] {*intIt; };
			auto pointerDeferenceExpection = [&pointerIt] {*pointerIt; };
			auto fooDeferenceExpection = [&fooIt] {*fooIt; };

			Assert::ExpectException<exception>(intDeferenceExpection);
			Assert::ExpectException<exception>(pointerDeferenceExpection);
			Assert::ExpectException<exception>(fooDeferenceExpection);

			intList.PushFront(testVariable1);
			pointerList.PushFront(pointerTestVariable1);
			fooList.PushFront(fooTestVariable1);

			auto intDeferenceExpection2 = [&intIt] {*intIt; };
			auto pointerDeferenceExpection2 = [&pointerIt] {*pointerIt; };
			auto fooDeferenceExpection2 = [&fooIt] {*fooIt; };

			Assert::ExpectException<exception>(intDeferenceExpection2);
			Assert::ExpectException<exception>(pointerDeferenceExpection2);
			Assert::ExpectException<exception>(fooDeferenceExpection2);
		}

		TEST_METHOD(TestIteratorFind)
		{
			SList<int32_t>::Iterator intIt;
			SList<int32_t> intList;
			SList<int32_t*>::Iterator pointerIt;
			SList<int32_t*> pointerList;
			SList<Foo>::Iterator fooIt;
			SList<Foo> fooList;

			intIt = intList.Find(testVariable1);
			pointerIt = pointerList.Find(pointerTestVariable1);
			fooIt = fooList.Find(fooTestVariable1);

			auto intDeferenceExpection = [&intIt] {*intIt; };
			auto pointerDeferenceExpection = [&pointerIt] {*pointerIt; };
			auto fooDeferenceExpection = [&fooIt] {*fooIt; };

			Assert::ExpectException<exception>(intDeferenceExpection);
			Assert::ExpectException<exception>(pointerDeferenceExpection);
			Assert::ExpectException<exception>(fooDeferenceExpection);

			intList.PushFront(testVariable1);
			pointerList.PushFront(pointerTestVariable1);
			fooList.PushFront(fooTestVariable1);

			intIt = intList.Find(testVariable1);
			pointerIt = pointerList.Find(pointerTestVariable1);
			fooIt = fooList.Find(fooTestVariable1);

			Assert::AreEqual(*intIt, testVariable1);
			Assert::AreEqual(*pointerIt, pointerTestVariable1);
			Assert::AreEqual(*fooIt, fooTestVariable1);

			intIt = intList.Find(testVariable2);
			pointerIt = pointerList.Find(pointerTestVariable2);
			fooIt = fooList.Find(fooTestVariable2);

			auto intDeferenceExpection2 = [&intIt] {*intIt; };
			auto pointerDeferenceExpection2 = [&pointerIt] {*pointerIt; };
			auto fooDeferenceExpection2 = [&fooIt] {*fooIt; };

			Assert::ExpectException<exception>(intDeferenceExpection2);
			Assert::ExpectException<exception>(pointerDeferenceExpection2);
			Assert::ExpectException<exception>(fooDeferenceExpection2);
		}

		TEST_METHOD(TestIteratorInsertAfter)
		{
			SList<int32_t>::Iterator intIt;
			SList<int32_t> intList;
			SList<int32_t*>::Iterator pointerIt;
			SList<int32_t*> pointerList;
			SList<Foo>::Iterator fooIt;
			SList<Foo> fooList;

			intIt = intList.begin();
			pointerIt = pointerList.begin();
			fooIt = fooList.begin();

			intList.InsertAfter(testVariable1, intIt);
			pointerList.InsertAfter(pointerTestVariable1, pointerIt);
			fooList.InsertAfter(fooTestVariable1, fooIt);

			/*auto intFrontException = [&intList] {intList.Front(); };
			auto pointerFrontException = [&pointerList] {pointerList.Front(); };
			auto fooFrontException = [&fooList] {fooList.Front(); };

			Assert::ExpectException<exception>(intFrontException);
			Assert::ExpectException<exception>(pointerFrontException);
			Assert::ExpectException<exception>(fooFrontException);*/

			Assert::AreEqual(intList.Back(), testVariable1);
			Assert::AreEqual(intList.Back(), intList.Front());
			Assert::AreEqual(pointerList.Back(), pointerTestVariable1);
			Assert::AreEqual(pointerList.Back(), pointerList.Front());
			Assert::AreEqual(fooList.Back(), fooTestVariable1);
			Assert::AreEqual(fooList.Back(), fooList.Front());

			intList.PushFront(testVariable1);
			pointerList.PushFront(pointerTestVariable1);
			fooList.PushFront(fooTestVariable1);

			intIt = intList.begin();
			pointerIt = pointerList.begin();
			fooIt = fooList.begin();

			intList.InsertAfter(testVariable2, intIt);
			pointerList.InsertAfter(pointerTestVariable2, pointerIt);
			fooList.InsertAfter(fooTestVariable2, fooIt);

			++intIt;
			++pointerIt;
			++fooIt;

			Assert::AreEqual(*intIt, testVariable2);
			Assert::AreEqual(*pointerIt, pointerTestVariable2);
			Assert::AreEqual(*fooIt, fooTestVariable2);
		}

		TEST_METHOD(TestIteratorRemove)
		{
			SList<int32_t>::Iterator intIt;
			SList<int32_t> intList;
			SList<int32_t> otherIntList;
			SList<int32_t*>::Iterator pointerIt;
			SList<int32_t*> pointerList;
			SList<int32_t*> otherPointerList;
			SList<Foo>::Iterator fooIt;
			SList<Foo> fooList;
			SList<Foo> otherFooList;

			for (int i = 0; i < maxNumberOfElements; i++)
			{
				intList.PushFront(testVariableArray[i]);
				pointerList.PushFront(pointerTestVariableArray[i]);
				fooList.PushFront(fooTestVariableArray[i]);
			}

			otherIntList = intList;
			otherPointerList = pointerList;
			otherFooList = fooList;

			int32_t intRemoveTestVariable = 40;
			int32_t* pointerRemoveTestVariable = &intRemoveTestVariable;
			Foo fooRemoveTestVariable(4, 40);

			intList.Remove(intRemoveTestVariable);
			pointerList.Remove(pointerRemoveTestVariable);
			fooList.Remove(fooRemoveTestVariable);

			int i = 0;
			for (intIt = intList.begin(); intIt != intList.end(); ++intIt)
			{
				Assert::AreEqual(*intIt, testVariableArray2[i++]);
			}

			i = 0;
			for (pointerIt = pointerList.begin(); pointerIt != pointerList.end(); ++pointerIt)
			{
				Assert::AreEqual(*pointerIt, pointerTestVariableArray2[i++]);
			}

			i = 0;
			for (fooIt = fooList.begin(); fooIt != fooList.end(); ++fooIt)
			{
				Assert::AreEqual(*fooIt, fooTestVariableArray2[i++]);
			}

			intList.Remove(testVariable3);
			pointerList.Remove(pointerTestVariable3);
			fooList.Remove(fooTestVariable3);

			intIt = intList.Find(testVariable3);
			pointerIt = pointerList.Find(pointerTestVariable3);
			fooIt = fooList.Find(fooTestVariable3);

			auto intDeferenceExpection = [&intIt] {*intIt; };
			auto pointerDeferenceExpection = [&pointerIt] {*pointerIt; };
			auto fooDeferenceExpection = [&fooIt] {*fooIt; };

			Assert::ExpectException<exception>(intDeferenceExpection);
			Assert::ExpectException<exception>(pointerDeferenceExpection);
			Assert::ExpectException<exception>(fooDeferenceExpection);

			intList = otherIntList;
			pointerList = otherPointerList;
			fooList = otherFooList;

			intList.Remove(testVariable2);
			pointerList.Remove(pointerTestVariable2);
			fooList.Remove(fooTestVariable2);

			intIt = intList.Find(testVariable2);
			pointerIt = pointerList.Find(pointerTestVariable2);
			fooIt = fooList.Find(fooTestVariable2);

			auto intDeferenceExpection2 = [&intIt] {*intIt; };
			auto pointerDeferenceExpection2 = [&pointerIt] {*pointerIt; };
			auto fooDeferenceExpection2 = [&fooIt] {*fooIt; };

			Assert::ExpectException<exception>(intDeferenceExpection2);
			Assert::ExpectException<exception>(pointerDeferenceExpection2);
			Assert::ExpectException<exception>(fooDeferenceExpection2);

			intList = otherIntList;
			pointerList = otherPointerList;
			fooList = otherFooList;

			intList.Remove(testVariable1);
			pointerList.Remove(pointerTestVariable1);
			fooList.Remove(fooTestVariable1);

			intIt = intList.Find(testVariable1);
			pointerIt = pointerList.Find(pointerTestVariable1);
			fooIt = fooList.Find(fooTestVariable1);

			auto intDeferenceExpection3 = [&intIt] {*intIt; };
			auto pointerDeferenceExpection3 = [&pointerIt] {*pointerIt; };
			auto fooDeferenceExpection3 = [&fooIt] {*fooIt; };

			Assert::ExpectException<exception>(intDeferenceExpection3);
			Assert::ExpectException<exception>(pointerDeferenceExpection3);
			Assert::ExpectException<exception>(fooDeferenceExpection3);

		}


	private:
		static _CrtMemState sStartMemState;
		static const  int32_t maxNumberOfElements = 3;
		std::int32_t testVariable1 = 10;
		std::int32_t testVariable2 = 20;
		std::int32_t testVariable3 = 30;
		std::int32_t testVariableArray[maxNumberOfElements] = { 10,20,30 };
		std::int32_t testVariableArray2[maxNumberOfElements] = { 30,20,10 };

		std::int32_t* pointerTestVariable1 = &testVariable1;
		std::int32_t* pointerTestVariable2 = &testVariable2;
		std::int32_t* pointerTestVariable3 = &testVariable3;
		std::int32_t* pointerTestVariableArray[maxNumberOfElements] = { pointerTestVariable1, pointerTestVariable2,
		pointerTestVariable3 };
		std::int32_t* pointerTestVariableArray2[maxNumberOfElements] = { pointerTestVariable3, pointerTestVariable2,
		pointerTestVariable1 };

		Foo fooTestVariable1 = { 1, 10 };
		Foo fooTestVariable2 = { 2, 20 };
		Foo fooTestVariable3 = { 3, 30 };
		Foo fooTestVariableArray[maxNumberOfElements] = { fooTestVariable1, fooTestVariable2, fooTestVariable3 };
		Foo fooTestVariableArray2[maxNumberOfElements] = { fooTestVariable3, fooTestVariable2, fooTestVariable1 };
	};
	_CrtMemState SListTest::sStartMemState;
}