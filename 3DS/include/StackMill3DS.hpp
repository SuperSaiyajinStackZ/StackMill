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

#ifndef _STACKMILL_3DS_HPP
#define _STACKMILL_3DS_HPP

#include "ConfigData.hpp"
#include "CreditsTab.hpp"
#include "GameTab.hpp"
#include "GFXData.hpp"
#include "LangHandler.hpp"
#include "SettingsTab.hpp"
#include "StackMill.hpp"
#include "Tab.hpp"
#include <3ds.h>

class StackMill3DS {
public:
	enum class Tabs : int8_t { Game = 0, Settings = 1, Credits = 2 };
	int Handler();
	void Draw();
	void DrawTop();
	void DrawTab();
	void InitApp();
	void ScanKeys();

	static std::unique_ptr<StackMill3DS> App;
	std::unique_ptr<GFXData> GData = nullptr;
	std::unique_ptr<LangHandler> LH = nullptr;
	std::unique_ptr<StackMill> Core = nullptr;
	Tabs ActiveTab = Tabs::Game;

	uint32_t Down = 0, Repeat = 0;
	touchPosition T;
	bool Running = true;
	uint8_t FadeAlpha = 255;

	void ConfigChanged() { this->CData->SetChanged(); };
private:
	std::unique_ptr<GameTab> Game = nullptr;
	std::unique_ptr<SettingsTab> Settings = nullptr;
	std::unique_ptr<Tab> _Tab = nullptr;
	std::unique_ptr<CreditsTab> Credits = nullptr;
	std::unique_ptr<ConfigData> CData = nullptr;
};

#endif