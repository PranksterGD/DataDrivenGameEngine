#pragma once
#include "Hashmap.h"
#include "RTTI.h"
#include "Datum.h"
namespace FieaGameEngine
{
	class Scope : public RTTI
	{


		RTTI_DECLARATIONS(Scope, RTTI)

	protected:

		typedef Hashmap <std::string, Datum>::Iterator Iterator;
		typedef Hashmap <std::string, Datum> TableType;
		typedef std::pair<std::string, Datum> EntryType;
		TableType mTable;

	public:

		/**Default constructor for the Scope that reserves memory.
		* @param-capacity: The initial capacity to reserve. Defaulted to 3 if no argument is passed in.*/
		explicit Scope(std::int32_t capacity = 3);

		/**Copy constructor for the scope
		* @param-otherScope: The other scope that is to be copied to.*/
		Scope(const Scope& otherScope);

		Scope(Scope&& otherScope);

		/**Copy constructor for the scope
		* @param-otherScope: The other scope that is to be assigned to.
		* @return: A reference to the scope after it has been assigned.*/
		Scope& operator=(const Scope& otherScope);

		Scope& operator=(Scope&& otherScope);

		/** Function that searches the scope for a specified key.
		* @param- key: The key to be searched for.
		* @return: A pointer to the datum referred to by they key, if the key is found.
		*Null pointer if the key is not found.*/
		Datum* Find(const std::string& key);

		/** Const version of the function that searches the scope for a specified key.
		* @param- key: The key to be searched for.
		* @return: A const pointer to the datum referred to by they key, if the key is found.
		* Null pointer if the key is not found.*/
		const Datum* Find(const std::string& key) const;

		/** Function that searches the scope for a specified key. If not found, then proceeds to
		* search the scope's parent for the key, as long as the next parent is not null.
		* @param- key: The key to be searched for.
		* @param-foundScope:Functions as an output parameter to set the actual scope where the key was found.
		* @return: A pointer to the datum referred to by they key, if the key is found.
		* Null pointer if the key is not found.*/
		Datum* Search(const std::string& key, Scope** foundScope = nullptr);


		/** Const version of the function that searches the scope for a specified key. If not found, then proceeds to
		* search the scope's parent for the key, as long as the next parent is not null.
		* @param- key: The key to be searched for.
		* @param-foundScope:Functions as an output parameter to set the actual scope where the key was found.
		* @return: A const pointer to the datum referred to by they key, if the key is found.
		* Null pointer if the key is not found.*/
		const Datum* Search(const std::string& key, Scope** returnScope = nullptr) const;

		/** Function that appends a new key-datum pair to the scope at a specified key.
		* @param key: They key where the new pair is to be appended to.
		* @return: A reference to the newly created datum at the key, if the key did not already exist,
		* or a reference to the datum that already existed at the specified key.*/
		Datum& Append(const std::string& key);


		/** Function that appends a new key-datum pair to the scope  at a specified key if necessary
		* and pushing back a new scope to the datum at the specified key.
		* @param key: They key where the new pair is to be appended to.
		* @return: A reference to the newly created scope at the key.
		* @exception: Throws an exception if a datum is found at the specified key that is not of type table*/
		Scope& AppendScope(const std::string& key);

		/** Function that adopts a scope into a specified key.
		* @param- scopeToAdopt: The scope that is to be adopted.
		* @param- key: The key where the scope is to be adopted to.
		* @exception: Throws an exception if a datum is found at the specified key that is not of type table*/
		void Adopt(Scope& scopeToAdpot, const std::string& key);

		/** Function that returns the parent of the scope.
		* @return: A pointer to the parent of the scope, null pointer if the scope has no parent.*/
		Scope* GetParent();

		/** A const function that returns the parent of the scope.
		* @return: A const pointer to the parent of the scope, null pointer if the scope has no parent.*/
		const Scope* GetParent() const;

		/** Subscript operator for the scope that returns a reference to a datum at a specified index.
		* @param index: The index to be accessed.
		* @return : A reference to the datum at the index.*/
		Datum& operator[] (std::uint32_t index);

		/** Subscript operator for the scope that returns a reference to a datum at a specified key.
		* @param key: The key to be accessed.
		* @return : A reference to the datum at the key.*/
		Datum& operator[] (const std::string& key);

		/** Const Subscript operator for the scope that returns a reference to a datum at a specified index.
		* @param index: The index to be accessed.
		* @return : A const reference to the datum at the index.*/
		const Datum& operator[] (std::uint32_t index) const;

		/** Const Subscript operator for the scope that returns a reference to a datum at a specified key.
		* @param key: The key to be accessed.
		* @return : A const reference to the datum at the key.*/
		const Datum& operator[] (const std::string& key) const;

		/** Equality operator for the scope.
		* @param otherScope: The other scope to be compared against.
		* @return A boolean- True if the scopes are equal, false otherwise.*/
		bool operator==(const Scope& otherScope) const;

		/** Inequality operator for the scope.
		* @param otherScope: The other scope to be compared against.
		* @return A boolean- True if the scopes are unequal, false otherwise.*/
		bool operator!=(const Scope& otherScope) const;

		/** Overridden equals method for the scope, that takes in an RTTI pointer.
		* @param rhs: A pointer to the other RTTI to be compared against.
		* @param A boolean- True if the rhs is a scope, and is equal to the lhs, false otherwise*/
		bool Equals(const RTTI* rhs) const override;

		/** Function that clears all the data in the scope and frees all the memory. */
		void Clear();

		/** Destructor for the scope, that removes itself from its parent, and then clears all its data */
		virtual ~Scope();

		Datum* FindContainedScope(Scope& scope, uint32_t& index);

		virtual Scope* Copy() const;	

		const Vector<EntryType*>& GetEntries() const;

	private:
		void Orphan(Scope& scopeToOrphan);

		void Reparent(Scope& otherScope);

		Vector <EntryType*> mOrderArray;
		Scope* mParent;
	};
}