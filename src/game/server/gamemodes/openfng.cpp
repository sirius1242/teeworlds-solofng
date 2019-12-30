/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#include <engine/shared/config.h>

#include <game/server/entities/character.h>
#include <game/server/gamecontext.h>
#include <game/server/player.h>
#include "openfng.h"

CGameControllerOpenFNG::CGameControllerOpenFNG(class CGameContext *pGameServer) : IGameController(pGameServer)
{
	m_pGameType = "openfng";
	m_GameFlags = GAMEFLAG_TEAMS;
}

// event
int CGameControllerOpenFNG::OnCharacterDeath(class CCharacter *pVictim, class CPlayer *pKiller, int Weapon)
{
	IGameController::OnCharacterDeath(pVictim, pKiller, Weapon);

	if(pKiller && Weapon != WEAPON_GAME && Weapon != WEAPON_NINJA && Weapon != WEAPON_MELT && Weapon != WEAPON_HAMMER)
	{
		// do team scoring
		if(pKiller->GetTeam() == pVictim->GetPlayer()->GetTeam())
			m_aTeamscore[pKiller->GetTeam()&1]-=g_Config.m_SvSacrTeammatePunish/2; // klant arschel
		else if(Weapon == WEAPON_SACR_ALL)
			IGameController::OnPlayerScore(pVictim, pKiller, (g_Config.m_SvSacrificeScore+1)/2, g_Config.m_SvSacrificeScore, EMOTE_HAPPY);
		else if((Weapon == WEAPON_SACR_RED && pKiller->GetTeam() == TEAM_RED)||(Weapon == WEAPON_SACR_BLUE && pKiller->GetTeam() == TEAM_BLUE))
			IGameController::OnPlayerScore(pVictim, pKiller, g_Config.m_SvSacrificeScore, g_Config.m_SvSacrificeScore*2, EMOTE_HAPPY);
		else if((Weapon == WEAPON_SACR_RED && pKiller->GetTeam() == TEAM_BLUE)||(Weapon == WEAPON_SACR_BLUE && pKiller->GetTeam() == TEAM_RED))
			IGameController::OnPlayerScore(pVictim, pKiller, -g_Config.m_SvWrongSacrScore, -g_Config.m_SvWrongSacrScore/2, EMOTE_PAIN);
		else
			m_aTeamscore[pKiller->GetTeam()&1]++; // good shit
	}

	pVictim->GetPlayer()->m_RespawnTick = max(pVictim->GetPlayer()->m_RespawnTick, Server()->Tick()+Server()->TickSpeed()*g_Config.m_SvRespawnDelayTDM);

	return 0;
}

void CGameControllerOpenFNG::OnCharacterSpawn(class CCharacter *pChr)
{
	IGameController::OnCharacterSpawn(pChr);
	pChr->GiveWeapon(WEAPON_LASER, -1);
}
