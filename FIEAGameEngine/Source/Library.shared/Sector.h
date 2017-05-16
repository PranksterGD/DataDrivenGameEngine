#pragma once
#include <cstdint>
#include <string>
#include "Attributed.h"
#include "WorldState.h"
#include "Entity.h"
namespace FieaGameEngine
{
	class World;

	ConcreteEntityFactory(Entity)

	class Sector final : public Attributed
	{
		RTTI_DECLARATIONS(Sector, Attributed)

	public:

		/**Constructor for the Sector.
		* @param: name- The name of the Sector, defaulted to an empty string is no name is specified.*/
		Sector(std::string name = "");

		/**Copy constructor for the Sector.
		* @param otherSector- The other Sector that is to be copied from.*/
		Sector(const Sector& otherSector);

		/**Move constructor for the Sector.
		* @param otherSector- The other Sector that is to be moved from.*/
		Sector(Sector&& otherSector);

		/**Assignment operator for the Sector.
		* @param otherSector- The other Sector that is to be assigned to.
		* @return- A reference to the Sector after assignment.*/
		Sector& operator=(const Sector& otherSector);

		/**Move assignment operator for the Sector.
		* @param otherSector - The other Sector that is to be moved to.
		* @return- A reference to the Sector after moving.*/
		Sector& operator=(Sector&& otherSector);

		/**Function that returns the name of the Sector.
		* @return - A constant reference to a string that contains the name of the Sector.*/
		const std::string& Name() const;

		/**Function that returns the name of the Sector.
		* @return - A reference to a string that contains the name of the Sector.*/
		std::string& Name();

		/**Function that is used to the set the name of the Sector.
		* @param name- The new name of the Sector.*/
		void SetName(const std::string& name);

		/**Function that is used to get the sectors of the Sector.
		* @return - A constant reference to a datum that contains pointers to all the entities of the Sector.*/
		const Datum& Entities() const;

		/**Function that is used to get the sectors of the Sector.
		* @return - A reference to a datum that contains pointers to all the entities of the Sector.*/
		Datum& Entities();

		const Datum& Actions() const;

		Datum& Actions();

		/**Function that is used to create a new entity and append it to the sector.
		* @param className- The name of the actual entity class that is to be created using the factory pattern.
		* @param instanceName- The name of entity that is to be created. */
		class Entity* CreateEntity(const std::string& className, const std::string& instanceName);
		
		/**Function that is used to change the world that the sector belongs to.
		* @param world- The new world that the sector exists in.*/
		void SetWorld(World& world);

		/**Function that is used to get the world that the sector exists in.
		* @return- A constant pointer to the world that the sector belongs to.*/
		const World* GetWorld() const;

		/**Function that is used to get the world that the sector exists in.
		* @return- A pointer to the world that the sector belongs to.*/
		World* GetWorld();

		/**Function that updates the Sector and all elements within it.
		* @param worldState- A reference to the worldState of the game. */
		void Update(WorldState& worldState);


		/**Destructor of the Sector that is defaulted. */
		~Sector() = default;

		static std::string sSectorsTag;

		virtual Scope* Copy() const override;

	protected:

		void InitalizeSignatures();

		void FixExternals();

	private:

		std::string mName;

		class World* mWorld;
	};
}