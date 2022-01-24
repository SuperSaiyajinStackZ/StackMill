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

#include "LangHandler.hpp"
#include <3ds.h>


LangHandler::LangHandler() {
	uint8_t Lang = 1;
	CFGU_GetSystemLanguage(&Lang); // Get System Language.

	switch(Lang) {
		case 0:
			this->ActiveLang = LangHandler::Langs::Japanese;
			break;

		case 1:
		default:
			this->ActiveLang = LangHandler::Langs::English;
			break;

		case 3:
			this->ActiveLang = LangHandler::Langs::German;
			break;

		case 4:
			this->ActiveLang = LangHandler::Langs::Italian;
			break;
	}
};


void LangHandler::LoadLang(const LangHandler::Langs Lng) { this->ActiveLang = Lng; };
std::string LangHandler::Translation(const LangHandler::Strings STR) const { return this->TranslationStrings[(int8_t)this->ActiveLang][(int8_t)STR]; };