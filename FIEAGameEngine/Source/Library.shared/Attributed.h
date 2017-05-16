#pragma once
#include "Vector.h"
#include "Hashmap.h"
#include "Scope.h"

namespace FieaGameEngine
{
	class Attributed : public Scope
	{

		RTTI_DECLARATIONS(Attributed, Scope)

	public:

		/**Default constructor for the Attribute that reserves memory.
		* @param-capacity: The initial capacity to reserve. Defaulted to 3 if no argument is passed in.*/
		explicit Attributed(std::int32_t capacity = 3);

		/**Copy constructor for the Attribute
		* @param-otherScope: The other Attribute that is to be copied to.*/
		Attributed(const Attributed& otherAttributed);

		/**Move Copy constructor for the Attribute
		* @param-otherAttributed: The other Attribute that is to be moved into this Attribute.*/
		Attributed(Attributed&& otherAttributed);

		/**Assignment operator for the Attribute
		* @param-otherAttributed: The other Attribute that is to be assigned to.
		* @return: A reference to the Attribute after it has been assigned.*/
		Attributed& operator= (const Attributed& otherAttributed);

		/**Move Assignment operator for the Attribute
		* @param-otherAttributed: The other Attribute that is to be moved into this Attribute.
		* @return: A reference to the Attribute after it has been assigned.*/
		Attributed& operator=(Attributed&& otherAttributed);

		/** Destructor for the Attribute, that is defaulted. */
		virtual ~Attributed() = default;

		/** Function that checks if a given string key is a prescribed attribute of the Attribute.
		* @param- key: The key to be checked.
		* @return: A boolean- True if the key is a prescribed attribute, false otherwise.*/
		bool IsPrescribedAttribute(const std::string& key) const;

		/** Function that checks if a given string key is an auxiliary attribute of the Attribute.
		* @param- key: The key to be checked.
		* @return: A boolean- True if the key is an auxiliary attribute, false otherwise.*/
		bool IsAuxiliaryAttribute(const std::string& key) const;

		/** Function that checks if a given string key is an attribute of the Attribute.
		* @param- key: The key to be checked.
		* @return: A boolean- True if the key is an attribute, false otherwise.*/
		bool IsAttribute(const std::string& key) const;

		/** Function that adds an auxiliary attribute to the Attribute.
		* @param- key: The name of the new attribute.
		* @return: A reference to the new datum created at the specified key.*/
		Datum& AppendAuxiliaryAttribute(const std::string& key);

		/** Static function that clears the prescribed attribute cache.*/
		static void ClearPrescribedAttributes();

		/** Function that returns a list of all prescribed attributes for the Attribute.
		* @return: A reference to the vector containing the names of all the attributes.*/
		Vector<std::string>& GetPrescribedAttributes();

		Vector<std::pair<std::string, Datum>*> GetAuxiliaryAttributes() const;

		/** Equality operator for the Attribute.
		* @param otherAttributed: The other Attribute to be compared against.
		* @return A boolean- True if the Attribute are equal, false otherwise.*/
		bool operator==(const Attributed& otherAttributed) const;

		/** Inequality operator for the Attribute.
		* @param otherAttributed: The other Attribute to be compared against.
		* @return A boolean- True if the Attribute are unequal, false otherwise.*/
		bool operator!=(const Attributed& otherAttributed) const;

		virtual Scope* Copy() const override;

		virtual bool Equals(const RTTI* rhs) const override;

	protected:

		void AddInternalAttribute(const std::string& key, std::int32_t defaultValue, std::uint32_t size = 1);

		void AddInternalAttribute(const std::string& key, float defaultValue, std::uint32_t size = 1);

		void AddInternalAttribute(const std::string& key, const std::string& defaultValue, std::uint32_t size = 1);

		void AddInternalAttribute(const std::string& key, const glm::vec4& defaultValue, std::uint32_t size = 1);

		void AddInternalAttribute(const std::string& key, const glm::mat4& defaultValue, std::uint32_t size = 1);

		void AddInternalAttribute(const std::string& key, RTTI* defaultValue, std::uint32_t size = 1);

		void AddExternalAttribute(const std::string& key, std::int32_t* value, std::uint32_t size);

		void AddExternalAttribute(const std::string& key, float* value, std::uint32_t size);

		void AddExternalAttribute(const std::string& key, std::string* value, std::uint32_t size);

		void AddExternalAttribute(const std::string& key, glm::vec4* value, std::uint32_t size);

		void AddExternalAttribute(const std::string& key, glm::mat4 *value, std::uint32_t size);

		void AddExternalAttribute(const std::string& key, RTTI** value, std::uint32_t size);

		Scope& AddScopeAttribute(const std::string&key);

		void AddScopeAttribute(const std::string&key, Scope& scope);

		void AddEmptyScopeAttribute(const std::string&key);

		void AddEmptyStringAttribute(const std::string&key);

		void InitalizeSignatures();

	private:
		static Hashmap <std::int64_t, Vector<std::string>> PrescribedAttributeList;
	};
}
