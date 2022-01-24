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

#ifndef _STACKMILL_CREDITS_TAB_HPP
#define _STACKMILL_CREDITS_TAB_HPP

#include "structs.hpp"

class CreditsTab {
public:
	void Draw();
	void Handler();
	static bool Swipe;
private:
	enum class SubTab : uint8_t { Main = 0, Translators = 1 };
	SubTab Tab = SubTab::Main;
	float Cubic = 0.0f;
	bool IntoTranslators = false;
	int TabPos[2] = { 0, 240 }; // 0: Main, 1: Translators.

	void DrawSubTab(const CreditsTab::SubTab STab, const int AddOffs);
	void DoSwipe();

	static constexpr Structs::ButtonPos TranslatorBtn = { 13, 202, 28, 33 };
	static constexpr Structs::ButtonPos CTabBtn = { 213, 0, 106, 20 };
};

#endif