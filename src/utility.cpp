#include "utility.h"

#if TXOBTOOL_COMPILER != COMPILER_MSC
string g_sLocaleName = "";
#endif

void FSetLocale()
{
	string sLocale = setlocale(LC_ALL, "");
#if TXOBTOOL_COMPILER != COMPILER_MSC
	vector<string> vLocale = FSSplit<string>(sLocale, ".");
	if (!vLocale.empty())
	{
		g_sLocaleName = vLocale.back();
	}
#endif
}

#if TXOBTOOL_COMPILER == COMPILER_MSC
wstring FSAToW(const string& a_sString)
{
	static wstring_convert<codecvt<wchar_t, char, mbstate_t>> c_cvt_a(new codecvt<wchar_t, char, mbstate_t>(""));
	return c_cvt_a.from_bytes(a_sString);
}
#else
wstring FSAToW(const string& a_sString)
{
	return FSTToT<string, wstring>(a_sString, g_sLocaleName, "WCHAR_T");
}
#endif

bool FMakeDir(const String::value_type* a_pDirName)
{
	if (FMkdir(a_pDirName) != 0)
	{
		if (errno != EEXIST)
		{
			return false;
		}
	}
	return true;
}

FILE* FFopenA(const char* a_pFileName, const char* a_pMode)
{
	FILE* fp = fopen(a_pFileName, a_pMode);
	if (fp == nullptr)
	{
		printf("ERROR: open file %s failed\n\n", a_pFileName);
	}
	return fp;
}

#if TXOBTOOL_COMPILER == COMPILER_MSC
FILE* FFopenW(const wchar_t* a_pFileName, const wchar_t* a_pMode)
{
	FILE* fp = _wfopen(a_pFileName, a_pMode);
	if (fp == nullptr)
	{
		wprintf(L"ERROR: open file %s failed\n\n", a_pFileName);
	}
	return fp;
}
#endif
