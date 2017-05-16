#pragma once
#include "IXmlParseHelper.h"
#include <cstdint>
#include "XmlParseMaster.h"

namespace UnitTest
{
	class XmlParseHelperFoo : public FieaGameEngine::IXmlParseHelper
	{
	public:

		class SharedData : public FieaGameEngine::XmlParseMaster::SharedData
		{
			RTTI_DECLARATIONS(SharedData, FieaGameEngine::XmlParseMaster::SharedData)
		public:

			/**Default constructor for the shared data.
			* @param-capacity: Master associated with the shared data. Defaulted to null pointer if no argument is passed in.*/
			SharedData(FieaGameEngine::XmlParseMaster* parseMaster = nullptr);

			/**Function that resets the shared data so that it is ready to be used to parse a new file */
			virtual void Initialize() override;

			/**Function that creates a new instance of the shared data.
			* @return- A pointer pointing to the new instance of shared data.*/
			virtual FieaGameEngine::XmlParseMaster::SharedData* Clone() const override;

			/**Copy constructor for the shared data that is deleted. */
			SharedData(const SharedData& otherSharedData) = delete;

			/**Assignment for the shared data that is deleted. */
			SharedData& operator=(const SharedData& otherSharedData) = delete;

			std::int32_t mHealth;
			std::int32_t mXPositon;
			std::int32_t mYPosition;
			std::int32_t mZPosition;
			std::int32_t mAmmo;
		};

		/**Default constructor for the helper. */
		XmlParseHelperFoo();

		/**Copy constructor for the helper that is deleted. */
		XmlParseHelperFoo(const XmlParseHelperFoo& otherHelper) = delete;

		/**Assignment for the helper that is deleted. */
		XmlParseHelperFoo& operator=(const XmlParseHelperFoo& otherHelper) = delete;

		/**Function that resets the helper so that it is ready to be used to parse a new file */
		virtual void Initialize(FieaGameEngine::XmlParseMaster* master) override;

		/**Function that attempts to the handle the start element callback event triggered by the parser.
		* @param name- The name of the field of the element.
		* @param map- A hashmap of the attribute names and values of the element
		* @return a boolean- True if the function succeeded in handling the event, false otherwise.*/
		virtual bool StartElementHandler(const std::string& name, const FieaGameEngine::Hashmap<std::string, std::string>& map)  override;

		/**Function that attempts to the handle the end element callback event triggered by the parser.
		* @param name- The name of the field of the element.
		* @return a boolean- True if the function succeeded in handling the event, false otherwise.*/
		virtual bool EndElementHandler(const std::string& name)  override;

		/**Function that attempts to the handle the character data event triggered by the parser.
		* @param data- A string that contains the character data.
		* @param length- The size of the string.
		* @return a boolean- True if the function succeeded in handling the event, false otherwise.*/
		virtual bool CharDataHandler(const std::string& data, std::uint32_t length)  override;

		/**Function that creates a new instance of the helper
		* @return- A pointer pointing to the new instance of the helper.*/
		virtual FieaGameEngine::IXmlParseHelper* Clone() const override;

		/**Destructor for the helper */
		virtual ~XmlParseHelperFoo();

		/**Function that returns the start element handler counter of the helper.
		* @return An integer that has the value of the start element handler counter.*/
		std::uint32_t StartElementHandlerCount();

		/**Function that returns the end element handler counter of the helper.
		* @return An integer that has the value of the end element handler counter.*/
		std::uint32_t EndElementHandlerCount();

		/**Function that returns the character data element handler counter of the helper.
		* @return An integer that has the value of the character data element handler counter.*/
		std::uint32_t CharDataHandlerCount();

		/**Function that returns the maximum depth reached by the helper.
		* @return An integer that has the value of the maximum depth reached by the helper.*/
		std::uint32_t MaxDepth();

		/**Function that is used to find out if the helper has been instantiated or not.
		* @return A boolean- True if the helper has been instantiated, false otherwise.*/
		bool IsInitialized();

	private:

		std::uint32_t mStartElementHandlerCount;
		std::uint32_t mEndElementHandlerCount;
		std::uint32_t mCharDataHandlerCount;
		std::uint32_t mMaxDepth;
		bool mIsInitialized;
		std::string mPreviousName;

	};
}
