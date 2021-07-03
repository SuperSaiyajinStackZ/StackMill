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

std::unique_ptr<StackMill3DS> StackMill3DS::App = nullptr;

StackMill3DS::StackMill3DS() {
	gfxInitDefault();
	romfsInit();
	Gui::init();
	hidSetRepeatParameters(25, 3);

	this->GData = std::make_unique<GFXData>(); // Graphic data.

	this->Game = std::make_unique<GameTab>(); // Game-Tab.
	this->Settings = std::make_unique<SettingsTab>(); // Settings-Tab.
	this->Credits = std::make_unique<CreditsTab>(); // Credits-Tab.
	this->_Tab = std::make_unique<Tab>(); // Tab Handler.

	this->Core = std::make_unique<StackMill>(true); // Current Game initializer.
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
	Gui::DrawString(68, 172, 0.45f, TEXT_COLOR, "Player 1", 100);
	Gui::DrawString(33, 200, 0.45f, C2D_Color32(0, 0, 0, 200), "Stones available: " + std::to_string(this->Core->Available(StackMill::GameStone::White)), 120);

	/* Player 2. */
	this->GData->DrawPlayer(false, 260, 40);
	Gui::Draw_Rect(257, 169, 106, 20, BAR_COLOR);
	Gui::DrawString(287, 172, 0.45f, TEXT_COLOR, "Player 2", 100);
	Gui::DrawString(253, 200, 0.45f, TEXT_BG_COLOR, "Stones available: " + std::to_string(this->Core->Available(StackMill::GameStone::Black)), 120);


	if (this->Game->RemoveMode) { // Removing a stone.
		Gui::DrawStringCentered(0, 220, 0.5f, TEXT_BG_COLOR, "Player " + std::to_string(this->Core->CurrentPlayer()) + ": Remove a Stone from your opponent.");

	} else { // The phase display.
		switch(this->Core->Phase((this->Core->CurrentPlayer() == 1) ? StackMill::GameStone::White : StackMill::GameStone::Black)) {
			case StackMill::Phases::Set:
				Gui::DrawStringCentered(0, 220, 0.5f, TEXT_BG_COLOR, "Player " + std::to_string(this->Core->CurrentPlayer()) + ": Set a Stone to a free intersection.");
				break;

			case StackMill::Phases::Move:
				Gui::DrawStringCentered(0, 220, 0.5f, TEXT_BG_COLOR, "Player " + std::to_string(this->Core->CurrentPlayer()) + ": Move a Stone around.");
				break;

			case StackMill::Phases::Jump:
				Gui::DrawStringCentered(0, 220, 0.5f, TEXT_BG_COLOR, "Player " + std::to_string(this->Core->CurrentPlayer()) + ": Jump a Stone to a free intersection.");
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

	this->DrawTab();
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
	romfsExit();
	gfxExit();
	return 0;
};


int main() {
	StackMill3DS::App = std::make_unique<StackMill3DS>();
	std::unique_ptr<Splash> _Splash = std::make_unique<Splash>();
	_Splash->Handler(); // Splash Handler.

	return StackMill3DS::App->Handler();
};