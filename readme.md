## Fng mod based on teeworlds 0.7.2

gametype: solofng, openfng, bolofng, boomfng

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
- `sv_loltext_hspace`: horizontal offset between loltext 'pixels'
- `sv_loltext_vspace`: vertical offset between loltext 'pixels'
- `sv_freezescore`: Score get when freeze others (except hammer)
- `sv_loltext`: Whether create loltext when score

#### Sacrifice shrine

shrine_red is tile of number 10, shrine_blue is tile of number 12 when editing maps; shrine_all is tile of number 8, the same as 0.6.

### usage (build with bam)
- download bam 0.5, and use `bam config` and `bam server` to compile
- Write an autoexec.cfg, and use `build/x86_64/debug/teeworlds_srv` to execute the server

<a href="https://repology.org/metapackage/teeworlds/versions">
    <img src="https://repology.org/badge/vertical-allrepos/teeworlds.svg" alt="Packaging status" align="right">
</a>

Teeworlds [![CircleCI](https://circleci.com/gh/teeworlds/teeworlds.svg?style=svg)](https://circleci.com/gh/teeworlds/teeworlds) [![AppVeyor Build Status](https://ci.appveyor.com/api/projects/status/github/teeworlds/teeworlds?branch=master&svg=true)](https://ci.appveyor.com/project/heinrich5991/teeworlds)
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

Originally written by Magnus Auvinen.


Building on Linux or macOS
==========================

Installing dependencies
-----------------------

    # Debian/Ubuntu
    sudo apt install build-essential cmake git libfreetype6-dev libsdl2-dev libpnglite-dev libwavpack-dev python3

    # Fedora
    sudo dnf install @development-tools cmake gcc-c++ git freetype-devel mesa-libGLU-devel pnglite-devel python3 SDL2-devel wavpack-devel

    # Arch Linux (doesn't have pnglite in its repositories)
    sudo pacman -S --needed base-devel cmake freetype2 git glu python sdl2 wavpack

    # macOS
    sudo brew install cmake freetype sdl2


Downloading repository
----------------------

    git clone https://github.com/teeworlds/teeworlds --recurse-submodules
    cd teeworlds

    # If you already cloned the repository before, use:
    # git submodule update --init


Building
--------

    mkdir -p build
    cd build
    cmake ..
    make

On subsequent builds, you only have to repeat the `make` step.

You can then run the client with `./teeworlds` and the server with
`./teeworlds_srv`.


Build options
-------------

The following options can be passed to the `cmake ..` command line (between the
`cmake` and `..`) in the "Building" step above.

`-GNinja`: Use the Ninja build system instead of Make. This automatically
parallizes the build and is generally **faster**. (Needs `sudo apt install
ninja-build` on Debian, `sudo dnf install ninja-build` on Fedora, and `sudo
pacman -S --needed ninja` on Arch Linux.)

`-DDEV=ON`: Enable debug mode and disable some release mechanics. This leads to
**faster** builds.

`-DCLIENT=OFF`: Disable generation of the client target. Can be useful on
headless servers which don't have graphics libraries like SDL2 installed.


Building on Windows with Visual Studio
======================================

Download and install some version of [Microsoft Visual
Studio](https://www.visualstudio.com/) (as of writing, MSVS Community 2017)
with the following components:

* Desktop development with C++ (on the main page)
* Python development (on the main page)
* Git for Windows (in Individual Components → Code tools)

Run Visual Studio. Open the Team Explorer (View → Team Explorer, Ctrl+^,
Ctrl+M). Click Clone (in the Team Explorer, Connect → Local Git Repositories).
Enter `https://github.com/teeworlds/teeworlds` into the first input box. Wait
for the download to complete (terminals might pop up).

Wait until the CMake configuration is done (watch the Output windows at the
bottom).

Select `teeworlds.exe` in the Select Startup Item… combobox next to the green
arrow. Wait for the compilation to finish.

For subsequent builds you only have to click the button with the green arrow
again.


Building on Windows with MinGW
==============================

Download and install MinGW with at least the following components:

- mingw-developer-toolkit-bin
- mingw32-base-bin
- mingw32-gcc-g++-bin
- msys-base-bin

Also install [Git](https://git-scm.com/downloads) (for downloading the source
code), [Python](https://www.python.org/downloads/) and
[CMake](https://cmake.org/download/).

Open CMake ("CMake (cmake-gui)" in the start menu). Click "Browse Source"
(first line) and select the directory with the Teeworlds source code. Next,
click "Browse Build" and create a subdirectory for the build (e.g. called
"build"). Then click "Configure". Select "MinGW Makefiles" as the generator and
click "Finish". Wait a bit (until the progress bar is full). Then click
"Generate".

You can now build Teeworlds by executing `mingw32-make` in the build directory.


Building with bam, guides for all operating systems
===================================================

You can also compile Teeworlds with bam, a custom build system. Instructions
for that can be found at https://www.teeworlds.com/?page=docs&wiki=hacking.
