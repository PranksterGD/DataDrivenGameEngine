#include "pch.h"

using namespace std;
using namespace FieaGameEngine;

#pragma  region HelperFoo

const string XmlParseHelperSector::sSectorTag = "Sector";

XmlParseHelperSector::XmlParseHelperSector() :
	IXmlParseHelper()
{

}
void XmlParseHelperSector::Initialize(XmlParseMaster* master)
{
	IXmlParseHelper::Initialize(master);
}

bool XmlParseHelperSector::StartElementHandler(const std::string& name, const Hashmap<std::string, std::string>& map)
{
	bool isHandled = false;
	name;
	map;
	XmlParseHelperTable::SharedData* data = nullptr;

	if (mMaster->GetSharedData() != nullptr)
	{
		data = mMaster->GetSharedData()->As<XmlParseHelperTable::SharedData>();
	}

	if (data != nullptr && name == sSectorTag)
	{
		if (!data->mScope->Is("World"))
		{
			throw exception("Cannot have sectors outside of worlds");
		}

		Sector* sector = new Sector(map[XmlParseHelperTable::sNameTag]);
		sector->SetWorld(*data->mScope->As<World>());

		data->mScope = sector;

		isHandled = true;
	}

	return isHandled;
}

bool XmlParseHelperSector::EndElementHandler(const std::string& name)
{
	name;
	bool isHandled = false;
	XmlParseHelperTable::SharedData* data = nullptr;

	if (mMaster->GetSharedData() != nullptr)
	{
		data = mMaster->GetSharedData()->As<XmlParseHelperTable::SharedData>();
	}

	if (data != nullptr && name == sSectorTag)
	{
		if (data->Depth() > 0)
		{
			data->mScope = data->mScope->GetParent();
		}

		isHandled = true;
	}

	return isHandled;
}

IXmlParseHelper* XmlParseHelperSector::Clone() const
{
	return new(XmlParseHelperSector);
}


XmlParseHelperSector::~XmlParseHelperSector()
{

}
