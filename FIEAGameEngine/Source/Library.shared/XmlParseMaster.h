#pragma once
#include <cstdint>
#include "IXmlParseHelper.h"
#include "Vector.h"
#include "expat.h"
#include "RTTI.h"
namespace FieaGameEngine
{
	class XmlParseMaster final
	{
	public:

		class SharedData : public RTTI
		{
			RTTI_DECLARATIONS(XmlParseMaster::SharedData, RTTI)

		public:
			/**Default constructor for the shared data.
			* @param-capacity: Master associated with the shared data. Defaulted to null pointer if no argument is passed in.*/
			SharedData(XmlParseMaster* parseMaster = nullptr);

			/**Copy constructor for the shared data that is deleted. */
			SharedData(const SharedData& otherSharedData) = delete;
			
			/**Assignment for the shared data that is deleted. */
			SharedData& operator=(const SharedData& otherSharedData) = delete;

			/**Function that creates a new instance of the shared data.
			* @return- A pointer pointing to the new instance of shared data.*/
			virtual SharedData* Clone() const;

			/**Function that resets the shared data so that it is ready to be used to parse a new file */
			virtual void Initialize();

			/**Function that is used to set the master associated with the shared data. 
			* @param parseMaster- The parse master that is to be associated with.*/
			void SetXmlParseMaster(const XmlParseMaster* parseMaster);

			/**Function that is used to get the master associated with the shared data.
			* @return- The master that is associated with the shared data.*/
			const XmlParseMaster* GetXmlParseMaster() const;

			/**Function that increments the depth counter of the shared data. */
			void IncrementDepth();

			/**Function that decrements the depth counter of the shared data. */
			void DecrementDepth();

			/**Function that returns the depth counter of the shared data.
			* @return- An integer whose value is the depth counter.*/
			std::uint32_t Depth() const;

			/**Destructor for the shared data */
			virtual ~SharedData();

		protected:
			std::uint32_t mDepth;
			const XmlParseMaster* mXmlParseMaster;
		};
		
	public:

		/**Default constructor for the parse master
		* @param-capacity: Shared data associated with the parse master. Defaulted to null pointer if no argument is passed in.*/
		XmlParseMaster(SharedData* sharedData = nullptr);

		/**Destructor for the parse master.*/
		~XmlParseMaster();

		/**Copy constructor for the parse master that is deleted. */
		XmlParseMaster(XmlParseMaster& otherxmlParseMaster) = delete;

		/**Assignment for the parse master that is deleted. */
		XmlParseMaster& operator=(XmlParseMaster& otherxmlParseMaster) = delete;
		
		/**Function that creates a new instance of the parse master.
		* @return- A pointer pointing to the new instance of parse master.*/
		 XmlParseMaster* Clone() const;

		/**Function that is used to add a new parse helper to the list of helpers in the parse master.
		* @param helper- The helper that is to be added.
		* @exception- Throws an exception if the master is a clone.*/
		void AddHelper(IXmlParseHelper& helper);

		/**Function that is used to remove a new parse helper to the list of helpers in the parse master.
		* @param helper- The helper that is to be removed.
		* @exception- Throws an exception if the master is a clone.*/
		void RemoveHelper(IXmlParseHelper& helper);

		/**Function that is used to parse a character buffer of a specified size.
		* @param data- The character buffer to be parsed.
		* @param size- The size of the buffer.
		* @exception- Throws an exception if the parsing fails.*/
		void Parse(const char* data, size_t size);

		/**Function that is used to parse a file.
		* @param fileName- The name of the file to be parsed.
		* @exception- Throws an exception if the file cannot be opened.*/
		void ParseFromFile(const std::string& fileName);

		/**Function that is used to get the name of the file being parsed.
		* @return- A reference to the string containing the name of the file.*/
		const std::string& GetFileName() const;

		/**Function that is used to get the shared data associated with the parse master.
		* @return- The shared that is associated with the shared data.*/
		SharedData* GetSharedData() const;

		/**Function that is used to set the shared data associated with the parse master.
		* @param sharedData- The shared data that is to be associated with.*/
		void SetSharedData(SharedData* sharedData);

	private:

		static void StartElementHandler(void* userData, const char* name, const char**atts);

		static void  EndElementHandler(void* userData, const char*name);

		static void CharDataHandler(void* userData, const char* data, int length);

		void RegisterCallbacks();

		Vector<IXmlParseHelper*> mHelperList;

		std::string mFileName;

		SharedData* mSharedData;

		XML_Parser mParser;

		bool mIsClone;
	};
}