#pragma once

class basestream;

enum EMNORMALTYPE
{
	EMNT_BASE					= 0,	// ³ë¸Ö - 1
	EMNT_SPEC					= 1,	// ½ºÆåÅ§·¯ - 2
	EMNT_REFLECT				= 2,	// ¹Ý»ç - 3
	EMNT_ILLUMI					= 3,	// ÀÏ·ç¹Ì³×ÀÌ¼Ç - 2
	EMNT_AMBIENT				= 4,	// ¿¥ºä¾ðÆ® - 2
	EMNT_FLOW					= 5,	// Flow - 3

	EMNT_SPEC_AMBIENT			= 6,	// ½ºÆå + ¿¥ºä¾ðÆ® - 2
	EMNT_SPEC_ILLUMI			= 7,	// ½ºÆå + ÀÏ·ç¹Ì³×ÀÌ¼Ç - 3
	EMNT_SPEC_AMBIENT_ILLUMI	= 8,	// ½ºÆå + ¿¥ºä¾ðÆ® + ÀÏ·ç¹Ì³×ÀÌ¼Ç - 3
	EMNT_SPEC_AMBIENT_FLOW		= 9,	// ½ºÆå + ¿¥ºä¾ðÆ® + Flow - 3

	EMNT_SIZE					= 10,	// Size
};

static const TSTRING g_strNormalTYPE[EMNT_SIZE] = 
{
	_T("EMNT_BASE"),				// 0
	_T("EMNT_SPEC"),				// 1
	_T("EMNT_REFLECT"),				// 2
	_T("EMNT_ILLUMI"),				// 3
	_T("EMNT_AMBIENT"),				// 4
	_T("EMNT_FLOW"),				// 5
	_T("EMNT_SPEC_AMBIENT"),		// 6
	_T("EMNT_SPEC_ILLUMI"),			// 7
	_T("EMNT_SPEC_AMBIENT_ILLUMI"),	// 8
	_T("EMNT_SPEC_AMBIENT_FLOW")	// 9
};

struct DXMATERIAL_HLSL
{
	EMNORMALTYPE	m_emRenderType;

	float	m_fNormalPower;
	float	m_fSpecPower;
	float	m_fIllumiPower;

	TSTRING	m_strSrcTex;		// ¼Ò½º ÅØ½ºÃÄ
	TSTRING	m_strNormal;		// ³ë¸Ö ¸Ê.
	TSTRING	m_strSpecular;		// ½ºÆåÅ§·¯ Àû¿ë ¹üÀ§.
	TSTRING	m_strIllumination;	// ÀÏ·ç¹Ì³×ÀÌ¼Ç Àû¿ë ¹üÀ§.

	LPDIRECT3DTEXTUREQ	m_pNormalMapTex;
	LPDIRECT3DTEXTUREQ	m_pSpecularMapTex;
	LPDIRECT3DTEXTUREQ	m_pIlluminationTex;

	void LodingTexture( LPDIRECT3DDEVICEQ pd3dDevice );
	void ReleaseTexture();

	void CleanUp();
	void Save( basestream& SFile );
	void Load( LPDIRECT3DDEVICEQ pd3dDevice, basestream& SFile );
	void Clone( LPDIRECT3DDEVICEQ pd3dDevice, DXMATERIAL_HLSL* pSrc );

	DXMATERIAL_HLSL();
	~DXMATERIAL_HLSL();
};

class DxMaterialHLSL
{
private:
	static const DWORD	VERSION;

public:
	DXMATERIAL_HLSL*	m_pMaterials;
	DWORD				m_dwMaterialNUM;

public:
	void OnCreateDevice( LPDIRECT3DDEVICEQ pd3dDevice, LPD3DXMATERIAL pMaterials, DWORD dwMaterialNUM );
	void OnDestroyDevice();

public:
	void ReleaseTexture();
	void ReloadTexture();

private:
	void CleanUp();

public:
	void Save( basestream& SFile );
	void Load( LPDIRECT3DDEVICEQ pd3dDevice, basestream& SFile );
	void Clone( LPDIRECT3DDEVICEQ pd3dDevice, DxMaterialHLSL* pSrc );

public:
	DxMaterialHLSL();
	~DxMaterialHLSL();
};



