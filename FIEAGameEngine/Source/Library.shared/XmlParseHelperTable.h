#pragma once
#include "IXmlParseHelper.h"
#include <cstdint>
#include "XmlParseMaster.h"
#include "Scope.h"

namespace FieaGameEngine
{
	class XmlParseHelperTable : public IXmlParseHelper
	{
	public:

		class SharedData : public XmlParseMaster::SharedData
		{
			RTTI_DECLARATIONS(SharedData, XmlParseMaster::SharedData)
		public:

			/**Default constructor for the shared data.
			* @param-capacity: Master associated with the shared data. Defaulted to null pointer if no argument is passed in.*/
			SharedData(XmlParseMaster* parseMaster = nullptr);

			/**Function that resets the shared data so that it is ready to be used to parse a new file */
			virtual void Initialize() override;

			/**Function that creates a new instance of the shared data.
			* @return- A pointer pointing to the new instance of shared data.*/
			virtual XmlParseMaster::SharedData* Clone() const override;

			/**Copy constructor for the shared data that is deleted. */
			SharedData(const SharedData& otherSharedData) = delete;

			/**Assignment for the shared data that is deleted. */
			SharedData& operator=(const SharedData& otherSharedData) = delete;

			~SharedData();

			Scope* mScope;
		};

		/**Default constructor for the helper. */
		XmlParseHelperTable();

		/**Copy constructor for the helper that is deleted. */
		XmlParseHelperTable(const XmlParseHelperTable& otherHelper) = delete;

		/**Assignment for the helper that is deleted. */
		XmlParseHelperTable& operator=(const XmlParseHelperTable& otherHelper) = delete;

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

		/**Function that creates a new instance of the helper
		* @return- A pointer pointing to the new instance of the helper.*/
		virtual FieaGameEngine::IXmlParseHelper* Clone() const override;

		/**Destructor for the helper */
		virtual ~XmlParseHelperTable();

		static const std::string sValueTag;
		static const std::string sNameTag;

	private:

		static const std::string sScopeTag;

	};
}
