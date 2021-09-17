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
#include "Tab.hpp"


float Tab::Cubic = 0.0f; // Cubic Bezier animation for tab switches.
int Tab::GameOffset = 0, Tab::SettingsOffset = 320, Tab::CreditsOffset = 640; // The tab draw-offset.
bool Tab::TabSwitch = false; // If true, don't accept any input from the other components until the switch is over.


void Tab::Draw() {
	/* Draw Tabs. */
	Gui::Draw_Rect(1, 0, 106, 17, (StackMill3DS::App->ActiveTab == StackMill3DS::Tabs::Game ? BAR_COLOR_OUTLINE : BAR_COLOR));
	Gui::Draw_Rect(107, 0, 106, 17, (StackMill3DS::App->ActiveTab == StackMill3DS::Tabs::Settings ? BAR_COLOR_OUTLINE : BAR_COLOR));
	Gui::Draw_Rect(213, 0, 106, 17, (StackMill3DS::App->ActiveTab == StackMill3DS::Tabs::Credits ? BAR_COLOR_OUTLINE : BAR_COLOR));

	/* Outline related things. */
	Gui::Draw_Rect(0, 17, 320, 1, BAR_COLOR_OUTLINE); // ---
	Gui::Draw_Rect(0, 0, 1, 17, BAR_COLOR_OUTLINE); // |
	Gui::Draw_Rect(107, 0, 1, 17, BAR_COLOR_OUTLINE); // |
	Gui::Draw_Rect(213, 0, 1, 17, BAR_COLOR_OUTLINE); // |
	Gui::Draw_Rect(319, 0, 1, 17, BAR_COLOR_OUTLINE); // |

	/* Tab Names. */
	Gui::DrawStringCentered(-106, 2, 0.45f, TEXT_COLOR, StackMill3DS::App->LH->Translation(LangHandler::Strings::Game), 100);
	Gui::DrawStringCentered(0, 2, 0.45f, TEXT_COLOR, StackMill3DS::App->LH->Translation(LangHandler::Strings::Settings), 100);
	Gui::DrawStringCentered(106, 2, 0.45f, TEXT_COLOR, StackMill3DS::App->LH->Translation(LangHandler::Strings::Credits), 100);
};


void Tab::Handler() {
	if (SettingsTab::Swipe) return; // No.

	if (Tab::TabSwitch) this->HandleSwitch(); // If we switch Tabs, handle the switch.
	else { // Otherwise handle the Tabs.

		if (StackMill3DS::App->Down & KEY_TOUCH) {
			for (int8_t Idx = 0; Idx < 3; Idx++) {
				if (Common::Touching(StackMill3DS::App->T, this->Tabs[Idx])) {
					this->SwitchTabs(Idx);
					break;
				}
			}
		}

		/* L -> Previous Tab. */
		if (StackMill3DS::App->Down & KEY_L) {
			switch(StackMill3DS::App->ActiveTab) {
				case StackMill3DS::Tabs::Game:
					break;

				case StackMill3DS::Tabs::Settings:
					this->SwitchTabs(0);
					break;

				case StackMill3DS::Tabs::Credits:
					this->SwitchTabs(1);
					break;
			}
		}

		/* R -> Next Tab. */
		if (StackMill3DS::App->Down & KEY_R) {
			switch(StackMill3DS::App->ActiveTab) {
				case StackMill3DS::Tabs::Game:
					this->SwitchTabs(1);
					break;

				case StackMill3DS::Tabs::Settings:
					this->SwitchTabs(2);
					break;

				case StackMill3DS::Tabs::Credits:
					break;
			}
		}
	}
};


/* Handle the Tab cubic bezier animation. */
void Tab::HandleSwitch() {
	if (Tab::TabSwitch) {
		if (Tab::Cubic < (this->TabsToGo == 1 ? 320.0f : 640.0f)) {
			Tab::Cubic = std::lerp(Tab::Cubic, (this->TabsToGo == 1 ? 321.0f : 641.0f), 0.1f);

			if (this->SwipeDir) { // Back.
				Tab::CreditsOffset = this->COffs - Tab::Cubic;
				Tab::SettingsOffset = this->SOffs - Tab::Cubic;
				Tab::GameOffset = this->GOffs - Tab::Cubic;

			} else { // Forward.
				Tab::CreditsOffset = this->COffs + Tab::Cubic;
				Tab::SettingsOffset = this->SOffs + Tab::Cubic;
				Tab::GameOffset = this->GOffs + Tab::Cubic;
			}


			if (Tab::Cubic >= (this->TabsToGo == 1 ? 320.0f : 640.0f)) {
				Tab::Cubic = 0.0f;

				/* Set to proper positions. */
				switch(this->NewTab) {
					case 0:
						Tab::GameOffset = 0, Tab::SettingsOffset = 320, Tab::CreditsOffset = 640;
						break;

					case 1:
						Tab::GameOffset = -320, Tab::SettingsOffset = 0, Tab::CreditsOffset = 320;
						break;

					case 2:
						Tab::GameOffset = -640, Tab::SettingsOffset = -320, Tab::CreditsOffset = 0;
						break;
				}

				Tab::TabSwitch = false;
				StackMill3DS::App->ActiveTab = (StackMill3DS::Tabs)this->NewTab;
			}
		}
	}
};


/* Switching the Tabs logic. */
void Tab::SwitchTabs(const int8_t TabIdx) {
	bool Good = false;

	switch(StackMill3DS::App->ActiveTab) {
		case StackMill3DS::Tabs::Game:
			if (TabIdx > 0) { // Ensure it is not 0, which is the first tab that is currently active.
				this->TabsToGo = TabIdx;
				this->SwipeDir = true;
				Good = true;
			}
			break;

		case StackMill3DS::Tabs::Settings:
			if (TabIdx != 1) { // Ensure it is not 1, which is the second tab that is currently active.
				this->TabsToGo = 1;
				this->SwipeDir = (TabIdx == 0 ? false : true);
				Good = true;
			}
			break;

		case StackMill3DS::Tabs::Credits:
			if (TabIdx < 2) { // Ensure it is not 2, which is the last tab that is currently active.
				this->TabsToGo = (TabIdx == 0 ? 2 : 1);
				this->SwipeDir = false;
				Good = true;
			}
			break;
	}

	/* In case the Tab action is good, now handle the animation. */
	if (Good) {
		this->NewTab = TabIdx;
		this->GOffs = Tab::GameOffset, this->SOffs = Tab::SettingsOffset, this->COffs = Tab::CreditsOffset;
		Tab::TabSwitch = true;
	}
};