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

#ifndef _STACKMILL_GAME_TAB_HPP
#define _STACKMILL_GAME_TAB_HPP

#include "structs.hpp"
#include <string>
#include <vector>

class GameTab {
public:
	void Draw();
	void Handler();

	static std::vector<int8_t> Preview; // Static for the Import | Export Option.
private:
	void NewGame();

	bool ShowPointer = true;
	bool StoneSelect = false, StartMode = true;
	int8_t Selection = 0, SelectedStone = 0, SelectionMode = 1, Winner = 0;

	void Up(int8_t &Slt);
	void Down(int8_t &Slt);
	void Left(int8_t &Slt);
	void Right(int8_t &Slt);
	void RemoveAction();
	void Reset();
	void CheckStatus();
	void AITurn();
	void PlayerTurn();

	/* Animations. */
	void Move(); // Moving.
	void Remove(); // Removing.
	void Place(); // Set / Place.
	void Jump(); // Jumping.

	void PopupPrompt();

	static constexpr Structs::ButtonPos Help = { 13, 202, 28, 33 };
	static constexpr Structs::ButtonPos Prompt[2] = {
		{ 24, 140, 124, 48 },
		{ 172, 140, 124, 48 }
	};

	/* Field Positions. */
	static constexpr Structs::ButtonPos Fields[24] = {
		{ 50, 20, 20, 20 },
		{ 150, 20, 20, 20 },
		{ 250, 20, 20, 20 },

		{ 250, 120, 20, 20 },
		{ 250, 220, 20, 20 },

		{ 150, 220, 20, 20 },
		{ 50, 220, 20, 20 },

		{ 50, 120, 20, 20 },


		{ 83, 54, 20, 20 },
		{ 150, 54, 20, 20 },
		{ 215, 54, 20, 20 },

		{ 215, 120, 20, 20 },
		{ 215, 188, 20, 20 },

		{ 150, 188, 20, 20 },
		{ 83, 188, 20, 20 },

		{ 83, 120, 20, 20 },


		{ 117, 88, 20, 20 },
		{ 150, 88, 20, 20 },
		{ 184, 88, 20, 20 },

		{ 184, 120, 20, 20 },
		{ 184, 155, 20, 20 },

		{ 150, 155, 20, 20 },
		{ 117, 155, 20, 20 },

		{ 117, 120, 20, 20 }
	};
};

#endif