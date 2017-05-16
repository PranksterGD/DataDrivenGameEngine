#include "pch.h"

using namespace std;
using namespace FieaGameEngine;

#pragma  region HelperFoo

const string XmlParseHelperTable::sScopeTag = "Scope";
const string XmlParseHelperTable::sNameTag = "name";
const string XmlParseHelperTable::sValueTag = "value";

XmlParseHelperTable::XmlParseHelperTable() :
	IXmlParseHelper()
{

}
void XmlParseHelperTable::Initialize(XmlParseMaster* master)
{
	IXmlParseHelper::Initialize(master);
}

bool XmlParseHelperTable::StartElementHandler(const std::string& name, const Hashmap<std::string, std::string>& map)
{
	bool isHandled = false;
	name;
	map;
	SharedData* data = nullptr;

	if (mMaster->GetSharedData() != nullptr)
	{
		data = mMaster->GetSharedData()->As<XmlParseHelperTable::SharedData>();
	}

	if (data != nullptr && name == sScopeTag)
	{
		if (data->Depth() == 1)
		{
			data->mScope = new Scope();

			//throw excception;
		}
		else
		{
			Scope& scope = data->mScope->AppendScope(map[sNameTag]);
			data->mScope = &scope;
		}

		isHandled = true;
	}

	return isHandled;
}

bool XmlParseHelperTable::EndElementHandler(const std::string& name)
{
	name;
	bool isHandled = false;
	SharedData* data = nullptr;

	if (mMaster->GetSharedData() != nullptr)
	{
		data = mMaster->GetSharedData()->As<SharedData>();
	}

	if (data != nullptr && name == sScopeTag)
	{
		if (data->Depth() > 0)
		{
			data->mScope = data->mScope->GetParent();
		}

		isHandled = true;
	}

	return isHandled;
}

IXmlParseHelper* XmlParseHelperTable::Clone() const
{
	return new(XmlParseHelperTable);
}


XmlParseHelperTable::~XmlParseHelperTable()
{

}

#pragma endregion EndHelperFoo

#pragma  region FooSharedData

RTTI_DEFINITIONS(XmlParseHelperTable::SharedData)

XmlParseHelperTable::SharedData::SharedData(XmlParseMaster* master) :
	XmlParseMaster::SharedData(master), mScope(nullptr)
{
	Initialize();
}

void XmlParseHelperTable::SharedData::Initialize()
{
	XmlParseMaster::SharedData::Initialize();

	if (mScope != nullptr)
	{
		delete(mScope);
		mScope = nullptr;
	}
}

XmlParseMaster::SharedData* XmlParseHelperTable::SharedData::Clone() const
{
	XmlParseMaster::SharedData* cloneSharedData = new SharedData();
	return cloneSharedData;
}

XmlParseHelperTable::SharedData::~SharedData()
{
	delete(mScope);
}


#pragma endregion EndFooSharedData