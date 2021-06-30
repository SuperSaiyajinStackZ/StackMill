/*
*   This file is part of StackMill
*   Copyright (C) 2021 SuperSaiyajinStackZ
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

#include "Common.hpp"
#include "GFXData.hpp"
#include "screenCommon.hpp"

GFXData::GFXData() { Gui::loadSheet("romfs:/gfx/sprites.t3x", this->Sprites); };
GFXData::~GFXData() { Gui::unloadSheet(this->Sprites); };

void GFXData::DrawTop() {
	Gui::ScreenDraw(Top);
	Gui::Draw_Rect(0, 0, 400, 20, BAR_COLOR);
	Gui::Draw_Rect(0, 20, 400, 1, BAR_COLOR_OUTLINE);
	Gui::Draw_Rect(0, 21, 400, 219, BG_COLOR);
};

void GFXData::DrawBottom() {
	Gui::ScreenDraw(Bottom);
	Gui::Draw_Rect(0, 0, 320, 240, BG_COLOR);
};

void GFXData::DrawStone(const int8_t StoneColor, const int X, const int Y, const float ScaleX, const float ScaleY) {
	Gui::DrawSprite(this->Sprites, sprites_0_idx + StoneColor, X, Y, ScaleX, ScaleY);
};

void GFXData::DrawPlayer(const bool StackZ, const int X, const int Y) {
	Gui::DrawSprite(this->Sprites, sprites_border_0_idx + (SettingsTab::StoneColors[(StackZ ? 0 : 1)]), X, Y);
	Gui::DrawSprite(this->Sprites, (StackZ ? sprites_StackZ_idx : sprites_Stackie_idx), X, Y);
};

void GFXData::DrawSprite(const size_t Idx, const int X, const int Y) {
	Gui::DrawSprite(this->Sprites, Idx, X, Y);
};

/*
	Draw the Corner Edges, being used for the Rules Component.

	const bool LeftSide: If that Corner should be drawn on the Left (true) or Right (false) side.
	const int XPos: The X Start Position where to draw.
	const int YPos: The Y Start Position where to draw (usually 25 with the bar, or 0 without).
	const int YSize: The Y Size of the Corners.
	const bool DrawArrow: If the Arrow should be drawn or not.
*/
void GFXData::DrawCornerEdge(const bool LeftSide, const int XPos, const int YPos, const int YSize, const bool DrawArrow) {
	if (LeftSide) {
		Gui::DrawSprite(this->Sprites, sprites_corner_idx, XPos, YPos);
		Gui::Draw_Rect(XPos, YPos + 25, 25, YSize - 50, BAR_COLOR_OUTLINE);
		Gui::DrawSprite(this->Sprites, sprites_corner_idx, XPos, YPos + YSize - 25, 1.0f, -1.0f);
		if (DrawArrow) Gui::DrawSprite(this->Sprites, sprites_arrow_idx, XPos + 5, YPos + ((YSize / 2) - (39 / 2)));

	} else {
		Gui::DrawSprite(this->Sprites, sprites_corner_idx, XPos, YPos, -1.0f, 1.0f);
		Gui::Draw_Rect(XPos, YPos + 25, 25, YSize - 50, BAR_COLOR_OUTLINE);
		Gui::DrawSprite(this->Sprites, sprites_corner_idx, XPos, YPos + YSize - 25, -1.0f, -1.0f);
		if (DrawArrow) Gui::DrawSprite(this->Sprites, sprites_arrow_idx, XPos, YPos + ((YSize / 2) - (39 / 2)), -1.0f, 1.0f);
	};
};