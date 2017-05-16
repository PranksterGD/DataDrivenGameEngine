#include "pch.h"

using namespace std;
using namespace FieaGameEngine;

#pragma  region HelperFoo

const string XmlParseHelperAction::sActionTag = "Action";
const string XmlParseHelperAction::sClassNameTag = "class";
const string XmlParseHelperAction::sInstaceNameTag = "name";

XmlParseHelperAction::XmlParseHelperAction() :
	IXmlParseHelper()
{

}
void XmlParseHelperAction::Initialize(XmlParseMaster* master)
{
	IXmlParseHelper::Initialize(master);
}

bool XmlParseHelperAction::StartElementHandler(const std::string& name, const Hashmap<std::string, std::string>& map)
{
	bool isHandled = false;
	name;
	map;
	XmlParseHelperTable::SharedData* data = nullptr;

	if (mMaster->GetSharedData() != nullptr)
	{
		data = mMaster->GetSharedData()->As<XmlParseHelperTable::SharedData>();
	}

	if (data != nullptr && name == sActionTag)
	{
		if (data->mScope == nullptr)
		{
			throw exception("Cannot have actions outside of scopes");
		}
	
		Action* action= Factory<Action>::Create(map[sClassNameTag]);
		action->SetName(map[sInstaceNameTag]);
		data->mScope->Adopt(*action, Entity::sActionsTag);

		data->mScope = action;

		isHandled = true;
	}

	return isHandled;
}

bool XmlParseHelperAction::EndElementHandler(const std::string& name)
{
	name;
	bool isHandled = false;
	XmlParseHelperTable::SharedData* data = nullptr;

	if (mMaster->GetSharedData() != nullptr)
	{
		data = mMaster->GetSharedData()->As<XmlParseHelperTable::SharedData>();
	}

	if (data != nullptr && name == sActionTag)
	{
		if (data->Depth() > 0)
		{
			data->mScope = data->mScope->GetParent();
		}

		isHandled = true;
	}

	return isHandled;
}

IXmlParseHelper* XmlParseHelperAction::Clone() const
{
	return new(XmlParseHelperAction);
}


XmlParseHelperAction::~XmlParseHelperAction()
{

}
