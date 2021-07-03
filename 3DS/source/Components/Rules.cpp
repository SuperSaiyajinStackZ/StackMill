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
	switch(PG) {
		case Rules::HelperPage::Main:
			if (AddOffs >= -400 && AddOffs <= 400) {
				Gui::DrawStringCentered(0 + AddOffs, 1, 0.6f, TEXT_COLOR, "Main ( 1 / 7 )");

				Gui::DrawStringCentered(0 + AddOffs, 30, 0.48f, TEXT_BG_COLOR,
					"StackMill is a clone of the Mill game.\n\n"
					"The game is also known under the following Synonym(s):\n"
					"Nine men's morris, or Nine-man morris\n"
					"Mill, mills, or the mill game\n"
					"Merels or merrills\n"
					"Merelles, marelles, or morelles\n"
					"Ninepenny marl\n"
					"Cowboy checkers\n\n"
					"Check out the other pages to read more about how the game works or also see the wikipedia site here: https://en.wikipedia.org/wiki/Nine_men%27s_morris.",
				395, 0, nullptr, C2D_WordWrap);
			};
			break;

		case Rules::HelperPage::HowToPlay:
			if (AddOffs >= -400 && AddOffs <= 400) {
				Gui::DrawStringCentered(0 + AddOffs, 1, 0.6f, TEXT_COLOR, "How to Play ( 2 / 7 )");

				Gui::DrawStringCentered(0 + AddOffs, 30, 0.48f, TEXT_BG_COLOR,
					"Shortly explained the rules:\n"
					"- Both Players try to get 3 Stones in a row to form a so called 'Mill'.\n\n"
					"- After a Mill is formed, the Player can remove a Stone from the opponent.\n\n"
					"Keep in mind however, that you can not remove a Stone from a formed Mill from your opponent, except all the Stones are inside a Mill.\n\n"
					"The game contains 3 Phases, the next pages will explain those Phases.",
				395, 0, nullptr, C2D_WordWrap);
			};
			break;

		case Rules::HelperPage::Phase1:
			if (AddOffs >= -400 && AddOffs <= 400) {
				Gui::DrawStringCentered(0 + AddOffs, 1, 0.6f, TEXT_COLOR, "Phase 1: Placing Stones ( 3 / 7 )");

				Gui::DrawStringCentered(0 + AddOffs, 30, 0.48f, TEXT_BG_COLOR,
					"This is the first Phase of the game which will be the case until all 9 Stones have been played.\n\n"
					"The first Player starts by placing a Stone on an intersection of the lines. Then the second Player does the same until all 9 Stones have been played.\n\n"
					"The goal in this Phase is to form a good way for the next Phase, so you can easilly move the Stones around.\n\n"
					"If all Stones are played, then the Game Phase will switch to the second Phase: Move.",
				395, 0, nullptr, C2D_WordWrap);
			};
			break;

		case Rules::HelperPage::Phase2:
			if (AddOffs >= -400 && AddOffs <= 400) {
				Gui::DrawStringCentered(0 + AddOffs, 1, 0.6f, TEXT_COLOR, "Phase 2: Moving Stones ( 4 / 7 )");

				Gui::DrawStringCentered(0 + AddOffs, 30, 0.48f, TEXT_BG_COLOR,
					"This is the second Phase of the game which will be the case until a Player only has 3 Stones left.\n\n"
					"The first Player starts by moving a Stone to the left, right, up or down. Then the next Player will do the same as well.\n\n"
					"The same process happens the whole time now, and the goal in this Phase is to move the Stones in a good way, so the opponent possibly can not move anymore or will have 3 or less Stones.\n\n"
					"If a Player only has 3 Stones left, then it will switch to an exclusive Phase for that Player, and the Phase is: Jump.",
				395, 0, nullptr, C2D_WordWrap);
			};
			break;

		case Rules::HelperPage::Phase3:
			if (AddOffs >= -400 && AddOffs <= 400) {
				Gui::DrawStringCentered(0 + AddOffs, 1, 0.6f, TEXT_COLOR, "Phase 3: 'Flying' / Jumping Stones ( 5 / 7 )");

				Gui::DrawStringCentered(0 + AddOffs, 30, 0.48f, TEXT_BG_COLOR,
					"This is the last Phase and is exclusive for Players with 3 Stones left.\n\n"
					"The Player can now jump Stones to any available Position.\n"
					"With this way, the Player is basically on the limits, because when the other Player reached a Mill, the Player lose.\n\n"
					"The goal of this Phase is to stop your opponent from forming Mills and try to reach a tie, by reducing the Stones from the opponent to 3 as well.\n\n"
					"The next page contains possible ways how to win a match",
				395, 0, nullptr, C2D_WordWrap);
			};
			break;

		case Rules::HelperPage::WinConditions:
			if (AddOffs >= -400 && AddOffs <= 400) {
				Gui::DrawStringCentered(0 + AddOffs, 1, 0.6f, TEXT_COLOR, "Win conditions ( 6 / 7 )");

				Gui::DrawStringCentered(0 + AddOffs, 30, 0.48f, TEXT_BG_COLOR,
					"To win a match, one of the following conditions needs to happen:\n\n"
					"- Your opponent can not do a valid turn anymore and hence is basically locked.\n\n"
					"- Your opponent has 3 Stones left and you got a Mill, then you basically take one Stone away and your opponent can not form a Mill anymore.\n\n"
					"Keep in mind however, that a tie is also possible, if both Players have 3 Stones left.",
				395, 0, nullptr, C2D_WordWrap);
			};
			break;

		case Rules::HelperPage::Instructions:
			if (AddOffs >= 0 && AddOffs <= 400) {
				Gui::DrawStringCentered(0 + AddOffs, 1, 0.6f, TEXT_COLOR, "Instructions ( 7 / 7 )");

				Gui::DrawStringCentered(0 + AddOffs, 30, 0.48f, TEXT_BG_COLOR,
					"The Instructions how to play the game are quite easy.\n\n"
					"- Phase 1: Tap a intersection from the lines to play a Stone.\n\n"
					"- Phase 2 & 3: Tap a Stone and tap on one of the highlighted Intersections to move / jump the Stone.\n\n"
					"- Remove: Tap a highlighted Stone to remove it.\n\n"
					"Keep in mind, that you can also use the D-Pad optionally, if you don't want to use touch.",
				395, 0, nullptr, C2D_WordWrap);
			};
			break;
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

		Gui::DrawStringCentered(0, this->ButtonPages[Idx].y + 8, 0.5f, TEXT_BG_COLOR, this->ButtonNames[Idx], 120);
	};

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