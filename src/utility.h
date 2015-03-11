#ifndef UTILITY_H_
#define UTILITY_H_

#define COMPILER_MSC  1
#define COMPILER_GNUC 2

#if defined(_MSC_VER)
#define TXOBTOOL_COMPILER COMPILER_MSC
#else
#define TXOBTOOL_COMPILER COMPILER_GNUC
#endif

#if TXOBTOOL_COMPILER == COMPILER_MSC
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <direct.h>
#include <codecvt>
#else
#include <iconv.h>
#endif
#include <errno.h>
#include <locale.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <string>
#include <vector>

using namespace std;

typedef int8_t n8;
typedef int16_t n16;
typedef int32_t n32;
typedef int64_t n64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

#if TXOBTOOL_COMPILER == COMPILER_MSC
typedef wstring String;
#define STR(x) L##x
#define FMkdir _wmkdir
#define FFopen FFopenA
#define FFopenUnicode FFopenW
#define FFseek _fseeki64
#define FFtell _ftelli64
#define FPrintf wprintf
#else
typedef string String;
#define STR(x) x
#define FMkdir(x) mkdir((x), S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH)
#define FFopen FFopenA
#define FFopenUnicode FFopenA
#define FFseek fseeko
#define FFtell ftello
#define FPrintf printf
#endif

#define CONVERT_ENDIAN(n) (((n) >> 24 & 0xFF) | ((n) >> 8 & 0xFF00) | (((n) & 0xFF00) << 8) | (((n) & 0xFF) << 24))

void FSetLocale();

template<typename T>
vector<T> FSSplit(const T& a_sString, const T& a_sSeparator)
{
	vector<T> vString;
	for (typename T::size_type nOffset = 0; nOffset < a_sString.size(); nOffset += a_sSeparator.size())
	{
		typename T::size_type nPos = a_sString.find(a_sSeparator, nOffset);
		if (nPos != T::npos)
		{
			vString.push_back(a_sString.substr(nOffset, nPos - nOffset));
			nOffset = nPos;
		}
		else
		{
			vString.push_back(a_sString.substr(nOffset));
			break;
		}
	}
	return vString;
}

#if TXOBTOOL_COMPILER != COMPILER_MSC
template<typename TSrc, typename TDest>
TDest FSTToT(const TSrc& a_sString, const string& a_sSrcType, const string& a_sDestType)
{
	TDest sConverted;
	iconv_t cvt = iconv_open(a_sDestType.c_str(), a_sSrcType.c_str());
	if (cvt == reinterpret_cast<iconv_t>(-1))
	{
		return sConverted;
	}
	size_t nStringLeft = a_sString.size() * sizeof(typename TSrc::value_type);
	static const n32 c_kBufferSize = 1024;
	static const n32 c_kConvertBufferSize = c_kBufferSize - 4;
	char buffer[c_kBufferSize];
	do
	{
		typename TSrc::value_type* pString = const_cast<typename TSrc::value_type*>(a_sString.c_str());
		char* pBuffer = buffer;
		size_t nBufferLeft = c_kConvertBufferSize;
		n32 nError = iconv(cvt, reinterpret_cast<char**>(&pString), &nStringLeft, &pBuffer, &nBufferLeft);
		if (nError == 0 || (nError == static_cast<size_t>(-1) && errno == E2BIG))
		{
			*reinterpret_cast<typename TDest::value_type*>(buffer + c_kConvertBufferSize - nBufferLeft) = 0;
			sConverted += reinterpret_cast<typename TDest::value_type*>(buffer);
			if (nError == 0)
			{
				break;
			}
		}
		else
		{
			break;
		}
	} while (true);
	iconv_close(cvt);
	return sConverted;
}
#endif

wstring FSAToW(const string& a_sString);

#if TXOBTOOL_COMPILER == COMPILER_MSC
#define FSAToUnicode(x) FSAToW(x)
#else
#define FSAToUnicode(x) string(x)
#endif

bool FMakeDir(const String::value_type* a_pDirName);

FILE* FFopenA(const char* a_pFileName, const char* a_pMode);

#if TXOBTOOL_COMPILER == COMPILER_MSC
FILE* FFopenW(const wchar_t* a_pFileName, const wchar_t* a_pMode);
#endif

#endif	// UTILITY_H_
