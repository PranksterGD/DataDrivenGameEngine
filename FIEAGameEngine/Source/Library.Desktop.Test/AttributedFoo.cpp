#include "pch.h"

using namespace std;
using namespace FieaGameEngine;
using namespace UnitTest;

RTTI_DEFINITIONS(AttributedFoo)

AttributedFoo::AttributedFoo() :
	Attributed()
{
	mIntData = 0;
	mFloatData = 0.0f;
	mStringData = "";
	mVectorData = glm::vec4();
	mMatrixData = glm::mat4();
	mRTTIData = nullptr;

	for (int32_t i = 0; i < ArraySize; ++i)
	{
		mIntArrayData[i] = 0;
		mFloatArrayData[i] = 0.0f;
		mStringArrayData[i] = "";
		mVectorArrayData[i] = glm::vec4();
		mMatrixArrayData[i] = glm::mat4();
		mRTTIArrayData[i] = nullptr;
	}

	InitalizeSignatures();
}

AttributedFoo::AttributedFoo(const AttributedFoo& otherAttributedFoo) 
{
	*this = otherAttributedFoo;
}

AttributedFoo::AttributedFoo(AttributedFoo&& otherAttributedFoo) 	
{
	*this = move(otherAttributedFoo);
}

AttributedFoo& AttributedFoo::operator=(const AttributedFoo& otherAttributedFoo)
{	
	mIntData = otherAttributedFoo.mIntData;
	mFloatData = otherAttributedFoo.mFloatData;
	mStringData = otherAttributedFoo.mStringData;
	mVectorData = otherAttributedFoo.mVectorData;
	mMatrixData = otherAttributedFoo.mMatrixData;
	mRTTIData = otherAttributedFoo.mRTTIData;

	for (int32_t i = 0; i < ArraySize; ++i)
	{
		mIntArrayData[i] = otherAttributedFoo.mIntArrayData[i];
		mFloatArrayData[i] = otherAttributedFoo.mFloatArrayData[i];
		mStringArrayData[i] = otherAttributedFoo.mStringArrayData[i];
		mVectorArrayData[i] = otherAttributedFoo.mVectorArrayData[i];
		mMatrixArrayData[i] = otherAttributedFoo.mMatrixArrayData[i];
		mRTTIArrayData[i] = otherAttributedFoo.mRTTIArrayData[i];
	}

	Attributed::operator=(otherAttributedFoo);
	FixExternals();
	return *this;
}

AttributedFoo& AttributedFoo::operator=(AttributedFoo&& otherAttributedFoo)
{
	mIntData = otherAttributedFoo.mIntData;
	mFloatData = otherAttributedFoo.mFloatData;
	mStringData = otherAttributedFoo.mStringData;
	mVectorData = otherAttributedFoo.mVectorData;
	mMatrixData = otherAttributedFoo.mMatrixData;
	mRTTIData = otherAttributedFoo.mRTTIData;

	for (int32_t i = 0; i < ArraySize; ++i)
	{
		mIntArrayData[i] = otherAttributedFoo.mIntArrayData[i];
		mFloatArrayData[i] = otherAttributedFoo.mFloatArrayData[i];
		mStringArrayData[i] = otherAttributedFoo.mStringArrayData[i];
		mVectorArrayData[i] = otherAttributedFoo.mVectorArrayData[i];
		mMatrixArrayData[i] = otherAttributedFoo.mMatrixArrayData[i];
		mRTTIArrayData[i] = otherAttributedFoo.mRTTIArrayData[i];
	}

	Attributed::operator=(move(otherAttributedFoo));
	FixExternals();
	return *this;
}

void AttributedFoo::InitalizeSignatures()
{
	Attributed::InitalizeSignatures();
	AddInternalAttribute("InternalInt", 0, 1);
	AddInternalAttribute("InternalFloat", 0.0f, 1);
	AddInternalAttribute("InternalString", "", 1);
	AddInternalAttribute("InternalVector", glm::vec4(), 1);
	AddInternalAttribute("InternalMatrix", glm::mat4(), 1);
	AddInternalAttribute("InternalRTTI", nullptr, 1);

	AddExternalAttribute("ExternalInt", &mIntData, 1);
	AddExternalAttribute("ExternalFloat", &mFloatData, 1);
	AddExternalAttribute("ExternalString", &mStringData, 1);
	AddExternalAttribute("ExternalVector", &mVectorData, 1);
	AddExternalAttribute("ExternalMatrix", &mMatrixData, 1);
	AddExternalAttribute("ExternalRTTI", &mRTTIData, 1);

	AddExternalAttribute("ExternalIntArray", mIntArrayData, ArraySize);
	AddExternalAttribute("ExternalFloatArray", mFloatArrayData, ArraySize);
	AddExternalAttribute("ExternalStringArray", mStringArrayData, ArraySize);
	AddExternalAttribute("ExternalVectorArray", mVectorArrayData, ArraySize);
	AddExternalAttribute("ExternalMatrixArray", mMatrixArrayData, ArraySize);
	AddExternalAttribute("ExternalRTTIArray", mRTTIArrayData, ArraySize);

	mNestedScope = &AddScopeAttribute("ScopeAttribute");

	mOtherNestedScope = new Scope();
	AddScopeAttribute("ScopeAttribute", *mOtherNestedScope);
}

void AttributedFoo::FixExternals()
{
	(*this)["ExternalInt"].SetStorage(&mIntData,1);
	(*this)["ExternalFloat"].SetStorage(&mFloatData, 1);
	(*this)["ExternalString"].SetStorage(&mStringData, 1);
	(*this)["ExternalVector"].SetStorage(&mVectorData, 1);
	(*this)["ExternalMatrix"].SetStorage(&mMatrixData, 1);
	(*this)["ExternalRTTI"].SetStorage(&mRTTIData, 1);

	(*this)["ExternalIntArray"].SetStorage(mIntArrayData, ArraySize);
	(*this)["ExternalFloatArray"].SetStorage(mFloatArrayData, ArraySize);
	(*this)["ExternalStringArray"].SetStorage(mStringArrayData, ArraySize);
	(*this)["ExternalVectorArray"].SetStorage(mVectorArrayData, ArraySize);
	(*this)["ExternalMatrixArray"].SetStorage(mMatrixArrayData, ArraySize);
	(*this)["ExternalRTTIArray"].SetStorage(mRTTIArrayData, ArraySize);
}

Scope* AttributedFoo::Copy() const
{
	return new AttributedFoo(*this);
}