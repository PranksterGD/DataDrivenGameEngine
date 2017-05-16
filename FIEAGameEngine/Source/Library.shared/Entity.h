#pragma once
#include <cstdint>
#include <string>
#include "Attributed.h"
#include "WorldState.h"
#include "Factory.h"

namespace FieaGameEngine
{
	class Sector;

	class Entity : public Attributed
	{
		RTTI_DECLARATIONS(Entity, Attributed)

	public:

		/**Constructor for the Entity.
		* @param: name- The name of the Entity, defaulted to an empty string is no name is specified.*/
		Entity(std::string name = "");

		/**Copy constructor for the Entity.
		* @param otherEntity- The other Entity that is to be copied from.*/
		Entity(const Entity& otherEntity);

		/**Move constructor for the Entity.
		* @param otherEntity- The other Entity that is to be moved from.*/
		Entity(Entity&& otherEntity);

		/**Assignment operator for the Entity.
		* @param otherEntity- The other Entity that is to be assigned to.
		* @return- A reference to the other Entity after assignment.*/
		Entity& operator=(Entity&& otherEntity);

		/**Move assignment operator for the Entity.
		* @param otherEntity - The other Entity that is to be moved to.
		* @return- A reference to the Entity after moving.*/
		Entity& operator=(const Entity& otherEntity);

		/**Function that returns the name of the Entity.
		* @return - A constant reference to a string that contains the name of the Entity.*/
		const std::string& Name() const;

		/**Function that returns the name of the Entity.
		* @return - A reference to a string that contains the name of the Entity.*/
		std::string& Name();

		/**Function that is used to the set the name of the Entity.
		* @param name- The new name of the Entity.*/
		void SetName(const std::string& name);

		/**Function that is used to get the sectors of the Sector.
		* @return - A constant reference to a datum that contains pointers to all the entities of the Sector.*/
		const Datum& Actions() const;

		/**Function that is used to get the sectors of the Sector.
		* @return - A reference to a datum that contains pointers to all the entities of the Sector.*/
		Datum& Actions();

		/**Function that is used to create a new entity and append it to the sector.
		* @param className- The name of the actual entity class that is to be created using the factory pattern.
		* @param instanceName- The name of entity that is to be created. */
		class Action* CreateAction(const std::string& className, const std::string& instanceName);

		/**Function that is used to change the sector that the Entity belongs to.
		* @param sector- The new sector that the Entity exists in.*/
		void SetSector(Sector& sector);

		/**Function that is used to get the sector that the sector Entity in.
		* @return- A constant pointer to the sector that the Entity belongs to.*/
		const Sector* GetSector() const;

		/**Function that is used to get the sector that the sector Entity in.
		* @return- A pointer to the sector that the Entity belongs to.*/
		Sector* GetSector();

		/**Function that updates the Entity and all elements within it.
		* @param worldState- A reference to the worldState of the game. */
		virtual void Update(WorldState& worldState);

		virtual Scope* Copy() const override;

		/**Destructor of the Entity that is defaulted. */
		virtual ~Entity() = default;

		static std::string sEntitiesTag;

		static std::string sActionsTag;

	protected:

		void InitalizeSignatures();

		void FixExternals();

		std::string mName;

		class Sector* mSector;
	};

#define ConcreteEntityFactory(ConcreteProductT) ConcreteFactory(ConcreteProductT, Entity)
}