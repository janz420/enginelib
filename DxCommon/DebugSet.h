//#include "OutPutStream.h"

#ifndef	__C_DEBUGSET__
#define	__C_DEBUGSET__

#define _ON_DEBUGSET

#include "../Common/gassert.h"
#include <string>

class	CD3DFontPar;
namespace CDebugSet
{
	#define ToViewP(arg) (ToView(PSTREAM(arg)))

#ifdef _ON_DEBUGSET
	//	Note	:	µ¿ÀûÀ¸·Î È­¸é¿¡ »Ñ¸²
	//	Usage	:	printf () »ç¿ë¹ý°ú °°À½		
	void ToView ( const char *szFormat, ... );
	
	//	Note	:	µ¿ÀûÀ¸·Î »Ñ¸®µÇ, ¶óÀÎÀ» ÁöÁ¤ÇÔ
	//				¶óÀÎÀº 0¹ø¶óÀÎºÎÅÍ ½ÃÀÛÇÔ
	void ToView ( int line, const char *szFormat, ... );
	void ToView ( int nChannel, int line, const char *szFormat, ... );
	void ToListView ( const char *szFormat, ... );

	void ToPos ( float x, float y, const char *szFormat, ... );
#else
	inline void ToView ( const char *szFormat, ... ) {}
	inline void ToView ( int line, const char *szFormat, ... ) {}
	inline void ToView ( int nChannel, int line, const char *szFormat, ... ) {}
	inline void ToListView ( const char *szFormat, ... ) {}
	inline void ToPos ( float x, float y, const char *szFormat, ... ) {}
#endif // _ON_DEBUGSET

	//	Note	:	ÆÄÀÏ·Î È­¸é¿¡ »Ñ¸²
	//	Usage	:	ÆÄÀÏ¸íÀ» Á¦ÀÏ ¾Õ¿¡ ¾²°í, µð¹ö±× Á¤º¸¸¦ printf ()¸¦ »ç¿ëÇÏµíÀÌ ÆÄ¶ó¹ÌÅÍ¸¦ ³Ñ±è
	void ToLogFile ( const char *szFormat, ... );	

	void ErrorVer ( const char *szFormat, ... );//ª©¥»¸¹¿ù»~´£¥Ü
	// ÃßÀû ·Î±×¸¦ ³²±æ¶§ »ç¿ëÇÔ
	void ToTracingFile ( const char *szAccountName, const char *szFormat, ... );
	// ÇØÅ·ÀÌ ÀÇ½ÉµÉ °æ¿ì ³²´Â ·Î±×
	void ToHackingFile( const char *szFormat, ... );
	// 10¾ïÀÌ»ó µ· ¾÷µ¥ÀÌÆ®½Ã ·Î±×¸¦ ³²±è
	void ToBillionUpdateFile( const char *szFormat, ... );

	void ToFile ( const char *szFileName, const char *szFormat, ... );
	void ToFileWithTime ( const char* szFileName, const char* szFormat, ... );
	void ClearFile ( const char *szFileName );
	
	const char* GetPath ();
	std::string GetCurTime ();

	//	Note	:	µð¹ö±×Á¤º¸¸¦ ÆÄÀÏ·Î Ãâ·ÂÇÒ ¶§, Àý´ë°æ·Î¸¦ ¼³Á¤ÇØ¾ß ÇÑ´Ù.
	//				È­¸éÀ¸·Î Á¤º¸¸¦ Ãâ·ÂÇÏ±â À§ÇØ, Font¸¦ ¼³Á¤ÇÑ´Ù.
	HRESULT OneTimeSceneInit ( const char *pszFullDir, bool bLogFileFinalOpen=false );
	HRESULT	InitDeviceObjects ( CD3DFontPar* pFont );
	HRESULT FinalCleanup();

	void SetLogFileFinalOpen( bool bUse );
	void SetSubjectName_ERROR( BOOL bUse );

	void FrameMove ( float fTime, float fETime );
	void Render ();

	// ÀÓ½Ã Å×½ºÆ®¿ë ( ÁØÇõ )
	void TempOnOff( bool bOn, const char* szFileName = NULL );
	void TempToFile( const char* szFormat, ... );

	void MsgBox( const char *szFormat, ... );
};

namespace CLOCKCHECK
{
	extern DWORD dwShi, dwSlo, dwEhi, dwElo;
	inline void CLOCKCHK_ST ()
	{
		__asm
		{
			rdtsc                      ;Å¬·°Ä«¿îÆ®¸¦ edx:eax·¹Áö½ºÅÍ¿¡ ÀúÀå
			mov     dwShi, edx       ;»óÀ§ dword ¸Þ¸ð¸®¿¡ ¹é¾÷
			mov     dwSlo, eax       ;ÇÏÀ§ dword ¸Þ¸ð¸®¿¡ ¹é¾÷       
		}
	}

	inline void CLOCKCHK_ED ( DWORD &dwHigh, DWORD &dwLow )
	{
		__asm
		{
			rdtsc                      ; Å¬·°Ä«¿îÆ®¸¦ edx:eax·¹Áö½ºÅÍ¿¡ ÀúÀå
			mov     dwElo, eax       ; ÇÏÀ§ dword °ª ÀúÀå
			mov     dwEhi, edx       ; »óÀ§ dword°ª ÀúÀå
		}

		dwHigh = dwEhi - dwShi;
		dwLow = dwElo - dwSlo;
	}
};

#endif	//	__C_DEBUGSET__