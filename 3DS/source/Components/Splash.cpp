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
#include "Splash.hpp"


void Splash::Handler() {
	while(aptMainLoop() && !this->Done) {
		C2D_TargetClear(Top, C2D_Color32(0, 0, 0, 0));
		C2D_TargetClear(Bottom, C2D_Color32(0, 0, 0, 0));
		Gui::clearTextBufs();
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

		StackMill3DS::App->GData->DrawTop();
		Gui::DrawStringCentered(0, 1, 0.6f, TEXT_COLOR, "StackMill");
		Gui::DrawString(340, 1, 0.6f, TEXT_COLOR, V_STRING); // Version.
		StackMill3DS::App->GData->DrawSprite(sprites_banner_idx, 72, 66);
		if (StackMill3DS::App->FadeAlpha > 0) Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(0, 0, 0, StackMill3DS::App->FadeAlpha));

		StackMill3DS::App->GData->DrawBottom();
		StackMill3DS::App->GData->DrawSprite(sprites_StackZ_idx, 110, 90);
		Gui::DrawStringCentered(0, 30, 0.5f, TEXT_BG_COLOR, "StackMill developed by SuperSaiyajinStackZ.\nCopyright (c) 2021");
		if (StackMill3DS::App->FadeAlpha > 0) Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(0, 0, 0, StackMill3DS::App->FadeAlpha));
		C3D_FrameEnd(0);

		/* State 0: Fade In. */
		if (this->State == 0) {
			if (StackMill3DS::App->FadeAlpha > 0) {
				StackMill3DS::App->FadeAlpha -= 5;

				if (StackMill3DS::App->FadeAlpha == 0) this->State = 1;
			};

		/* State 1: Waiting. */
		} else if (this->State == 1) {
			if (this->Wait > 0) {
				this->Wait--;

				if (this->Wait == 0) this->State = 2;
			};

		/* State 2: Fade Out. */
		} else if (this->State == 2) {
			if (StackMill3DS::App->FadeAlpha < 255) {
				StackMill3DS::App->FadeAlpha += 5;

				if (StackMill3DS::App->FadeAlpha == 255) this->Done = true;
			};
		};
	};

	this->Done = false;

	/* Now Fade the screen in again. */
	while(aptMainLoop() && !this->Done) {
		StackMill3DS::App->Draw();

		if (StackMill3DS::App->FadeAlpha > 0) {
			StackMill3DS::App->FadeAlpha -= 5;

			if (StackMill3DS::App->FadeAlpha == 0) this->Done = true;
		};
	};
};