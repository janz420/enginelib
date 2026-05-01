#pragma once
#include <string>
#include "../Common/CList.h"
#include "DxSkinCharData.h"

class DxSkinDataDummy
{
	typedef std::vector<SANIMCONINFO*>	VECANIMCONINFO;

public:
	std::string				m_strFileName;

	float					m_fScale;
	std::string				m_strPIECE[PIECE_SIZE];
	std::string				m_strSkeleton;

	VECANIMCONINFO			m_vecANIMINFO;
	D3DXVECTOR3				m_vMax, m_vMin;

public:
	enum				{ MAX_BONE = 1024 };
	DWORD				m_dwBONE;
	float				m_fBONE1[MAX_BONE];
	float				m_fBONE2[MAX_BONE];
	float				m_fBONE3[MAX_BONE];
	std::string			m_strBONE[MAX_BONE];

protected:
	BOOL LOAD_0100 ( basestream &SFile );
	BOOL LOAD_0101 ( basestream &SFile );
	BOOL LOAD_0103 ( basestream &SFile );
	//added by XMEN2 | 13-9-2012 | add new version for chf
	BOOL LOAD_0104 ( basestream &SFile );
	BOOL LOAD_0106 ( basestream &SFile );
	BOOL LOAD_0107 ( basestream &SFile );
	BOOL LOAD_0108 ( basestream &SFile );
public:
	BOOL LoadFile ( const char* szFile );
	void CleanUp ();

public:
	SANIMCONINFO* FindAniInfo ( const char* szName );

public:
	DxSkinDataDummy(void);
	~DxSkinDataDummy(void);
};
