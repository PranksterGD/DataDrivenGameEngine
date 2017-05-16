#pragma once
#include "Action.h"

namespace FieaGameEngine
{
	class ActionEvent final : public Action
	{
		RTTI_DECLARATIONS(ActionEvent, Action)

	public:

		/**Constructor for the ActionEvent.
		* @param: name- The name of the ActionEvent, defaulted to an empty string is no name is specified.*/
		ActionEvent(const std::string& name = "", const std::string& subType = "", std::int32_t delay = 0);

		/**Copy constructor for the ActionEvent.
		* @param otherActionEvent- The other ActionEvent that is to be copied from.*/
		ActionEvent(const ActionEvent& otherActionEvent);

		/**Move constructor for the ActionActionEvent.
		* @param otherActionEvent- The other ActionEvent that is to be moved from.*/
		ActionEvent(ActionEvent&& otherActionEvent);

		/**Assignment operator for the ActionEvent.
		* @param otherActionEvent- The other ActionEvent that is to be assigned to.
		* @return- A reference to the other Entity after assignment.*/
		ActionEvent& operator=(ActionEvent&& otherActionEvent);

		/**Move assignment operator for the ActionEvent.
		* @param otherActionEvent - The other ActionEvent that is to be moved to.
		* @return- A reference to the ActionEvent after moving.*/
		ActionEvent& operator=(const ActionEvent& otherActionEvent);
		
		/*Function that creates a new Event<ReactionAttributed> and copies all of the action's
		auxiliary attributes onto the message of the event, and then enqueues it.
		* @param worldState- The world state of the game world. */
		virtual void Update(WorldState& worldState) override;

		/*Function used to the set the delay of the event created by the action.
		* @param delay- The delay to set.*/
		void SetDelay(std::int32_t delay);

		/*Function to retrieve the delay of the event created by the action.
		* @return - An integer that is the delay.*/
		std::int32_t GetDelay() const;

		/*Function used to the set the subtype of the event created by the action.
		* @param delay- The subtype to set.*/
		void SetSubtype(const std::string& subtype);

		/*Function to retrieve the subtype of the event created by the action.
		* @return - An const string reference that holds the subtype.*/
		const std::string& GetSubtype() const;

		/*Virtual constructor for the action.*/
		virtual Scope* Copy() const override;

		/*Destructor for the event that is defaulted.*/
		~ActionEvent() = default;

	protected:

		void InitalizeSignatures();

		void FixExternals();

	private:

		std::string mSubtype;

		std::int32_t mDelay;
	};

	ConcreteActionFactory(ActionEvent)
}