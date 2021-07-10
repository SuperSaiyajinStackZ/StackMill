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

#include "StackMill.hpp"
#include <time.h>
#include <unistd.h> // access().

/*
	Game Data Structure.

	0x0: Current Player. ( 0x1 / 0x2 ).
	0x1: Removing a Stone phase? ( 0x0 for false, 0x1 for true ).
	0x2 - 0x19: Field stones. ( 0x0: Unused / Free, 0x1: White / Player 1, 0x2: Black / Player 2 ).
	0x1A - 0x22: Player 1 Stones. ( 0x0 - 0x17: Position; 0x19: Not played, 0x1A: Gone ).
	0x23: Player 1 Phase. ( 0x0: Set, 0x1: Move, 0x2: Jump ).
	0x24 - 0x2C: Player 2 Stones. ( 0x0 - 0x17: Position; 0x19: Not played, 0x1A: Gone ).
	0x2D: Player 2 Phase. ( 0x0: Set, 0x1: Move, 0x2: Jump ).

	GameDataSize: 0x2E --> 46 Bytes.
*/

/*
	Game Field Indexes visually here.

	0			1			2
		8		9		10
			16	17	18
	7	15	23		19	11	3
			22	21	20
		14		13		12
	6			5			4
*/


/*
	Init / Load a new game.

	const bool GenerateSeed: If generating the random seed for random operations, or not.
*/
void StackMill::LoadGame(const bool GenerateSeed) {
	/* Init Player and field. */
	for (int8_t Idx = 0; Idx < 2; Idx++) this->Players[Idx] = std::make_unique<StackMill::Player>();
	for (int8_t Idx = 0; Idx < 24; Idx++) this->_Field[Idx] = StackMill::GameStone::None;

	this->CPlayer = 1; // Current Player is ALWAYS the White (1) one.
	this->RemovePhase = false;
	if (GenerateSeed) srand(time(nullptr));
	this->GameValid = true;
};


/*
	Returns whetever it can do the specified play or not.

	const int8_t OldPos: The old position of the stone, only used in Move Phase.
	const int8_t NewPos: The new position for the stone to set.
	const StackMill::Phases Phase: The Phase to interact with.
*/
bool StackMill::CanDoSpecifiedPlay(const int8_t OldPos, const int8_t NewPos, const StackMill::Phases Phase) {
	if (OldPos < 0 || OldPos > 23 || NewPos < 0 || NewPos > 23) return false; // Bounds checks.

	switch(Phase) {
		/* Set and Jump are pretty much the same from the logic. */
		case StackMill::Phases::Set:
		case StackMill::Phases::Jump:
			return (this->_Field[NewPos] == StackMill::GameStone::None);

		/* Phase: Move a stone for 1 position. */
		case StackMill::Phases::Move: {
			/* Get the possible play positions. */
			const std::vector<int8_t> PossiblePositions = this->PlayablePositions(OldPos, StackMill::Phases::Move);

			if (!PossiblePositions.empty()) {
				/* Go through all the Positions and check if the New Position is included. */
				for (int8_t Idx = 0; Idx < (int8_t)PossiblePositions.size(); Idx++) {
					if (PossiblePositions[Idx] == NewPos) return true; // Included!
				};
			};
		};

		break;
	};

	return false;
};


/*
	Returns a std::vector of play-able positions. It also returns an empty vector, if nothing is play-able, so keep that in mind!

	const int8_t StonePosition: The position of the to checked stone. Only used in Move Phase.
	const StackMill::Phases Phase: The Phase to interact with.
*/
std::vector<int8_t> StackMill::PlayablePositions(const int8_t StonePosition, const StackMill::Phases Phase) {
	std::vector<int8_t> Positions;

	switch(Phase) {
		/* Set and Jump are pretty much the same from the logic. */
		case StackMill::Phases::Set:
		case StackMill::Phases::Jump:
			/* Check if Index is empty, if so, push that index back. */
			for (int8_t Idx = 0; Idx < 24; Idx++) {
				if (this->_Field[Idx] == StackMill::GameStone::None) Positions.push_back(Idx);
			};
			break;

		/* Phase: Move a stone for 1 position. */
		case StackMill::Phases::Move:
			if (StonePosition < 0 || StonePosition > 23) return Positions; // Bounds checks.

			/* The checks here do the following: Check for play-able positions, if playable -> Check if the position is empty and if so, push the new position back. */
			switch(StonePosition) {
				case 0:
					if (this->_Field[1] == StackMill::GameStone::None) Positions.push_back(1); // ->
					if (this->_Field[7] == StackMill::GameStone::None) Positions.push_back(7); // DOWN
					break;

				case 1:
					if (this->_Field[0] == StackMill::GameStone::None) Positions.push_back(0); // <-
					if (this->_Field[2] == StackMill::GameStone::None) Positions.push_back(2); // ->
					if (this->_Field[9] == StackMill::GameStone::None) Positions.push_back(9); // DOWN
					break;

				case 2:
					if (this->_Field[1] == StackMill::GameStone::None) Positions.push_back(1); // <-
					if (this->_Field[3] == StackMill::GameStone::None) Positions.push_back(3); // DOWN
					break;

				case 3:
					if (this->_Field[2] == StackMill::GameStone::None) Positions.push_back(2); // ^
					if (this->_Field[4] == StackMill::GameStone::None) Positions.push_back(4); // DOWN
					if (this->_Field[11] == StackMill::GameStone::None) Positions.push_back(11); // <-
					break;

				case 4:
					if (this->_Field[3] == StackMill::GameStone::None) Positions.push_back(3); // ^
					if (this->_Field[5] == StackMill::GameStone::None) Positions.push_back(5); // <-
					break;

				case 5:
					if (this->_Field[4] == StackMill::GameStone::None) Positions.push_back(4); // ->
					if (this->_Field[6] == StackMill::GameStone::None) Positions.push_back(6); // <-
					if (this->_Field[13] == StackMill::GameStone::None) Positions.push_back(13); // ^
					break;

				case 6:
					if (this->_Field[5] == StackMill::GameStone::None) Positions.push_back(5); // ->
					if (this->_Field[7] == StackMill::GameStone::None) Positions.push_back(7); // ^
					break;

				case 7:
					if (this->_Field[0] == StackMill::GameStone::None) Positions.push_back(0); // ^
					if (this->_Field[6] == StackMill::GameStone::None) Positions.push_back(6); // DOWN
					if (this->_Field[15] == StackMill::GameStone::None) Positions.push_back(15); // ->
					break;

				case 8:
					if (this->_Field[9] == StackMill::GameStone::None) Positions.push_back(9); // ->
					if (this->_Field[15] == StackMill::GameStone::None) Positions.push_back(15); // DOWN
					break;

				case 9:
					if (this->_Field[1] == StackMill::GameStone::None) Positions.push_back(1); // ^
					if (this->_Field[8] == StackMill::GameStone::None) Positions.push_back(8); // <-
					if (this->_Field[10] == StackMill::GameStone::None) Positions.push_back(10); // ->
					if (this->_Field[17] == StackMill::GameStone::None) Positions.push_back(17); // DOWN
					break;

				case 10:
					if (this->_Field[9] == StackMill::GameStone::None) Positions.push_back(9); // <-
					if (this->_Field[11] == StackMill::GameStone::None) Positions.push_back(11); // DOWN
					break;

				case 11:
					if (this->_Field[3] == StackMill::GameStone::None) Positions.push_back(3); // ->
					if (this->_Field[10] == StackMill::GameStone::None) Positions.push_back(10); // ^
					if (this->_Field[12] == StackMill::GameStone::None) Positions.push_back(12); // DOWN
					if (this->_Field[19] == StackMill::GameStone::None) Positions.push_back(19); // <-
					break;

				case 12:
					if (this->_Field[11] == StackMill::GameStone::None) Positions.push_back(11); // ^
					if (this->_Field[13] == StackMill::GameStone::None) Positions.push_back(13); // <-
					break;

				case 13:
					if (this->_Field[5] == StackMill::GameStone::None) Positions.push_back(5); // DOWN
					if (this->_Field[12] == StackMill::GameStone::None) Positions.push_back(12); // ->
					if (this->_Field[14] == StackMill::GameStone::None) Positions.push_back(14); // <-
					if (this->_Field[21] == StackMill::GameStone::None) Positions.push_back(21); // ^
					break;

				case 14:
					if (this->_Field[13] == StackMill::GameStone::None) Positions.push_back(13); // ->
					if (this->_Field[15] == StackMill::GameStone::None) Positions.push_back(15); // ^
					break;

				case 15:
					if (this->_Field[7] == StackMill::GameStone::None) Positions.push_back(7); // <-
					if (this->_Field[8] == StackMill::GameStone::None) Positions.push_back(8); // ^
					if (this->_Field[14] == StackMill::GameStone::None) Positions.push_back(14); // DOWN
					if (this->_Field[23] == StackMill::GameStone::None) Positions.push_back(23); // ->
					break;


				case 16:
					if (this->_Field[17] == StackMill::GameStone::None) Positions.push_back(17); // ->
					if (this->_Field[23] == StackMill::GameStone::None) Positions.push_back(23); // DOWN
					break;

				case 17:
					if (this->_Field[9] == StackMill::GameStone::None) Positions.push_back(9); // ^
					if (this->_Field[16] == StackMill::GameStone::None) Positions.push_back(16); // <-
					if (this->_Field[18] == StackMill::GameStone::None) Positions.push_back(18); // ->
					break;

				case 18:
					if (this->_Field[17] == StackMill::GameStone::None) Positions.push_back(17); // <-
					if (this->_Field[19] == StackMill::GameStone::None) Positions.push_back(19); // DOWN
					break;

				case 19:
					if (this->_Field[11] == StackMill::GameStone::None) Positions.push_back(11); // ->
					if (this->_Field[18] == StackMill::GameStone::None) Positions.push_back(18); // ^
					if (this->_Field[20] == StackMill::GameStone::None) Positions.push_back(20); // DOWN
					break;

				case 20:
					if (this->_Field[19] == StackMill::GameStone::None) Positions.push_back(19); // ^
					if (this->_Field[21] == StackMill::GameStone::None) Positions.push_back(21); // <-
					break;

				case 21:
					if (this->_Field[13] == StackMill::GameStone::None) Positions.push_back(13); // DOWN
					if (this->_Field[20] == StackMill::GameStone::None) Positions.push_back(20); // ->
					if (this->_Field[22] == StackMill::GameStone::None) Positions.push_back(22); // <-
					break;

				case 22:
					if (this->_Field[21] == StackMill::GameStone::None) Positions.push_back(21); // ->
					if (this->_Field[23] == StackMill::GameStone::None) Positions.push_back(23); // ^
					break;

				case 23:
					if (this->_Field[15] == StackMill::GameStone::None) Positions.push_back(15); // <-
					if (this->_Field[16] == StackMill::GameStone::None) Positions.push_back(16); // ^
					if (this->_Field[22] == StackMill::GameStone::None) Positions.push_back(22); // DOWN
					break;
			};
	};

	Positions.shrink_to_fit();
	return Positions;
};


/*
	Returns, whetever a match is possible with the specified Stone as the last played stone.

	const int8_t StoneIdx: The last played stone position, from which around to check for a match.
	const StackMill::GameStone Stone: The stone color which to check for a match.
*/
bool StackMill::Match(const int8_t StoneIdx, const StackMill::GameStone Stone) {
	if (this->_Field[StoneIdx] == Stone) {
		std::vector<int8_t> Includes;

		/* Check if the specified Stone index is included in any of the matches, if so, push that index back. */
		for (int8_t Idx = 0; Idx < 16; Idx++) {
			if (this->Fields[Idx].Stones[0] == StoneIdx || this->Fields[Idx].Stones[1] == StoneIdx || this->Fields[Idx].Stones[2] == StoneIdx) {
				Includes.push_back(Idx);
			};
		};

		Includes.shrink_to_fit(); // No need for useless allocation.

		/* Now check if 3 in a row exist, if so, return true, else it would go to the fallback option, which is false. */
		for (int8_t I = 0; I < (int8_t)Includes.size(); I++) {
			if (this->_Field[this->Fields[Includes[I]].Stones[0]] == Stone && // Check first stone.
				this->_Field[this->Fields[Includes[I]].Stones[1]] == Stone && // Check second stone.
				this->_Field[this->Fields[Includes[I]].Stones[2]] == Stone) return true; // And the last and if it matches, return true.
		};
	};

	return false;
};


/*
	Returns the remove state of the action.

	const int8_t StoneIdx: The stone position you want to remove.
	const StackMill::GameStone Stone: The stone color to remove. (Black for Player 2, White for Player 1)

	This returns...
	* StackMill::RemoveState::Lost: If the Player from which the stone got removed has 2 or less stones left.
	* StackMill::RemoveState::Removed: If the Player from which the stone got removed has 3 or more stones left.
	* StackMill::RemoveState::Invalid: If the specified stone cannot be removed.
*/
StackMill::RemoveState StackMill::StoneRemove(const int8_t StoneIdx, const StackMill::GameStone Stone) {
	if (this->_Field[StoneIdx] == Stone) { // Ensure the specified stone position is actually the stone to remove.
		bool Included = false;

		/* Check if the Stone Index Position is included in the remove-able stones. */
		const std::vector<int8_t> Removeables = this->RemoveableStones(Stone);

		for (int8_t Idx = 0; Idx < (int8_t)Removeables.size(); Idx++) {
			if (Removeables[Idx] == StoneIdx) {
				Included = true; // It is included, so we can continue.
				break;
			};
		};

		if (Included) { // If the StoneIdx is included -> Continue.
			int8_t RemoveIdx = -1;

			/* Check all stones of the specified color if it matches with the StoneIdx. Sets the RemoveIdx to which one matches. */
			for (int8_t Idx = 0; Idx < 9; Idx++) {
				if (this->Players[Stone == StackMill::GameStone::Black]->Position(Idx) == StoneIdx) {
					RemoveIdx = Idx;
					break;
				};
			};

			/* Only do this, if stone can actually be removed. */
			if (RemoveIdx != -1) {
				/* Set that stone index of the Player to -2, which means it got removed and empty specified position on the field. */
				this->Players[Stone == StackMill::GameStone::Black]->Position(RemoveIdx, -2);
				this->_Field[StoneIdx] = StackMill::GameStone::None;

				/* In case only 3 Stones are available -> Switch to the Jump Phase. */
				if (this->Players[Stone == StackMill::GameStone::Black]->Available() == 3) this->Players[Stone == StackMill::GameStone::Black]->Phase(StackMill::Phases::Jump);
				return (this->Players[Stone == StackMill::GameStone::Black]->Available() < 3 ? StackMill::RemoveState::Lost : StackMill::RemoveState::Removed);
			};
		};
	};

	return StackMill::RemoveState::Invalid;
};


/*
	Returns a vector of all remove-able stones from the specified stone color.

	const StackMill::GameStone Stone: The stone color to get all remove-able indexes from.
*/
std::vector<int8_t> StackMill::RemoveableStones(const StackMill::GameStone Stone) {
	std::vector<int8_t> Stones, PotentialMills;
	bool Contains = false;

	/* Go through all the Player stones. */
	for (int8_t Idx = 0; Idx < 9; Idx++) {
		const int8_t Index = this->Players[Stone == StackMill::GameStone::Black]->Position(Idx);

		/* Ensure the index is 0 or larger. -1 would be not set and -2 already lost. */
		if (Index > -1) {
			Contains = false; // Reset contains state.
			PotentialMills.clear();

			/* Check if index' position matches one of the possibilities, if so, push the Index back to the Indexes vector. */
			for (int8_t Idx2 = 0; Idx2 < 16; Idx2++) {
				if (this->Fields[Idx2].Stones[0] == Index || this->Fields[Idx2].Stones[1] == Index || this->Fields[Idx2].Stones[2] == Index) {
					PotentialMills.push_back(Idx2);
				};
			};

			PotentialMills.shrink_to_fit();
			if (PotentialMills.empty()) continue; // Go to the next stone.

			/* Now check, if that index position actually contains a Mill, because you cannot remove a stone from it, except all stones are mills. */
			for (int8_t Idx2 = 0; Idx2 < (int8_t)PotentialMills.size(); Idx2++) {
				if (this->_Field[this->Fields[PotentialMills[Idx2]].Stones[0]] == Stone && // Check first Match position.
					this->_Field[this->Fields[PotentialMills[Idx2]].Stones[1]] == Stone && // Check second Match position.
					this->_Field[this->Fields[PotentialMills[Idx2]].Stones[2]] == Stone) { // Check third Match position.
						Contains = true; // If it contains it, set that it contains it.
						break;
				};
			};

			/* If it doesn't contain it, that stone can be removed freely. */
			if (!Contains) Stones.push_back(Index);
		};
	};

	/* Additional checks, in case the remove-able stones are empty. */
	if (Stones.empty()) {
		/* Go through all the stones of the player and get it's index. */
		for (int8_t Idx = 0; Idx < 9; Idx++) {
			const int8_t Index = this->Players[Stone == StackMill::GameStone::Black]->Position(Idx);

			/* If 0 or larger -> Push it back to the remove-able stone positions, because all are mills and you can remove any from them. */
			if (Index > -1) Stones.push_back(Index);
		};
	};

	Stones.shrink_to_fit(); // Get rid of useless allocation.
	return Stones;
};


/*
	Do a play turn and return a state for the turn.

	const int8_t OldPos: The old stone position to play.
	const int8_t NewPos: The new stone position to play.

	This returns...
	* StackMill::PlayStatus::Normal: If no match exist, however was successfully able to play.
	* StackMill::PlayStatus::Match: If a match exist, so you could remove a stone from your opponent.
	* StackMill::PlayStatus::Invalid: If the play was invalid, due to not valid position to play.
*/
StackMill::PlayStatus StackMill::Play(const int8_t OldPos, const int8_t NewPos) {
	/* Player Phase: Set a stone to a free spot. */
	if (this->Players[this->CPlayer - 1]->Phase() == StackMill::Phases::Set) {
		if (this->CanDoSpecifiedPlay(OldPos, NewPos, StackMill::Phases::Set)) { // Ensure we can actually play it.

			/* Set Position from the Players stones to the setted one, and set the Field to the color of the Player. */
			this->Players[this->CPlayer - 1]->Position(this->Players[this->CPlayer - 1]->Idx(), NewPos);
			this->_Field[NewPos] = (this->CPlayer == 1 ? StackMill::GameStone::White : StackMill::GameStone::Black);

			if (this->Players[this->CPlayer - 1]->Idx() < 8) this->Players[this->CPlayer - 1]->IncreaseIdx();

			/* If 9 Stones are already played -> We switch to the Move Phase. */
			else this->Players[this->CPlayer - 1]->Phase(StackMill::Phases::Move);

			/* Check, if a match is possible with the setted stone. */
			if (this->Match(NewPos, (this->CPlayer == 1 ? StackMill::GameStone::White : StackMill::GameStone::Black))) {
				return StackMill::PlayStatus::Match; // 3 in einer Reihe!

			} else {
				return StackMill::PlayStatus::Normal;
			};
		};

	/* The Phase is Move OR Jump, both of them do not rely on new setted stones anymore and instead change the available ones. */
	} else {
		int8_t StonePos = -1;

		/* Check for the right stone that contains the old position. */
		for (int8_t I = 0; I < 9; I++) {
			if (this->Players[this->CPlayer - 1]->Position(I) == OldPos) {
				StonePos = I;
				break;
			};
		};

		/* If the previous check was successful, then we can go ahead. */
		if (StonePos != -1) {

			/* Ensure we can actually play it. */
			if (this->CanDoSpecifiedPlay(OldPos, NewPos, this->Players[this->CPlayer - 1]->Phase())) {

				/* Move the Stone from the Player to the new position. */
				this->Players[this->CPlayer - 1]->Position(StonePos, NewPos);

				/* Clear old position and set that stone / color to the new position. */
				this->_Field[OldPos] = StackMill::GameStone::None;
				this->_Field[NewPos] = (this->CPlayer == 1 ? StackMill::GameStone::White : StackMill::GameStone::Black);

				/* Check, if a match is possible with the setted stone. */
				if (this->Match(NewPos, (this->CPlayer == 1 ? StackMill::GameStone::White : StackMill::GameStone::Black))) {
					return StackMill::PlayStatus::Match; // 3 in einer Reihe!

				} else {
					return StackMill::PlayStatus::Normal;
				};
			};
		};
	};

	return StackMill::PlayStatus::Invalid; // If something went wrong, returns Invalid.
};


/*
	Returns whetever a player can still do a play, or is basically locked because no plays possible anymore.
*/
bool StackMill::CanPlay() {
	/* Go through all 9 Stones. */
	for (int8_t Idx = 0; Idx < 9; Idx++) {

		/* If position is not -2, then the stone is still available to check. */
		if (this->Players[this->CPlayer - 1]->Position(Idx) != -2) {

			/* Get all play-able positions. */
			const std::vector<int8_t> Plays = this->PlayablePositions(this->Players[this->CPlayer - 1]->Position(Idx), this->Players[this->CPlayer - 1]->Phase());

			/* In case it's not empty, we can play. */
			if (!Plays.empty()) return true;
		};
	};

	return false; // If nothing is play-able, return false.
};


/*
	Random AI / Computer Play.

	Returns a std::pair of first: Old Position (Stone Position), second: New Position.
*/
std::pair<int8_t, int8_t> StackMill::AIRandomPlay() {
	std::pair<int8_t, int8_t> Play = std::make_pair(-1, -1);
	std::vector<int8_t> PossiblePlays;

	switch(this->Phase((this->CPlayer == 1) ? StackMill::GameStone::White : StackMill::GameStone::Black)) {
		/* Player Phase: Set a stone to a free spot. */
		case StackMill::Phases::Set:

			/* Check all Field position for free spots and push them back to the PossiblePlays vector. */
			for (int8_t Idx = 0; Idx < 24; Idx++) {
				if (this->Field(Idx) == StackMill::GameStone::None) PossiblePlays.push_back(Idx);
			};

			/* Choose a random free spot. */
			PossiblePlays.shrink_to_fit();
			if (!PossiblePlays.empty()) Play.second = PossiblePlays[rand() % (int8_t)PossiblePlays.size()];
			break;

		/* Player Phase: Move a stone for 1 spot. */
		case StackMill::Phases::Move:

			/* Check all available Stones for play-abilities and push them to the PossiblePlays vector. */
			for (int8_t Idx = 0; Idx < 9; Idx++) {
				if (this->Players[this->CPlayer - 1]->Position(Idx) > -1) {
					if (!this->PlayablePositions(this->Players[this->CPlayer - 1]->Position(Idx), StackMill::Phases::Move).empty()) {
						PossiblePlays.push_back(this->Players[this->CPlayer - 1]->Position(Idx));
					};
				};
			};

			/* Choose a random Stone that is play-able. */
			PossiblePlays.shrink_to_fit();
			if (!PossiblePlays.empty()) Play.first = PossiblePlays[rand() % (int8_t)PossiblePlays.size()];

			/* Do the same as above.. but for the new position for that stone. */
			PossiblePlays = this->PlayablePositions(Play.first, StackMill::Phases::Move);
			PossiblePlays.shrink_to_fit();
			if (!PossiblePlays.empty()) Play.second = PossiblePlays[rand() % (int8_t)PossiblePlays.size()];
			break;

		/* Player Phase: Jump to a free spot. */
		case StackMill::Phases::Jump:

			/* Check all Field position for free spots and push them back to the PossiblePlays vector. */
			for (int8_t Idx = 0; Idx < 24; Idx++) {
				if (this->Field(Idx) == StackMill::GameStone::None) PossiblePlays.push_back(Idx);
			};

			/* Choose a random free spot. */
			PossiblePlays.shrink_to_fit();
			if (!PossiblePlays.empty()) Play.second = PossiblePlays[rand() % (int8_t)PossiblePlays.size()];
			PossiblePlays.clear(); // Clear for the next operation.

			/* Check for all play-able Stones and push them back to the PossiblePlays vector. */
			for (int8_t Idx = 0; Idx < 9; Idx++) {
				if (this->Players[this->CPlayer - 1]->Position(Idx) > -1) {
					PossiblePlays.push_back(this->Players[this->CPlayer - 1]->Position(Idx));
				};
			};

			/* Choose a random Stone that is play-able. */
			PossiblePlays.shrink_to_fit();
			if (!PossiblePlays.empty()) Play.first = PossiblePlays[rand() % (int8_t)PossiblePlays.size()];
			break;
	};

	return Play;
};


/*
	An AI, that isn't completely random, in case something can cause a match, in that case it does a 50:50 base.

	Returns a std::pair of first: Old Position (Stone Position), second: New Position.
*/
std::pair<int8_t, int8_t> StackMill::AI5050() {
	std::pair<int8_t, int8_t> Play = std::make_pair(-1, -1);
	std::vector<int8_t> PossiblePlays;

	switch(this->Phase((this->CPlayer == 1) ? StackMill::GameStone::White : StackMill::GameStone::Black)) {
		/* Player Phase: Set a stone to a free spot. */
		case StackMill::Phases::Set: {
			bool Danger = false, CanMatch = false;
			int8_t DangerIdx = -1, MatchIdx = -1;

			for (int8_t Idx = 0; Idx < 24; Idx++) {
				if (this->_Field[Idx] == StackMill::GameStone::None) {
					PossiblePlays.push_back(Idx); // Since it is empty, push the possible plays back to the vector.

					if (!Danger) {
						/* Set the stone temporarely here to check for a match. */
						this->_Field[Idx] = (this->CPlayer == 1 ? StackMill::GameStone::Black : StackMill::GameStone::White);

						/* The opponent aka player has a dangerous situation for the Computer / AI, cause a match is possible with the next Stone. */
						if (this->Match(Idx, this->_Field[Idx])) {
							Danger = true, DangerIdx = Idx;
						};

						this->_Field[Idx] = StackMill::GameStone::None; // Reset again, because we don't play there actually.
					};

					if (!CanMatch) {
						/* Set the stone temporarely here to check for a match. */
						this->_Field[Idx] = (this->CPlayer == 1 ? StackMill::GameStone::White : StackMill::GameStone::Black);

						/* The Computer / AI can do a match. */
						if (this->Match(Idx, this->_Field[Idx])) {
							CanMatch = true, MatchIdx = Idx;
						};

						this->_Field[Idx] = StackMill::GameStone::None; // Reset again, because we don't play there actually.
					};
				};
			};

			PossiblePlays.shrink_to_fit(); // Get rid of useless allocation.

			/* If one of those fit, do 50:50 chance for a match or counter. */
			bool MatchCounter = false, DangerCounter = false;

			if (CanMatch) MatchCounter = (rand() % 2 + 1) == 1;
			if (Danger) DangerCounter = (rand() % 2 + 1) == 1;

			if (MatchCounter) Play.second = MatchIdx;
			else if (DangerCounter) Play.second = DangerIdx;
			else {
				if (!PossiblePlays.empty()) Play.second = PossiblePlays[(rand() % (int8_t)PossiblePlays.size())];
			};
		};
		break;

		/* Player Phase: Move a stone for 1 spot. */
		case StackMill::Phases::Move: {
			std::vector<int8_t> OpponentPossiblePlays;
			bool Danger = false, CanMatch = false;
			std::pair<int8_t, int8_t> DangerIdx = { -1, -1 };
			std::pair<int8_t, int8_t> MatchIdx = { -1, -1 }; // first: StonePos, second: MovePos.


			/* Check all available Stones for play-abilities and push them to the PossiblePlays vector. */
			for (int8_t Idx = 0; Idx < 9; Idx++) {
				/* Check for play-able positions for the Computer. */
				if (this->Players[this->CPlayer == 2]->Position(Idx) > -1) {
					if (!this->PlayablePositions(this->Players[this->CPlayer == 2]->Position(Idx), StackMill::Phases::Move).empty()) {
						PossiblePlays.push_back(this->Players[this->CPlayer == 2]->Position(Idx));
					};
				};

				/*
					Do the same for the opponent, AKA: Player.

					this->CPlayer == 1, because the AI is usually Player 2 and with a check of Player 1, it would be false, hence it accesses the 0 index.
				*/
				if (this->Players[this->CPlayer == 1]->Position(Idx) > -1) {
					if (!this->PlayablePositions(this->Players[this->CPlayer == 1]->Position(Idx), this->Players[this->CPlayer == 1]->Phase()).empty()) {
						OpponentPossiblePlays.push_back(this->Players[this->CPlayer == 1]->Position(Idx));
					};
				};
			};

			/* No useless allocation. */
			PossiblePlays.shrink_to_fit(); OpponentPossiblePlays.shrink_to_fit();


			/* Go through all possibilities for the Computer. */
			for (int8_t Idx = 0; Idx < (int8_t)PossiblePlays.size(); Idx++) {
				const std::vector<int8_t> Checks = this->PlayablePositions(PossiblePlays[Idx], StackMill::Phases::Move);

				/* Check for all possible positions. */
				for (int8_t Idx2 = 0; Idx2 < (int8_t)Checks.size(); Idx2++) {
					/* Temporarely move the stone to check if a match exist. */
					this->_Field[Checks[Idx2]] = this->_Field[PossiblePlays[Idx]];
					this->_Field[PossiblePlays[Idx]] = StackMill::GameStone::None;

					/* The Computer / AI can do a match. */
					if (this->Match(Checks[Idx2], this->_Field[Checks[Idx2]])) {
						CanMatch = true, MatchIdx = { PossiblePlays[Idx], Checks[Idx2] };
					};

					/* Reset temporarely stuff. */
					this->_Field[PossiblePlays[Idx]] = this->_Field[Checks[Idx2]];
					this->_Field[Checks[Idx2]] = StackMill::GameStone::None;
				}

				if (CanMatch) break;
			};

			/* Do the same for the Opponent AKA Player. */
			for (int8_t Idx = 0; Idx < (int8_t)OpponentPossiblePlays.size(); Idx++) {
				const std::vector<int8_t> Checks = this->PlayablePositions(OpponentPossiblePlays[Idx], this->Players[this->CPlayer == 1]->Phase());

				/* Check for all possible positions. */
				for (int8_t Idx2 = 0; Idx2 < (int8_t)Checks.size(); Idx2++) {
					/* Temporarely move the stone to check if a match exist. */
					this->_Field[Checks[Idx2]] = this->_Field[OpponentPossiblePlays[Idx]];
					this->_Field[OpponentPossiblePlays[Idx]] = StackMill::GameStone::None;

					/* The Opponent AKA Player can do a match. */
					if (this->Match(Checks[Idx2], this->_Field[Checks[Idx2]])) {
						Danger = true, DangerIdx = { OpponentPossiblePlays[Idx], Checks[Idx2] };
					};

					/* Reset temporarely stuff. */
					this->_Field[OpponentPossiblePlays[Idx]] = this->_Field[Checks[Idx2]];
					this->_Field[Checks[Idx2]] = StackMill::GameStone::None;
				}

				if (Danger) break;
			};

			/* If one of those fit, do 50:50 chance for a match or counter. */
			bool MatchCounter = false, DangerCounter = false;

			if (CanMatch) MatchCounter = (rand() % 2 + 1) == 1;
			if (Danger) DangerCounter = (rand() % 2 + 1) == 1;

			if (MatchCounter) Play = MatchIdx; // 100% Match.

			/* Here is an exception, trying to block the Stone if possible. */
			else if (DangerCounter) {
				bool CanBlock = false;

				/* Go through all possibilities for the Computer. */
				for (int8_t Idx = 0; Idx < (int8_t)PossiblePlays.size(); Idx++) {
					const std::vector<int8_t> Checks = this->PlayablePositions(PossiblePlays[Idx], StackMill::Phases::Move);

					/* Check for all possible positions. */
					for (int8_t Idx2 = 0; Idx2 < (int8_t)Checks.size(); Idx2++) {
						if (Checks[Idx2] == DangerIdx.second) {
							MatchIdx = { PossiblePlays[Idx], Checks[Idx2] };
							CanBlock = true;
							break;
						};
					};

					if (CanBlock) break;
				};

				if (CanBlock) Play = MatchIdx;

			} else {
				/* If not empty, set randomly. */
				if (!PossiblePlays.empty()) {
					Play.first = PossiblePlays[rand() % (int8_t)PossiblePlays.size()];

					/* Do the same as above.. but for the new position for that stone. */
					PossiblePlays = this->PlayablePositions(Play.first, StackMill::Phases::Move);
					PossiblePlays.shrink_to_fit();
					if (!PossiblePlays.empty()) Play.second = PossiblePlays[rand() % (int8_t)PossiblePlays.size()];
				};
			};
		};
		break;

		/* Player Phase: Jump to a free spot. */
		case StackMill::Phases::Jump: {
			std::vector<int8_t> OpponentPossiblePlays;
			bool Danger = false, CanMatch = false;
			std::pair<int8_t, int8_t> DangerIdx = { -1, -1 };
			std::pair<int8_t, int8_t> MatchIdx = { -1, -1 }; // first: StonePos, second: MovePos.


			/* Check all available Stones for play-abilities and push them to the PossiblePlays vector. */
			for (int8_t Idx = 0; Idx < 9; Idx++) {
				/* Check for play-able positions for the Computer. */
				if (this->Players[this->CPlayer == 2]->Position(Idx) > -1) {
					if (!this->PlayablePositions(this->Players[this->CPlayer == 2]->Position(Idx), StackMill::Phases::Jump).empty()) {
						PossiblePlays.push_back(this->Players[this->CPlayer == 2]->Position(Idx));
					};
				};


				/*
					Do the same for the opponent, AKA: Player.

					this->CPlayer == 1, because the AI is usually Player 2 and with a check of Player 1, it would be false, hence it accesses the 0 index.
				*/
				if (this->Players[this->CPlayer == 1]->Position(Idx) > -1) {
					if (!this->PlayablePositions(this->Players[this->CPlayer == 1]->Position(Idx), this->Players[this->CPlayer == 1]->Phase()).empty()) {
						OpponentPossiblePlays.push_back(this->Players[this->CPlayer == 1]->Position(Idx));
					};
				};
			};

			/* No useless allocation. */
			PossiblePlays.shrink_to_fit(); OpponentPossiblePlays.shrink_to_fit();


			/* Go through all possibilities for the Computer. */
			for (int8_t Idx = 0; Idx < (int8_t)PossiblePlays.size(); Idx++) {
				const std::vector<int8_t> Checks = this->PlayablePositions(PossiblePlays[Idx], StackMill::Phases::Jump);

				/* Check for all possible positions. */
				for (int8_t Idx2 = 0; Idx2 < (int8_t)Checks.size(); Idx2++) {
					/* Temporarely move the stone to check if a match exist. */
					this->_Field[Checks[Idx2]] = this->_Field[PossiblePlays[Idx]];
					this->_Field[PossiblePlays[Idx]] = StackMill::GameStone::None;

					/* The Computer / AI can do a match. */
					if (this->Match(Checks[Idx2], this->_Field[Checks[Idx2]])) {
						CanMatch = true, MatchIdx = { PossiblePlays[Idx], Checks[Idx2] };
					};

					/* Reset temporarely stuff. */
					this->_Field[PossiblePlays[Idx]] = this->_Field[Checks[Idx2]];
					this->_Field[Checks[Idx2]] = StackMill::GameStone::None;
				}

				if (CanMatch) break;
			};

			/* Do the same for the Opponent AKA Player. */
			for (int8_t Idx = 0; Idx < (int8_t)OpponentPossiblePlays.size(); Idx++) {
				const std::vector<int8_t> Checks = this->PlayablePositions(OpponentPossiblePlays[Idx], this->Players[this->CPlayer == 1]->Phase());

				/* Check for all possible positions. */
				for (int8_t Idx2 = 0; Idx2 < (int8_t)Checks.size(); Idx2++) {
					/* Temporarely move the stone to check if a match exist. */
					this->_Field[Checks[Idx2]] = this->_Field[OpponentPossiblePlays[Idx]];
					this->_Field[OpponentPossiblePlays[Idx]] = StackMill::GameStone::None;

					/* The Opponent AKA Player can do a match. */
					if (this->Match(Checks[Idx2], this->_Field[Checks[Idx2]])) {
						Danger = true, DangerIdx = { OpponentPossiblePlays[Idx], Checks[Idx2] };
					};

					/* Reset temporarely stuff. */
					this->_Field[OpponentPossiblePlays[Idx]] = this->_Field[Checks[Idx2]];
					this->_Field[Checks[Idx2]] = StackMill::GameStone::None;
				}

				if (Danger) break;
			};

			/* If one of those fit, do 50:50 chance for a match or counter. */
			bool MatchCounter = false, DangerCounter = false;

			if (CanMatch) MatchCounter = (rand() % 2 + 1) == 1;
			if (Danger) DangerCounter = (rand() % 2 + 1) == 1;

			if (MatchCounter) Play = MatchIdx; // 100% Match.

			/* Here is an exception, trying to block the Stone if possible. */
			else if (DangerCounter) {
				bool CanBlock = false;

				/* Go through all possibilities for the Computer. */
				for (int8_t Idx = 0; Idx < (int8_t)PossiblePlays.size(); Idx++) {
					const std::vector<int8_t> Checks = this->PlayablePositions(PossiblePlays[Idx], StackMill::Phases::Jump);

					/* Check for all possible positions. */
					for (int8_t Idx2 = 0; Idx2 < (int8_t)Checks.size(); Idx2++) {
						if (Checks[Idx2] == DangerIdx.second) {
							MatchIdx = { PossiblePlays[Idx], Checks[Idx2] };
							CanBlock = true;
							break;
						};
					};

					if (CanBlock) break;
				};

				if (CanBlock) Play = MatchIdx;

			} else {
				/* If not empty, set randomly. */
				if (!PossiblePlays.empty()) {
					Play.first = PossiblePlays[rand() % (int8_t)PossiblePlays.size()];

					/* Do the same as above.. but for the new position for that stone. */
					PossiblePlays = this->PlayablePositions(Play.first, StackMill::Phases::Jump);
					PossiblePlays.shrink_to_fit();
					if (!PossiblePlays.empty()) Play.second = PossiblePlays[rand() % (int8_t)PossiblePlays.size()];
				};
			};
		};
		break;
	};

	return Play;
};


/*
	Remove Action of a Stone for the AI.
	Priority is to remove stones that have as much stones together as possible.

	Returns an int8_t of the position to remove.
*/
int8_t StackMill::AIStoneRemove() {
	int8_t Play = -1;
	std::vector<int8_t> Removeables = this->RemoveableStones((this->CPlayer == 1) ? StackMill::GameStone::Black : StackMill::GameStone::White);
	std::vector<int8_t> MatchingStones;

	for (int8_t Idx = 0; Idx < (int8_t)Removeables.size(); Idx++) {
		MatchingStones.push_back(0); // Push back a 0.
		std::vector<int8_t> Includes;

		/* Check if the specified Stone index is included in any of the matches, if so, push that index back. */
		for (int8_t Idx2 = 0; Idx2 < 16; Idx2++) {
			if (this->Fields[Idx2].Stones[0] == Removeables[Idx] || this->Fields[Idx2].Stones[1] == Removeables[Idx] || this->Fields[Idx2].Stones[2] == Removeables[Idx]) {
				Includes.push_back(Idx2);
			};
		};

		Includes.shrink_to_fit(); // No need for useless allocation.

		/* Now go check the amount of stones that are there. */
		for (int8_t Idx2 = 0; Idx2 < (int8_t)Includes.size(); Idx2++) {
			int8_t Temp = 0;

			for (int8_t Idx3 = 0; Idx3 < 3; Idx3++) {
				if (this->_Field[this->Fields[Includes[Idx2]].Stones[Idx3]] == ((this->CPlayer == 1) ? StackMill::GameStone::Black : StackMill::GameStone::White)) Temp++;
			};

			if (Temp > MatchingStones[Idx]) MatchingStones[Idx] = Temp;
		};
	};

	for (int8_t Idx2 = 0; Idx2 < (int8_t)MatchingStones.size(); Idx2++) {
		if (MatchingStones[Idx2] > Play) Play = Removeables[Idx2];
	};

	return Play;
};


bool StackMill::ImportGame(const std::string &Path) {
	this->GameValid = false;
	if (access(Path.c_str(), F_OK) != 0) return false; // File doesn't exist.

	FILE *GameData = fopen(Path.c_str(), "rb");

	if (GameData) {
		fseek(GameData, 0, SEEK_END);
		const uint32_t GameSize = ftell(GameData);
		fseek(GameData, 0, SEEK_SET);

		if (GameSize == this->DataSize) {
			std::unique_ptr<uint8_t[]> Data = std::make_unique<uint8_t[]>(this->DataSize);
			fread(Data.get(), 1, this->DataSize, GameData);


			if (Data[0x0] > 0x0 && Data[0x0] < 3) this->CPlayer = Data[0x0];
			else this->CPlayer = 0x1;

			this->RemovePhase = Data[0x1];

			/* Get the GameField Stones. */
			for (int8_t Idx = 0; Idx < 24; Idx++) {
				switch(Data[0x2 + Idx]) {
					case 0x0:
					default:
						this->_Field[Idx] = StackMill::GameStone::None;
						break;

					case 0x1:
						this->_Field[Idx] = StackMill::GameStone::White;
						break;

					case 0x2:
						this->_Field[Idx] = StackMill::GameStone::Black;
						break;
				};
			};

			/* Init Player. */
			for (int8_t Idx = 0; Idx < 2; Idx++) this->Players[Idx] = std::make_unique<StackMill::Player>();

			/* Get Player 1 Stones. */
			for (int8_t Idx = 0; Idx < 9; Idx++) {
				if (Data[0x1A + Idx] < 24) this->Players[0]->Position(Idx, Data[0x1A + Idx]);
				else if (Data[0x1A + Idx] == 0x19) this->Players[0]->Position(Idx, -1);
				else if (Data[0x1A + Idx] == 0x1A) this->Players[0]->Position(Idx, -2);
			};

			/* Get Player 1 Phase. */
			switch(Data[0x23]) {
				case 0: // Set.
					this->Players[0]->Phase(StackMill::Phases::Set);
					break;

				case 1: // Move.
					this->Players[0]->Phase(StackMill::Phases::Move);
					break;

				case 2: // Jump.
					this->Players[0]->Phase(StackMill::Phases::Jump);
					break;
			};


			/* Get Player 2 Stones. */
			for (int8_t Idx = 0; Idx < 9; Idx++) {
				if (Data[0x24 + Idx] < 24) this->Players[1]->Position(Idx, Data[0x24 + Idx]);
				else if (Data[0x24 + Idx] == 0x19) this->Players[1]->Position(Idx, -1);
				else if (Data[0x24 + Idx] == 0x1A) this->Players[1]->Position(Idx, -2);
			};

			/* Get Player 2 Phase. */
			switch(Data[0x2D]) {
				case 0: // Set.
					this->Players[1]->Phase(StackMill::Phases::Set);
					break;

				case 1: // Move.
					this->Players[1]->Phase(StackMill::Phases::Move);
					break;

				case 2: // Jump.
					this->Players[1]->Phase(StackMill::Phases::Jump);
					break;
			};

			this->GameValid = true;
		};

		fclose(GameData);
	};

	return this->GameValid;
};


bool StackMill::ExportGame(const std::string &Path) {
	std::unique_ptr<uint8_t[]> Data = std::make_unique<uint8_t[]>(this->DataSize); // Allocate data of 0x2E.

	Data[0x0] = this->CPlayer;
	Data[0x1] = this->RemovePhase;

	/* Get the GameField Stones. */
	for (int8_t Idx = 0; Idx < 24; Idx++) {
		switch(this->_Field[Idx]) {
			case StackMill::GameStone::None:
				Data[0x2 + Idx] = 0x0;
				break;

			case StackMill::GameStone::White:
				Data[0x2 + Idx] = 0x1;
				break;

			case StackMill::GameStone::Black:
				Data[0x2 + Idx] = 0x2;
				break;
		};
	};


	/* Get Player 1 Stones. */
	for (int8_t Idx = 0; Idx < 9; Idx++) {
		if (this->Players[0]->Position(Idx) >= 0 && this->Players[0]->Position(Idx) < 24) Data[0x1A + Idx] = this->Players[0]->Position(Idx);
		else if (this->Players[0]->Position(Idx) == -1) Data[0x1A + Idx] = 0x19;
		else if (this->Players[0]->Position(Idx) == -2) Data[0x1A + Idx] = 0x1A;
	};

	/* Get Player 1 Phase. */
	switch(this->Players[0]->Phase()) {
		case StackMill::Phases::Set: // Set.
			Data[0x23] = 0x0;
			break;

		case StackMill::Phases::Move: // Move.
			Data[0x23] = 0x1;
			break;

		case StackMill::Phases::Jump: // Jump.
			Data[0x23] = 0x2;
			break;
	};


	/* Get Player 2 Stones. */
	for (int8_t Idx = 0; Idx < 9; Idx++) {
		if (this->Players[1]->Position(Idx) >= 0 && this->Players[1]->Position(Idx) < 24) Data[0x24 + Idx] = this->Players[1]->Position(Idx);
		else if (this->Players[1]->Position(Idx) == -1) Data[0x24 + Idx] = 0x19;
		else if (this->Players[1]->Position(Idx) == -2) Data[0x24 + Idx] = 0x1A;
	};

	/* Get Player 2 Phase. */
	switch(this->Players[1]->Phase()) {
		case StackMill::Phases::Set: // Set.
			Data[0x2D] = 0x0;
			break;

		case StackMill::Phases::Move: // Move.
			Data[0x2D] = 0x1;
			break;

		case StackMill::Phases::Jump: // Jump.
			Data[0x2D] = 0x2;
			break;
	};


	/* Handle Writing to the GameDataFile. */
	FILE *GameOut = fopen(Path.c_str(), "wb");
	if (GameOut) {
		fwrite(Data.get(), 1, this->DataSize, GameOut);
		fclose(GameOut);
		return true;
	};

	return false;
};