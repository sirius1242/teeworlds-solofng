/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#include <engine/shared/config.h>

#include <game/server/entities/character.h>
#include <game/server/gamecontext.h>
#include <game/server/player.h>
#include "tdm.h"

CGameControllerTDM::CGameControllerTDM(class CGameContext *pGameServer) : IGameController(pGameServer)
{
	m_pGameType = "TDM";
	m_GameFlags = GAMEFLAG_TEAMS;
}

// event
int CGameControllerTDM::OnCharacterDeath(class CCharacter *pVictim, class CPlayer *pKiller, int Weapon)
{
	IGameController::OnCharacterDeath(pVictim, pKiller, Weapon);

	char aBuf[256];
	if(pKiller && Weapon != WEAPON_GAME && Weapon != WEAPON_NINJA && Weapon != WEAPON_MELT)
	{
		// do team scoring
		CCharacter * pChr = pKiller->GetCharacter();
		if(pKiller->GetTeam() == pVictim->GetPlayer()->GetTeam() && Weapon != WEAPON_NINJA)
			m_aTeamscore[pKiller->GetTeam()&1]-=g_Config.m_SvSacrTeammatePunish; // klant arschel
		else if(Weapon == WEAPON_SACR_ALL)
		{
			m_aTeamscore[pKiller->GetTeam()&1]+=g_Config.m_SvSacrificeScore;
			pKiller->m_Score+=(g_Config.m_SvSacrificeScore+1)/2;
			str_format(aBuf, sizeof aBuf, "%s team sacrificed (%+d), pleasing the gods", (pKiller->GetTeam() == TEAM_RED)?"Red":"Blue", g_Config.m_SvSacrificeScore);
			if (pChr)
				pChr->SetEmote(EMOTE_HAPPY, Server()->Tick() + Server()->TickSpeed());
			GameServer()->SendBroadcast(aBuf, -1);
		}
		else if((Weapon == WEAPON_SACR_RED && pKiller->GetTeam() == TEAM_RED)||(Weapon == WEAPON_SACR_BLUE && pKiller->GetTeam() == TEAM_BLUE))
		{
			m_aTeamscore[pKiller->GetTeam()&1]+=g_Config.m_SvSacrificeScore*2;
			pKiller->m_Score+=g_Config.m_SvSacrificeScore;
			str_format(aBuf, sizeof aBuf, "%s team sacrificed (%+d), pleasing the gods", (pKiller->GetTeam() == TEAM_RED)?"Red":"Blue", g_Config.m_SvSacrificeScore*2);
			if (pChr)
				pChr->SetEmote(EMOTE_HAPPY, Server()->Tick() + Server()->TickSpeed());
			GameServer()->SendBroadcast(aBuf, -1);
		}
		else if((Weapon == WEAPON_SACR_RED && pKiller->GetTeam() == TEAM_BLUE)||(Weapon == WEAPON_SACR_BLUE && pKiller->GetTeam() == TEAM_RED))
		{
			pKiller->m_Score-=g_Config.m_SvWrongSacrScore;
			m_aTeamscore[pKiller->GetTeam()&1]-=g_Config.m_SvWrongSacrScore/2;
			str_format(aBuf, sizeof aBuf, "%s sacrificed in the wrong shrine (-%d)", Server()->ClientName(pKiller->GetCID()), g_Config.m_SvSacrificeScore/2);
			if (g_Config.m_SvPunishWrongSacr)
				pKiller->GetCharacter()->Freeze(pKiller->GetCID(), WEAPON_NINJA);
			if (pChr)
				pChr->SetEmote(EMOTE_PAIN, Server()->Tick() + Server()->TickSpeed());
			GameServer()->SendBroadcast(aBuf, -1);
		}
		else
			m_aTeamscore[pKiller->GetTeam()&1]++; // good shit
	}

	pVictim->GetPlayer()->m_RespawnTick = max(pVictim->GetPlayer()->m_RespawnTick, Server()->Tick()+Server()->TickSpeed()*g_Config.m_SvRespawnDelayTDM);

	return 0;
}
