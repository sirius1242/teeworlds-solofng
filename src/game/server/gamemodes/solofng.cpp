/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#include <engine/shared/config.h>
#include <game/server/entities/character.h>
#include <game/server/gamecontext.h>
#include <game/server/player.h>

#include "solofng.h"

CGameControllerSolofng::CGameControllerSolofng(CGameContext *pGameServer)
: IGameController(pGameServer)
{
	m_pGameType = "solofng";
}

int CGameControllerSolofng::OnCharacterDeath(class CCharacter *pVictim, class CPlayer *pKiller, int Weapon)
{
	IGameController::OnCharacterDeath(pVictim, pKiller, Weapon);

	char aBuf[256];
	if (Weapon == WEAPON_SACR_RED || Weapon == WEAPON_SACR_BLUE)
	{
		pKiller->m_Score+=g_Config.m_SvSacrificeScore;
		str_format(aBuf, sizeof aBuf, "%s sacrificed (%+d), pleasing the gods", Server()->ClientName(pKiller->GetCID()), g_Config.m_SvSacrificeScore);
		GameServer()->SendBroadcast(aBuf, -1);
	}
	else if(Weapon == WEAPON_SACR_ALL)
	{
		pKiller->m_Score+=(g_Config.m_SvSacrificeScore+1)/2;
		str_format(aBuf, sizeof aBuf, "%s sacrificed (%+d), pleasing the gods", Server()->ClientName(pKiller->GetCID()), (g_Config.m_SvSacrificeScore+1)/2);
		GameServer()->SendBroadcast(aBuf, -1);
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