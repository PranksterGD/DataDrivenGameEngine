#include "pch.h"

using namespace FieaGameEngine;
using namespace std;

#pragma  region XmlParseMaster

XmlParseMaster::XmlParseMaster(SharedData* sharedData) :
	mSharedData(sharedData), mFileName(""), mParser(XML_ParserCreate(nullptr)), mIsClone(false)
{
	RegisterCallbacks();

	if (sharedData != nullptr)
	{
		sharedData->SetXmlParseMaster(this);
	}
}

XmlParseMaster::~XmlParseMaster()
{
	if (mIsClone)
	{
		for (const IXmlParseHelper* helper : mHelperList)
		{
			delete(helper);
		}

		delete(mSharedData);
	}

	XML_ParserFree(mParser);
}

XmlParseMaster* XmlParseMaster::Clone() const
{
	XmlParseMaster* cloneParseMaster = new XmlParseMaster();
	cloneParseMaster->mIsClone = true;

	cloneParseMaster->mHelperList.Reserve(mHelperList.Size());

	for (const IXmlParseHelper* helper : mHelperList)
	{
		cloneParseMaster->mHelperList.PushBack(helper->Clone());
	}

	if (mSharedData != nullptr)
	{
		cloneParseMaster->SetSharedData(mSharedData->Clone());
	}
	return cloneParseMaster;
}

void XmlParseMaster::AddHelper(IXmlParseHelper& helper)
{
	if (mIsClone)
	{
		throw exception("Cannot add helper to a clone master");
	}

	if (mHelperList.Find(&helper) != mHelperList.end())
	{
		throw exception("Cannot add the same helper twice.");
	}

	mHelperList.PushBack(&helper);
}

void XmlParseMaster::RemoveHelper(IXmlParseHelper& helper)
{
	if (mIsClone)
	{
		throw exception("Cannot remove helper from a clone master");
	}

	mHelperList.Remove(&helper);
}

void XmlParseMaster::SetSharedData(SharedData* sharedData)
{
	if (mIsClone)
	{
		throw exception("Cannot set shared data for a cloned master");
	}

	mSharedData = sharedData;
	mSharedData->SetXmlParseMaster(this);
}

XmlParseMaster::SharedData* XmlParseMaster::GetSharedData() const
{
	return mSharedData;
}

const string& XmlParseMaster::GetFileName() const
{
	return mFileName;
}

void XmlParseMaster::StartElementHandler(void* userData, const char* name, const char**atts)
{
	XmlParseMaster* master =static_cast<XmlParseMaster*>(userData);

	Hashmap<string, string> map;

	for (int32_t i = 0; atts[i]; i += 2)
	{
		pair<string, string> element = { atts[i], atts[i + 1] };
		map.Insert(element);
	}

	if (master->GetSharedData() != nullptr)
	{
		master->GetSharedData()->IncrementDepth();
	}

	for (IXmlParseHelper* helper : master->mHelperList)
	{
		if (helper->StartElementHandler(name, map))
		{
			break;
		}
	}
}

void XmlParseMaster::EndElementHandler(void* userData, const char* name)
{
	XmlParseMaster* master = static_cast<XmlParseMaster*>(userData);

	if (master->GetSharedData() != nullptr)
	{
		master->GetSharedData()->DecrementDepth();
	}

	for (IXmlParseHelper* helper : master->mHelperList)
	{
		if (helper->EndElementHandler(name))
		{
			break;
		}
	}
}

void XmlParseMaster::CharDataHandler(void* userData, const char* data, int length)
{
	XmlParseMaster* master = static_cast<XmlParseMaster*>(userData);

	string terminatedData = string(data,length);

	for (IXmlParseHelper* helper : master->mHelperList)
	{
		if (helper->CharDataHandler(terminatedData, length))
		{
			break;
		}
	}
}

void XmlParseMaster::ParseFromFile(const std::string& fileName)
{
	ifstream fileHandle(fileName, ios::binary);

	if (fileHandle.bad())
	{
		throw exception("Could not open file");
	}

	mFileName = fileName;

	string data = string(istreambuf_iterator <char>(fileHandle), istreambuf_iterator<char>());

	Parse(data.c_str(), data.length());

	fileHandle.close();
}

void XmlParseMaster::Parse(const char* data, size_t size)
{
	mSharedData->Initialize();

	for (IXmlParseHelper* helper : mHelperList)
	{
		helper->Initialize(this);
	}

	XML_Status status = XML_Parse(mParser, data, static_cast<int32_t>(size), true);

	if (status == XML_STATUS_ERROR)
	{
		throw exception("Failed to parse");
	}

	XML_ParserFree(mParser);

	mParser = XML_ParserCreate(nullptr);

	RegisterCallbacks();
}

void XmlParseMaster::RegisterCallbacks()
{
	XML_SetElementHandler(mParser, StartElementHandler, EndElementHandler);

	XML_SetCharacterDataHandler(mParser, CharDataHandler);

	XML_SetUserData(mParser, this);
}

#pragma  endregion XmlParseMaster

#pragma  region SharedData

RTTI_DEFINITIONS(XmlParseMaster::SharedData)

XmlParseMaster::SharedData::SharedData(XmlParseMaster* parseMaster) :
	mDepth(0), mXmlParseMaster(parseMaster)
{

}

void XmlParseMaster::SharedData::DecrementDepth()
{
	if (mDepth == 0)
	{
		throw exception("Depth is already zero");
	}

	--mDepth;
}

void XmlParseMaster::SharedData::IncrementDepth()
{
	++mDepth;
}

uint32_t XmlParseMaster::SharedData::Depth() const
{
	return mDepth;
}

const XmlParseMaster* XmlParseMaster::SharedData::GetXmlParseMaster() const
{
	return mXmlParseMaster;
}

void XmlParseMaster::SharedData::SetXmlParseMaster(const XmlParseMaster* parseMaster)
{
	mXmlParseMaster = parseMaster;
}

XmlParseMaster::SharedData* XmlParseMaster::SharedData::Clone() const
{
	XmlParseMaster::SharedData* newSharedData = new (XmlParseMaster::SharedData);

	newSharedData->SetXmlParseMaster(this->mXmlParseMaster);

	return newSharedData;
}

void XmlParseMaster::SharedData::Initialize()
{
	mDepth = 0;
}

XmlParseMaster::SharedData::~SharedData()
{

}


#pragma  endregion SharedData