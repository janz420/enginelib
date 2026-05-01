#ifndef DXPIECEDEFINE_H_
#define DXPIECEDEFINE_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "DxPieceDefine.h"

enum EMPIECECHAR
{
	PIECE_HEAD		= 0,
	PIECE_UPBODY	= 1,
	PIECE_LOBODY	= 2,
	PIECE_GLOVE		= 3,
	PIECE_RHAND		= 4,
	PIECE_LHAND		= 5,
	PIECE_FOOT		= 6,
	PIECE_HAIR		= 7,
	PIECE_HEADGEAR	= 8,
	PIECE_VEHICLE	= 9,
	PIECE_WING		= 10,
	PIECE_RFINGER		= 11,
	PIECE_LFINGER		= 12,
	PIECE_WRIST			= 13,
	PIECE_REBOOT_RHAND	= 14,
	PIECE_REBOOT_LHAND	= 15,
	PIECE_NECK			= 16,
	PIECE_BELT			= 17,
	PIECE_JIAOHUAN		= 18,
	PIECE_XUEBAO		= 19,

	PIECE_REV01			= 20,
	PIECE_REV02			= 21,
	PIECE_REV03			= 22,




	PIECE_SIZE		= 23
};

enum EMPEACEZONEWEAPON
{
	EMPEACE_WEAPON_RSLOT = 0,
	EMPEACE_WEAPON_WHAL_SLOT = 1,
	EMPEACE_WEAPON_STICK_RSLOT = 2,
	EMPEACE_WEAPON_R_GUN_SLOT = 3,
	EMPEACE_WEAPON_L_GUN_SLOT = 4,
	EMPEACE_WEAPON_GUN_SLOT = 5,
	//added by XMEN2 | 24-8-2012 | add weapon back slot for assassin class
	EMPEACE_WEAPON_R_SPEAR_SLOT = 6,
	EMPEACE_WEAPON_L_SPEAR_SLOT = 7,
	EMPEACE_WEAPON_SIDE_SLOT = 8,
	EMPEACE_WEAPON_KUNAI_SLOT = 9,
	
	EMPEACE_WEAPON_USER_SLOT	 = 10, 
	EMPEACE_WEAPON_WHIP_SLOT	 = 11,
	EMPEACE_WEAPON_BOX_SLOT		 = 12,
	EMPEACE_WEAPON_HAMMER_SLOT	 = 13,
	EMPEACE_WEAPON_UMBRELLA_SLOT = 14,
	EMPEACE_WEAPON_WHIP_HAND	 = 15,
	EMPEACE_WEAPON_MAGIC_BOX	 = 16,
	EMPEACE_WEAPON_UMBRELLA_BONE = 17,

	EMPEACE_WEAPON_SIZE = 18,
};

namespace SKINTYPE_STING
{
	const TCHAR	m_szWHEREBACKTYPE[EMPEACE_WEAPON_SIZE][64] =
	{
		_T("slot_rhand"),
		_T("whal_slot"),
		_T("stick_rslot"),
		_T("r_gun_slot"),
		_T("l_gun_slot"),
		_T("gun_slot"),
		_T("r_spear_slot"),
		_T("l_spear_slot"),
		_T("side_slot"),
		_T("kunai_slot"),
		_T("user_slot"),
		_T("whip_slot"),
		_T("box_slot"),

		_T("hammer_slot"),
		_T("umbrella_slot"),
		_T("whip_hand"),
		_T("magic_box"),
		_T("umbrella_bone00"),
	};
};

#endif // DXPIECEDEFINE_H_