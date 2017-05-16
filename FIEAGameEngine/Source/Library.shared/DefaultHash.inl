namespace FieaGameEngine
{

	/************************************************************************/
	/* SList Implementation
	/************************************************************************/
	template<typename TKey>
	std::uint32_t DefaultHash<TKey>::operator ()(const TKey& key) const
	{
		const std::uint8_t * data = reinterpret_cast<const std::uint8_t *> (&key);
		std::uint32_t hashReturn = 0;
	
		for (std::uint32_t i = 0; i < sizeof(TKey); ++i)
		{
			hashReturn += data[i] + 13;
		}
		return hashReturn;
	}


	inline std::uint32_t DefaultHash<char *>::operator()(char* key) const
	{
		std::uint32_t hashReturn = 0;

		for (std::uint32_t i = 0; i < strlen(key); ++i)
		{
			hashReturn += key[i] + 13;
		}

		return hashReturn;
	}

	inline std::uint32_t DefaultHash<std::string>::operator()(const std::string& key) const
	{
		std::uint32_t hashReturn = 0;

		for (std::uint32_t i = 0; i < key.size() ; ++i)
		{
			hashReturn += key[i] + 13;
		}

		return hashReturn;
	}

	inline std::uint32_t DefaultHash<std::int32_t*>::operator() (std::int32_t* key) const
	{
		const std::uint8_t * data = reinterpret_cast<const std::uint8_t *> (key);
		std::uint32_t hashReturn = 0;

		for (std::uint32_t i = 0; i < sizeof(std::int32_t); ++i)
		{
			hashReturn += data[i] + 13;
		}
		return hashReturn;
	}
}