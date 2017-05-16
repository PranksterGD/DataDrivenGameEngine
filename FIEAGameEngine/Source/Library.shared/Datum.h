#pragma once
#include <cstdint>
#include <string>
#define GLM_FORCE_CXX98
#include "glm/glm/glm/glm.hpp"
#include "RTTI.h"
namespace FieaGameEngine
{
	class Scope;
	enum class DatumType
	{
		INVALID,
		INTEGER,
		FLOAT,
		VECTOR,
		MATRIX,
		STRING,
		POINTER,
		TABLE
	};

	class Datum final
	{
	public:
		/** The constructor that creates a Datum and defaults its type to invalid. Does not
		reserve any memory. */
		Datum(); 

		/** Copy constructor for the datum. 
		* @param otherDatum- The other datum to which this datum is to be copied to.*/
		Datum(const Datum& otherDatum);

		Datum(Datum&& otherDatum);

		/** Assignment operator for the datum.
		* @param otherDatum- The other datum to which this datum is to be assigned to.
		* @return A reference to the datum after the assignment is complete.*/
		Datum& operator=(const Datum& otherDatum);

		Datum& operator=(Datum&& otherDatum);

		/** Integer scalar assignment operator for the datum
		*If the datum has no data, sets the datum type to integer and pushes back the value.
		*Else, sets the first element of the datum to be the value.
		* @param value- The value that the datum is to be assigned to.
		* @return A reference to the datum after the assignment is complete.
		* @exception Throws an exception if the datum type is not either integer or invalid.*/
		Datum& operator=(const std::int32_t& value);

		/** Float scalar assignment operator for the datum
		*If the datum has no data, sets the datum type to float and pushes back the value.
		*Else, sets the first element of the datum to be the value.
		* @param value- The value that the datum is to be assigned to.
		* @return A reference to the datum after the assignment is complete.
		* @exception Throws an exception if the datum type is not either float or invalid.*/
		Datum& operator=(const float& value);

		/** String scalar assignment operator for the datum
		*If the datum has no data, sets the datum type to string and pushes back the value.
		*Else, sets the first element of the datum to be the value.
		* @param value- The value that the datum is to be assigned to.
		* @return A reference to the datum after the assignment is complete.
		* @exception Throws an exception if the datum type is not either string or invalid.*/
		Datum& operator=(const std::string& value);

		/** Vector scalar assignment operator for the datum
		*If the datum has no data, sets the datum type to vector and pushes back the value.
		*Else, sets the first element of the datum to be the value.
		* @param value- The value that the datum is to be assigned to.
		* @return A reference to the datum after the assignment is complete.
		* @exception Throws an exception if the datum type is not either vector or invalid.*/
		Datum& operator=(const glm::vec4& value);

		/** Matrix scalar assignment operator for the datum
		*If the datum has no data, sets the datum type to matrix and pushes back the value.
		*Else, sets the first element of the datum to be the value.
		* @param value- The value that the datum is to be assigned to.
		* @return A reference to the datum after the assignment is complete.
		* @exception Throws an exception if the datum type is not either matrix or invalid.*/
		Datum& operator=(const glm::mat4 &value);

		/** RTTI Pointer scalar assignment operator for the datum
		*If the datum has no data, sets the datum type to pointer and pushes back the value.
		*Else, sets the first element of the datum to be the value.
		* @param value- The value that the datum is to be assigned to.
		* @return A reference to the datum after the assignment is complete.
		* @exception Throws an exception if the datum type is not either pointer or invalid.*/
		Datum& operator=(RTTI* value);

		Datum& operator=(Scope* value);

		/** Destructor for the datum that clears all memory */
		~Datum();

		/** Function that returns the type of the datum.
		* @return- A constant reference to the type of the datum.*/
		const DatumType& Type() const;

		/** Function that sets the type of the datum.
		* @param type- The type to set the datum to.
		* @exception Throws an exception if the type of the datum before it is set is not invalid.*/
		void SetType(const DatumType& type);

		/** Function that returns the number of elements in the datum.
		* @return The size of the datum.*/
		std::uint32_t Size() const;

		/** Function that returns the capacity of the datum.
		* @return The capacity of the datum.*/
		std::uint32_t Capacity() const;

		/** Function that sets the size of the datum to a specified value.
		* If the passed in size is greater than the capacity of the datum, the capacity grow.s
		* If the passed in size is less than the size of the datum, the data is truncated, but the
		* capacity remains unchanged.
		* @param size- The new size of the datum.*/
		void ReSize(std::uint32_t size);

		/** Function that destroys all the elements in the datum, sets its size and capacity to zero,
		 frees all the memory and sets the type to invalid.*/
		void Clear();

		/** Function that sets the datum to point to an external integer array. 
		* If the datum currently has any internal storage, the data is cleared.
		* Sets the type of the datum to be integer if the type is invalid.
		* @param newArray- The array that the datum is to point to.
		* @param size- The size of the new array.
		* @exception- Throws an exception of the type of the datum is not integer.*/
		void SetStorage(std::int32_t* newArray, std::uint32_t size);

		/** Function that sets the datum to point to an external float array.
		* If the datum currently has any internal storage, the data is cleared.
		* Sets the type of the datum to be float if the type is invalid.
		* @param newArray- The array that the datum is to point to.
		* @param size- The size of the new array.
		* @exception- Throws an exception of the type of the datum is not float.*/
		void SetStorage(float* newArray, std::uint32_t size);

		/** Function that sets the datum to point to an external string array.
		* If the datum currently has any internal storage, the data is cleared.
		* Sets the type of the datum to be string if the type is invalid.
		* @param newArray- The array that the datum is to point to.
		* @param size- The size of the new array.
		* @exception- Throws an exception of the type of the datum is not string.*/
		void SetStorage(std::string* newArray, std::uint32_t size);

		/** Function that sets the datum to point to an external vector array.
		* If the datum currently has any internal storage, the data is cleared.
		* Sets the type of the datum to be vector if the type is invalid.
		* @param newArray- The array that the datum is to point to.
		* @param size- The size of the new array.
		* @exception- Throws an exception of the type of the datum is not vector.*/
		void SetStorage(glm::vec4* newArray, std::uint32_t size);

		/** Function that sets the datum to point to an external matrix array.
		* If the datum currently has any internal storage, the data is cleared.
		* Sets the type of the datum to be matrix if the type is invalid.
		* @param newArray- The array that the datum is to point to.
		* @param size- The size of the new array.
		* @exception- Throws an exception of the type of the datum is not matrix.*/
		void SetStorage(glm::mat4* newArray, std::uint32_t size);

		/** Function that sets the datum to point to an external RTTI pointer array.
		* If the datum currently has any internal storage, the data is cleared.
		* Sets the type of the datum to be pointer if the type is invalid.
		* @param newArray- The array that the datum is to point to.
		* @param size- The size of the new array.
		* @exception- Throws an exception of the type of the datum is not pointer.*/
		void SetStorage(RTTI** newArray, std::uint32_t size);


		/** Comparison operator for the datum.
		* Two datums are equal if they have the same type, size, isExternal, and all
		their elements are the same.
		* @param otherDatum- The datum to be compared against.
		* @return A boolean- True if the datums are equal, false otherwise.*/
		bool operator==(const Datum&otherDatum) const;

		/** Scalar comparison operator for the datum.
		* If the Datum is not of type integer, or if the datum has more than one element, returns false.
		* Else, compares the value of the element of the datum with the value passed in.
		* @param value- The value to be compared against.
		* @return A boolean- True if equal, false otherwise.*/
		bool operator==(const std::int32_t& value) const;

		/** Scalar comparison operator for the datum.
		* If the Datum is not of type float, or if the datum has more than one element, returns false.
		* Else, compares the value of the element of the datum with the value passed in.
		* @param value- The value to be compared against.
		* @return A boolean- True if equal, false otherwise.*/
		bool operator==(const float& value) const;

		/** Scalar comparison operator for the datum.
		* If the Datum is not of type string, or if the datum has more than one element, returns false.
		* Else, compares the value of the element of the datum with the value passed in.
		* @param value- The value to be compared against.
		* @return A boolean- True if equal, false otherwise.*/
		bool operator==(const std::string& value) const;

		/** Scalar comparison operator for the datum.
		* If the Datum is not of type vector, or if the datum has more than one element, returns false.
		* Else, compares the value of the element of the datum with the value passed in.
		* @param value- The value to be compared against.
		* @return A boolean- True if equal, false otherwise.*/
		bool operator==(const glm::vec4& value) const;

		/** Scalar comparison operator for the datum.
		* If the Datum is not of type matrix, or if the datum has more than one element, returns false.
		* Else, compares the value of the element of the datum with the value passed in.
		* @param value- The value to be compared against.
		* @return A boolean- True if equal, false otherwise.*/
		bool operator==(const glm::mat4& value) const;

		/** Scalar comparison operator for the datum.
		* If the Datum is not of type pointer, or if the datum has more than one element, returns false.
		* Else, compares the value of the element of the datum with the value passed in.
		* @param value- The value to be compared against.
		* @return A boolean- True if equal, false otherwise.*/
		bool operator==(const RTTI* value) const;

		/** Scalar comparison operator for the datum.
		* If the Datum is not of type table, or if the datum has more than one element, returns false.
		* Else, compares the value of the element of the datum with the value passed in.
		* @param value- The value to be compared against.
		* @return A boolean- True if equal, false otherwise.*/
		bool operator==(const Scope& value) const;

		/** Inequality operator for the datum.
		* Two datums are unequal if they have different types or size or isExternal or if any of
		their elements are the different.
		* @param otherDatum- The datum to be compared against.
		* @return A boolean- True if the datums are equal, false otherwise.*/
		bool operator!=(const Datum&otherDatum) const;

		/** Scalar inequality operator for the datum.
		* If the Datum is not of type integer, or if the datum has more than one element, returns true.
		* Else, compares the value of the element of the datum with the value passed in.
		* @param value- The value to be compared against.
		* @return A boolean- True if unequal, false otherwise.*/
		bool operator!=(const std::int32_t& value) const;

		/** Scalar inequality operator for the datum.
		* If the Datum is not of type float, or if the datum has more than one element, returns true.
		* Else, compares the value of the element of the datum with the value passed in.
		* @param value- The value to be compared against.
		* @return A boolean- True if unequal, false otherwise.*/
		bool operator!=(const float& value) const;

		/** Scalar inequality operator for the datum.
		* If the Datum is not of type string, or if the datum has more than one element, returns true.
		* Else, compares the value of the element of the datum with the value passed in.
		* @param value- The value to be compared against.
		* @return A boolean- True if unequal, false otherwise.*/
		bool operator!=(const std::string& value) const;

		/** Scalar inequality operator for the datum.
		* If the Datum is not of type vector, or if the datum has more than one element, returns true.
		* Else, compares the value of the element of the datum with the value passed in.
		* @param value- The value to be compared against.
		* @return A boolean- True if unequal, false otherwise.*/
		bool operator!=(const glm::vec4& value) const;

		/** Scalar inequality operator for the datum.
		* If the Datum is not of type matrix, or if the datum has more than one element, returns true.
		* Else, compares the value of the element of the datum with the value passed in.
		* @param value- The value to be compared against.
		* @return A boolean- True if unequal, false otherwise.*/
		bool operator!=(const glm::mat4& value) const;

		/** Scalar inequality operator for the datum.
		* If the Datum is not of type pointer, or if the datum has more than one element, returns true.
		* Else, compares the value of the element of the datum with the value passed in.
		* @param value- The value to be compared against.
		* @return A boolean- True if unequal, false otherwise.*/
		bool operator!=(const RTTI* value) const;

		/** Scalar inequality operator for the datum.
		* If the Datum is not of type table, or if the datum has more than one element, returns true.
		* Else, compares the value of the element of the datum with the value passed in.
		* @param value- The value to be compared against.
		* @return A boolean- True if unequal, false otherwise.*/
		bool operator!=(const Scope& value) const;

		/** Function that sets the element at an index of the datum to be a new value.
		* @param value- The value to set.
		* @param index- The index to set the value at.
		* @exception- Throws an exception if the index is greater than the size of the datum, or if
		 the datum type is not integer.*/
		void Set(const std::int32_t& value, std::uint32_t index = 0);

		/** Function that sets the element at an index of the datum to be a new value.
		* @param value- The value to set.
		* @param index- The index to set the value at.
		* @exception- Throws an exception if the index is greater than the size of the datum, or if
		the datum type is not float.*/
		void Set(const float& value, std::uint32_t index = 0);

		/** Function that sets the element at an index of the datum to be a new value.
		* @param value- The value to set.
		* @param index- The index to set the value at.
		* @exception- Throws an exception if the index is greater than the size of the datum, or if
		the datum type is not string.*/
		void Set(const std::string& value, std::uint32_t index = 0);

		/** Function that sets the element at an index of the datum to be a new value.
		* @param value- The value to set.
		* @param index- The index to set the value at.
		* @exception- Throws an exception if the index is greater than the size of the datum, or if
		the datum type is not vector.*/
		void Set(const glm::vec4& value, std::uint32_t index = 0);

		/** Function that sets the element at an index of the datum to be a new value.
		* @param value- The value to set.
		* @param index- The index to set the value at.
		* @exception- Throws an exception if the index is greater than the size of the datum, or if
		the datum type is not matrix.*/
		void Set(const glm::mat4& value, std::uint32_t index = 0);

		/** Function that sets the element at an index of the datum to be a new value.
		* @param value- The value to set.
		* @param index- The index to set the value at.
		* @exception- Throws an exception if the index is greater than the size of the datum, or if
		the datum type is not pointer.*/
		void Set(RTTI* value, std::uint32_t index = 0);

		/** Function that sets the element at an index of the datum to be a new value.
		* @param value- The value to set.
		* @param index- The index to set the value at.
		* @exception- Throws an exception if the index is greater than the size of the datum, or if
		the datum type is not table.*/
		void Set(Scope* value, std::uint32_t index = 0);

		/** Function that  adds a new element to the datum.
		* Reserves more memory if the datum's capacity is already full.
		* Sets the datum type to be integer if it is invalid.
		* @param value- The new element to be added.
		* @exception- Throws an exception if the datum type is not integer or invalid.*/
		void PushBack(const std::int32_t& value);

		/** Function that  adds a new element to the datum.
		* Reserves more memory if the datum's capacity is already full.
		* Sets the datum type to be float if it is invalid.
		* @param value- The new element to be added.
		* @exception- Throws an exception if the datum type is not float or invalid.*/
		void PushBack(const float& value);

		/** Function that  adds a new element to the datum.
		* Reserves more memory if the datum's capacity is already full.
		* Sets the datum type to be string if it is invalid.
		* @param value- The new element to be added.
		* @exception- Throws an exception if the datum type is not string or invalid.*/
		void PushBack(const std::string& value);

		/** Function that  adds a new element to the datum.
		* Reserves more memory if the datum's capacity is already full.
		* Sets the datum type to be vector if it is invalid.
		* @param value- The new element to be added.
		* @exception- Throws an exception if the datum type is not vector or invalid.*/
		void PushBack(const glm::vec4& value);

		/** Function that  adds a new element to the datum.
		* Reserves more memory if the datum's capacity is already full.
		* Sets the datum type to be matrix if it is invalid.
		* @param value- The new element to be added.
		* @exception- Throws an exception if the datum type is not matrix or invalid.*/
		void PushBack(const glm::mat4& value);

		/** Function that  adds a new element to the datum.
		* Reserves more memory if the datum's capacity is already full.
		* Sets the datum type to be pointer if it is invalid.
		* @param value- The new element to be added.
		* @exception- Throws an exception if the datum type is not pointer or invalid.*/
		void PushBack(RTTI* value);

		/** Function that  adds a new element to the datum.
		* Reserves more memory if the datum's capacity is already full.
		* Sets the datum type to be table if it is invalid.
		* @param value- The new element to be added.
		* @exception- Throws an exception if the datum type is not table or invalid.*/
		void PushBack(Scope* value);

		/** Templated Get method, that returns the element at a specified index.
		* @param index- The index whose element is to be returned.
		* @param return- The value at the index.
		* @exception- Throws an exception of the datum type is not the type of the template argument
		 or if the index is greater than the size of the datum.*/
		template<typename T>
		T Get(std::uint32_t index = 0);

		/** Const version of the templated Get method, that returns the element at a specified index.
		* @param index- The index whose element is to be returned.
		* @param return- The value at the index.
		* @exception- Throws an exception of the datum type is not the type of the template argument
		or if the index is greater than the size of the datum.*/
		template<typename T>
		const T Get(std::uint32_t index = 0) const;

		/** Function that sets the value at a particular index, by parsing a string.
		* @param valueToParse- The string that holds the value to be set.
		* @param index- The index to be set.
		* @exception- Throws exception of the index is out of bounds, if the type of the datum
		 is invalid, or if the parsing failed.*/
		void SetFromString(const std::string& valueToParse, std::uint32_t index = 0);

		void PushBackFromString(const std::string& valueToParse);

		/** Function that returns the contents of the datum at a particular index in a string form.
		* @param index- The index which is to be converted to a string
		* @return The string format of the element at the specified index
		* @exception- Throws an exception if the type of the datum is not set..*/
		std::string ToString(std::uint32_t index = 0);

		/** Function that increases  the capacity of the datum to the passed in amount. Does nothing if
		 the passed in value is less that the current capacity.
		 * @param newCapacity- The new capacity of the datum.*/
		void Reserve(const std::uint32_t newCapacity);

		bool Remove(Scope* value);

		bool IsExternal() const;

	private:

		union DatumUnion
		{
			std::int32_t* intArray;
			float* floatArray;
			std::string* stringArray;
			glm::vec4* vectorArray;
			glm::mat4* matrixArray;
			RTTI** RTTIArray;
			Scope** ScopeArray;
			void* voidPointer;
		};

		DatumUnion mDatum;
		std::uint32_t mSize;
		std::uint32_t mCapacity;
		DatumType mDatumType;
		bool mIsExternal;
	};

	/** Integer specialization of the templated Get method.
	* @param index- The index whose element is to be returned.
	* @param return- A reference to the value at the index.
	* @exception- Throws an exception of the datum type is not of type integer.
	or if the index is greater than the size of the datum.*/
	template<>
	 int32_t& Datum::Get<int32_t&>(std::uint32_t index);

	 /** float specialization of the templated Get method.
	 * @param index- The index whose element is to be returned.
	 * @param return- A reference to the value at the index.
	 * @exception- Throws an exception of the datum type is not of type float.
	 or if the index is greater than the size of the datum.*/
	template<>
	 float& Datum::Get<float&>(std::uint32_t index);

	 /** string specialization of the templated Get method.
	 * @param index- The index whose element is to be returned.
	 * @param return- A reference to the value at the index.
	 * @exception- Throws an exception of the datum type is not of type string.
	 or if the index is greater than the size of the datum.*/
	template<>
	 std::string& Datum::Get<std::string&>(std::uint32_t index);

	 /** Vector specialization of the templated Get method.
	 * @param index- The index whose element is to be returned.
	 * @param return- A reference to the value at the index.
	 * @exception- Throws an exception of the datum type is not of type vector.
	 or if the index is greater than the size of the datum.*/
	template<>
	 glm::vec4& Datum::Get<glm::vec4&>(std::uint32_t index);

	 /** Matrix specialization of the templated Get method.
	 * @param index- The index whose element is to be returned.
	 * @param return- A reference to the value at the index.
	 * @exception- Throws an exception of the datum type is not of type matrix.
	 or if the index is greater than the size of the datum.*/
	template<>
	 glm::mat4& Datum::Get<glm::mat4&>(std::uint32_t index);

	 /** Pointer specialization of the templated Get method.
	 * @param index- The index whose element is to be returned.
	 * @param return- A reference to the value at the index.
	 * @exception- Throws an exception of the datum type is not of type pointer.
	 or if the index is greater than the size of the datum.*/
	template<>
	 RTTI*& Datum::Get<RTTI*&>(std::uint32_t index);

	 /** Table specialization of the templated Get method.
	 * @param index- The index whose element is to be returned.
	 * @param return- A reference to the value at the index.
	 * @exception- Throws an exception of the datum type is not of type Table.
	 or if the index is greater than the size of the datum.*/
	 template<>
	 Scope*& Datum::Get<Scope*&>(std::uint32_t index);

	 /** Const version of the integer specialization of the templated Get method.
	 * @param index- The index whose element is to be returned.
	 * @param return- A const reference to the value at the index.
	 * @exception- Throws an exception of the datum type is not of type integer.
	 or if the index is greater than the size of the datum.*/
	template<>
	 const int32_t& Datum::Get<const int32_t&>(std::uint32_t index) const;

	 /** Const version of the float specialization of the templated Get method.
	 * @param index- The index whose element is to be returned.
	 * @param return- A const reference to the value at the index.
	 * @exception- Throws an exception of the datum type is not of type float.
	 or if the index is greater than the size of the datum.*/
	template<>
	 const float& Datum::Get<const float&>(std::uint32_t index) const;

	 /** Const version of the string specialization of the templated Get method.
	 * @param index- The index whose element is to be returned.
	 * @param return- A const reference to the value at the index.
	 * @exception- Throws an exception of the datum type is not of type string.
	 or if the index is greater than the size of the datum.*/
	template<>
	 const std::string& Datum::Get<const std::string&>(std::uint32_t index) const;

	 /** Const version of the vector specialization of the templated Get method.
	 * @param index- The index whose element is to be returned.
	 * @param return- A const reference to the value at the index.
	 * @exception- Throws an exception of the datum type is not of type vector.
	 or if the index is greater than the size of the datum.*/
	template<>
	 const glm::vec4& Datum::Get<const glm::vec4&>(std::uint32_t index) const;

	 /** Const version of the matrix specialization of the templated Get method.
	 * @param index- The index whose element is to be returned.
	 * @param return- A const reference to the value at the index.
	 * @exception- Throws an exception of the datum type is not of type matrix.
	 or if the index is greater than the size of the datum.*/
	template<>
	 const glm::mat4& Datum::Get<const glm::mat4&>(std::uint32_t index) const;

	 /** Const version of the pointer specialization of the templated Get method.
	 * @param index- The index whose element is to be returned.
	 * @param return- A const reference to the value at the index.
	 * @exception- Throws an exception of the datum type is not of type pointer.
	 or if the index is greater than the size of the datum.*/
	 template<>
	const RTTI*& Datum::Get<const RTTI*&>(std::uint32_t index) const;

	/** Const version of the table specialization of the templated Get method.
	* @param index- The index whose element is to be returned.
	* @param return- A const reference to the value at the index.
	* @exception- Throws an exception of the datum type is not of type table.
	or if the index is greater than the size of the datum.*/
	template<>
	const Scope*& Datum::Get<const Scope*&>(std::uint32_t index) const;

}



