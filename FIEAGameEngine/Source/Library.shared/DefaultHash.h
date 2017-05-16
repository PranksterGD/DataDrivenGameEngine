#pragma once
#include <string>
namespace FieaGameEngine
{
	template <typename TKey>
	class DefaultHash
	{
	public:
		 std::uint32_t operator() (const TKey& Key) const;
	};

	template<>
	class DefaultHash<char*>
	{
	public:
		std::uint32_t operator() (char* key) const;
	};

	template<>
	class DefaultHash<std::string>
	{
	public:
		std::uint32_t operator() (const std::string& key) const;
	};

	template<>
	class DefaultHash<std::int32_t*>
	{
	public:
		std::uint32_t operator() (std::int32_t* key) const;
	};
}

#include "DefaultHash.inl"