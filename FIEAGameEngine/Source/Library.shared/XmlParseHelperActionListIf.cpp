#include "pch.h"

using namespace std;
using namespace FieaGameEngine;

#pragma  region HelperFoo

const string XmlparseHelperActionListIf::sIfTag = "If";
const string XmlparseHelperActionListIf::sClassNameTag = "class";
const string XmlparseHelperActionListIf::sInstaceNameTag = "name";
const string XmlparseHelperActionListIf::sConditionTag = "condition";

XmlparseHelperActionListIf::XmlparseHelperActionListIf() :
	IXmlParseHelper()
{

}
void XmlparseHelperActionListIf::Initialize(XmlParseMaster* master)
{
	IXmlParseHelper::Initialize(master);
}

bool XmlparseHelperActionListIf::StartElementHandler(const std::string& name, const Hashmap<std::string, std::string>& map)
{
	bool isHandled = false;
	name;
	map;
	XmlParseHelperTable::SharedData* data = nullptr;

	if (mMaster->GetSharedData() != nullptr)
	{
		data = mMaster->GetSharedData()->As<XmlParseHelperTable::SharedData>();
	}

	if (data != nullptr && name == sIfTag)
	{
		if (data->mScope == nullptr)
		{
			throw exception("Cannot have actions outside of scopes");
		}
		string actionName;

		if (map.ContainsKey(sInstaceNameTag))
		{
			actionName = map[sInstaceNameTag];
		}

		ActionListIf* action = new ActionListIf(actionName);
		action->SetCondition(stoi(map[sConditionTag]));
		data->mScope->Adopt(*action, Entity::sActionsTag);

		data->mScope = action;

		isHandled = true;
	}

	return isHandled;
}

bool XmlparseHelperActionListIf::EndElementHandler(const std::string& name)
{
	name;
	bool isHandled = false;
	XmlParseHelperTable::SharedData* data = nullptr;

	if (mMaster->GetSharedData() != nullptr)
	{
		data = mMaster->GetSharedData()->As<XmlParseHelperTable::SharedData>();
	}

	if (data != nullptr && name == sIfTag)
	{
		if (data->Depth() > 0)
		{
			data->mScope = data->mScope->GetParent();
		}

		isHandled = true;
	}

	return isHandled;
}

IXmlParseHelper* XmlparseHelperActionListIf::Clone() const
{
	return new(XmlparseHelperActionListIf);
}


XmlparseHelperActionListIf::~XmlparseHelperActionListIf()
{

}
