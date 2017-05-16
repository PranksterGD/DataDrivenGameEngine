#include "pch.h"

using namespace std;
using namespace FieaGameEngine;

#pragma  region HelperFoo

const string XmlParseHelperReaction::sReactionTag = "Reaction";
const string XmlParseHelperReaction::sClassNameTag = "class";
const string XmlParseHelperReaction::sInstaceNameTag = "name";

XmlParseHelperReaction::XmlParseHelperReaction() :
	IXmlParseHelper()
{

}
void XmlParseHelperReaction::Initialize(XmlParseMaster* master)
{
	IXmlParseHelper::Initialize(master);
}

bool XmlParseHelperReaction::StartElementHandler(const std::string& name, const Hashmap<std::string, std::string>& map)
{
	bool isHandled = false;
	name;
	map;
	XmlParseHelperTable::SharedData* data = nullptr;

	if (mMaster->GetSharedData() != nullptr)
	{
		data = mMaster->GetSharedData()->As<XmlParseHelperTable::SharedData>();
	}

	if (data != nullptr && name == sReactionTag)
	{
		if (data->mScope == nullptr)
		{
			throw exception("Cannot have reactions outside of scopes");
		}

		Reaction* reaction = Factory<Reaction>::Create(map[sClassNameTag]);
		reaction->SetName(map[sInstaceNameTag]);
		data->mScope->Adopt(*reaction, Reaction::sReactionsTag);

		data->mScope = reaction;

		isHandled = true;
	}

	return isHandled;
}

bool XmlParseHelperReaction::EndElementHandler(const std::string& name)
{
	name;
	bool isHandled = false;
	XmlParseHelperTable::SharedData* data = nullptr;

	if (mMaster->GetSharedData() != nullptr)
	{
		data = mMaster->GetSharedData()->As<XmlParseHelperTable::SharedData>();
	}

	if (data != nullptr && name == sReactionTag)
	{
		if (data->Depth() > 0)
		{
			data->mScope = data->mScope->GetParent();
		}

		isHandled = true;
	}

	return isHandled;
}

IXmlParseHelper* XmlParseHelperReaction::Clone() const
{
	return new(XmlParseHelperReaction);
}


XmlParseHelperReaction::~XmlParseHelperReaction()
{

}
