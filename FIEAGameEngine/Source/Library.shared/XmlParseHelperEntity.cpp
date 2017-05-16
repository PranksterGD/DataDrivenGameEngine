#include "pch.h"

using namespace std;
using namespace FieaGameEngine;

#pragma  region HelperFoo

const string XmlParseHelperEntity::sEntityTag = "Entity";
const string XmlParseHelperEntity::sClassNameTag = "class";
const string XmlParseHelperEntity::sInstaceNameTag = "name";

XmlParseHelperEntity::XmlParseHelperEntity() :
	IXmlParseHelper()
{

}
void XmlParseHelperEntity::Initialize(XmlParseMaster* master)
{
	IXmlParseHelper::Initialize(master);
}

bool XmlParseHelperEntity::StartElementHandler(const std::string& name, const Hashmap<std::string, std::string>& map)
{
	bool isHandled = false;
	name;
	map;
	XmlParseHelperTable::SharedData* data = nullptr;

	if (mMaster->GetSharedData() != nullptr)
	{
		data = mMaster->GetSharedData()->As<XmlParseHelperTable::SharedData>();
	}

	if (data != nullptr && name == sEntityTag)
	{
		if (!data->mScope->Is("Sector"))
		{
			throw exception("Cannot have entities outside of sectors");
		}

		EntityFactory a;

		Entity* entity = Factory<Entity>::Create(map[sClassNameTag]);
		entity->SetName(map[sInstaceNameTag]);
		entity->SetSector(*data->mScope->As<Sector>());

		data->mScope = entity;

		isHandled = true;
	}

	return isHandled;
}

bool XmlParseHelperEntity::EndElementHandler(const std::string& name)
{
	name;
	bool isHandled = false;
	XmlParseHelperTable::SharedData* data = nullptr;

	if (mMaster->GetSharedData() != nullptr)
	{
		data = mMaster->GetSharedData()->As<XmlParseHelperTable::SharedData>();
	}

	if (data != nullptr && name == sEntityTag)
	{
		if (data->Depth() > 0)
		{
			data->mScope = data->mScope->GetParent();
		}

		isHandled = true;
	}

	return isHandled;
}

IXmlParseHelper* XmlParseHelperEntity::Clone() const
{
	return new(XmlParseHelperEntity);
}


XmlParseHelperEntity::~XmlParseHelperEntity()
{

}
