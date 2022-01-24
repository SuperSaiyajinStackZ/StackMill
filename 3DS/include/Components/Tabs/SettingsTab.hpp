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

#ifndef _STACKMILL_SETTINGS_TAB_HPP
#define _STACKMILL_SETTINGS_TAB_HPP

#include "structs.hpp"

class SettingsTab {
public:
	void Draw();
	void Handler();

	static int8_t StoneColors[3], AI;
	static bool Swipe;
private:
	enum class SubMenu : int8_t { Main = 0, GameSettings = 1, Language = 2, ImportExport = 3 };
	SubMenu Menu = SubMenu::Main;
	int8_t SelectedOption = 0, Language = 0;
	float Cubic = 0.0f;
	int MenuPos[2] = { 0, 240 }; // 0: Main, 1: The others.
	bool In = true;

	void DrawMenu(const SettingsTab::SubMenu M, const int AddOffs);
	void DoSwipe();


	void MainHandle();
	static constexpr Structs::ButtonPos MainPos[4] = {
		{ 90, 50, 140, 35 },  // Game Settings.
		{ 90, 110, 140, 35 }, // Language.
		{ 90, 170, 140, 35 }, // Import | Export.
		{ 107, 0, 106, 20 }   // Main Settings Tab.
	};


	void GameSettingsHandle();
	/* X-Positions of the Stone colors. */
	static constexpr int XPos[10] = { 15, 45, 75, 105, 135, 165, 195, 225, 255, 285 };


	void LanguageHandle();
	static constexpr Structs::ButtonPos LanguagePos[4] = {
		{ 37, 32, 18, 18 },  // English.
		{ 37, 72, 18, 18 },  // Deutsch.
		{ 37, 112, 18, 18 }, // 日本語 (Japanese).
		{ 37, 152, 18, 18 }  // Italiano.
	};


	void ImportExportHandle();
	static constexpr Structs::ButtonPos ImportExportPos[2] = {
		{ 90, 50, 140, 35 }, // Import.
		{ 90, 110, 140, 35 } // Export.
	};
};

#endif