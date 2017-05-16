#include "pch.h"

using namespace std;
using namespace FieaGameEngine;

#pragma  region HelperFoo

const string XmlParseHelperString::sStringTag = "string";

XmlParseHelperString::XmlParseHelperString() :
	IXmlParseHelper()
{

}
void XmlParseHelperString::Initialize(XmlParseMaster* master)
{
	IXmlParseHelper::Initialize(master);
}

bool XmlParseHelperString::StartElementHandler(const std::string& name, const Hashmap<std::string, std::string>& map)
{
	bool isHandled = false;
	name;
	map;
	XmlParseHelperTable::SharedData* data = nullptr;

	if (mMaster->GetSharedData() != nullptr)
	{
		data = mMaster->GetSharedData()->As<XmlParseHelperTable::SharedData>();
	}

	if (data != nullptr && name == sStringTag)
	{
		if (data->mScope == nullptr)
		{
			throw exception("Scope not set");
		}

		Datum& datum = data->mScope->Append(map[XmlParseHelperTable::sNameTag]);

		if (datum.IsExternal())
		{
			datum.SetFromString(map[XmlParseHelperTable::sValueTag]);
		}
		else
		{
			datum.SetType(DatumType::STRING);
			datum.PushBackFromString(map[XmlParseHelperTable::sValueTag]);
		}

		isHandled = true;
	}

	return isHandled;
}

bool XmlParseHelperString::EndElementHandler(const std::string& name)
{
	name;
	bool isHandled = false;
	XmlParseHelperTable::SharedData* data = nullptr;

	if (mMaster->GetSharedData() != nullptr)
	{
		data = mMaster->GetSharedData()->As<XmlParseHelperTable::SharedData>();
	}

	if (data != nullptr && name == sStringTag)
	{

		isHandled = true;
	}

	return isHandled;
}

IXmlParseHelper* XmlParseHelperString::Clone() const
{
	return new(XmlParseHelperString);
}


XmlParseHelperString::~XmlParseHelperString()
{

}

