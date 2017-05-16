#pragma once
#include "Reaction.h"

namespace FieaGameEngine
{
	class ReactionAttributed final : public Reaction
	{
		RTTI_DECLARATIONS(ReactionAttributed, Reaction)

	public:

		/**Constructor for the ReactionAttirubted.
		* @param: name- The name of the ReactionAttirubted, defaulted to an empty string is no name is specified*/
		ReactionAttributed(const std::string& name = "");

		/**Copy constructor for the ReactionAttirubted.
		* @param otherReactionAttirubted- The other ReactionAttirubted that is to be copied from.*/
		ReactionAttributed(const ReactionAttributed& otherReactionAttirubted);

		/**Move constructor for the ReactionAttirubted.
		* @param otherReactionAttirubted- The other ReactionAttirubted that is to be moved from.*/
		ReactionAttributed(ReactionAttributed&& ReactionAttirubted);

		/**Assignment operator for the ReactionAttirubted.
		* @param otherReactionAttirubted- The other ReactionAttirubted that is to be assigned to.
		* @return- A reference to the ReactionAttirubted after assignment.*/
		ReactionAttributed& operator=(const ReactionAttributed& otherReactionAttirubted);

		/**Move assignment operator for the ReactionAttirubted.
		* @param otherReactionAttirubted - The other ReactionAttirubted that is to be moved to.
		* @return- A reference to the ReactionAttirubted after moving.*/
		ReactionAttributed& operator=(ReactionAttributed&& ReactionAttirubted);

		/*Function that receives events that fire. If the event is of type ReactionAttribute, copies
		the auxiliary attributes of the event's message into the reaction, and then calls update on its
		action list*/
		virtual void Notify(const EventPublisher& eventPublisher) override;

		/*Virtual constructor for the reaction.*/
		virtual Scope* Copy() const override;

		/*Destructor for the reaction that un-subscribes itself from events of type ReactionAttribute*/
		~ReactionAttributed();

	private:

		void InitalizeSignatures();
	};

	ConcreteReactionFactory(ReactionAttributed)
}