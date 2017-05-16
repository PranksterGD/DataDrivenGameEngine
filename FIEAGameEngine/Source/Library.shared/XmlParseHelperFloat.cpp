#include "pch.h"

using namespace std;
using namespace FieaGameEngine;

#pragma  region HelperFoo

const string XmlParseHelperFloat::sFloatTag = "float";


XmlParseHelperFloat::XmlParseHelperFloat() :
	IXmlParseHelper()
{

}
void XmlParseHelperFloat::Initialize(XmlParseMaster* master)
{
	IXmlParseHelper::Initialize(master);
}

bool XmlParseHelperFloat::StartElementHandler(const std::string& name, const Hashmap<std::string, std::string>& map)
{
	bool isHandled = false;
	name;
	map;
	XmlParseHelperTable::SharedData* data = nullptr;

	if (mMaster->GetSharedData() != nullptr)
	{
		data = mMaster->GetSharedData()->As<XmlParseHelperTable::SharedData>();
	}

	if (data != nullptr && name == sFloatTag)
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
			datum.SetType(DatumType::FLOAT);
			datum.PushBackFromString(map[XmlParseHelperTable::sValueTag]);
		}

		isHandled = true;
	}

	return isHandled;
}

bool XmlParseHelperFloat::EndElementHandler(const std::string& name)
{
	name;
	bool isHandled = false;
	XmlParseHelperTable::SharedData* data = nullptr;

	if (mMaster->GetSharedData() != nullptr)
	{
		data = mMaster->GetSharedData()->As<XmlParseHelperTable::SharedData>();
	}

	if (data != nullptr && name == sFloatTag)
	{

		isHandled = true;
	}

	return isHandled;
}

IXmlParseHelper* XmlParseHelperFloat::Clone() const
{
	return new(XmlParseHelperFloat);
}


XmlParseHelperFloat::~XmlParseHelperFloat()
{

}

