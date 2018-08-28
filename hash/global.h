#define _HASH_SEED	(std::size_t)0xdeadbeef

template<class _Kty> inline
std::size_t hash_value(const _Kty& _Keyval)
{	// hash _Keyval to size_t value one-to-one
    return ((std::size_t)_Keyval ^ _HASH_SEED);
}

inline std::size_t hash_value(const std::string& _Str)
{	// hash string to size_t value
    return (_STD _Hash_seq((const unsigned char *)_Str.c_str(),
        _Str.length()));
}

inline std::size_t hash_value(_In_z_ const char *_Str)
{	// hash NTBS to size_t value
    return (_STD _Hash_seq((const unsigned char *)_Str,
        _CSTD strlen(_Str)));
}

inline std::size_t hash_value(_In_z_ const wchar_t *_Str)
{	// hash NTWCS to size_t value
    return (_STD _Hash_seq((const unsigned char *)_Str,
        _CSTD wcslen(_Str) * sizeof (wchar_t)));
}