#ifndef TXOBTOOL_H_
#define TXOBTOOL_H_

#include <sdw.h>

class CTxobTool
{
public:
	enum EParseOptionReturn
	{
		kParseOptionReturnSuccess,
		kParseOptionReturnIllegalOption,
		kParseOptionReturnNoArgument,
		kParseOptionReturnOptionConflict
	};
	enum EAction
	{
		kActionNone,
		kActionExport,
		kActionImport,
		kActionHelp
	};
	struct SOption
	{
		const char* Name;
		int Key;
		const char* Doc;
	};
	CTxobTool();
	~CTxobTool();
	int ParseOptions(int a_nArgc, char* a_pArgv[]);
	int CheckOptions();
	int Help();
	int Action();
	static SOption s_Option[];
private:
	EParseOptionReturn parseOptions(const char* a_pName, int& a_nIndex, int a_nArgc, char* a_pArgv[]);
	EParseOptionReturn parseOptions(int a_nKey, int& a_nIndex, int a_nArgc, char* a_pArgv[]);
	bool exportFile();
	bool importFile();
	EAction m_eAction;
	string m_sFileName;
	string m_sDirName;
	bool m_bVerbose;
};

#endif	// TXOBTOOL_H_
