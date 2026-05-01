#pragma once

#include <map>
#include <string>

#include "../DxEffect/DxEffectFrame.h"
#include "../DxEffect/DxStaticMesh.h"
#include "../DxOctree/DxLandEff.h"
#include "../Meshs/DxFrameMesh.h"
#include "../Meshs/DxAnimationManager.h"

struct DXREPLACEPIECE
{
	char*			szFileName;
	
	D3DXVECTOR3		vMax;
	D3DXVECTOR3		vMin;

	DxFrame*		pFrameRoot;
	DxFrame*		pAphaMapFrameHead;

	DxStaticMesh*	m_pStaticMesh;

	DxAnimationMan*	pAniManHead;
	BOOL			bRendAni;

	PDXEFFECTBASE	pEffectHead;		//	Frame Eff
	PDXEFFECTBASE	pGlobalEffectHead;	//	Global Eff

	//	Note : Single Effect
	DWORD			m_dwNumLandEff;
	PLANDEFF		m_pLandEffList;

	int				nRefCount;

	DXREPLACEPIECE*	pNext;

public:
	DXREPLACEPIECE () :
		szFileName(NULL),
		vMax(0,0,0),
		vMin(0,0,0),
		pFrameRoot(NULL),
		pAphaMapFrameHead(NULL),
		m_pStaticMesh(NULL),
		pAniManHead(NULL),
		bRendAni(TRUE),
		pEffectHead(NULL),
		pGlobalEffectHead(NULL),
		m_dwNumLandEff(0),
		m_pLandEffList(NULL),
		nRefCount(0),
		pNext(NULL)
	{
	}

	~DXREPLACEPIECE ();

	HRESULT Load ( const char* szFile, LPDIRECT3DDEVICEQ pd3dDevice );

	HRESULT InitDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice );
	HRESULT RestoreDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice );
	HRESULT InvalidateDeviceObjects ();
	HRESULT DeleteDeviceObjects ();
	
	HRESULT CleanUp ()
	{
		InvalidateDeviceObjects ();
		DeleteDeviceObjects ();
		return S_OK;
	}

protected:
	HRESULT UpdateFrames ( DxFrame *pframeCur, D3DXMATRIX &matCur );

public:
	HRESULT UpdateEffect ( float fTime, float fETime )
	{
		HRESULT hr=S_OK;

		PDXEFFECTBASE pEffCur = pGlobalEffectHead;
		for ( ; pEffCur; pEffCur = pEffCur->pEffectNext )
		{
			hr = pEffCur->FrameMove ( fTime, fETime );
			if ( FAILED(hr) )	return hr;
		}

		return S_OK;
	}

public:
	HRESULT SetCurTime ( float fCurTime );
	HRESULT FrameMove ( float fTime, float fETime );
	
protected:
	void DrawFrame ( DxFrame *pframeCur, LPDIRECT3DDEVICEQ pd3dDevice, float fAlpha );
	void DrawAlpha ( DxFrame *pframeCur, LPDIRECT3DDEVICEQ pd3dDevice, float fAlpha );
	HRESULT RenderAlpha ( LPDIRECT3DDEVICEQ pd3dDevice, BOOL bShadow, float fAlpha );

	void AddLandEff ( PLANDEFF pLandEff );

public:
	HRESULT Render( LPDIRECT3DDEVICEQ pd3dDevice, D3DXMATRIX* pMatWorld, CLIPVOLUME* pCV, float fAlpha );
	void	Render_ALPHA( LPDIRECT3DDEVICEQ pd3dDevice, D3DXMATRIX* pMatWorld, CLIPVOLUME* pCV, float fAlpha );
};

struct DXPIECEOBJ
{
	float			fCurTime;
	char*			szFileName;
	
	char*			szFrameName;
	D3DXMATRIX		matComb;		//	Original Trans Matrix

	DXREPLACEPIECE*	pReplacePiece;

	D3DXVECTOR3		m_vCenter;		// 
	float			m_fLengthPOW2;	//

	float			m_fAlpha;		// Pick 했을 경우.
	BOOL			m_bAplhaBlend;	// 

	VEC_DWORD		m_vecPointIndex;	// 자신에게 영향을 주는 Point Light Index

	DXPIECEOBJ*		pNext;
	DXPIECEOBJ*		pPickAlphaNext;

	void SetPiece ( DXREPLACEPIECE* pPiece )
	{
		szFileName = pPiece->szFileName;
		pReplacePiece = pPiece;
	}

	void CheckPickAlpha( const D3DXVECTOR3& vMax, const D3DXVECTOR3& vMin, float fLength, float fElapsedTime );

	void CheckPointLight();									// 자신과 맞닿아 있는 빛을 체크를 한다.	< 기본적으로 빛은 로딩되어 있어야 함 >
	void RenderPointLight( LPDIRECT3DDEVICEQ pd3dDevice );	// Point Light를 적용시킨다.

	DXPIECEOBJ () :
		fCurTime(0.0f),
		szFileName(NULL),
		szFrameName(NULL),
		pReplacePiece(NULL),
		m_vCenter(0.f,0.f,0.f),
		m_fLengthPOW2(0.f),
		m_fAlpha(1.f),
		m_bAplhaBlend(FALSE),
		pNext(NULL),
		pPickAlphaNext(NULL)
	{
	}

	~DXPIECEOBJ()
	{
		//	szFileName, pReplacePiece, pPickAlphaNext is Reference Point ... No Delete

		SAFE_DELETE_ARRAY(szFrameName);
		SAFE_DELETE(pNext);
		pPickAlphaNext = NULL;
	}

public:
	static DWORD m_dwVERSION;

public:
	DWORD	GetSaveSetSize ();
	void	SaveSet		( CSerialFile &SFile );
	void	SaveFile	( CSerialFile &SFile );
};
typedef DXPIECEOBJ* LPDXPIECEOBJ;

struct DXPIECEOBJNODE
{
	DXPIECEOBJ*	pPieceObj;
	
	union
	{
		struct { float fMaxX, fMaxY, fMaxZ; };
		struct { D3DXVECTOR3 vMax; };
	};
	union
	{
		struct { float fMinX, fMinY, fMinZ; };
		struct { D3DXVECTOR3 vMin; };
	};

	DXPIECEOBJNODE *pLeftChild;
	DXPIECEOBJNODE *pRightChild;

	BOOL IsCollisionVolume ( CLIPVOLUME &cv );

	DXPIECEOBJNODE () :
		pPieceObj(NULL),
		vMax(0,0,0),
		vMin(0,0,0),
		pLeftChild(NULL),
		pRightChild(NULL)
	{
	}

	~DXPIECEOBJNODE ()
	{
		SAFE_DELETE(pLeftChild);
		SAFE_DELETE(pRightChild);
	}
};
typedef DXPIECEOBJNODE* LPDXPIECEOBJNODE;

//----------------------------------------------------------------------------------------------------------------------
//								D	x		P	i	e	c	e		Q	u	i	c	k		S	o	r	t
//	Note : 괜히 소트한다음 뿌리면 느릴까봐 걱정. ^^;
//			한곳에 집어넣고 배열로 정렬을 하는 것 인가 ?
//----------------------------------------------------------------------------------------------------------------------
class DxPieceQuickSort2
{
protected:
	struct PIECEDISTANCE
	{
		float		m_fDistance;
		DXPIECEOBJ*	m_pPiece;
	};
	PIECEDISTANCE*	m_pArrayPiece;	// 배열
	DWORD			m_dwArraySize;	// 최대 가능한 배열 사이즈
	DWORD			m_dwPieceCount;	// 현재 배열 사이즈

public:
	void SetArrayMaxSize( DWORD dwCount );									// 최대 배열 사이즈 셋팅
	void Reset();															// 현재 배열 사이즈 초기화.
	void InsertData( DXPIECEOBJ* pPiece, const D3DXVECTOR3& vFromPt );	// 무작위 Piece 데이타
	void QuickSortProcess();												// Quick Sort 작업
	void RenderPickAlpha( LPDIRECT3DDEVICEQ pd3dDevice );

protected:
	void DxQuickSort( PIECEDISTANCE pArray[], int m, int n );
	void Swap( PIECEDISTANCE& pData1, PIECEDISTANCE& pData2 );

public:
	DxPieceQuickSort2();
	~DxPieceQuickSort2();
};

class DxReplaceContainer
{
private:
	typedef std::map<std::string,DXREPLACEPIECE*>	REPLACEMAP;
	typedef REPLACEMAP::iterator					REPLACEMAP_ITER;

protected:
	LPDIRECT3DDEVICEQ	m_pd3dDevice;

protected:
	char				szPiecePath[MAX_PATH];

public:
	enum EMREFLECTOPTION
	{
		EM_NULL = 0,
		EM_REFLECT = 1,
		EM_REFLECT_OLD = 2,
	};

public:
	char* GetPath ()	{ return szPiecePath; }

protected:
	REPLACEMAP			m_mapReplace;

public:
	DXREPLACEPIECE* FindPice ( const char *szFile );

public:
	DXREPLACEPIECE* LoadPiece ( const char *szFile );
	void ReleasePiece ( char *szXFile );

public:
	HRESULT CleanUp ();

public:
	HRESULT OneTimeSceneInit ( char* szPath );
	HRESULT InitDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice );
	HRESULT RestoreDeviceObjects ();
	HRESULT InvalidateDeviceObjects ();
	HRESULT DeleteDeviceObjects ();
	HRESULT FinalCleanup ();

	HRESULT FrameMove ( float fTime, float fETime );

	//	Note :  Replace Object... Make.... AABB-Tree
	//
protected:
	static void MakeAABBTree ( LPDXPIECEOBJ *ppArray, DWORD dwArraySize, LPDXPIECEOBJNODE &pTreeNode,
				   const D3DXVECTOR3 vMax, const D3DXVECTOR3 vMin );

public:
	static void MakeAABBTree ( LPDXPIECEOBJNODE &pTreeHead, LPDXPIECEOBJ pListHead );

	//	Note : Replace Object... Render.... AABB-Tree
	//
protected:
	static float m_fTime, m_fElapsedTime;
	static BOOL m_bRendAABBB;
	static DWORD m_dwRendPiece;
	static DXPIECEOBJ*			m_pPickAlpha;	// PickAlpha CheckObject... This Point Insert
	static DxPieceQuickSort2	m_sQuickSort;

public:
	static BOOL IsRendAABB () { return m_bRendAABBB; }
	static void SetRendAABB ( BOOL bRend ) { m_bRendAABBB = bRend; }
	static HRESULT SetTime ( float fTime, float fElapsedTime );

	// Note : LandMan에서 불린다.
	static HRESULT DrawRePlacePiece( LPDIRECT3DDEVICEQ pd3dDevice, DXPIECEOBJ *pObjList, DXPIECEOBJNODE *pObjTree, 
									CLIPVOLUME *pCV, EMREFLECTOPTION emReflect, float fDisPOW2 );

	// Note : 알파를 빼려고 한다.
	static void DrawRePlacePiece( LPDIRECT3DDEVICEQ pd3dDevice, DXPIECEOBJNODE *pObjTree, CLIPVOLUME *pCV, EMREFLECTOPTION emReflect, float fDisPOW2 );
	static void DrawRePlacePiece_ALPHA( LPDIRECT3DDEVICEQ pd3dDevice, DXPIECEOBJNODE *pObjTree, CLIPVOLUME *pCV, EMREFLECTOPTION emReflect );
	static void DrawRePlacePiecePickAlpha( LPDIRECT3DDEVICEQ pd3dDevice );

	// Note : DrawRePlacePiece에서 불린다. 계속 노드를 탄다.
	static HRESULT DrawRePlacePieceNode ( LPDIRECT3DDEVICEQ pd3dDevice, DXPIECEOBJNODE *pNode, 
										CLIPVOLUME *pCV, EMREFLECTOPTION emReflect, float fDisPOW2 );

	static void DrawRePlacePieceNode_ALPHA( LPDIRECT3DDEVICEQ pd3dDevice, DXPIECEOBJNODE *pNode, CLIPVOLUME *pCV, EMREFLECTOPTION emReflect );

protected:
	DxReplaceContainer(void);

public:
	virtual ~DxReplaceContainer(void);

public:
	static DxReplaceContainer& GetInstance();
};
