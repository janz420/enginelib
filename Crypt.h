#ifndef NEOEASYCRYPTION_TEST_
#define NEOEASYCRYPTION_TEST_

#pragma once

namespace CCrypt
{
	enum
	{
		//default
		EN = 0x101820, //101820, 420, 42011
		EN2 = 0x20, //20, 2011
		END = 0x03,
	};
	enum
	{
		ENTYPE_ALL,
	};
	enum
	{
		ENCRY_VER = 0x100,
		ENCRY_HEADER_SIZE = 12,
	};

	enum 
	{
		TEXTURE_DDS,
		TEXTURE_TGA,

		TEXTURE_TYPE,
	};

	enum 
	{
		TEX_HEADER_SIZE = 12,
		TEX_VERSION		= 0x100,
		TEX_XOR_DATA	= 0xA0,
		TEX_DIFF_DATA	= 0xA3,
	};


	extern BOOL	bCryptRCC;
	extern BOOL	bEngineDebug;
	extern BOOL	bEngineDebugLog; // Added By Janzs420

	void Encryption(BYTE* B,int dwSize);
	void Decryption(BYTE* B,int dwSize);
	void LoadSetting( const TCHAR *szRootPath );

};

#endif
