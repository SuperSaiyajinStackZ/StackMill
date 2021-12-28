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
int8_t SettingsTab::AI = 1;
bool SettingsTab::Swipe = false;


void SettingsTab::DrawMenu(const SettingsTab::SubMenu M, const int AddOffs) {
	if (AddOffs > -240 && AddOffs < 240) {
		switch(M) {
			case SettingsTab::SubMenu::Main:
				for (int8_t Idx = 0; Idx < 3; Idx++) {
					Gui::drawGrid(this->MainPos[Idx].x + Tab::SettingsOffset, this->MainPos[Idx].y + AddOffs, this->MainPos[Idx].w, this->MainPos[Idx].h, BAR_COLOR_OUTLINE);
					/* If Idx is the current Selection -> Fill the button with the bar color. */
					if ((Idx == this->SelectedOption)) Gui::Draw_Rect(this->MainPos[Idx].x + 1 + Tab::SettingsOffset, this->MainPos[Idx].y + 1 + AddOffs, this->MainPos[Idx].w - 2, this->MainPos[Idx].h - 2, BAR_COLOR);
				}

				Gui::DrawStringCentered(Tab::SettingsOffset, this->MainPos[0].y + 10 + AddOffs, 0.5f, TEXT_BG_COLOR, StackMill3DS::App->LH->Translation(LangHandler::Strings::GameSettings), 135);
				Gui::DrawStringCentered(Tab::SettingsOffset, this->MainPos[1].y + 10 + AddOffs, 0.5f, TEXT_BG_COLOR, StackMill3DS::App->LH->Translation(LangHandler::Strings::Language), 135);
				Gui::DrawStringCentered(Tab::SettingsOffset, this->MainPos[2].y + 10 + AddOffs, 0.5f, TEXT_BG_COLOR, StackMill3DS::App->LH->Translation(LangHandler::Strings::ImportExport), 135);
				break;

			/* Game Settings. */
			case SettingsTab::SubMenu::GameSettings:
				/* Player 1 Stone Color. */
				Gui::DrawStringCentered(0 + Tab::SettingsOffset, 25 + AddOffs, 0.5f, TEXT_BG_COLOR, StackMill3DS::App->LH->Translation(LangHandler::Strings::Player1Color), 310);
				for (int8_t Idx = 0; Idx < 10; Idx++) {
					StackMill3DS::App->GData->DrawStone(Idx, this->XPos[Idx] + Tab::SettingsOffset, 45 + AddOffs);
				}

				StackMill3DS::App->GData->DrawSprite(sprites_pointer_idx, this->XPos[SettingsTab::StoneColors[0]] + 6 + Tab::SettingsOffset, 51 + AddOffs);
				if (this->SelectedOption == 0) Gui::drawGrid(5 + Tab::SettingsOffset, 25 + AddOffs, 310, 50, BAR_COLOR_OUTLINE);

				/* Player 2 Stone Color. */
				Gui::DrawStringCentered(0 + Tab::SettingsOffset, 80 + AddOffs, 0.5f, TEXT_BG_COLOR, StackMill3DS::App->LH->Translation(LangHandler::Strings::Player2Color), 310);
				for (int8_t Idx = 0; Idx < 10; Idx++) {
					StackMill3DS::App->GData->DrawStone(Idx, this->XPos[Idx] + Tab::SettingsOffset, 100 + AddOffs);
				}

				StackMill3DS::App->GData->DrawSprite(sprites_pointer_idx, this->XPos[SettingsTab::StoneColors[1]] + 6 + Tab::SettingsOffset, 106 + AddOffs);
				if (this->SelectedOption == 1) Gui::drawGrid(5 + Tab::SettingsOffset, 80 + AddOffs, 310, 50, BAR_COLOR_OUTLINE);

				/* Possibly Play Color. */
				Gui::DrawStringCentered(0 + Tab::SettingsOffset, 135 + AddOffs, 0.5f, TEXT_BG_COLOR, StackMill3DS::App->LH->Translation(LangHandler::Strings::PreviewColor), 310);
				for (int8_t Idx = 0; Idx < 10; Idx++) {
					StackMill3DS::App->GData->DrawStone(Idx, this->XPos[Idx] + Tab::SettingsOffset, 155 + AddOffs);
				}

				StackMill3DS::App->GData->DrawSprite(sprites_pointer_idx, this->XPos[SettingsTab::StoneColors[2]] + 6 + Tab::SettingsOffset, 161 + AddOffs);
				if (this->SelectedOption == 2) Gui::drawGrid(5 + Tab::SettingsOffset, 135 + AddOffs, 310, 50, BAR_COLOR_OUTLINE);

				/* AI. */
				Gui::DrawStringCentered(0 + Tab::SettingsOffset, 190 + AddOffs, 0.5f, TEXT_BG_COLOR, StackMill3DS::App->LH->Translation(LangHandler::Strings::Computer), 310);
				StackMill3DS::App->GData->DrawStone(9, this->XPos[4] - 15 + Tab::SettingsOffset, 210 + AddOffs); // Red.
				StackMill3DS::App->GData->DrawStone(4, this->XPos[5] - 15 + Tab::SettingsOffset, 210 + AddOffs); // Yellow.
				StackMill3DS::App->GData->DrawStone(7, this->XPos[6] - 15 + Tab::SettingsOffset, 210 + AddOffs); // Green.

				StackMill3DS::App->GData->DrawSprite(sprites_pointer_idx, this->XPos[4 + SettingsTab::AI] - 15 + 6 + Tab::SettingsOffset, 216 + AddOffs);
				if (this->SelectedOption == 3) Gui::drawGrid(5 + Tab::SettingsOffset, 190 + AddOffs, 310, 45, BAR_COLOR_OUTLINE);
				break;

			/* Language Selection. */
			case SettingsTab::SubMenu::Language: { // Needed to do '{' because of a declared variable inside it.
				int8_t ClrIdx = 0;

				for (int8_t Lang = 0; Lang < 3; Lang++) {
					/* Switch the chip color index, so the selection looks good. */
					if (ClrIdx < 9) ClrIdx++;
					else ClrIdx = 0;

					StackMill3DS::App->GData->DrawStone(ClrIdx, this->LanguagePos[Lang].x + Tab::SettingsOffset, this->LanguagePos[Lang].y + AddOffs);
					if (this->Language == Lang) StackMill3DS::App->GData->DrawSprite(sprites_pointer_idx, this->LanguagePos[Lang].x + 6 + Tab::SettingsOffset, this->LanguagePos[Lang].y + 6 + AddOffs);
				}

				Gui::DrawString(this->LanguagePos[0].x + 25 + Tab::SettingsOffset, this->LanguagePos[0].y - 1 + AddOffs, 0.6f, TEXT_BG_COLOR, "English");
				Gui::DrawString(this->LanguagePos[1].x + 25 + Tab::SettingsOffset, this->LanguagePos[1].y - 1 + AddOffs, 0.6f, TEXT_BG_COLOR, "Deutsch");
				Gui::DrawString(this->LanguagePos[2].x + 25 + Tab::SettingsOffset, this->LanguagePos[2].y - 1 + AddOffs, 0.6f, TEXT_BG_COLOR, "日本語");
				break;
			}

			/* Import / Export Game. */
			case SettingsTab::SubMenu::ImportExport:
				for (int8_t Idx = 0; Idx < 2; Idx++) {
					Gui::drawGrid(this->ImportExportPos[Idx].x + Tab::SettingsOffset, this->ImportExportPos[Idx].y + AddOffs, this->ImportExportPos[Idx].w, this->ImportExportPos[Idx].h, BAR_COLOR_OUTLINE);
					/* If Idx is the current Selection -> Fill the button with the bar color. */
					if ((Idx == this->SelectedOption)) Gui::Draw_Rect(this->ImportExportPos[Idx].x + 1 + Tab::SettingsOffset, this->ImportExportPos[Idx].y + 1 + AddOffs, this->ImportExportPos[Idx].w - 2, this->ImportExportPos[Idx].h - 2, BAR_COLOR);
				}

				Gui::DrawStringCentered(Tab::SettingsOffset, this->ImportExportPos[0].y + 10 + AddOffs, 0.5f, TEXT_BG_COLOR, StackMill3DS::App->LH->Translation(LangHandler::Strings::ImportGame), 135);
				Gui::DrawStringCentered(Tab::SettingsOffset, this->ImportExportPos[1].y + 10 + AddOffs, 0.5f, TEXT_BG_COLOR, StackMill3DS::App->LH->Translation(LangHandler::Strings::ExportGame), 135);
				break;
		}
	}
};


void SettingsTab::Draw() {
	this->DrawMenu(SettingsTab::SubMenu::Main, this->MenuPos[0]);

	/* Handle next menu draws. */
	switch(this->Menu) {
		case SettingsTab::SubMenu::Main:
			break; // Already handled above ^.

		case SettingsTab::SubMenu::GameSettings:
			this->DrawMenu(SettingsTab::SubMenu::GameSettings, this->MenuPos[1]);
			break;

		case SettingsTab::SubMenu::Language:
			this->DrawMenu(SettingsTab::SubMenu::Language, this->MenuPos[1]);
			break;

		case SettingsTab::SubMenu::ImportExport:
			this->DrawMenu(SettingsTab::SubMenu::ImportExport, this->MenuPos[1]);
			break;
	}
};


void SettingsTab::MainHandle() {
	if (StackMill3DS::App->Down & KEY_TOUCH) {
		for (int8_t Idx = 1; Idx < 4; Idx++) {
			if (this->MainPos[Idx - 1].Touched(StackMill3DS::App->T)) {
				this->Menu = (SettingsTab::SubMenu)Idx;
				this->In = true, this->SelectedOption = 0;
				if (this->Menu == SettingsTab::SubMenu::Language) this->Language = StackMill3DS::App->LH->GetLang();
				SettingsTab::Swipe = true;
				break;
			}
		}
	}

	if (StackMill3DS::App->Down & KEY_A) {
		switch(this->SelectedOption) {
			case 0:
				this->Menu = SettingsTab::SubMenu::GameSettings;
				this->In = true, this->SelectedOption = 0;
				SettingsTab::Swipe = true;
				break;

			case 1:
				this->Menu = SettingsTab::SubMenu::Language;
				this->In = true, this->Language = StackMill3DS::App->LH->GetLang();
				SettingsTab::Swipe = true;
				break;

			case 2:
				this->Menu = SettingsTab::SubMenu::ImportExport;
				this->In = true, this->SelectedOption = 0;
				SettingsTab::Swipe = true;
				break;
		}
	}

	if (StackMill3DS::App->Down & KEY_DOWN) {
		if (this->SelectedOption < 2) this->SelectedOption++;
	}

	if (StackMill3DS::App->Down & KEY_UP) {
		if (this->SelectedOption > 0) this->SelectedOption--;
	}
};


void SettingsTab::GameSettingsHandle() {
	if (StackMill3DS::App->Down & KEY_B) {
		this->In = false, this->SelectedOption = 0;
		SettingsTab::Swipe = true;
	}

	if (StackMill3DS::App->Down & KEY_TOUCH) {
		/* Stone Color Handler. */
		for (int8_t Idx = 0; Idx < 10; Idx++) {

			/* Check X first. */
			if (StackMill3DS::App->T.px >= this->XPos[Idx] && StackMill3DS::App->T.px <= this->XPos[Idx] + 20) {

				/* Now loop through the Category / Y Position. */
				for (int8_t Idx2 = 0; Idx2 < 3; Idx2++) {
					if (StackMill3DS::App->T.py >= (45 + (Idx2 * 55)) && StackMill3DS::App->T.py <= (45 + (Idx2 * 55) + 20)) {
						SettingsTab::StoneColors[Idx2] = Idx;
						StackMill3DS::App->ConfigChanged();
						return;
					}
				}
			}
		}

		/* AI Mode Handler. */
		for (int8_t Idx = 0; Idx < 3; Idx++) {
			if (StackMill3DS::App->T.px >= this->XPos[4 + Idx] - 15 && StackMill3DS::App->T.px <= this->XPos[4 + Idx] - 15 + 20 && StackMill3DS::App->T.py >= 210 && StackMill3DS::App->T.py <= 230) {
				SettingsTab::AI = Idx;
				StackMill3DS::App->ConfigChanged();
				return;
			}
		}
	}

	/* Option Switch. */
	if (StackMill3DS::App->Repeat & KEY_DOWN) {
		if (this->SelectedOption < 3) this->SelectedOption++;
	}

	if (StackMill3DS::App->Repeat & KEY_UP) {
		if (this->SelectedOption > 0) this->SelectedOption--;
	}

	/* Color Switch & AI Switch. */
	if (StackMill3DS::App->Repeat & KEY_RIGHT) {
		if (this->SelectedOption < 3) {
			if (SettingsTab::StoneColors[this->SelectedOption] < 9) {
				SettingsTab::StoneColors[this->SelectedOption]++;
				StackMill3DS::App->ConfigChanged();
			}

		} else {
			if (SettingsTab::AI < 2) {
				SettingsTab::AI++;
				StackMill3DS::App->ConfigChanged();
			}
		}
	}

	if (StackMill3DS::App->Repeat & KEY_LEFT) {
		if (this->SelectedOption < 3) {
			if (SettingsTab::StoneColors[this->SelectedOption] > 0) {
				SettingsTab::StoneColors[this->SelectedOption]--;
				StackMill3DS::App->ConfigChanged();
			}

		} else {
			if (SettingsTab::AI > 0) {
				SettingsTab::AI--;
				StackMill3DS::App->ConfigChanged();
			}
		}
	}
};


void SettingsTab::LanguageHandle() {
	if (StackMill3DS::App->Down & KEY_B) {
		this->In = false, this->SelectedOption = 1;
		SettingsTab::Swipe = true;
	}

	if (StackMill3DS::App->Down & KEY_DOWN) {
		if (this->Language < 2) this->Language++;
	}

	if (StackMill3DS::App->Down & KEY_UP) {
		if (this->Language > 0) this->Language--;
	}

	if (StackMill3DS::App->Down & KEY_A) {
		/* Load Language. */
		StackMill3DS::App->LH->LoadLang((LangHandler::Langs)this->Language);
		StackMill3DS::App->ConfigChanged();

		this->In = false, this->SelectedOption = 1;
		SettingsTab::Swipe = true;
	}

	if (StackMill3DS::App->Down & KEY_TOUCH) {
		for (int8_t Idx = 0; Idx < 3; Idx++) {
			if (this->LanguagePos[Idx].Touched(StackMill3DS::App->T)) {
				this->Language = Idx;

				/* Load Language. */
				StackMill3DS::App->LH->LoadLang((LangHandler::Langs)this->Language);
				StackMill3DS::App->ConfigChanged();

				this->In = false, this->SelectedOption = 1;
				SettingsTab::Swipe = true;
				break;
			}
		}
	}
};


void SettingsTab::ImportExportHandle() {
	if (StackMill3DS::App->Down & KEY_B) {
		this->In = false, this->SelectedOption = 2;
		SettingsTab::Swipe = true;
	}

	if (StackMill3DS::App->Down & KEY_DOWN) {
		if (this->SelectedOption < 1) this->SelectedOption++;
	}

	if (StackMill3DS::App->Down & KEY_UP) {
		if (this->SelectedOption > 0) this->SelectedOption--;
	}

	if (StackMill3DS::App->Down & KEY_A) {
		switch(this->SelectedOption) {
			case 0: // Import Game.
				if (StackMill3DS::App->Core->ImportGame("sdmc:/3ds/StackMill/GameData.dat")) {
					if (StackMill3DS::App->Core->InRemove()) {
						GameTab::Preview = StackMill3DS::App->Core->RemoveableStones((StackMill3DS::App->Core->CurrentPlayer() == 1) ? StackMill::GameStone::Black : StackMill::GameStone::White);
					}

					this->In = false, this->SelectedOption = 2;
					SettingsTab::Swipe = true;
				}
				break;

			case 1: // Export Game.
				if (StackMill3DS::App->Core->ExportGame("sdmc:/3ds/StackMill/GameData.dat")) {
					this->In = false, this->SelectedOption = 2;
					SettingsTab::Swipe = true;
				}
				break;
		}
	}

	if (StackMill3DS::App->Down & KEY_TOUCH) {
		if (this->ImportExportPos[0].Touched(StackMill3DS::App->T)) { // Import Game.
			if (StackMill3DS::App->Core->ImportGame("sdmc:/3ds/StackMill/GameData.dat")) {
				if (StackMill3DS::App->Core->InRemove()) {
					GameTab::Preview = StackMill3DS::App->Core->RemoveableStones((StackMill3DS::App->Core->CurrentPlayer() == 1) ? StackMill::GameStone::Black : StackMill::GameStone::White);
				}

				this->In = false, this->SelectedOption = 2;
				SettingsTab::Swipe = true;
			}

		} else if (this->ImportExportPos[1].Touched(StackMill3DS::App->T)) { // Export Game.
			if (StackMill3DS::App->Core->ExportGame("sdmc:/3ds/StackMill/GameData.dat")) {
				this->In = false, this->SelectedOption = 2;
				SettingsTab::Swipe = true;
			}
		}
	}
};


void SettingsTab::Handler() {
	if (Tab::TabSwitch) return;

	if (SettingsTab::Swipe) this->DoSwipe();
	else {
		switch(this->Menu) {
			case SettingsTab::SubMenu::Main:
				this->MainHandle();
				break;

			case SettingsTab::SubMenu::GameSettings:
				this->GameSettingsHandle();
				break;

			case SettingsTab::SubMenu::Language:
				this->LanguageHandle();
				break;

			case SettingsTab::SubMenu::ImportExport:
				this->ImportExportHandle();
				break;
		}
	}
};


void SettingsTab::DoSwipe() {
	if (this->Cubic < 240.0f) {
		this->Cubic = std::lerp(this->Cubic, 241.0f, 0.1f);

		if (this->In) this->MenuPos[0] = 0 - this->Cubic, this->MenuPos[1] = 240 - this->Cubic;
		else this->MenuPos[0] = -240 + this->Cubic, this->MenuPos[1] = 0 + this->Cubic;

		if (this->Cubic >= 240.0f) {
			if (this->In) this->MenuPos[0] = -240, this->MenuPos[1] = 0;
			else {
				this->MenuPos[0] = 0, this->MenuPos[1] = 240;
				this->Menu = SettingsTab::SubMenu::Main;
			}

			this->Cubic = 0.0f, SettingsTab::Swipe = false;
		}
	}
};