#include "pch.h"

using namespace FieaGameEngine;
using namespace std;

IXmlParseHelper::IXmlParseHelper() :
	mMaster(nullptr)
{

}
void IXmlParseHelper::Initialize(XmlParseMaster* master)
{
	mMaster = master;
}


bool IXmlParseHelper::CharDataHandler(const std::string& data, uint32_t length) 
{
	data;
	length;
	return false;
}

IXmlParseHelper::~IXmlParseHelper()
{

}