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

#ifndef _STACKMILL_TAB_HPP
#define _STACKMILL_TAB_HPP

#include "structs.hpp"

class Tab {
public:
	void Draw();
	void Handler();

	static float Cubic;
	static int SettingsOffset, GameOffset, CreditsOffset;
	static bool TabSwitch;
private:
	bool SwipeDir = false;
	int8_t TabsToGo = 0, NewTab = 0;
	int SOffs = 320, GOffs = 0, COffs = 640;

	static constexpr Structs::ButtonPos Tabs[3] = {
		{ 1, 0, 106, 20 },
		{ 107, 0, 106, 20 },
		{ 213, 0, 106, 20 }
	};

	void SwitchTabs(const int8_t TabIdx);
	void HandleSwitch();
};

#endif