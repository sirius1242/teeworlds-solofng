/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#include <engine/shared/config.h>
#include <game/server/entities/character.h>
#include <game/server/gamecontext.h>
#include <game/server/player.h>

#include "solofng.h"

CGameControllerSoloFNG::CGameControllerSoloFNG(CGameContext *pGameServer)
: IGameController(pGameServer)
{
	m_pGameType = "solofng";
}

int CGameControllerSoloFNG::OnCharacterDeath(class CCharacter *pVictim, class CPlayer *pKiller, int Weapon)
{
	IGameController::OnCharacterDeath(pVictim, pKiller, Weapon);

	if (pKiller == pVictim->GetPlayer())
		return 0;
	else if (Weapon == WEAPON_SACR_RED || Weapon == WEAPON_SACR_BLUE)
		IGameController::OnPlayerScore(pVictim, pKiller, g_Config.m_SvSacrificeScore, 0, EMOTE_HAPPY);
	else if(Weapon == WEAPON_SACR_ALL)
		IGameController::OnPlayerScore(pVictim, pKiller, (g_Config.m_SvSacrificeScore+1)/2, 0, EMOTE_HAPPY);

	return 0;
}

void CGameControllerSoloFNG::OnCharacterSpawn(class CCharacter *pChr)
{
	IGameController::OnCharacterSpawn(pChr);
	pChr->GiveWeapon(WEAPON_LASER, -1);
}