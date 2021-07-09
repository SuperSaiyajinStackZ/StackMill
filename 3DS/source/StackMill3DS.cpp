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

#include "screenCommon.hpp"
#include "Splash.hpp"
#include "StackMill3DS.hpp"
#include <dirent.h>
#include <unistd.h>


std::unique_ptr<StackMill3DS> StackMill3DS::App = nullptr;


StackMill3DS::StackMill3DS() {
	gfxInitDefault();
	romfsInit();
	cfguInit();
	Gui::init();
	hidSetRepeatParameters(25, 2);

	mkdir("sdmc:/3ds", 0x777);
	mkdir("sdmc:/3ds/StackMill", 0x777); // For the GameData and Config.

	this->GData = std::make_unique<GFXData>(); // Graphic data.
	this->LH = std::make_unique<LangHandler>();
	this->Core = std::make_unique<StackMill>(true); // Current Game initializer.

	this->_Tab = std::make_unique<Tab>(); // Tab Handler.
	this->Game = std::make_unique<GameTab>(); // Game-Tab.
	this->Settings = std::make_unique<SettingsTab>(); // Settings-Tab.
	this->Credits = std::make_unique<CreditsTab>(); // Credits-Tab.
	this->LoadConfig();
};


void StackMill3DS::DrawTab() { this->_Tab->Draw(); };


void StackMill3DS::DrawTop() {
	/* Draw the top screen content. */
	this->GData->DrawTop();
	Gui::DrawStringCentered(0, 1, 0.6f, TEXT_COLOR, "StackMill");
	Gui::DrawString(340, 1, 0.6f, TEXT_COLOR, V_STRING); // Version.

	/* Player 1. */
	this->GData->DrawPlayer(true, 40, 40);
	Gui::Draw_Rect(37, 169, 106, 20, BAR_COLOR);
	Gui::DrawString(68, 172, 0.45f, TEXT_COLOR, this->LH->Translation(LangHandler::Strings::Player) + " 1", 100);
	Gui::DrawString(33, 200, 0.45f, C2D_Color32(0, 0, 0, 200), this->LH->Translation(LangHandler::Strings::StonesAvailable) + std::to_string(this->Core->Available(StackMill::GameStone::White)), 120);

	/* Player 2. */
	this->GData->DrawPlayer(false, 260, 40);
	Gui::Draw_Rect(257, 169, 106, 20, BAR_COLOR);
	Gui::DrawString(287, 172, 0.45f, TEXT_COLOR, this->LH->Translation(LangHandler::Strings::Player) + " 2", 100);
	Gui::DrawString(253, 200, 0.45f, TEXT_BG_COLOR, this->LH->Translation(LangHandler::Strings::StonesAvailable) + std::to_string(this->Core->Available(StackMill::GameStone::Black)), 120);


	if (this->Core->InRemove()) { // Removing a stone.
		Gui::DrawStringCentered(0, 220, 0.5f, TEXT_BG_COLOR, this->LH->Translation(LangHandler::Strings::Player) + " " + std::to_string(this->Core->CurrentPlayer()) + ": " + this->LH->Translation(LangHandler::Strings::RemoveStone));

	} else { // The phase display.
		switch(this->Core->Phase((this->Core->CurrentPlayer() == 1) ? StackMill::GameStone::White : StackMill::GameStone::Black)) {
			case StackMill::Phases::Set:
				Gui::DrawStringCentered(0, 220, 0.5f, TEXT_BG_COLOR, this->LH->Translation(LangHandler::Strings::Player) + " " + std::to_string(this->Core->CurrentPlayer()) + ": " + this->LH->Translation(LangHandler::Strings::SetStone));
				break;

			case StackMill::Phases::Move:
				Gui::DrawStringCentered(0, 220, 0.5f, TEXT_BG_COLOR, this->LH->Translation(LangHandler::Strings::Player) + " " + std::to_string(this->Core->CurrentPlayer()) + ": " + this->LH->Translation(LangHandler::Strings::MoveStone));
				break;

			case StackMill::Phases::Jump:
				Gui::DrawStringCentered(0, 220, 0.5f, TEXT_BG_COLOR, this->LH->Translation(LangHandler::Strings::Player) + ": " + this->LH->Translation(LangHandler::Strings::JumpStone));
				break;
		};
	};
};


void StackMill3DS::Draw() {
	C2D_TargetClear(Top, C2D_Color32(0, 0, 0, 0));
	C2D_TargetClear(Bottom, C2D_Color32(0, 0, 0, 0));
	Gui::clearTextBufs();
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

	this->DrawTop();
	if (this->FadeAlpha > 0) Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(0, 0, 0, this->FadeAlpha));

	this->GData->DrawBottom();
	if (Tab::TabSwitch) { // On Tab Switch, draw all with animation.
		this->Game->Draw();
		this->Settings->Draw();
		this->Credits->Draw();

	} else { // Else draw only active tab.
		switch(this->ActiveTab) {
			case StackMill3DS::Tabs::Settings:
				this->Settings->Draw();
				break;

			case StackMill3DS::Tabs::Game:
				this->Game->Draw();
				break;

			case StackMill3DS::Tabs::Credits:
				this->Credits->Draw();
				break;
		};
	};

	this->DrawTab();
	if (this->FadeAlpha > 0) Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(0, 0, 0, this->FadeAlpha));
	C3D_FrameEnd(0);
};


int StackMill3DS::Handler() {
	while(aptMainLoop() && this->Running) {
		this->Draw();

		hidScanInput();
		this->Down = hidKeysDown();
		this->Repeat = hidKeysDownRepeat();
		hidTouchRead(&this->T);

		this->_Tab->Handler();

		switch(this->ActiveTab) {
			case StackMill3DS::Tabs::Settings:
				this->Settings->Handler();
				break;

			case StackMill3DS::Tabs::Game:
				this->Game->Handler();
				break;

			case StackMill3DS::Tabs::Credits:
				break;
		};
	};

	Gui::exit();
	this->SaveConfig();
	cfguExit();
	romfsExit();
	gfxExit();
	return 0;
};


/*
	Config Information.

	53 4D 49 4C // SMIL (Stack MILl identifier).
	01 // Config version.
	01 00 01 04 01 // Language, Player 1 Stone color, Player 2 Stone color, Play Preview Color, Computer.
*/
void StackMill3DS::LoadConfig() {
	bool Good = false;
	if (access("sdmc:/3ds/StackMill/Config.bin", F_OK) == 0) Good = true; // File exist.

	if (Good) {
		FILE *ConfigData = fopen("sdmc:/3ds/StackMill/Config.bin", "rb");

		if (ConfigData) {
			fseek(ConfigData, 0, SEEK_END);
			const uint32_t CFGSize = ftell(ConfigData);
			fseek(ConfigData, 0, SEEK_SET);

			if (CFGSize == this->ConfigSize) { // Ensure size is the proper one.
				std::unique_ptr<uint8_t[]> Data = std::make_unique<uint8_t[]>(this->ConfigSize);
				fread(Data.get(), 1, this->ConfigSize, ConfigData); // Read data.

				/* Ensure Identifier matches. */
				if (Data[0x0] == 'S' && Data[0x1] == 'M' && Data[0x2] == 'I' && Data[0x3] == 'L') {
					if (Data[0x4] == this->ConfigVer) { // Ensure config version is the current one.

						/* Language. */
						switch(Data[0x5]) {
							case 0:
								this->LH->LoadLang(LangHandler::Langs::Japanese);
								break;

							case 1:
							default:
								this->LH->LoadLang(LangHandler::Langs::English);
								break;

							case 3:
								this->LH->LoadLang(LangHandler::Langs::German);
								break;
						};

						/* Stone colors. */
						if (Data[0x6] < 10) SettingsTab::StoneColors[0x0] = Data[0x6]; // Player 1.
						if (Data[0x7] < 10) SettingsTab::StoneColors[0x1] = Data[0x7]; // Player 2.
						if (Data[0x8] < 10) SettingsTab::StoneColors[0x2] = Data[0x8]; // Preview.
						if (Data[0x9] < 3) SettingsTab::AI = Data[0x9];

					} else {
						Good = false; // Config version doesn't match.
					};

				} else {
					Good = false; // Identifier doesn't match.
				};

			} else {
				Good = false; // Size doesn't match.
			};

			fclose(ConfigData);
		};
	};

	if (!Good) this->ConfigChanged = true; // Needs to save at the end.
};


void StackMill3DS::SaveConfig() {
	if (this->ConfigChanged) {
		std::unique_ptr<uint8_t[]> Data = std::make_unique<uint8_t[]>(this->ConfigSize); // Allocate data of 0xA.

		Data[0x0] = 'S'; Data[0x1] = 'M'; Data[0x2] = 'I'; Data[0x3] = 'L'; Data[0x4] = this->ConfigVer; // Some Metadata.

		/* Language. */
		switch(this->LH->GetLangEnum()) {
			case LangHandler::Langs::Japanese:
				Data[0x5] = 0;
				break;

			case LangHandler::Langs::English:
				Data[0x5] = 1;
				break;

			case LangHandler::Langs::German:
				Data[0x5] = 3;
				break;
		};

		/* Stone colors. */
		Data[0x6] = SettingsTab::StoneColors[0x0]; // Player 1.
		Data[0x7] = SettingsTab::StoneColors[0x1]; // Player 2.
		Data[0x8] = SettingsTab::StoneColors[0x2]; // Preview.
		Data[0x9] = SettingsTab::AI;

		/* Handle Writing to the ConfigData. */
		FILE *ConfigOut = fopen("sdmc:/3ds/StackMill/Config.bin", "wb");
		if (ConfigOut) {
			fwrite(Data.get(), 1, this->ConfigSize, ConfigOut);
			fclose(ConfigOut);
		};
	};
};


int main() {
	StackMill3DS::App = std::make_unique<StackMill3DS>();
	std::unique_ptr<Splash> _Splash = std::make_unique<Splash>();
	_Splash->Handler(); // Splash Handler.

	return StackMill3DS::App->Handler();
};