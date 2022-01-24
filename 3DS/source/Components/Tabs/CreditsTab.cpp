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

#include "Common.hpp"
#include "CreditsTab.hpp"

bool CreditsTab::Swipe = false;

void CreditsTab::Draw() {
	if (CreditsTab::Swipe) {
		this->DrawSubTab(CreditsTab::SubTab::Main, this->TabPos[0]);
		this->DrawSubTab(CreditsTab::SubTab::Translators, this->TabPos[1]);

	} else {
		switch(this->Tab) {
			case CreditsTab::SubTab::Main:
				this->DrawSubTab(CreditsTab::SubTab::Main, this->TabPos[0]);
				break;

			case CreditsTab::SubTab::Translators:
				this->DrawSubTab(CreditsTab::SubTab::Translators, this->TabPos[1]);
				break;
		}
	}
};


void CreditsTab::DrawSubTab(const CreditsTab::SubTab STab, const int AddOffs) {
	if (AddOffs > -240 && AddOffs < 240) {
		switch(STab) {
			/* Main Credits Tab. */
			case CreditsTab::SubTab::Main:
				Gui::DrawStringCentered(0 + Tab::CreditsOffset, 35 + AddOffs, 0.5f, TEXT_BG_COLOR, StackMill3DS::App->LH->Translation(LangHandler::Strings::DevBy), 310);
				Gui::DrawStringCentered(0 + Tab::CreditsOffset, 55 + AddOffs, 0.5f, TEXT_BG_COLOR, StackMill3DS::App->LH->Translation(LangHandler::Strings::SmilCore), 310);
				Gui::DrawStringCentered(0 + Tab::CreditsOffset, 70 + AddOffs, 0.5f, TEXT_BG_COLOR, StackMill3DS::App->LH->Translation(LangHandler::Strings::Graphics), 310);
				Gui::DrawStringCentered(0 + Tab::CreditsOffset, 85 + AddOffs, 0.5f, TEXT_BG_COLOR, StackMill3DS::App->LH->Translation(LangHandler::Strings::UnivCore), 310);

				StackMill3DS::App->GData->DrawSprite(sprites_StackZ_idx, 110 + Tab::CreditsOffset, 105 + AddOffs);
				StackMill3DS::App->GData->DrawSprite(sprites_translators_idx, this->TranslatorBtn.x + Tab::CreditsOffset, this->TranslatorBtn.y + AddOffs);
				break;

			/* Translators Credits Tab. */
			case CreditsTab::SubTab::Translators:
				Gui::DrawStringCentered(0 + Tab::CreditsOffset, 35 + AddOffs, 0.6f, TEXT_BG_COLOR, StackMill3DS::App->LH->Translation(LangHandler::Strings::Translators), 310);

				Gui::DrawStringCentered(0 + Tab::CreditsOffset, 65 + AddOffs, 0.5f, TEXT_BG_COLOR, "Deutsch - SuperSaiyajinStackZ", 310);
				Gui::DrawStringCentered(0 + Tab::CreditsOffset, 85 + AddOffs, 0.5f, TEXT_BG_COLOR, "English - Pk11, SuperSaiyajinStackZ", 310);
				Gui::DrawStringCentered(0 + Tab::CreditsOffset, 105 + AddOffs, 0.5f, TEXT_BG_COLOR, "Italiano - Samplasion", 310);
				Gui::DrawStringCentered(0 + Tab::CreditsOffset, 125 + AddOffs, 0.5f, TEXT_BG_COLOR, "日本語 - Pk11", 310);
				break;
		}
	}
};


void CreditsTab::Handler() {
	if (Tab::TabSwitch) return;

	if (CreditsTab::Swipe) this->DoSwipe();
	else {
		if (this->Tab == CreditsTab::SubTab::Main) {
			if ((StackMill3DS::App->Down & KEY_TOUCH && this->TranslatorBtn.Touched(StackMill3DS::App->T)) || (StackMill3DS::App->Down & KEY_A)) {
				this->IntoTranslators = true;
				CreditsTab::Swipe = true;
			}

		} else {
			if ((StackMill3DS::App->Down & KEY_TOUCH && this->CTabBtn.Touched(StackMill3DS::App->T)) || (StackMill3DS::App->Down & KEY_B)) {
				this->IntoTranslators = false;
				CreditsTab::Swipe = true;
			}
		}
	}
};


void CreditsTab::DoSwipe() {
	if (this->Cubic < 240.0f) {
		this->Cubic = std::lerp(this->Cubic, 241.0f, 0.1f);

		if (this->IntoTranslators) this->TabPos[0] = 0 - this->Cubic, this->TabPos[1] = 240 - this->Cubic;
		else this->TabPos[0] = -240 + this->Cubic, this->TabPos[1] = 0 + this->Cubic;

		if (this->Cubic >= 240.0f) {
			if (this->IntoTranslators) {
				this->TabPos[0] = -240, this->TabPos[1] = 0;
				this->Tab = CreditsTab::SubTab::Translators;

			} else {
				this->TabPos[0] = 0, this->TabPos[1] = 240;
				this->Tab = CreditsTab::SubTab::Main;
			}

			this->Cubic = 0.0f, CreditsTab::Swipe = false;
		}
	}
};