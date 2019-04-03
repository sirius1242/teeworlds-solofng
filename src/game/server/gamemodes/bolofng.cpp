/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#include <engine/shared/config.h>
#include <game/server/entities/character.h>
#include <game/server/gamecontext.h>
#include <game/server/player.h>

#include "bolofng.h"

CGameControllerBoloFNG::CGameControllerBoloFNG(CGameContext *pGameServer)
: CGameControllerSoloFNG(pGameServer)
{
	m_pGameType = "bolofng";
}

int CGameControllerBoloFNG::OnCharacterDeath(class CCharacter *pVictim, class CPlayer *pKiller, int Weapon)
{
	return CGameControllerSoloFNG::OnCharacterDeath(pVictim, pKiller, Weapon);
}

void CGameControllerBoloFNG::OnCharacterSpawn(class CCharacter *pChr)
{
	IGameController::OnCharacterSpawn(pChr);
	pChr->GiveWeapon(WEAPON_GRENADE, -1);
}
