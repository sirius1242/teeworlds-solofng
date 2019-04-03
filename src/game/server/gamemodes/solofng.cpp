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

	char aBuf[256];
	char lolt[64];
	if (Weapon == WEAPON_SACR_RED || Weapon == WEAPON_SACR_BLUE)
	{
		pKiller->m_Score+=g_Config.m_SvSacrificeScore;
		str_format(aBuf, sizeof aBuf, "%s sacrificed (%+d), pleasing the gods", Server()->ClientName(pKiller->GetCID()), g_Config.m_SvSacrificeScore);
		GameServer()->SendBroadcast(aBuf, -1);
		str_format(lolt, sizeof lolt, "%+d", g_Config.m_SvSacrificeScore);
		GameServer()->CreateLolText(pKiller->GetCharacter(), false, vec2(0.f, -50.f), vec2(0.f, 0.f), 50, lolt);
	}
	else if(Weapon == WEAPON_SACR_ALL)
	{
		pKiller->m_Score+=(g_Config.m_SvSacrificeScore+1)/2;
		str_format(aBuf, sizeof aBuf, "%s sacrificed (%+d), pleasing the gods", Server()->ClientName(pKiller->GetCID()), (g_Config.m_SvSacrificeScore+1)/2);
		GameServer()->SendBroadcast(aBuf, -1);
		str_format(lolt, sizeof lolt, "%+d", (g_Config.m_SvSacrificeScore+1)/2);
		GameServer()->CreateLolText(pKiller->GetCharacter(), false, vec2(0.f, -50.f), vec2(0.f, 0.f), 50, lolt);
	}

	// set sacrificer's face to happy (taunt!)
	if (Weapon == WEAPON_SACR_RED || Weapon == WEAPON_SACR_BLUE || Weapon == WEAPON_SACR_ALL)
	{
		CCharacter * pChr = pKiller->GetCharacter();
		if (pChr)
			pChr->SetEmote(EMOTE_HAPPY, Server()->Tick() + Server()->TickSpeed());
	}
	return 0;
}

void CGameControllerSoloFNG::OnCharacterSpawn(class CCharacter *pChr)
{
	IGameController::OnCharacterSpawn(pChr);
	pChr->GiveWeapon(WEAPON_LASER, -1);
}