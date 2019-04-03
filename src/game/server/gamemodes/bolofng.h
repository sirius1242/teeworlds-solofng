/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#ifndef GAME_SERVER_GAMEMODES_BOLOFNG_H
#define GAME_SERVER_GAMEMODES_BOLOFNG_H
#include <game/server/gamecontroller.h>
#include "solofng.h"

class CGameControllerBoloFNG : public CGameControllerSoloFNG
{
public:
	CGameControllerBoloFNG(class CGameContext *pGameServer);

	// event
	virtual int OnCharacterDeath(class CCharacter *pVictim, class CPlayer *pKiller, int Weapon);
	virtual void OnCharacterSpawn(class CCharacter *pChr);
};

#endif
