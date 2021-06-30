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
#include "CreditsTab.hpp"

void CreditsTab::Draw() {
	Gui::DrawStringCentered(0 + Tab::CreditsOffset, 35, 0.5f, TEXT_BG_COLOR, "StackMill developed by SuperSaiyajinStackZ.");
	Gui::DrawStringCentered(0 + Tab::CreditsOffset, 55, 0.5f, TEXT_BG_COLOR, "StackMill-Core: SuperSaiyajinStackZ");
	Gui::DrawStringCentered(0 + Tab::CreditsOffset, 70, 0.5f, TEXT_BG_COLOR, "Graphics: SuperSaiyajinStackZ");
	Gui::DrawStringCentered(0 + Tab::CreditsOffset, 85, 0.5f, TEXT_BG_COLOR, "Universal-Core: Universal-Team");

	StackMill3DS::App->GData->DrawSprite(sprites_StackZ_idx, 110 + Tab::CreditsOffset, 105);
};