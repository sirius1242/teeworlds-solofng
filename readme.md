## Solofng mod based on teeworlds 0.7.2

#### Commands:
- `sv_superhammer`: Allow hammer to freeze, 0 to disable
- `sv_sacrscore`: Score get when sacrificed
- `sv_wrongsacrscore`: player decrease score for sacrificing in wrong shrine
- `sv_freezethrough`: Laser through freeze player (0 to disable)
- `sv_teammatethrough`: Laser through player in same team (0 to disable)
- `sv_punish_wrongsacr`: Time to freeze who is sacrificing in a wrong-colored shrine. (0 to disable)
- `sv_hammermelt`: how many ticks to subtract from freezetime, when hammering frozen teammates
- `sv_meltscore`: player score for melting
- `sv_sacrteammate_punish`: Score decrease when sacrifice player in same team.
- `sv_anticamper`: 0 disables, 1 enables anticamper in all modes and 2 only in Instagib
- `sv_anticamper_freeze`: If a player should freeze on camping (and how long) or die
- `sv_anticamper_time`: How long to wait till the player dies/freezes
- `sv_anticamper_range`: Distance how far away the player must move to escape anticamper
- `sv_hammer_scale_x`: linearly scale up hammer x power, percentage, for hammering enemies and unfrozen teammates
- `sv_hammer_scale_y`: linearly scale up hammer y power, percentage, for hammering enemies and unfrozen teammates
- `sv_melt_hammer_scale_x`: linearly scale up hammer x power, percentage, for hammering frozen teammates
- `sv_melt_hammer_scale_y`: linearly scale up hammer y power, percentage, for hammering frozen teammates
- ` sv_loltext_hspace`: horizontal offset between loltext 'pixels'
- ` sv_loltext_vspace`: vertical offset between loltext 'pixels'

#### Sacrifice shrine

shrine_red is tile of number 10, shrine_blue is tile of number 12 when editing maps; shrine_all is tile of number 8, the same as 0.6.

### usage
- download bam 0.5, and use `bam config` and `bam server` to compile
- Write an autoexec.cfg, and use `build/x86_64/debug/teeworlds_srv` to execute the server

Teeworlds [![CircleCI](https://circleci.com/gh/teeworlds/teeworlds.svg?style=svg)](https://circleci.com/gh/teeworlds/teeworlds)
=========

A retro multiplayer shooter
---------------------------

Teeworlds is a free online multiplayer game, available for all major
operating systems. Battle with up to 16 players in a variety of game
modes, including Team Deathmatch and Capture The Flag. You can even
design your own maps!

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software. See license.txt for full license
text including copyright information.

Please visit https://www.teeworlds.com/ for up-to-date information about
the game, including new versions, custom maps and much more.

Instructions to build the game can be found at 
https://teeworlds.com/?page=docs&wiki=compiling_everything. In
particular, you will need SDL2 and FreeType installed.

Originally written by Magnus Auvinen.
