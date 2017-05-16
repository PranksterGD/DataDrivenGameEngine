#pragma once
namespace FieaGameEngine
{
	class IncrementFunctor
	{
	public:
		virtual std::uint32_t operator() (uint32_t Size, uint32_t Capacity);
	};
}