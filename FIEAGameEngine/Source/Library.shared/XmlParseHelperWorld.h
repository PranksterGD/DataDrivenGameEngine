#pragma once
#include "IXmlParseHelper.h"
#include <cstdint>
#include "XmlParseMaster.h"
#include "Scope.h"

namespace FieaGameEngine
{
	class XmlParseHelperWorld : public IXmlParseHelper
	{
	public:

		

		/**Default constructor for the helper. */
		XmlParseHelperWorld();

		/**Copy constructor for the helper that is deleted. */
		XmlParseHelperWorld(const XmlParseHelperWorld& otherHelper) = delete;

		/**Assignment for the helper that is deleted. */
		XmlParseHelperWorld& operator=(const XmlParseHelperWorld& otherHelper) = delete;

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
		virtual ~XmlParseHelperWorld();

		static const std::string sValueTag;
		static const std::string sNameTag;

	private:

		static const std::string sWorldTag;

	};
}
