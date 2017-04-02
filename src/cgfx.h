#ifndef CGFX_H_
#define CGFX_H_

#include <sdw.h>

namespace pvrtexture
{
	class CPVRTexture;
}

class CCgfx
{
public:
	enum ETextureFormat
	{
		kTextureFormatRGBA8888 = 0,
		kTextureFormatRGB888 = 1,
		kTextureFormatRGBA5551 = 2,
		kTextureFormatRGB565 = 3,
		kTextureFormatRGBA4444 = 4,
		kTextureFormatLA88 = 5,
		kTextureFormatHL8 = 6,
		kTextureFormatL8 = 7,
		kTextureFormatA8 = 8,
		kTextureFormatLA44 = 9,
		kTextureFormatL4 = 10,
		kTextureFormatA4 = 11,
		kTextureFormatETC1 = 12,
		kTextureFormatETC1_A4 = 13
	};
	CCgfx();
	~CCgfx();
	void SetFileName(const string& a_sFileName);
	void SetDirName(const string& a_sDirName);
	void SetVerbose(bool a_bVerbose);
	bool ExportFile();
	bool ImportFile();
	static bool IsCgfxFile(const string& a_sFileName);
	static const u32 s_uSignatureCgfx;
	static const u32 s_uSignatureTxob;
	static const int s_nBPP[];
	static const int s_nDecodeTransByte[64];
private:
	static int decode(u8* a_pBuffer, n32 a_nWidth, n32 a_nHeight, n32 a_nFormat, pvrtexture::CPVRTexture** a_pPVRTexture);
	static void encode(u8* a_pData, n32 a_nWidth, n32 a_nHeight, n32 a_nFormat, n32 a_nMipmapLevel, n32 a_nBPP, u8** a_pBuffer);
	string m_sFileName;
	UString m_sDirName;
	bool m_bVerbose;
};

#endif	// CGFX_H_
