#pragma once
#include <cstdint>
#include <exception>
namespace FieaGameEngine
{
	template <typename T>
	class Vector
	{
	public:
		class Iterator
		{
			friend class Vector;
		public:
			/**The default constructor for the iterator. */
			Iterator();
			
			/**The copy constructor for the iterator.
			* @param otherIterator- The other Iterator from which the current iterator is to be
			copied from.
			*/
			Iterator(const Iterator& otherIterator);

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

			/**The assignment operator for the iterator.
			* @param otherIterator- The other Iterator to which the current iterator is to be
			assigned to.
			*/
			Iterator& operator=(const Iterator& otherIterator);

			/**The deference operator for the iterator.
			* @return A reference of the data pointed to by the iterator.
			*/
			T& operator*();

			/**The const version  deference operator for the iterator.
			* @return A const  reference of the data pointed to by the iterator.
			*/
			const T& operator* () const;
		private:
			Iterator(T* data, const Vector& owner);
			T* mData;
			const Vector* mOwner;
		};

		/** The default constructor that sets the size to zero and the capacity to
		the default value, and creates a buffer which can hold the capacity number of elements*/
		Vector(std::uint32_t capacity=defaultCapacity);

		/** The subscript operator for the vector.
		* @param index- The index value to access.
		* @return- A Reference to the data at the specified index.
		*/
		T& operator[](const std::uint32_t index);

		/** The const subscript operator for the vector.
		* @param index- The index value to access.
		* @return- A const  Reference to the data at the specified index.
		*/
		const T& operator[](const std::uint32_t index) const;

		/** Removes the last item from the vector, reduces size by one but keeps the
		capacity the same. Calls the destructor for the removed item.
		*/
		void PopBack();

		/** Checks if the vector is empty or not.
		* @return A boolean: True->Vector is empty. False->Vector is not empty.
		*/
		bool IsEmpty() const;

		/** Function that returns a constant reference to the element at the start of the vector.
		* @return A reference to the element at the  start of the vector.
		*/
		T& Front();

		/** Function that returns a constant reference to the element at the start of the vector.
		* @return A constant reference to the element at the  start of the vector.
		*/
		const T& Front() const;

		/** Function that returns a constant reference to the last element of the vector.
		* @return A reference to the last element of the vector.
		*/
		T& Back();

		/** Function that returns a constant reference to the last element of the vector.
		* @return A constant reference to the last element of the vector.
		*/
		const T& Back() const;

		/** Function that returns the size of the vector.
		* @return The size of the vector.
		*/
		std::uint32_t Size() const;

		/** Function that returns the capacity of the vector.
		* @return The capacity of the vector.
		*/
		std::uint32_t Capacity() const;

		/** Function that returns an iterator pointing to the first element of the vector.
		*@return An iterator pointing to the first element of the vector.
		*/
		Iterator begin() const;

		/** Function that returns a constant iterator that points to the memory location just 
		past the end of the vector.
		*@return A constant iterator that points to the memory location just past the
		end of the vector.
		*/
		const Iterator end() const;

		/** Function that appends an item to the end of the vector
		* @param value- The value to be appended to the vector
		*/
		Iterator PushBack(const T& value);

		/**The copy constructor that performs a deep copy.
		* @param otherVector The other vector that is to be copied.
		*/
		Vector(const Vector& otherVector);

		Vector(Vector&& otherVector);

		/** The assignment operator that assigns a vector to another, while performing a deep copy.
		* @param otherVector The other vector that is to be copied.
		* @return Reference to the current vector, after the other vector has been deep copied onto it.
		*/
		Vector& operator=(const Vector& otherVector);

		Vector& operator=(Vector&& otherVector);

		/** Function that returns  a reference to the  element at a specified index.
		* @param index- The index whose value is required..
		* @return Reference to the element at the specified index.
		*/
		T& At(const std::uint32_t index);

		/** Function that returns  a const  reference to the  element at a specified index.
		* @param index- The index whose value is required..
		* @return Const reference to the element at the specified index.
		*/
		const T& At(const std::uint32_t index) const;

		/** The destructor for the vector that clears all the elements in the vector and reduces
		the size to zero, then shrinks the capacity to match the size, and frees the buffer held
		by the vector.
		*/
		~Vector();

		/** Function that increases the capacity of the vector to a certain amount. Does nothing
		if the specified capacity is less than the current capacity.
		* @param newCapacity- The new capacity of the vector.
		* @return Const reference to the element at the specified index.
		*/
		void Reserve(const std::uint32_t newCapacity);

		/** Function that searches the vector  for a value and returns an iterator pointing to that value,
		or an iterator pointing to end if the value is not found.
		*@param value- The value to be searched for.
		*@return An iterator pointing to the found value.
		*/
		Iterator Find(const T& value) const;

		/** Function that clears all the elements in the vector, calls their destructors and
		sets the size to zero.
		*/
		void Clear();

		/** Function that removes the first occurrence of a value from the list. Does nothing if the value
		is not found in the list.
		*@param value- The value to be removed from the list.
		*/
		void Remove(const T& value);

		/** Function that removes all elements in the vector between two iterators.
		*@param value- The iterators between which the elements are to be removed.
		*/
		void Remove(Iterator& it, Iterator& otherIt);

		/**Function that sets the capacity of the vector equal to its size.
		*/
		void ShrinkToFit();

		/**Function that calls a functor to get the increment value of capacity
		when PushBack() needs more capacity.
		*/
		uint32_t Realloate();

		void Destroy();

	private:
		void DeepCopy(const Vector& otherVector);
		std::uint32_t mSize;
		std::uint32_t mCapacity;
		T* mBuffer;
		static const std::uint32_t defaultCapacity = 3;
	};
}

#include "Vector.inl"