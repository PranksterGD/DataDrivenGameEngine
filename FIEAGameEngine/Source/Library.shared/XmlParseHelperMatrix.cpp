#include "pch.h"

using namespace std;
using namespace FieaGameEngine;

#pragma  region HelperFoo

const string XmlParseHelperMatrix::sMatrixTag = "matrix";

XmlParseHelperMatrix::XmlParseHelperMatrix() :
	IXmlParseHelper()
{

}
void XmlParseHelperMatrix::Initialize(XmlParseMaster* master)
{
	IXmlParseHelper::Initialize(master);
}

bool XmlParseHelperMatrix::StartElementHandler(const std::string& name, const Hashmap<std::string, std::string>& map)
{
	bool isHandled = false;
	name;
	map;
	XmlParseHelperTable::SharedData* data = nullptr;

	if (mMaster->GetSharedData() != nullptr)
	{
		data = mMaster->GetSharedData()->As<XmlParseHelperTable::SharedData>();
	}

	if (data != nullptr && name == sMatrixTag)
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
			datum.SetType(DatumType::MATRIX);
			datum.PushBackFromString(map[XmlParseHelperTable::sValueTag]);
		}

		isHandled = true;
	}

	return isHandled;
}

bool XmlParseHelperMatrix::EndElementHandler(const std::string& name)
{
	name;
	bool isHandled = false;
	XmlParseHelperTable::SharedData* data = nullptr;

	if (mMaster->GetSharedData() != nullptr)
	{
		data = mMaster->GetSharedData()->As<XmlParseHelperTable::SharedData>();
	}

	if (data != nullptr && name == sMatrixTag)
	{

		isHandled = true;
	}

	return isHandled;
}

IXmlParseHelper* XmlParseHelperMatrix::Clone() const
{
	return new(XmlParseHelperMatrix);
}


XmlParseHelperMatrix::~XmlParseHelperMatrix()
{

}

