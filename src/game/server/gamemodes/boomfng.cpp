/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#include <engine/shared/config.h>
#include <game/server/entities/character.h>
#include <game/server/gamecontext.h>
#include <game/server/player.h>

#include "boomfng.h"

CGameControllerBoomFNG::CGameControllerBoomFNG(CGameContext *pGameServer)
: CGameControllerOpenFNG(pGameServer)
{
	m_pGameType = "boomfng";
}

int CGameControllerBoomFNG::OnCharacterDeath(class CCharacter *pVictim, class CPlayer *pKiller, int Weapon)
{
	return CGameControllerOpenFNG::OnCharacterDeath(pVictim, pKiller, Weapon);
}

void CGameControllerBoomFNG::OnCharacterSpawn(class CCharacter *pChr)
{
	IGameController::OnCharacterSpawn(pChr);
	pChr->GiveWeapon(WEAPON_GRENADE, -1);
}
