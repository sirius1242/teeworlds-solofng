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


	if(pKiller && Weapon != WEAPON_GAME)
	{
		// do team scoring
		if(pKiller == pVictim->GetPlayer() || pKiller->GetTeam() == pVictim->GetPlayer()->GetTeam())
			m_aTeamscore[pKiller->GetTeam()&1]--; // klant arschel
		else if(Weapon == WEAPON_SACR_ALL)
			m_aTeamscore[pKiller->GetTeam()&1]+=g_Config.m_SvSacrificeScore;
		else if(Weapon == WEAPON_SACR_RED)
		{
			if (pKiller->GetTeam() == TEAM_RED)
				m_aTeamscore[pKiller->GetTeam()&1]+=g_Config.m_SvSacrificeScore*2;
			if (pKiller->GetTeam() == TEAM_BLUE)
			{
				m_aTeamscore[pKiller->GetTeam()&1]-=(g_Config.m_SvWrongSacrScore+1)/2;
				if (g_Config.m_SvPunishWrongSacr)
					pKiller->GetCharacter()->Freeze(pKiller->GetCID(), pKiller->GetCID());
			}
		}
		else if(Weapon == WEAPON_SACR_BLUE)
		{
			if (pKiller->GetTeam() == TEAM_BLUE)
				m_aTeamscore[pKiller->GetTeam()&1]+=g_Config.m_SvSacrificeScore*2;
			if (pKiller->GetTeam() == TEAM_RED)
			{
				m_aTeamscore[pKiller->GetTeam()&1]-=(g_Config.m_SvWrongSacrScore+1)/2;
				if (g_Config.m_SvPunishWrongSacr)
					pKiller->GetCharacter()->Freeze(pKiller->GetCID(), pKiller->GetCID());
			}
		}
		else
			m_aTeamscore[pKiller->GetTeam()&1]++; // good shit
	}

	pVictim->GetPlayer()->m_RespawnTick = max(pVictim->GetPlayer()->m_RespawnTick, Server()->Tick()+Server()->TickSpeed()*g_Config.m_SvRespawnDelayTDM);

	return 0;
}
