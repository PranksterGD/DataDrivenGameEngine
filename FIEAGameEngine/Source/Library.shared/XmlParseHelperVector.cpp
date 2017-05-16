#include "pch.h"

using namespace std;
using namespace FieaGameEngine;

#pragma  region HelperFoo

const string XmlParseHelperVector::sVectorTag = "vector";

XmlParseHelperVector::XmlParseHelperVector() :
	IXmlParseHelper()
{

}
void XmlParseHelperVector::Initialize(XmlParseMaster* master)
{
	IXmlParseHelper::Initialize(master);
}

bool XmlParseHelperVector::StartElementHandler(const std::string& name, const Hashmap<std::string, std::string>& map)
{
	bool isHandled = false;
	name;
	map;
	XmlParseHelperTable::SharedData* data = nullptr;

	if (mMaster->GetSharedData() != nullptr)
	{
		data = mMaster->GetSharedData()->As<XmlParseHelperTable::SharedData>();
	}

	if (data != nullptr && name == sVectorTag)
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
			datum.SetType(DatumType::VECTOR);
			datum.PushBackFromString(map[XmlParseHelperTable::sValueTag]);
		}

		isHandled = true;
	}

	return isHandled;
}

bool XmlParseHelperVector::EndElementHandler(const std::string& name)
{
	name;
	bool isHandled = false;
	XmlParseHelperTable::SharedData* data = nullptr;

	if (mMaster->GetSharedData() != nullptr)
	{
		data = mMaster->GetSharedData()->As<XmlParseHelperTable::SharedData>();
	}

	if (data != nullptr && name == sVectorTag)
	{

		isHandled = true;
	}

	return isHandled;
}

IXmlParseHelper* XmlParseHelperVector::Clone() const
{
	return new(XmlParseHelperVector);
}


XmlParseHelperVector::~XmlParseHelperVector()
{

}

