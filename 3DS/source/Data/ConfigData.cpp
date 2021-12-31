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

#include "StackMill3DS.hpp"
#include <unistd.h>


/*
	Config Information.

	53 4D 49 4C // SMIL (Stack MILl identifier).
	01 // Config version.
	01 00 01 04 01 // Language, Player 1 Stone color, Player 2 Stone color, Play Preview Color, Computer.
*/
void ConfigData::LoadConfig() {
	bool Good = false;
	if (access("sdmc:/3ds/StackMill/Config.bin", F_OK) == 0) Good = true; // File exist.

	if (Good) {
		FILE *ConfigIn = fopen("sdmc:/3ds/StackMill/Config.bin", "rb");

		if (ConfigIn) {
			fseek(ConfigIn, 0, SEEK_END);
			const uint32_t CFGSize = ftell(ConfigIn);
			fseek(ConfigIn, 0, SEEK_SET);

			if (CFGSize == this->ConfigSize) { // Ensure size is the proper one.
				std::unique_ptr<uint8_t[]> Data = std::make_unique<uint8_t[]>(this->ConfigSize);
				fread(Data.get(), 1, this->ConfigSize, ConfigIn); // Read data.

				/* Ensure Identifier matches. */
				if (Data[0x0] == 'S' && Data[0x1] == 'M' && Data[0x2] == 'I' && Data[0x3] == 'L') {
					if (Data[0x4] == this->ConfigVer) { // Ensure config version is the current one.

						/* Language. */
						switch(Data[0x5]) {
							case 0:
								StackMill3DS::App->LH->LoadLang(LangHandler::Langs::Japanese);
								break;

							case 1:
							default:
								StackMill3DS::App->LH->LoadLang(LangHandler::Langs::English);
								break;

							case 3:
								StackMill3DS::App->LH->LoadLang(LangHandler::Langs::German);
								break;
						}

						/* Stone colors. */
						if (Data[0x6] < 10) SettingsTab::StoneColors[0x0] = Data[0x6]; // Player 1.
						if (Data[0x7] < 10) SettingsTab::StoneColors[0x1] = Data[0x7]; // Player 2.
						if (Data[0x8] < 10) SettingsTab::StoneColors[0x2] = Data[0x8]; // Preview.
						if (Data[0x9] < 3) SettingsTab::AI = Data[0x9];

					} else {
						Good = false; // Config version doesn't match.
					}

				} else {
					Good = false; // Identifier doesn't match.
				}

			} else {
				Good = false; // Size doesn't match.
			}

			fclose(ConfigIn);
		}
	}

	if (!Good) this->ConfigChanged = true; // Needs to save at the end.
};


void ConfigData::SaveConfig() {
	if (this->ConfigChanged) {
		std::unique_ptr<uint8_t[]> Data = std::make_unique<uint8_t[]>(this->ConfigSize); // Allocate data of 0xA.

		Data[0x0] = 'S'; Data[0x1] = 'M'; Data[0x2] = 'I'; Data[0x3] = 'L'; Data[0x4] = this->ConfigVer; // Some Metadata.

		/* Language. */
		switch(StackMill3DS::App->LH->GetLangEnum()) {
			case LangHandler::Langs::Japanese:
				Data[0x5] = 0;
				break;

			case LangHandler::Langs::English:
				Data[0x5] = 1;
				break;

			case LangHandler::Langs::German:
				Data[0x5] = 3;
				break;
		}

		/* Stone colors. */
		Data[0x6] = SettingsTab::StoneColors[0x0]; // Player 1.
		Data[0x7] = SettingsTab::StoneColors[0x1]; // Player 2.
		Data[0x8] = SettingsTab::StoneColors[0x2]; // Preview.
		Data[0x9] = SettingsTab::AI;

		/* Handle Writing to the ConfigData. */
		FILE *ConfigOut = fopen("sdmc:/3ds/StackMill/Config.bin", "wb");
		if (ConfigOut) {
			fwrite(Data.get(), 1, this->ConfigSize, ConfigOut);
			fclose(ConfigOut);
		}
	}
};