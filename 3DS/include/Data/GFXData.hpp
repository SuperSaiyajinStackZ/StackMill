/*
*   This file is part of StackMill
*   Copyright (C) 2021-2022 SuperSaiyajinStackZ
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*   Additional Terms 7.b and 7.c of GPLv3 apply to this file:
*       * Requiring preservation of specified reasonable legal notices or
*         author attributions in that material or in the Appropriate Legal
*         Notices displayed by works containing it.
*       * Prohibiting misrepresentation of the origin of that material,
*         or requiring that modified versions of such material be marked in
*         reasonable ways as different from the original version.
*/

#ifndef _STACKMILL_GFXDATA_HPP
#define _STACKMILL_GFXDATA_HPP

#include "sprites.h"
#include <citro2d.h>
#include <string>

#define BG_COLOR			C2D_Color32(255, 255, 204, 200)
#define BAR_COLOR			C2D_Color32(82, 82, 82, 200)
#define BAR_COLOR_OUTLINE	C2D_Color32(40, 40, 40, 200)
#define TEXT_COLOR			C2D_Color32(255, 255, 255, 200)
#define TEXT_BG_COLOR		C2D_Color32(0, 0, 0, 200)

class GFXData {
public:
	GFXData();
	~GFXData();

	void DrawTop();
	void DrawBottom();

	void DrawStone(const int8_t StoneColor, const int X, const int Y, const float ScaleX = 1.0f, const float ScaleY = 1.0f);
	void DrawPlayer(const bool StackZ, const int X, const int Y);
	void DrawSprite(const size_t Idx, const int X, const int Y);
	void DrawCornerEdge(const bool LeftSide, const int XPos, const int YPos, const int YSize, const bool DrawArrow);
private:
	C2D_SpriteSheet Sprites = nullptr;
};

#endif