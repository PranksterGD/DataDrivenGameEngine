#include "pch.h"

using namespace std;
using namespace FieaGameEngine;

#pragma  region HelperFoo

const string XmlParseHelperInteger::sIntergerTag = "integer";

XmlParseHelperInteger::XmlParseHelperInteger() :
	IXmlParseHelper()
{

}
void XmlParseHelperInteger::Initialize(XmlParseMaster* master)
{
	IXmlParseHelper::Initialize(master);
}

bool XmlParseHelperInteger::StartElementHandler(const std::string& name, const Hashmap<std::string, std::string>& map)
{
	bool isHandled = false;
	name;
	map;
	XmlParseHelperTable::SharedData* data = nullptr;

	if (mMaster->GetSharedData() != nullptr)
	{
		data = mMaster->GetSharedData()->As<XmlParseHelperTable::SharedData>();
	}

	if (data != nullptr && name == sIntergerTag)
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
			datum.SetType(DatumType::INTEGER);
			datum.PushBackFromString(map[XmlParseHelperTable::sValueTag]);
		}



		isHandled = true;
	}

	return isHandled;
}

bool XmlParseHelperInteger::EndElementHandler(const std::string& name)
{
	name;
	bool isHandled = false;
	XmlParseHelperTable::SharedData* data = nullptr;

	if (mMaster->GetSharedData() != nullptr)
	{
		data = mMaster->GetSharedData()->As<XmlParseHelperTable::SharedData>();
	}

	if (data != nullptr && name == sIntergerTag)
	{

		isHandled = true;
	}

	return isHandled;
}

IXmlParseHelper* XmlParseHelperInteger::Clone() const
{
	return new(XmlParseHelperInteger);
}


XmlParseHelperInteger::~XmlParseHelperInteger()
{

}

