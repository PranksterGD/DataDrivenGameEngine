#pragma once
#include<string>
#include "Hashmap.h"


namespace FieaGameEngine
{
	class XmlParseMaster;

	class IXmlParseHelper
	{
	public:
		/**Default constructor for the helper. */
		IXmlParseHelper();

		/**Function that resets the helper so that it is ready to be used to parse a new file */
		virtual void Initialize(XmlParseMaster* master);

		/**Copy constructor for the helper that is deleted. */
		IXmlParseHelper(const IXmlParseHelper& otherHelper) = delete;

		/**Assignment for the helper that is deleted. */
		IXmlParseHelper& operator=(const IXmlParseHelper& otherHelper) = delete;

		/**Function that attempts to the handle the start element callback event triggered by the parser.
		* @param name- The name of the field of the element.
		* @param map- A hashmap of the attribute names and values of the element
		* @return a boolean- True if the function succeeded in handling the event, false otherwise.*/
		virtual bool StartElementHandler(const std::string& name, const Hashmap<std::string, std::string>& map) = 0;

		/**Function that attempts to the handle the end element callback event triggered by the parser.
		* @param name- The name of the field of the element.
		* @return a boolean- True if the function succeeded in handling the event, false otherwise.*/
		virtual bool EndElementHandler(const std::string& name) = 0;

		/**Function that attempts to the handle the character data event triggered by the parser.
		* @param data- A string that contains the character data.
		* @param length- The size of the string.
		* @return a boolean- True if the function succeeded in handling the event, false otherwise.*/
		virtual bool CharDataHandler(const std::string& data, std::uint32_t length) ;

		/**Function that creates a new instance of the helper
		* @return- A pointer pointing to the new instance of the helper.*/
		virtual IXmlParseHelper* Clone() const =0;


		/**Destructor for the helper */
		virtual ~IXmlParseHelper();

	protected:

		XmlParseMaster* mMaster;
	};
}