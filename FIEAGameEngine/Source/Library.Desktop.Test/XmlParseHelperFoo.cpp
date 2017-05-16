#include "pch.h"

using namespace std;
using namespace UnitTest;
using namespace FieaGameEngine;

#pragma  region HelperFoo

XmlParseHelperFoo::XmlParseHelperFoo() :
	IXmlParseHelper()
{
	mStartElementHandlerCount = 0;
	mEndElementHandlerCount = 0;
	mCharDataHandlerCount = 0;
	mMaxDepth = 0;
	mIsInitialized = false;
	mPreviousName = "";
}
void XmlParseHelperFoo::Initialize(XmlParseMaster* master)
{
	IXmlParseHelper::Initialize(master);

	mStartElementHandlerCount = 0;
	mEndElementHandlerCount = 0;
	mCharDataHandlerCount = 0;
	mMaxDepth = 0;
	mIsInitialized = true;
	mPreviousName = "";
}

bool XmlParseHelperFoo::StartElementHandler(const std::string& name, const Hashmap<std::string, std::string>& map)
{
	bool isHandled = false;
	name;
	map;
	SharedData* data = nullptr;
	
	if (mMaster->GetSharedData() != nullptr)
	{
		data = mMaster->GetSharedData()->As<XmlParseHelperFoo::SharedData>();
	}

	if (data != nullptr)
	{
		mStartElementHandlerCount++;
		isHandled = true;

		if (name == "Soldier")
		{
			data->mHealth = stoi(map["Health"]);
		}

		if (name == "Weapon")
		{
			data->mAmmo = stoi(map["Ammo"]);
		}

		if (data->Depth() > mMaxDepth)
		{
			mMaxDepth = data->Depth();
		}

		mPreviousName = name;
	}

	return isHandled;
}

bool XmlParseHelperFoo::EndElementHandler(const std::string& name)
{
	name;
	bool isHandled = false;
	SharedData* data = nullptr;

	if (mMaster->GetSharedData() != nullptr)
	{
		data = mMaster->GetSharedData()->As<SharedData>();
	}

	if (data != nullptr)
	{
		mEndElementHandlerCount++;
		isHandled = true;
	}

	return isHandled;
}

bool XmlParseHelperFoo::CharDataHandler(const std::string& data, std::uint32_t length)
{
	bool isHandled = false;
	data;
	length;

	SharedData* sharedData = nullptr;

	if (mMaster->GetSharedData() != nullptr)
	{
		sharedData = mMaster->GetSharedData()->As<SharedData>();
	}

	if (sharedData != nullptr)
	{
		mCharDataHandlerCount++;
		isHandled = true;

		if (mPreviousName == "X")
		{
			sharedData->mXPositon = stoi(data);
		}
		else
		if (mPreviousName == "Y")
		{
			sharedData->mYPosition = stoi(data);
		}
		else
		if (mPreviousName == "Z")
		{
			sharedData->mZPosition = stoi(data);
		}
	}

	return isHandled;
}


IXmlParseHelper* XmlParseHelperFoo::Clone() const
{
	IXmlParseHelper* cloneHelper = new(XmlParseHelperFoo);

	return cloneHelper;
}

uint32_t XmlParseHelperFoo::StartElementHandlerCount()
{
	return mStartElementHandlerCount;
}

uint32_t XmlParseHelperFoo::EndElementHandlerCount()
{
	return mEndElementHandlerCount;
}

uint32_t XmlParseHelperFoo::CharDataHandlerCount()
{
	return mCharDataHandlerCount;
}

uint32_t XmlParseHelperFoo::MaxDepth()
{
	return mMaxDepth;
}

bool XmlParseHelperFoo::IsInitialized()
{
	return mIsInitialized;
}

XmlParseHelperFoo::~XmlParseHelperFoo()
{

}

#pragma endregion EndHelperFoo

#pragma  region FooSharedData

RTTI_DEFINITIONS(XmlParseHelperFoo::SharedData)

XmlParseHelperFoo::SharedData::SharedData(XmlParseMaster* master) :
	XmlParseMaster::SharedData(master)
{
	Initialize();
}

void XmlParseHelperFoo::SharedData::Initialize()
{
	XmlParseMaster::SharedData::Initialize();

	mHealth = 0;
	mXPositon = 0;
	mYPosition = 0;
	mZPosition = 0;
	mAmmo = 0;
}

XmlParseMaster::SharedData* XmlParseHelperFoo::SharedData::Clone() const
{
	XmlParseMaster::SharedData* cloneSharedData = new SharedData();
	return cloneSharedData;
}



#pragma endregion EndFooSharedData