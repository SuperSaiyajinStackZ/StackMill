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
#include "Rules.hpp"


void Rules::DrawPages(const Rules::HelperPage PG, const int AddOffs) {
	if (AddOffs >= -400 && AddOffs <= 400) {
		switch(PG) {
			case Rules::HelperPage::Main:
				Gui::DrawStringCentered(0 + AddOffs, 1, 0.6f, TEXT_COLOR, StackMill3DS::App->LH->Translation(LangHandler::Strings::Rules_1));
				Gui::DrawStringCentered(0 + AddOffs, 30, 0.48f, TEXT_BG_COLOR, StackMill3DS::App->LH->Translation(LangHandler::Strings::Rules_1T), 395, 0, nullptr, C2D_WordWrap);
				break;

			case Rules::HelperPage::HowToPlay:
				Gui::DrawStringCentered(0 + AddOffs, 1, 0.6f, TEXT_COLOR, StackMill3DS::App->LH->Translation(LangHandler::Strings::Rules_2));
				Gui::DrawStringCentered(0 + AddOffs, 30, 0.48f, TEXT_BG_COLOR, StackMill3DS::App->LH->Translation(LangHandler::Strings::Rules_2T), 395, 0, nullptr, C2D_WordWrap);
				break;

			case Rules::HelperPage::Phase1:
				Gui::DrawStringCentered(0 + AddOffs, 1, 0.6f, TEXT_COLOR, StackMill3DS::App->LH->Translation(LangHandler::Strings::Rules_3));
				Gui::DrawStringCentered(0 + AddOffs, 30, 0.48f, TEXT_BG_COLOR, StackMill3DS::App->LH->Translation(LangHandler::Strings::Rules_3T), 395, 0, nullptr, C2D_WordWrap);
				break;

			case Rules::HelperPage::Phase2:
				Gui::DrawStringCentered(0 + AddOffs, 1, 0.6f, TEXT_COLOR, StackMill3DS::App->LH->Translation(LangHandler::Strings::Rules_4));
				Gui::DrawStringCentered(0 + AddOffs, 30, 0.48f, TEXT_BG_COLOR, StackMill3DS::App->LH->Translation(LangHandler::Strings::Rules_4T), 395, 0, nullptr, C2D_WordWrap);
				break;

			case Rules::HelperPage::Phase3:
				Gui::DrawStringCentered(0 + AddOffs, 1, 0.6f, TEXT_COLOR, StackMill3DS::App->LH->Translation(LangHandler::Strings::Rules_5));
				Gui::DrawStringCentered(0 + AddOffs, 30, 0.48f, TEXT_BG_COLOR, StackMill3DS::App->LH->Translation(LangHandler::Strings::Rules_5T), 395, 0, nullptr, C2D_WordWrap);
				break;

			case Rules::HelperPage::WinConditions:
				Gui::DrawStringCentered(0 + AddOffs, 1, 0.6f, TEXT_COLOR, StackMill3DS::App->LH->Translation(LangHandler::Strings::Rules_6));
				Gui::DrawStringCentered(0 + AddOffs, 30, 0.48f, TEXT_BG_COLOR, StackMill3DS::App->LH->Translation(LangHandler::Strings::Rules_6T), 395, 0, nullptr, C2D_WordWrap);
				break;

			case Rules::HelperPage::Instructions:
				Gui::DrawStringCentered(0 + AddOffs, 1, 0.6f, TEXT_COLOR, StackMill3DS::App->LH->Translation(LangHandler::Strings::Rules_7));
				Gui::DrawStringCentered(0 + AddOffs, 30, 0.48f, TEXT_BG_COLOR, StackMill3DS::App->LH->Translation(LangHandler::Strings::Rules_7T), 395, 0, nullptr, C2D_WordWrap);
				break;
		};
	};
};


/* Page Button Handler. */
bool Rules::PageButtonHandle(const int PG) {
	const int Cur = (int)this->Page;

	if (Cur == PG) return false;

	if (Cur < PG) {
		this->ToSwipe = PG - Cur;
		this->Direction = true;
		this->DoSwipe = true;

	} else {
		this->ToSwipe = Cur - PG;
		this->Direction = false;
		this->DoSwipe = true;
	};

	return true;
};


void Rules::DrawTop() {
	StackMill3DS::App->GData->DrawTop();

	/* Draw all pages. */
	this->DrawPages(Rules::HelperPage::Main, this->PageOffs[0]);
	this->DrawPages(Rules::HelperPage::HowToPlay, this->PageOffs[1]);
	this->DrawPages(Rules::HelperPage::Phase1, this->PageOffs[2]);
	this->DrawPages(Rules::HelperPage::Phase2, this->PageOffs[3]);
	this->DrawPages(Rules::HelperPage::Phase3, this->PageOffs[4]);
	this->DrawPages(Rules::HelperPage::WinConditions, this->PageOffs[5]);
	this->DrawPages(Rules::HelperPage::Instructions, this->PageOffs[6]);

	if (StackMill3DS::App->FadeAlpha > 0) Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(0, 0, 0, StackMill3DS::App->FadeAlpha));
};


void Rules::DrawBottom() {
	StackMill3DS::App->GData->DrawBottom();

	/* Display Pages left / right buttons. */
	StackMill3DS::App->GData->DrawCornerEdge(true, this->Pages[0].x, this->Pages[0].y, this->Pages[0].h, this->CanGoPrev());
	StackMill3DS::App->GData->DrawCornerEdge(false, this->Pages[1].x, this->Pages[1].y, this->Pages[1].h, this->CanGoNext());

	/* Display page buttons on the middle. */
	for (int8_t Idx = 0; Idx < 7; Idx++) {
		Gui::drawGrid(this->ButtonPages[Idx].x, this->ButtonPages[Idx].y, this->ButtonPages[Idx].w, this->ButtonPages[Idx].h, BAR_COLOR_OUTLINE);
		/* If Idx is the current page -> Fill the button with the bar color. */
		if ((Idx == (int)this->Page)) Gui::Draw_Rect(this->ButtonPages[Idx].x + 1, this->ButtonPages[Idx].y + 1, this->ButtonPages[Idx].w - 2, this->ButtonPages[Idx].h - 2, BAR_COLOR);
	};

	Gui::DrawStringCentered(0, this->ButtonPages[0].y + 8, 0.5f, TEXT_BG_COLOR, StackMill3DS::App->LH->Translation(LangHandler::Strings::Rules1), 115);
	Gui::DrawStringCentered(0, this->ButtonPages[1].y + 8, 0.5f, TEXT_BG_COLOR, StackMill3DS::App->LH->Translation(LangHandler::Strings::Rules2), 115);
	Gui::DrawStringCentered(0, this->ButtonPages[2].y + 8, 0.5f, TEXT_BG_COLOR, StackMill3DS::App->LH->Translation(LangHandler::Strings::Rules3), 115);
	Gui::DrawStringCentered(0, this->ButtonPages[3].y + 8, 0.5f, TEXT_BG_COLOR, StackMill3DS::App->LH->Translation(LangHandler::Strings::Rules4), 115);
	Gui::DrawStringCentered(0, this->ButtonPages[4].y + 8, 0.5f, TEXT_BG_COLOR, StackMill3DS::App->LH->Translation(LangHandler::Strings::Rules5), 115);
	Gui::DrawStringCentered(0, this->ButtonPages[5].y + 8, 0.5f, TEXT_BG_COLOR, StackMill3DS::App->LH->Translation(LangHandler::Strings::Rules6), 115);
	Gui::DrawStringCentered(0, this->ButtonPages[6].y + 8, 0.5f, TEXT_BG_COLOR, StackMill3DS::App->LH->Translation(LangHandler::Strings::Rules7), 115);

	if (StackMill3DS::App->FadeAlpha > 0) Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(0, 0, 0, StackMill3DS::App->FadeAlpha));
};


/* Handle the Input such as page switch. */
void Rules::HelperHandler(uint32_t &Down, touchPosition &T) {
	if (this->DoSwipe) this->PageSwitch();
	else {
		if (Down & KEY_TOUCH) {
			if (Common::Touching(T, this->Pages[0])) {
				if (this->CanGoPrev()) {
					this->Direction = false;
					this->ToSwipe = 1;
					this->DoSwipe = true;
				};

			} else if (Common::Touching(T, this->Pages[1])) {
				if (this->CanGoNext()) {
					this->Direction = true;
					this->ToSwipe = 1;
					this->DoSwipe = true;
				};

			} else {
				for (int8_t Idx = 0; Idx < 7; Idx++) {
					if (Common::Touching(T, this->ButtonPages[Idx])) {
						if (this->PageButtonHandle(Idx)) break;
					};
				};
			};
		};

		if (Down & KEY_L || Down & KEY_UP) {
			if (this->CanGoPrev()) {
				this->Direction = false;
				this->ToSwipe = 1;
				this->DoSwipe = true;
			};
		};

		if (Down & KEY_R || Down & KEY_DOWN) {
			if (this->CanGoNext()) {
				this->Direction = true;
				this->ToSwipe = 1;
				this->DoSwipe = true;
			};
		};

		if (Down & KEY_B) this->Done = true;
	};
};


bool Rules::CanGoNext() const { return this->Page != Rules::HelperPage::Instructions; };
bool Rules::CanGoPrev() const { return this->Page != Rules::HelperPage::Main; };


/* Switches the pages. */
void Rules::PageHandler() {
	int Idx = (int)this->Page;
	if (this->Direction) Idx += this->ToSwipe; // Forward.
	else Idx -= this->ToSwipe; // Backward.

	this->Page = (Rules::HelperPage)Idx;
};


/* Handle the page switch cubic bezier animation. */
void Rules::PageSwitch() {
	if (this->DoSwipe) {
		if (this->Cubic < (this->ToSwipe * 400.0f)) {
			this->Cubic = std::lerp(this->Cubic, (this->ToSwipe * 400.0f) + 1.0f, 0.1f);

			if (this->Direction) { // Back.
				for (int8_t Idx = 0; Idx < 7; Idx++) this->PageOffs[Idx] = this->BackupOffs[Idx] - this->Cubic;

			} else { // Forward.
				for (int8_t Idx = 0; Idx < 7; Idx++) this->PageOffs[Idx] = this->BackupOffs[Idx] + this->Cubic;
			};

			if (this->Cubic >= (this->ToSwipe * 400.0f)) {
				this->Cubic = 0.0f;

				for (int8_t Idx = 0; Idx < 7; Idx++) {
					this->PageOffs[Idx] = (this->Direction ? this->BackupOffs[Idx] - (this->ToSwipe * 400) : this->BackupOffs[Idx] + (this->ToSwipe * 400));
					this->BackupOffs[Idx] = this->PageOffs[Idx];
				};

				this->DoSwipe = false;
				this->PageHandler();
			};
		};
	};
};


void Rules::Handler() {
	/* Fade main screen out. */
	while(aptMainLoop() && !this->Done) {
		StackMill3DS::App->Draw();

		if (StackMill3DS::App->FadeAlpha < 255) {
			StackMill3DS::App->FadeAlpha += 5;

			if (StackMill3DS::App->FadeAlpha == 255) this->Done = true;
		};
	};

	this->Done = false;

	/* Fade Rules screen in and do the main handle. */
	while(aptMainLoop() && !this->FullDone) {
		C2D_TargetClear(Top, C2D_Color32(0, 0, 0, 0));
		C2D_TargetClear(Bottom, C2D_Color32(0, 0, 0, 0));
		Gui::clearTextBufs();
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		this->DrawTop();
		this->DrawBottom();
		C3D_FrameEnd(0);


		if (this->Done) { // Done -> fade out.
			if (StackMill3DS::App->FadeAlpha < 255) {
				StackMill3DS::App->FadeAlpha += 5;

				if (StackMill3DS::App->FadeAlpha == 255) this->FullDone = true;
			};

			continue;
		};

		if (this->FirstAccess) { // FirstAccess -> Fade in.
			if (StackMill3DS::App->FadeAlpha > 0) {
				StackMill3DS::App->FadeAlpha -= 5;

				if (StackMill3DS::App->FadeAlpha == 0) this->FirstAccess = false;
			};

			continue;
		};

		/* Handle Input. */
		hidScanInput();
		uint32_t Down = hidKeysDown();
		touchPosition T;
		hidTouchRead(&T);
		this->HelperHandler(Down, T);
	};

	this->Done = false;

	/* Now Fade the main screen in again. */
	while(aptMainLoop() && !this->Done) {
		StackMill3DS::App->Draw();

		if (StackMill3DS::App->FadeAlpha > 0) {
			StackMill3DS::App->FadeAlpha -= 5;

			if (StackMill3DS::App->FadeAlpha == 0) this->Done = true;
		};
	};
};