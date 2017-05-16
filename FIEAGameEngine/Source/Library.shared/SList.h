#pragma once
#include <cstdint>
#include <exception>
namespace FieaGameEngine
{
	template <typename T>
	class SList
	{
	private:
		struct Node
		{
			Node(T data, Node* next = nullptr);
			Node();
			T Data;
			Node* Next;
		};
	public:
		class Iterator
		{
			friend class SList;
		public:
			/**The default constructor for the iterator. */
			Iterator();

			/**The equality operator for the iterator
			* @param otherIterator- The iterator to be compared against
			* @return A boolean: True- the iterators are equal. False-They are not equal 
			*/
			bool operator==(const Iterator& otherIterator) const;

			/**The inequality operator for the iterator
			* @param otherIterator- The iterator to be compared against
			* @return A boolean: True- the iterators are not equal. False-They are  equal
			*/
			bool operator!=(const Iterator& otherIterator) const;

			/**The pre increment operator for the iterator.
			* @return Reference to the iterator after increment.
			*/
			Iterator& operator++();

			/**The post increment operator for the iterator.
			* @return A copy of the iterator before increment.
			*/
			Iterator operator++(int);

			/**The deference operator for the iterator.
			* @return A reference of the data pointed to by the iterator.
			*/
			T& operator*();

			/**The const version  deference operator for the iterator.
			* @return A const  reference of the data pointed to by the iterator.
			*/
			const T& operator* () const;

			/**The default destructor for the iterator. */
			~Iterator();
		private:
			Node* mNode;
			Iterator(Node* node, const SList* owner);
			const SList* mOwner;
		};
	public:
		/** The default constructor that sets the mFront and mBack to null and sets the mSize to zero. */
		SList();

		/**The copy constructor that performs a deep copy.
		* @param otherList The other SList that is to be copied.
		*/
		SList(const SList& otherList);

		SList(SList&& otherList);

		/** The destructor that deferences all pointers stored within the list before it is destroyed. */
		~SList();

		/** The assignment operator that assigns a SList to another, while performing a deep copy.
		* @param otherList The other SList that is to be copied.
		* @return Reference to the current SList, after the other SList has been deep copied onto it.
		*/
		SList& operator=(const SList &otherList);

		SList& operator=(SList&& otherList);

		/** Function that adds a new node to the front of the list.
		* @param value The value of the new node to be added to the list.
		* @return An iterator pointing to the location of the newly pushed element.
		*/
		Iterator PushFront(const T &value);

		/** Function that adds a new node to the back of the list.
		* @param value The value of the new node to be added to the list.
		* @return An iterator pointing to the location of the newly pushed element.
		*/
		Iterator PushBack(const T &value);

		/** Function that removes the element at the front of the list, returns a copy of it and deletes it.
		* @return The element at the front of the list.
		*/
		T PopFront();

		/** Function that returns true if there are no elements in the list, false otherwise.
		* @return If the list is empty or not.
		*/
		bool IsEmpty() const;

		/** Function that returns a constant reference to the element at the front of the list.
		* @return A constant reference to the element at the front of the list.
		*/
		const T& Front() const;

		/** Function that returns a constant reference to the element at the back of the list.
		* @return A constant reference to the element at the back of the list.
		*/
		const T& Back() const;

		/** Function that returns a reference to the element at the front of the list.
		* @return A reference to the element at the front of the list.
		*/
		T& Front();

		/** Function that returns a reference to the element at the back of the list.
		* @return A reference to the element at the back of the list.
		*/
		T& Back();

		/** Function that returns the size of the list.
		*@return The size of the list.
		*/
		std::uint32_t Size();

		/**Function the clears all pointers that are being held within the list.
		*/
		void Clear();

		/** Function that returns an iterator pointing to the first element of the list.
		*@return An iterator pointing to the first element of the list.
		*/
		Iterator begin() const;

		/** Function that returns a constant iterator that is out of the list.
		*@return A constant iterator that is out of the list .
		*/
		const Iterator end() const;

		/** Function that inserts an element after the element being pointed to by another iterator or
		appends it to the list if the iterator is out of the list.
		*@param value- The value to be inserted. it- The iterator after which the value is to be appended to.
		*@return A constant iterator that is out of the list .
		*/
		Iterator InsertAfter(const T& value, Iterator it);

		/** Function that searches the list for a value and returns an iterator pointing to that value,
		or an iterator pointing to end if the value is not found.
		*@param value- The value to be searched for.
		*@return An iterator pointing to the found value.
		*/
		Iterator Find(const T& value) const;

		/** Function that removes the first occurrence of a value from the list. Does nothing if the value
		is not found in the list.
		*@param value- The value to be removed from the list.
		*/
		void Remove(const T& value);

	private:
		/** The Node that points to the front of the list */
		Node* mFront;

		/** The Node that points to the back of the list */
		Node* mBack;

		/** The size of the list */
		std::uint32_t mSize;

		//Helper function that deep copies all the nodes of one list to another
		void CopyNodes(const SList& otherList);
	};
}

#include "Slist.inl"