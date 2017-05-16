#pragma once
#include <cstdint>
#include <string>
#include "Attributed.h"
#include "WorldState.h"
#include "Vector.h"
#include "EventQueue.h"
namespace FieaGameEngine
{
	 class World final  : public Attributed 
	{
		RTTI_DECLARATIONS(World, Attributed)
	public:

		/**Constructor for the world.
		* @param: name- The name of the world, defaulted to an empty string is no name is specified*/
		World(std::string name = "");

		/**Copy constructor for the world.
		* @param otherWorld- The other world that is to be copied from.*/
		World(const World& otherWorld);

		/**Move constructor for the world.
		* @param otherworld- The other world that is to be moved from.*/
		World(World&& otherWorld);

		/**Assignment operator for the world.
		* @param otherworld- The other world that is to be assigned to.
		* @return- A reference to the world after assignment.*/
		World& operator=(const World& otherWorld);

		/**Move assignment operator for the world.
		* @param otherWorld - The other world that is to be moved to.
		* @return- A reference to the world after moving.*/
		World& operator=(World&& otherWorld);

		/**Function that returns the name of the world.
		* @return - A constant reference to a string that contains the name of the world.*/
		const std::string& Name() const;

		/**Function that returns the name of the world.
		* @return - A reference to a string that contains the name of the world.*/
		std::string& Name();
		
		/**Function that is used to the set the name of the world.
		* @param name- The new name of the world.*/
		void SetName(const std::string& name);

		/**Function that is used to get the sectors of the world.
		* @return - A constant reference to a datum that contains pointers to all the sectors of the world.*/
		const Datum& Sectors() const;

		/**Function that is used to get the sectors of the world.
		* @return - A reference to a datum that contains pointers to all the sectors of the world.*/
		Datum& Sectors();

		const Datum& Actions() const;

		Datum& Actions();

		/**Function that is used to create a new sector and append it to the world.
		* @param name- The name of the sector to be created.*/
		class Sector* CreateSector(const std::string& name);

		class Action* CreateAction(const std::string& className, const std::string& instanceName);

		/**Function that updates the world and all elements within it.
		* @param worldState- A reference to the worldState of the game. */
		void Update(WorldState& worldState);

		void AddToDeletionQueue(Scope* scopeToDelete);

		/**Destructor of the world that is defaulted. */
		virtual ~World() = default;

		static std::string sNameTag;

		virtual Scope* Copy() const override;

		 EventQueue& GetEventQueue();

		const  EventQueue& GetEventQueue() const;


	private:

		void InitalizeSignatures();
		void FixExternals();

		std::string mName;

		Vector<Scope*> mDeletionQueue;
		EventQueue mEventQueue;
	};
}