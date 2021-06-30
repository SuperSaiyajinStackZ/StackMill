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
#include "SettingsTab.hpp"

int8_t SettingsTab::StoneColors[3] = { 1, 0, 4 }; // 0: Player 1, 1: Player 2, 2: Preview Color.
bool SettingsTab::AI = true;

void SettingsTab::Draw() {
	/* Player 1 Stone Color. */
	Gui::DrawStringCentered(0 + Tab::SettingsOffset, 25, 0.5f, TEXT_BG_COLOR, "Player 1 Stone Color");
	for (int8_t Idx = 0; Idx < 10; Idx++) {
		StackMill3DS::App->GData->DrawStone(Idx, this->XPos[Idx] + Tab::SettingsOffset, 45);
	};

	StackMill3DS::App->GData->DrawSprite(sprites_pointer_idx, this->XPos[SettingsTab::StoneColors[0]] + 6 + Tab::SettingsOffset, 51);
	if (this->SelectedOption == 0) Gui::drawGrid(5 + Tab::SettingsOffset, 25, 310, 50, BAR_COLOR_OUTLINE);


	/* Player 2 Stone Color. */
	Gui::DrawStringCentered(0 + Tab::SettingsOffset, 80, 0.5f, TEXT_BG_COLOR, "Player 2 Stone Color");
	for (int8_t Idx = 0; Idx < 10; Idx++) {
		StackMill3DS::App->GData->DrawStone(Idx, this->XPos[Idx] + Tab::SettingsOffset, 100);
	};

	StackMill3DS::App->GData->DrawSprite(sprites_pointer_idx, this->XPos[SettingsTab::StoneColors[1]] + 6 + Tab::SettingsOffset, 106);
	if (this->SelectedOption == 1) Gui::drawGrid(5 + Tab::SettingsOffset, 80, 310, 50, BAR_COLOR_OUTLINE);


	/* Possibly Play Color. */
	Gui::DrawStringCentered(0 + Tab::SettingsOffset, 135, 0.5f, TEXT_BG_COLOR, "Preview Play Color");
	for (int8_t Idx = 0; Idx < 10; Idx++) {
		StackMill3DS::App->GData->DrawStone(Idx, this->XPos[Idx] + Tab::SettingsOffset, 155);
	};

	StackMill3DS::App->GData->DrawSprite(sprites_pointer_idx, this->XPos[SettingsTab::StoneColors[2]] + 6 + Tab::SettingsOffset, 161);
	if (this->SelectedOption == 2) Gui::drawGrid(5 + Tab::SettingsOffset, 135, 310, 50, BAR_COLOR_OUTLINE);


	/* AI. */
	Gui::DrawStringCentered(0 + Tab::SettingsOffset, 190, 0.5f, TEXT_BG_COLOR, "Using Random Computer AI");
	StackMill3DS::App->GData->DrawStone(9, this->XPos[4] + Tab::SettingsOffset, 210); // Red.
	StackMill3DS::App->GData->DrawStone(7, this->XPos[5] + Tab::SettingsOffset, 210); // Green.

	StackMill3DS::App->GData->DrawSprite(sprites_pointer_idx, this->XPos[4 + SettingsTab::AI] + 6 + Tab::SettingsOffset, 216);
	if (this->SelectedOption == 3) Gui::drawGrid(5 + Tab::SettingsOffset, 190, 310, 45, BAR_COLOR_OUTLINE);
};

void SettingsTab::Handler() {
	if (Tab::TabSwitch) return;

	if (StackMill3DS::App->Down & KEY_TOUCH) {
		/* Stone Color Handler. */
		for (int8_t Idx = 0; Idx < 10; Idx++) {

			/* Check X first. */
			if (StackMill3DS::App->T.px >= this->XPos[Idx] && StackMill3DS::App->T.px <= this->XPos[Idx] + 20) {

				/* Now loop through the Category / Y Position. */
				for (int8_t Idx2 = 0; Idx2 < 3; Idx2++) {
					if (StackMill3DS::App->T.py >= (45 + (Idx2 * 55)) && StackMill3DS::App->T.py <= (45 + (Idx2 * 55) + 20)) {
						SettingsTab::StoneColors[Idx2] = Idx;
						return;
					};
				};
			};
		};

		/* AI Mode Handler. */
		for (int8_t Idx = 0; Idx < 2; Idx++) {
			if (StackMill3DS::App->T.px >= this->XPos[4 + Idx] && StackMill3DS::App->T.px <= this->XPos[4 + Idx] + 20 && StackMill3DS::App->T.py >= 210 && StackMill3DS::App->T.py <= 230) {
				SettingsTab::AI = Idx;
				return;
			};
		};
	};

	/* Option Switch. */
	if (StackMill3DS::App->Repeat & KEY_DOWN) {
		if (this->SelectedOption < 3) this->SelectedOption++;
	};
	if (StackMill3DS::App->Repeat & KEY_UP) {
		if (this->SelectedOption > 0) this->SelectedOption--;
	};

	/* Color Switch & AI Switch. */
	if (StackMill3DS::App->Repeat & KEY_RIGHT) {
		if (this->SelectedOption < 3) {
			if (SettingsTab::StoneColors[this->SelectedOption] < 9) SettingsTab::StoneColors[this->SelectedOption]++;

		} else {
			if (!SettingsTab::AI) SettingsTab::AI = true;
		};
	};
	if (StackMill3DS::App->Repeat & KEY_LEFT) {
		if (this->SelectedOption < 3) {
			if (SettingsTab::StoneColors[this->SelectedOption] > 0) SettingsTab::StoneColors[this->SelectedOption]--;

		} else {
			if (SettingsTab::AI) SettingsTab::AI = false;
		};
	};
};