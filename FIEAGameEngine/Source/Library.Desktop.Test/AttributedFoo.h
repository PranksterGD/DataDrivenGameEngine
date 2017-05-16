#pragma once
#include <cstdint>
#include "Attributed.h"
namespace UnitTest
{
	class AttributedFoo : public FieaGameEngine::Attributed
	{
		RTTI_DECLARATIONS(AttributedFoo, FieaGameEngine::Attributed)

		static const std::uint32_t ArraySize = 5;
	public:
		AttributedFoo();
		AttributedFoo(const AttributedFoo& otherAttributedFoo);
		AttributedFoo(AttributedFoo&& otherAttributedFoo);
		~AttributedFoo() = default;
		AttributedFoo& operator=(const AttributedFoo& otherAttributedFoo);
		AttributedFoo& operator=(AttributedFoo&& otherAttributedFoo);

		std::int32_t mIntData;
		std::int32_t mIntArrayData[ArraySize];

		float mFloatData;
		float mFloatArrayData[ArraySize];

		std::string mStringData;
		std::string mStringArrayData[ArraySize];

		glm::vec4 mVectorData;
		glm::vec4 mVectorArrayData[ArraySize];

		glm::mat4 mMatrixData;
		glm::mat4 mMatrixArrayData[ArraySize];

		RTTI* mRTTIData;
		RTTI* mRTTIArrayData[ArraySize];

		Scope* mNestedScope;
		Scope* mOtherNestedScope;

		virtual Scope* Copy() const override;

	protected:
		void InitalizeSignatures();
		void FixExternals();

	private:
	};
}