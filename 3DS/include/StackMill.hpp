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

#ifndef _STACKMILL_CORE_HPP
#define _STACKMILL_CORE_HPP

#include <memory>
#include <vector>

class StackMill {
public:
	/* Some enum class states that are needed to check states. */
	enum class GameStone : int8_t { None = 0, White = 1, Black = 2 };
	enum class Phases : int8_t { Set = 0, Move = 1, Jump = 2 };
	enum class PlayStatus : int8_t { Invalid = 0, Normal = 1, Match = 2 };
	enum class RemoveState : int8_t { Invalid = 0, Removed = 1, Lost = 2 };

	/* Constructor and Loader. */
	StackMill(const bool GenerateSeed = false) { this->LoadGame(GenerateSeed); };
	void LoadGame(const bool GenerateSeed = false);

	/* Some return things about the game. */
	StackMill::GameStone Field(const int8_t Pos) const {
		if (Pos < 0 || Pos > 23) return StackMill::GameStone::None;

		return this->_Field[Pos];
	};
	int8_t Available(const StackMill::GameStone Stone) const { return this->Players[Stone == StackMill::GameStone::Black]->Available(); };
	int8_t Position(const StackMill::GameStone Stone, const int8_t Pos) { return this->Players[Stone == StackMill::GameStone::Black]->Position(Pos); };
	int8_t CurrentPlayer() const { return this->CPlayer; };
	StackMill::Phases Phase(const StackMill::GameStone Stone) const { return this->Players[Stone == StackMill::GameStone::Black]->Phase(); };
	int8_t PlayerIdx(const StackMill::GameStone Stone) const { return this->Players[Stone == StackMill::GameStone::Black]->Idx(); };


	/* Checks. */
	bool CanDoSpecifiedPlay(const int8_t OldPos, const int8_t NewPos, const StackMill::Phases Phase);
	std::vector<int8_t> PlayablePositions(const int8_t StonePos, const StackMill::Phases Phase);
	bool Match(const int8_t StoneIdx, const StackMill::GameStone Stone);
	std::vector<int8_t> RemoveableStones(const StackMill::GameStone Stone);
	bool Good(const int8_t Pos, const StackMill::GameStone Stone) const { return this->_Field[Pos] == Stone; };
	bool CanPlay();

	/* Actual actions. */
	StackMill::PlayStatus Play(const int8_t OldPos, const int8_t NewPos);
	StackMill::RemoveState StoneRemove(const int8_t StoneIdx, const StackMill::GameStone Stone);

	void NextPlayer() { this->CPlayer = (this->CPlayer == 1 ? 2 : 1); };

	std::pair<int8_t, int8_t> AIRandomPlay();
	std::pair<int8_t, int8_t> AI5050();
	int8_t AIStoneRemove();
private:
	struct MatchField { int8_t Stones[3] = { 0 }; }; // 3 Stones.


	/* Player class implementation of StackMill. */
	class Player {
	public:
		Player() { this->Reset(); }; // Set the stones back to -1 at the start.

		void Reset() {
			for (int8_t Idx = 0; Idx < 9; Idx++) this->Stones[Idx] = -1;
			this->StoneIdx = 0;
		};

		/* Player Mode. */
		StackMill::Phases Phase() const { return this->_Phase; };
		void Phase(const StackMill::Phases P) { this->_Phase = P; };

		/* Player Stone Position. */
		int8_t Position(const int8_t Pos) const {
			if (Pos < 0 || Pos > 8) return -2;
			return this->Stones[Pos];
		};
		void Position(const int8_t Pos, const int8_t NewPos) {
			if (Pos < 0 || Pos > 8 || NewPos < -2 || NewPos > 23) return;
			this->Stones[Pos] = NewPos;
		};

		/* Returns the available / left Stones from the Player. */
		int8_t Available() {
			int8_t InGame = 0;

			for (int8_t Idx = 0; Idx < 9; Idx++) {
				if (this->Stones[Idx] != -2) InGame++;
			};

			return InGame;
		};

		int8_t Idx() const { return this->StoneIdx; };
		void IncreaseIdx() { this->StoneIdx++; };
	private:
		int8_t Stones[9] = { -1 };
		int8_t StoneIdx = 0;
		StackMill::Phases _Phase = StackMill::Phases::Set;
	};

	/* Some needed stuff for the game. */
	std::unique_ptr<StackMill::Player> Players[2] = { nullptr };
	StackMill::GameStone _Field[24] = { StackMill::GameStone::None };
	int8_t CPlayer = 1; // Current Player.

	/* The Matching Field. */
	static constexpr StackMill::MatchField Fields[16] = {
		/* Outside-Fields. */
		{ 0, 1, 2 },
		{ 2, 3, 4 },
		{ 4, 5, 6 },
		{ 6, 7, 0 },

		/* Middle-Fields. */
		{ 8, 9, 10 },
		{ 10, 11, 12 },
		{ 12, 13, 14 },
		{ 14, 15, 8 },

		/* Inside-Fields. */
		{ 16, 17, 18 },
		{ 18, 19, 20 },
		{ 20, 21, 22 },
		{ 22, 23, 16 },

		/* From Outside to Inside. */
		{ 1, 9, 17 },
		{ 3, 11, 19 },
		{ 5, 13, 21 },
		{ 7, 15, 23 }
	};
};

#endif