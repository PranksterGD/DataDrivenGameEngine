#pragma once
#include "Attributed.h"
#include "World.h"
namespace FieaGameEngine
{
	class EventMessageAttributed : public Attributed
	{
	public:

		RTTI_DECLARATIONS(EventMessageAttributed, Attributed)

	public:

		/**Constructor for the EventMessageAttributed.
		* @param: name- The name of the EventMessageAttributed, defaulted to an empty string is no name is specified*/
		EventMessageAttributed(const std::string& subtype = "", WorldState* worldstate = nullptr);

		/**Copy constructor for the EventMessageAttributed.
		* @param otherEventMessageAttributed- The other EventMessageAttributed that is to be copied from.*/
		EventMessageAttributed(const EventMessageAttributed& otherEventMessageAttributed);

		/**Move constructor for the EventMessageAttributed.
		* @param otherEventMessageAttributed- The other EventMessageAttributed that is to be moved from.*/
		EventMessageAttributed(EventMessageAttributed&& otherEventMessageAttributed);

		/**Assignment operator for the EventMessageAttributed.
		* @param otherEventMessageAttributed- The other EventMessageAttributed that is to be assigned to.
		* @return- A reference to the EventMessageAttributed after assignment.*/
		EventMessageAttributed& operator=(const EventMessageAttributed& otherEventMessageAttributed);

		/**Move assignment operator for the EventMessageAttributed.
		* @param otherEventMessageAttributed - The other EventMessageAttributed that is to be moved to.
		* @return- A reference to the EventMessageAttributed after moving.*/
		EventMessageAttributed& operator=(EventMessageAttributed&& otherEventMessageAttributed);

		/*Function to retrieve the subtype of the event message.
		* @return - An const string reference that holds the subtype.*/
		const std::string& GetSubType() const;

		/*Function used to the set the subtype of the event message.
		* @param delay- The subtype to set.*/
		void SetSubType(const std::string& subtype);

		/*Function to retrieve the worldstate associated with the event message.
		* @return - A world state pointer.*/
		WorldState* GetWorldState() const;

		/*Function used to the set the worldstate associated with the event message.
		* @param delay- The worldstate to set.*/
		void SetWorldState(WorldState& world);

		/*Virtual constructor for the event message.*/
		virtual Scope* Copy() const override;

		/*Destructor for the event message that is defaulted.*/
		virtual~EventMessageAttributed() = default;

		static std::string sSubtypeTag;

	protected:

		void InitalizeSignatures();
		void FixExternals();

	private:

		std::string mSubType;
		WorldState* mWorldState;
		static std::string sWorldTag;
	};
}