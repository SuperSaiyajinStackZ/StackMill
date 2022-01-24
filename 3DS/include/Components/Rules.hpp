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

#ifndef _STACKMILL_RULES_HPP
#define _STACKMILL_RULES_HPP

#include "structs.hpp"

class Rules {
public:
	void DrawTop();
	void DrawBottom();
	void Handler();
private:
	enum class HelperPage : int8_t { Main = 0, HowToPlay = 1, Phase1 = 2, Phase2 = 3, Phase3 = 4, WinConditions = 5, Instructions = 6 };
	HelperPage Page = HelperPage::Main;

	bool CanGoNext() const;
	bool CanGoPrev() const;
	void HelperHandler();
	void PageSwitch();
	void PageHandler();
	void DrawPages(const Rules::HelperPage PG, const int AddOffs = 0);
	bool PageButtonHandle(const int PG);

	float Cubic = 0.0f;
	int PageOffs[7] = { 0, 400, 800, 1200, 1600, 2000, 2400 }, BackupOffs[7] = { 0, 400, 800, 1200, 1600, 2000, 2400 }, ToSwipe = 0;
	bool FirstAccess = true, DoSwipe = false, Done = false, FullDone = false, Direction = false;

	/* Pages Buttons. */
	static constexpr Structs::ButtonPos Pages[2] = {
		{ 0, 15, 25, 215 },
		{ 295, 15, 25, 215 }
	};

	/* Back to game button. */
	static constexpr Structs::ButtonPos GameBtn = { 48, 180, 28, 33 };

	/* Button for the Pages. */
	static constexpr Structs::ButtonPos ButtonPages[7] = {
		{ 100, 15, 120, 30 },
		{ 100, 45, 120, 30 },
		{ 100, 75, 120, 30 },
		{ 100, 105, 120, 30 },
		{ 100, 135, 120, 30 },
		{ 100, 165, 120, 30 },
		{ 100, 195, 120, 30 }
	};
};

#endif