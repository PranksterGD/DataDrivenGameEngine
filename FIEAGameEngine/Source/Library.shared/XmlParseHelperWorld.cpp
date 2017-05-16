#include "pch.h"

using namespace std;
using namespace FieaGameEngine;

#pragma  region HelperFoo

const string XmlParseHelperWorld::sWorldTag = "World";
const string XmlParseHelperWorld::sNameTag = "name";
const string XmlParseHelperWorld::sValueTag = "value";

XmlParseHelperWorld::XmlParseHelperWorld() :
	IXmlParseHelper()
{

}
void XmlParseHelperWorld::Initialize(XmlParseMaster* master)
{
	IXmlParseHelper::Initialize(master);
}

bool XmlParseHelperWorld::StartElementHandler(const std::string& name, const Hashmap<std::string, std::string>& map)
{
	bool isHandled = false;
	name;
	map;
	XmlParseHelperTable::SharedData* data = nullptr;

	if (mMaster->GetSharedData() != nullptr)
	{
		data = mMaster->GetSharedData()->As<XmlParseHelperTable::SharedData>();
	}

	if (data != nullptr && name == sWorldTag)
	{
		if (data->Depth() > 1)
		{
			throw exception("Cannot have nested worlds");
		}

		data->mScope = new World(map[sNameTag]);

		isHandled = true;
	}

	return isHandled;
}

bool XmlParseHelperWorld::EndElementHandler(const std::string& name)
{
	name;
	bool isHandled = false;
	XmlParseHelperTable::SharedData* data = nullptr;

	if (mMaster->GetSharedData() != nullptr)
	{
		data = mMaster->GetSharedData()->As<XmlParseHelperTable::SharedData>();
	}

	if (data != nullptr && name == sWorldTag)
	{
		if (data->Depth() > 0)
		{
			data->mScope = data->mScope->GetParent();
		}

		isHandled = true;
	}

	return isHandled;
}

IXmlParseHelper* XmlParseHelperWorld::Clone() const
{
	return new(XmlParseHelperWorld);
}


XmlParseHelperWorld::~XmlParseHelperWorld()
{

}
