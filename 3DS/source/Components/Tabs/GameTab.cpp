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

#include "Common.hpp"
#include "GameTab.hpp"
#include "Rules.hpp"


std::vector<int8_t> GameTab::Preview;


void GameTab::NewGame() {
	GameTab::Preview.clear();
	this->StartMode = true;
	StackMill3DS::App->Core->LoadGame();
	this->SelectedStone = 0, this->Selection = 0, this->SelectionMode = 1;
};


void GameTab::Draw() {
	StackMill3DS::App->GData->DrawSprite(sprites_field_idx, 50 + Tab::GameOffset, 20);

	/* Draw the Stones. */
	for (int8_t Idx = 0; Idx < 24; Idx++) {
		if (StackMill3DS::App->Core->Field(Idx) != StackMill::GameStone::None) {
			StackMill3DS::App->GData->DrawStone(SettingsTab::StoneColors[StackMill3DS::App->Core->Field(Idx) == StackMill::GameStone::Black], this->Fields[Idx].x + Tab::GameOffset, this->Fields[Idx].y);
		}
	}

	/* If Selection Phase -> Display the Preview of the play-able Stones. */
	if (this->SelectionMode) {
		if (GameTab::Preview.size() > 0) {
			for (int8_t Idx = 0; Idx < (int8_t)GameTab::Preview.size(); Idx++) {
				StackMill3DS::App->GData->DrawStone(SettingsTab::StoneColors[2], this->Fields[GameTab::Preview[Idx]].x + Tab::GameOffset, this->Fields[GameTab::Preview[Idx]].y);
			}
		}
	}

	/* In case the Pointer is set to shown, display it. */
	if (this->ShowPointer) StackMill3DS::App->GData->DrawSprite(sprites_pointer_idx, this->Fields[(this->SelectionMode ? this->Selection : this->SelectedStone)].x + 6 + Tab::GameOffset, this->Fields[(this->SelectionMode ? this->Selection : this->SelectedStone)].y + 6);
	StackMill3DS::App->GData->DrawSprite(sprites_help_idx, this->Help.x + Tab::GameOffset, this->Help.y);

	/* Draw Side Stones. */
	for (int8_t Idx = 0; Idx < 9; Idx++) {
		if (StackMill3DS::App->Core->Position(StackMill::GameStone::White, Idx) == -1) {
			StackMill3DS::App->GData->DrawStone(SettingsTab::StoneColors[0], (Idx % 2 == 0 ? 5 + Tab::GameOffset : 30 + Tab::GameOffset), 40 + (Idx / 2 * 30));
		}

		if (StackMill3DS::App->Core->Position(StackMill::GameStone::Black, Idx) == -1) {
			StackMill3DS::App->GData->DrawStone(SettingsTab::StoneColors[1], (Idx % 2 == 0 ? 270 + Tab::GameOffset : 295 + Tab::GameOffset), 40 + (Idx / 2 * 30));
		}
	}
};


/* Goes a position up. */
void GameTab::Up(int8_t &Slt) {
	switch(Slt) {
		case 6: Slt = 7; break;
		case 7: Slt = 0; break;

		case 14: Slt = 15; break;
		case 15: Slt = 8; break;

		case 22: Slt = 23; break;
		case 23: Slt = 16; break;

		case 5: Slt = 13; break;
		case 13: Slt = 21; break;

		case 17: Slt = 9; break;
		case 9: Slt = 1; break;

		case 20: Slt = 19; break;
		case 19: Slt = 18; break;

		case 12: Slt = 11; break;
		case 11: Slt = 10; break;

		case 4: Slt = 3; break;
		case 3: Slt = 2; break;
	}
};


/* Goes a position down. */
void GameTab::Down(int8_t &Slt) {
	switch(Slt) {
		case 0: Slt = 7; break;
		case 7: Slt = 6; break;

		case 8: Slt = 15; break;
		case 15: Slt = 14; break;

		case 16: Slt = 23; break;
		case 23: Slt = 22; break;

		case 21: Slt = 13; break;
		case 13: Slt = 5; break;

		case 1: Slt = 9; break;
		case 9: Slt = 17; break;

		case 18: Slt = 19; break;
		case 19: Slt = 20; break;

		case 10: Slt = 11; break;
		case 11: Slt = 12; break;

		case 2: Slt = 3; break;
		case 3: Slt = 4; break;
	}
};


/* Goes a position right. */
void GameTab::Right(int8_t &Slt) {
	switch(Slt) {
		case 0: Slt = 1; break;
		case 1: Slt = 2; break;

		case 8: Slt = 9; break;
		case 9: Slt = 10; break;

		case 16: Slt = 17; break;
		case 17: Slt = 18; break;

		case 7: Slt = 15; break;
		case 15: Slt = 23; break;

		case 19: Slt = 11; break;
		case 11: Slt = 3; break;

		case 22: Slt = 21; break;
		case 21: Slt = 20; break;

		case 14: Slt = 13; break;
		case 13: Slt = 12; break;

		case 6: Slt = 5; break;
		case 5: Slt = 4; break;
	}
};


/* Goes a position left. */
void GameTab::Left(int8_t &Slt) {
	switch(Slt) {
		case 2: Slt = 1; break;
		case 1: Slt = 0; break;

		case 10: Slt = 9; break;
		case 9: Slt = 8; break;

		case 18: Slt = 17; break;
		case 17: Slt = 16; break;

		case 23: Slt = 15; break;
		case 15: Slt = 7; break;

		case 3: Slt = 11; break;
		case 11: Slt = 19; break;

		case 20: Slt = 21; break;
		case 21: Slt = 22; break;

		case 12: Slt = 13; break;
		case 13: Slt = 14; break;

		case 4: Slt = 5; break;
		case 5: Slt = 6; break;
	}
};


/* Removing a Stone of the opponent Action. */
void GameTab::RemoveAction() {
	if (StackMill3DS::App->Down & KEY_TOUCH) {
		const StackMill::GameStone Stone = ((StackMill3DS::App->Core->CurrentPlayer() == 1) ? StackMill::GameStone::Black : StackMill::GameStone::White);

		for (int8_t Idx = 0; Idx < 24; Idx++) {
			if (this->Fields[Idx].Touched(StackMill3DS::App->T)) {
				if (this->ShowPointer) this->ShowPointer = false;

				bool CanContinue = false;

				for (int8_t Idx2 = 0; Idx2 < (int8_t)GameTab::Preview.size(); Idx2++) {
					if (GameTab::Preview[Idx2] == Idx) {
						CanContinue = true;
						break;
					}
				}

				if (CanContinue) {
					this->Selection = Idx;
					this->Remove();
					const StackMill::RemoveState State = StackMill3DS::App->Core->StoneRemove(this->Selection, Stone);

					switch(State) {
						case StackMill::RemoveState::Lost:
							this->Winner = StackMill3DS::App->Core->CurrentPlayer();
							this->PopupPrompt();
							break;

						case StackMill::RemoveState::Removed:
							StackMill3DS::App->Core->NextPlayer();
							this->StartMode = (StackMill3DS::App->Core->Phase((StackMill3DS::App->Core->CurrentPlayer() == 1) ? StackMill::GameStone::White : StackMill::GameStone::Black) == StackMill::Phases::Set);
							this->Reset();
							StackMill3DS::App->Core->InRemove(false);
							if (this->StartMode) this->SelectionMode = 1;
							this->CheckStatus();
							break;

						case StackMill::RemoveState::Invalid:
							break;
					}
				}
			}
		}
	}

	if (StackMill3DS::App->Down & KEY_A) {
		const StackMill::GameStone Stone = ((StackMill3DS::App->Core->CurrentPlayer() == 1) ? StackMill::GameStone::Black : StackMill::GameStone::White);

		if (!this->ShowPointer) this->ShowPointer = true;
		bool CanContinue = false;

		for (int8_t Idx = 0; Idx < (int8_t)GameTab::Preview.size(); Idx++) {
			if (GameTab::Preview[Idx] == this->Selection) {
				CanContinue = true;
				break;
			}
		}

		/* We can remove the Stone. */
		if (CanContinue) {
			this->Remove();

			const StackMill::RemoveState State = StackMill3DS::App->Core->StoneRemove(this->Selection, Stone);

			switch(State) {
				case StackMill::RemoveState::Lost:
					this->Winner = StackMill3DS::App->Core->CurrentPlayer();
					this->PopupPrompt();
					break;

				case StackMill::RemoveState::Removed:
					StackMill3DS::App->Core->NextPlayer();
					this->StartMode = (StackMill3DS::App->Core->Phase((StackMill3DS::App->Core->CurrentPlayer() == 1) ? StackMill::GameStone::White : StackMill::GameStone::Black) == StackMill::Phases::Set);
					this->Reset();
					StackMill3DS::App->Core->InRemove(false);
					if (this->StartMode) this->SelectionMode = 1;
					this->CheckStatus();
					break;

				case StackMill::RemoveState::Invalid:
					break;
			}
		}
	}
};


/* Check if a winner exist. */
void GameTab::CheckStatus() {
	/* Both players have 3 Stones left, a tie. */
	if (StackMill3DS::App->Core->Available(StackMill::GameStone::White) == 3 && StackMill3DS::App->Core->Available(StackMill::GameStone::Black) == 3) {
		this->Winner = 0;
		this->PopupPrompt();
		return;
	}

	/* Current Player cannot continue anymore, so lost. */
	if (!StackMill3DS::App->Core->CanPlay()) {
		this->Winner = ((StackMill3DS::App->Core->CurrentPlayer() == 1) ? 2 : 1);
		this->PopupPrompt();
	}
};


/* Reset some things for the next turn. */
void GameTab::Reset() {
	GameTab::Preview.clear();
	this->SelectedStone = this->Selection;
	this->SelectionMode = 0;
};


/* Player Turn Logic. */
void GameTab::PlayerTurn() {
	if (StackMill3DS::App->Repeat & KEY_LEFT) {
		this->Left((this->SelectionMode ? this->Selection : this->SelectedStone));
		if (!this->ShowPointer) this->ShowPointer = true;
	}

	if (StackMill3DS::App->Repeat & KEY_RIGHT) {
		this->Right((this->SelectionMode ? this->Selection : this->SelectedStone));
		if (!this->ShowPointer) this->ShowPointer = true;
	}

	if (StackMill3DS::App->Repeat & KEY_UP) {
		this->Up((this->SelectionMode ? this->Selection : this->SelectedStone));
		if (!this->ShowPointer) this->ShowPointer = true;
	}

	if (StackMill3DS::App->Repeat & KEY_DOWN) {
		this->Down((this->SelectionMode ? this->Selection : this->SelectedStone));
		if (!this->ShowPointer) this->ShowPointer = true;
	}

	/* Helper / Rules book. */
	if (StackMill3DS::App->Down & KEY_SELECT) {
		std::unique_ptr<Rules> Ovl = std::make_unique<Rules>();
		Ovl->Handler();
		return;
	}
	if (StackMill3DS::App->Down & KEY_TOUCH) {
		if (this->Help.Touched(StackMill3DS::App->T)) {
			std::unique_ptr<Rules> Ovl = std::make_unique<Rules>();
			Ovl->Handler();
			return;
		}
	}

	if (StackMill3DS::App->Core->InRemove()) this->RemoveAction(); // We are in the remove action.
	else {
		/* If Move / Jump Phase, try to go to stone selection. */
		if (StackMill3DS::App->Down & KEY_B) {
			if (!this->StartMode) {
				if (!this->ShowPointer) this->ShowPointer = true;

				if (this->SelectionMode) {
					this->SelectionMode = 0;
					GameTab::Preview.clear();
				}
			}
		}

		if (StackMill3DS::App->Down & KEY_TOUCH) {
			for (int8_t Idx = 0; Idx < 24; Idx++) {
				if (this->Fields[Idx].Touched(StackMill3DS::App->T)) {
					if (this->ShowPointer) this->ShowPointer = false;

					/* If Move / Jump Phase, try to go to Stone Selection. */
					if (!this->StartMode) {
						if (!this->SelectionMode) {

							if (StackMill3DS::App->Core->Good(Idx, (StackMill3DS::App->Core->CurrentPlayer() == 1) ? StackMill::GameStone::White : StackMill::GameStone::Black)) {

								this->SelectedStone = Idx;
								GameTab::Preview = StackMill3DS::App->Core->PlayablePositions(this->SelectedStone, StackMill3DS::App->Core->Phase((StackMill3DS::App->Core->CurrentPlayer() == 1) ? StackMill::GameStone::White : StackMill::GameStone::Black));

								if (!GameTab::Preview.empty()) {
									this->SelectionMode = 1;
									this->Selection = this->SelectedStone;
								}

								break;
							} else continue;
						}
					}

					/* In case Pos and Stone Selection are the same, go back to Stone Selection. */
					if (Idx == this->SelectedStone) {
						if (!this->StartMode) {
							if (this->SelectionMode) {
								this->SelectionMode = 0;
								GameTab::Preview.clear();
							}

							break;
						}
					}

					/* Check if the specific play can be done. */
					if (StackMill3DS::App->Core->CanDoSpecifiedPlay(this->SelectedStone, Idx, StackMill3DS::App->Core->Phase((StackMill3DS::App->Core->CurrentPlayer() == 1) ? StackMill::GameStone::White : StackMill::GameStone::Black))) {
						this->Selection = Idx;

						/* Here the animation. */
						switch(StackMill3DS::App->Core->Phase((StackMill3DS::App->Core->CurrentPlayer() == 1) ? StackMill::GameStone::White : StackMill::GameStone::Black)) {
							case StackMill::Phases::Set:
								this->Place();
								break;

							case StackMill::Phases::Move:
								this->Move();
								break;

							case StackMill::Phases::Jump:
								this->Jump();
								break;
						}

						const StackMill::PlayStatus Status = StackMill3DS::App->Core->Play(this->SelectedStone, this->Selection);

						/* Here the PlayStatus Handle. */
						switch(Status) {
							case StackMill::PlayStatus::Normal:
								StackMill3DS::App->Core->NextPlayer();
								this->Reset();
								this->StartMode = (StackMill3DS::App->Core->Phase((StackMill3DS::App->Core->CurrentPlayer() == 1) ? StackMill::GameStone::White : StackMill::GameStone::Black) == StackMill::Phases::Set);

								if (this->StartMode) this->SelectionMode = 1;
								this->CheckStatus();
								break;

							case StackMill::PlayStatus::Match:
								GameTab::Preview = StackMill3DS::App->Core->RemoveableStones((StackMill3DS::App->Core->CurrentPlayer() == 1) ? StackMill::GameStone::Black : StackMill::GameStone::White);
								StackMill3DS::App->Core->InRemove(true);
								break;

							case StackMill::PlayStatus::Invalid:
								break;
						}

						break;
					}
				}
			}
		}

		if (StackMill3DS::App->Down & KEY_A) {
			if (!this->ShowPointer) this->ShowPointer = true;

			if (!this->StartMode) {
				if (!this->SelectionMode) {
					if (StackMill3DS::App->Core->Good(this->SelectedStone, (StackMill3DS::App->Core->CurrentPlayer() == 1) ? StackMill::GameStone::White : StackMill::GameStone::Black)) {
						GameTab::Preview = StackMill3DS::App->Core->PlayablePositions(this->SelectedStone, StackMill3DS::App->Core->Phase((StackMill3DS::App->Core->CurrentPlayer() == 1) ? StackMill::GameStone::White : StackMill::GameStone::Black));

						if (!GameTab::Preview.empty()) {
							this->SelectionMode = 1;
							this->Selection = this->SelectedStone;
						}
					}

					return;
				}
			}

			/* In case Pos and Stone Selection are the same, go back to Stone Selection. */
			if (this->Selection == this->SelectedStone) {
				if (!this->StartMode) {
					if (this->SelectionMode) {
						this->SelectionMode = 0;
						GameTab::Preview.clear();
					}

					return;
				}
			}

			/* Check if the specific play can be done. */
			if (StackMill3DS::App->Core->CanDoSpecifiedPlay(this->SelectedStone, this->Selection, StackMill3DS::App->Core->Phase((StackMill3DS::App->Core->CurrentPlayer() == 1) ? StackMill::GameStone::White : StackMill::GameStone::Black))) {

				/* Here the animation. */
				switch(StackMill3DS::App->Core->Phase((StackMill3DS::App->Core->CurrentPlayer() == 1) ? StackMill::GameStone::White : StackMill::GameStone::Black)) {
					case StackMill::Phases::Set:
						this->Place();
						break;

					case StackMill::Phases::Move:
						this->Move();
						break;

					case StackMill::Phases::Jump:
						this->Jump();
						break;
				}

				const StackMill::PlayStatus Status = StackMill3DS::App->Core->Play(this->SelectedStone, this->Selection);

				/* Here the PlayStatus Handle. */
				switch(Status) {
					case StackMill::PlayStatus::Normal:
						StackMill3DS::App->Core->NextPlayer();
						this->Reset();
						this->StartMode = (StackMill3DS::App->Core->Phase((StackMill3DS::App->Core->CurrentPlayer() == 1) ? StackMill::GameStone::White : StackMill::GameStone::Black) == StackMill::Phases::Set);
						if (this->StartMode) this->SelectionMode = 1;
						this->CheckStatus();
						break;

					case StackMill::PlayStatus::Match:
						GameTab::Preview = StackMill3DS::App->Core->RemoveableStones((StackMill3DS::App->Core->CurrentPlayer() == 1) ? StackMill::GameStone::Black : StackMill::GameStone::White);
						StackMill3DS::App->Core->InRemove(true);
						break;

					case StackMill::PlayStatus::Invalid:
						break;
				}
			}
		}
	}
};


/* The AI Handler. */
void GameTab::AITurn() {
	GameTab::Preview.clear();

	/* Do the turn. */
	std::pair<int8_t, int8_t> Turn = (SettingsTab::AI == 1 ? StackMill3DS::App->Core->AIRandomPlay() : StackMill3DS::App->Core->AI5050());
	bool Status = false;

	/* Animation + Set Action. */
	switch(StackMill3DS::App->Core->Phase((StackMill3DS::App->Core->CurrentPlayer() == 1) ? StackMill::GameStone::White : StackMill::GameStone::Black)) {
		case StackMill::Phases::Set:
			if (Turn.second > -1) {
				this->Selection = Turn.second;
				this->Place();
				Status = true;
			}
			break;

		case StackMill::Phases::Move:
			if (Turn.first > -1 && Turn.second > -1) {
				this->SelectedStone = Turn.first;
				this->Selection = Turn.second;
				this->Move();
				Status = true;
			}
			break;

		case StackMill::Phases::Jump:
			if (Turn.first > -1 && Turn.second > -1) {
				this->SelectedStone = Turn.first;
				this->Selection = Turn.second;
				this->Jump();
				Status = true;
			}
	}

	if (Status) {
		const StackMill::PlayStatus PStatus = StackMill3DS::App->Core->Play(this->SelectedStone, this->Selection);

		/* Play Status Handler. */
		switch(PStatus) {
			case StackMill::PlayStatus::Normal:
				StackMill3DS::App->Core->NextPlayer();
				this->Reset();
				this->StartMode = (StackMill3DS::App->Core->Phase((StackMill3DS::App->Core->CurrentPlayer() == 1) ? StackMill::GameStone::White : StackMill::GameStone::Black) == StackMill::Phases::Set);
				if (this->StartMode) this->SelectionMode = 1;
				this->CheckStatus();
				break;

			case StackMill::PlayStatus::Match: {
				/* Select the Stone to remove randomly. */
				this->Selection = StackMill3DS::App->Core->AIStoneRemove();
				if (this->Selection > -1) {
					this->Remove();

					const StackMill::RemoveState State = StackMill3DS::App->Core->StoneRemove(this->Selection, (StackMill3DS::App->Core->CurrentPlayer() == 1 ? StackMill::GameStone::Black : StackMill::GameStone::White));

					/* Remove Handler. */
					switch(State) {
						case StackMill::RemoveState::Lost:
							this->Winner = StackMill3DS::App->Core->CurrentPlayer();
							this->PopupPrompt();
							break;

						case StackMill::RemoveState::Removed:
							StackMill3DS::App->Core->NextPlayer();
							this->Reset();
							this->StartMode = (StackMill3DS::App->Core->Phase((StackMill3DS::App->Core->CurrentPlayer() == 1) ? StackMill::GameStone::White : StackMill::GameStone::Black) == StackMill::Phases::Set);
							if (this->StartMode) this->SelectionMode = 1;
							this->CheckStatus();
							break;

						case StackMill::RemoveState::Invalid:
							break;
					}
				}

				break;
			}

			case StackMill::PlayStatus::Invalid:
				break;
		}
	}

	GameTab::Preview.clear();
};


void GameTab::Handler() {
	if (Tab::TabSwitch || SettingsTab::Swipe) return; // No Input.

	if (StackMill3DS::App->Down & KEY_START && StackMill3DS::App->Down & KEY_X) this->AIvsAI = !this->AIvsAI;

	if (this->AIvsAI) this->AITurn();
	else {
		/* If Player 2, it's Player 2 (If 0) or AI's mode (If 1 or 2). */
		if (StackMill3DS::App->Core->CurrentPlayer() == 2) {
			if (SettingsTab::AI > 0) {
				this->AITurn();
				return; // Return so we don't go to the Player Logic.
			}
		}

		this->PlayerTurn();
	}
};


/* Move the stone with cubic bezier. */
void GameTab::Move() {
	int8_t Direction = -1; // Direction to move the Stone.
	int ToMove = 0, Pos = 0; // ToMove: The amount to move, Pos: The Stone additional Position.
	bool Done = false; // Animation done.

	/* Ensure X is not the same between start and destination. */
	if (this->Fields[this->SelectedStone].x != this->Fields[this->Selection].x) {

		/* Destination is larger than the start, so go to the right. */
		if (this->Fields[this->SelectedStone].x < this->Fields[this->Selection].x) {
			ToMove = this->Fields[this->Selection].x - this->Fields[this->SelectedStone].x;
			Direction = 1; // ->

		} else { // Destination is smaller than the start, so go to the left.
			ToMove = this->Fields[this->SelectedStone].x - this->Fields[this->Selection].x;
			Direction = 3; // <-
		}

	} else {
		/* Ensure Y is not the same between start and destination. */
		if (this->Fields[this->SelectedStone].y != this->Fields[this->Selection].y) {

			/* Destination is larger than the start, so go down. */
			if (this->Fields[this->SelectedStone].y < this->Fields[this->Selection].y) {
				ToMove = this->Fields[this->Selection].y - this->Fields[this->SelectedStone].y;
				Direction = 2; // ↓

			} else { // Destination is smaller than the start, so go up.
				ToMove = this->Fields[this->SelectedStone].y - this->Fields[this->Selection].y;
				Direction = 0; // ^
			}
		}
	}

	/* If Direction is not -1, aka start and destination being the same, don't do this. */
	if (Direction != -1) {
		while(aptMainLoop() && !Done) {
			C2D_TargetClear(Top, C2D_Color32(0, 0, 0, 0));
			C2D_TargetClear(Bottom, C2D_Color32(0, 0, 0, 0));
			Gui::clearTextBufs();
			C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

			StackMill3DS::App->DrawTop();
			StackMill3DS::App->GData->DrawBottom();
			StackMill3DS::App->DrawTab();
			StackMill3DS::App->GData->DrawSprite(sprites_field_idx, 50, 20);

			/* Draw the Stones. */
			for (int8_t Idx = 0; Idx < 24; Idx++) {
				/* Draw the Stone to animate. */
				if (Idx == this->SelectedStone) {
					switch(Direction) {
						case 0: // ^
							StackMill3DS::App->GData->DrawStone(SettingsTab::StoneColors[StackMill3DS::App->Core->Field(Idx) == StackMill::GameStone::Black], this->Fields[Idx].x, this->Fields[Idx].y - Pos);
							break;

						case 1: // ->
							StackMill3DS::App->GData->DrawStone(SettingsTab::StoneColors[StackMill3DS::App->Core->Field(Idx) == StackMill::GameStone::Black], this->Fields[Idx].x + Pos, this->Fields[Idx].y);
							break;

						case 2: // ↓
							StackMill3DS::App->GData->DrawStone(SettingsTab::StoneColors[StackMill3DS::App->Core->Field(Idx) == StackMill::GameStone::Black], this->Fields[Idx].x, this->Fields[Idx].y + Pos);
							break;

						case 3: // <-
							StackMill3DS::App->GData->DrawStone(SettingsTab::StoneColors[StackMill3DS::App->Core->Field(Idx) == StackMill::GameStone::Black], this->Fields[Idx].x - Pos, this->Fields[Idx].y);
							break;
					}

				/* Draw all the other Stones without animation. */
				} else {
					if (StackMill3DS::App->Core->Field(Idx) != StackMill::GameStone::None) {
						StackMill3DS::App->GData->DrawStone(SettingsTab::StoneColors[StackMill3DS::App->Core->Field(Idx) == StackMill::GameStone::Black], this->Fields[Idx].x, this->Fields[Idx].y);
					}
				}
			}

			StackMill3DS::App->GData->DrawSprite(sprites_help_idx, this->Help.x, this->Help.y);
			C3D_FrameEnd(0);
			Pos = std::lerp(Pos, ToMove + 0.1f, 0.1f); // cubic bezier animation for the Stone to move.
			Pos++;

			if (Pos >= ToMove) Done = true;
		}
	}
};


/* Scale the stone out with cubic bezier animation. */
void GameTab::Remove() {
	bool Done = false;
	float Scale = 0.0f;

	while(aptMainLoop() && !Done) {
		C2D_TargetClear(Top, C2D_Color32(0, 0, 0, 0));
		C2D_TargetClear(Bottom, C2D_Color32(0, 0, 0, 0));
		Gui::clearTextBufs();
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

		StackMill3DS::App->DrawTop();
		StackMill3DS::App->GData->DrawBottom();
		StackMill3DS::App->DrawTab();
		StackMill3DS::App->GData->DrawSprite(sprites_field_idx, 50, 20);

		/* Draw the Stones. */
		for (int8_t Idx = 0; Idx < 24; Idx++) {
			/* Draw the Stone to scale out. */
			if (Idx == this->Selection) {
				if (Scale >= 0.0f) {
					StackMill3DS::App->GData->DrawStone(SettingsTab::StoneColors[StackMill3DS::App->Core->Field(Idx) == StackMill::GameStone::Black], this->Fields[Idx].x, this->Fields[Idx].y, 1.0f - Scale, 1.0f - Scale);
				}

			/* Draw all the other Stones. */
			} else {
				if (StackMill3DS::App->Core->Field(Idx) != StackMill::GameStone::None) {
					StackMill3DS::App->GData->DrawStone(SettingsTab::StoneColors[StackMill3DS::App->Core->Field(Idx) == StackMill::GameStone::Black], this->Fields[Idx].x, this->Fields[Idx].y);
				}
			}
		}

		/* Draw Side Stones. */
		for (int8_t Idx = 0; Idx < 9; Idx++) {
			if (StackMill3DS::App->Core->Position(StackMill::GameStone::White, Idx) == -1) {
				StackMill3DS::App->GData->DrawStone(SettingsTab::StoneColors[0], (Idx % 2 == 0 ? 5 + Tab::GameOffset : 30 + Tab::GameOffset), 40 + (Idx / 2 * 30));
			}

			if (StackMill3DS::App->Core->Position(StackMill::GameStone::Black, Idx) == -1) {
				StackMill3DS::App->GData->DrawStone(SettingsTab::StoneColors[1], (Idx % 2 == 0 ? 270 + Tab::GameOffset : 295 + Tab::GameOffset), 40 + (Idx / 2 * 30));
			}
		}

		StackMill3DS::App->GData->DrawSprite(sprites_help_idx, this->Help.x, this->Help.y);
		C3D_FrameEnd(0);
		gspWaitForVBlank();
		Scale = std::lerp(Scale, 1.1f, 0.1f); // cubic bezier animation for the Stone to remove.

		if (Scale >= 1.0f) Done = true;
	}
};


/* Scale the stone in with cubic bezier animation. */
void GameTab::Place() {
	bool Done = false;
	float Scale = 0.0f;

	while(aptMainLoop() && !Done) {
		C2D_TargetClear(Top, C2D_Color32(0, 0, 0, 0));
		C2D_TargetClear(Bottom, C2D_Color32(0, 0, 0, 0));
		Gui::clearTextBufs();
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

		StackMill3DS::App->DrawTop();
		StackMill3DS::App->GData->DrawBottom();
		StackMill3DS::App->DrawTab();
		StackMill3DS::App->GData->DrawSprite(sprites_field_idx, 50, 20);

		/* Draw the Stones. */
		for (int8_t Idx = 0; Idx < 24; Idx++) {
			/* Draw the to placed Stone. */
			if (Idx == this->Selection) {
				StackMill3DS::App->GData->DrawStone(SettingsTab::StoneColors[StackMill3DS::App->Core->CurrentPlayer() - 1], this->Fields[Idx].x, this->Fields[Idx].y, Scale, Scale);

			/* Draw all the other Stones. */
			} else {
				if (StackMill3DS::App->Core->Field(Idx) != StackMill::GameStone::None) {
					StackMill3DS::App->GData->DrawStone(SettingsTab::StoneColors[StackMill3DS::App->Core->Field(Idx) == StackMill::GameStone::Black], this->Fields[Idx].x, this->Fields[Idx].y);
				}
			}
		}

		/* Side Stones. */
		for (int8_t Idx = 0; Idx < 9; Idx++) {
			bool ContinueDraw = true;

			if (StackMill3DS::App->Core->CurrentPlayer() == 1) {
				if (StackMill3DS::App->Core->PlayerIdx(StackMill::GameStone::White) == Idx) {
					StackMill3DS::App->GData->DrawStone(SettingsTab::StoneColors[0], (Idx % 2 == 0 ? 5 + Tab::GameOffset : 30 + Tab::GameOffset), 40 + (Idx / 2 * 30), 1.0f - Scale, 1.0f - Scale);
					ContinueDraw = false;
				}
			}

			if (ContinueDraw) {
				if (StackMill3DS::App->Core->Position(StackMill::GameStone::White, Idx) == -1) {
					StackMill3DS::App->GData->DrawStone(SettingsTab::StoneColors[0], (Idx % 2 == 0 ? 5 + Tab::GameOffset : 30 + Tab::GameOffset), 40 + (Idx / 2 * 30));
				}
			}

			ContinueDraw = true;

			if (StackMill3DS::App->Core->CurrentPlayer() == 2) {
				if (StackMill3DS::App->Core->PlayerIdx(StackMill::GameStone::Black) == Idx) {
					StackMill3DS::App->GData->DrawStone(SettingsTab::StoneColors[1], (Idx % 2 == 0 ? 270 + Tab::GameOffset : 295 + Tab::GameOffset), 40 + (Idx / 2 * 30), 1.0f - Scale, 1.0f - Scale);
					ContinueDraw = false;
				}
			}

			if (ContinueDraw) {
				if (StackMill3DS::App->Core->Position(StackMill::GameStone::Black, Idx) == -1) {
					StackMill3DS::App->GData->DrawStone(SettingsTab::StoneColors[1], (Idx % 2 == 0 ? 270 + Tab::GameOffset : 295 + Tab::GameOffset), 40 + (Idx / 2 * 30));
				}
			}
		}

		StackMill3DS::App->GData->DrawSprite(sprites_help_idx, this->Help.x, this->Help.y);
		C3D_FrameEnd(0);
		Scale = std::lerp(Scale, 1.1f, 0.1f); // cubic bezier animation for the Stone to place.

		if (Scale >= 1.0f) Done = true;
	}
};


/* Scale the old stone out and new stone in at the same time with cubic bezier animation. */
void GameTab::Jump() {
	bool Done = false;
	float Scale = 0.0f;

	while(aptMainLoop() && !Done) {
		C2D_TargetClear(Top, C2D_Color32(0, 0, 0, 0));
		C2D_TargetClear(Bottom, C2D_Color32(0, 0, 0, 0));
		Gui::clearTextBufs();
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

		StackMill3DS::App->DrawTop();
		StackMill3DS::App->GData->DrawBottom();
		StackMill3DS::App->DrawTab();
		StackMill3DS::App->GData->DrawSprite(sprites_field_idx, 50, 20);

		/* Draw the Stones. */
		for (int8_t Idx = 0; Idx < 24; Idx++) {
			/* Draw the new positioned Stone. */
			if (Idx == this->Selection) {
				StackMill3DS::App->GData->DrawStone(SettingsTab::StoneColors[StackMill3DS::App->Core->CurrentPlayer() - 1], this->Fields[Idx].x, this->Fields[Idx].y, Scale, Scale);

			/* Draw the old positioned Stone. */
			} else if (Idx == this->SelectedStone) {
				StackMill3DS::App->GData->DrawStone(SettingsTab::StoneColors[StackMill3DS::App->Core->CurrentPlayer() - 1], this->Fields[Idx].x, this->Fields[Idx].y, 1.0f - Scale, 1.0f - Scale);

			/* Draw all the other Stones. */
			} else {
				if (StackMill3DS::App->Core->Field(Idx) != StackMill::GameStone::None) {
					StackMill3DS::App->GData->DrawStone(SettingsTab::StoneColors[StackMill3DS::App->Core->Field(Idx) == StackMill::GameStone::Black], this->Fields[Idx].x, this->Fields[Idx].y);
				}
			}
		}

		/* Draw Side Stones. */
		for (int8_t Idx = 0; Idx < 9; Idx++) {
			if (StackMill3DS::App->Core->Position(StackMill::GameStone::White, Idx) == -1) {
				StackMill3DS::App->GData->DrawStone(SettingsTab::StoneColors[0], (Idx % 2 == 0 ? 5 + Tab::GameOffset : 30 + Tab::GameOffset), 40 + (Idx / 2 * 30));
			}

			if (StackMill3DS::App->Core->Position(StackMill::GameStone::Black, Idx) == -1) {
				StackMill3DS::App->GData->DrawStone(SettingsTab::StoneColors[1], (Idx % 2 == 0 ? 270 + Tab::GameOffset : 295 + Tab::GameOffset), 40 + (Idx / 2 * 30));
			}
		}

		StackMill3DS::App->GData->DrawSprite(sprites_help_idx, this->Help.x, this->Help.y);
		C3D_FrameEnd(0);
		Scale = std::lerp(Scale, 1.1f, 0.1f); // cubic bezier animation for the Stone to "jump".

		if (Scale >= 1.0f) Done = true;
	}
};


/* Message prompt to start a new game or exit the app. */
void GameTab::PopupPrompt() {
	float Cubic = 0.0f, CubicAlpha = 0.0f;
	bool State = false, Done = false, SwipedIn = false, EndIt = false;
	int PromptPos = 240;
	uint8_t Alpha = 0;

	while(aptMainLoop() && !Done) {
		C2D_TargetClear(Top, C2D_Color32(0, 0, 0, 0));
		C2D_TargetClear(Bottom, C2D_Color32(0, 0, 0, 0));
		Gui::clearTextBufs();
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);

		StackMill3DS::App->DrawTop();
		Gui::Draw_Rect(0, 0, 400, 240, C2D_Color32(0, 0, 0, Alpha)); // Dim the top screen with the Alpha.
		StackMill3DS::App->GData->DrawBottom();
		StackMill3DS::App->DrawTab();
		StackMill3DS::App->GData->DrawSprite(sprites_field_idx, 50, 20);

		/* Draw the Stones. */
		for (int8_t Idx = 0; Idx < 24; Idx++) {
			if (StackMill3DS::App->Core->Field(Idx) != StackMill::GameStone::None) {
				StackMill3DS::App->GData->DrawStone(SettingsTab::StoneColors[StackMill3DS::App->Core->Field(Idx) == StackMill::GameStone::Black], this->Fields[Idx].x, this->Fields[Idx].y + (EndIt && State ? PromptPos : 0));
			}
		}

		if (EndIt && State) {
			/* Draw Side Stones. */
			for (int8_t Idx = 0; Idx < 9; Idx++) {
				StackMill3DS::App->GData->DrawStone(SettingsTab::StoneColors[0], (Idx % 2 == 0 ? 5 : 30) - 240 + PromptPos, 40 + (Idx / 2 * 30));

				StackMill3DS::App->GData->DrawStone(SettingsTab::StoneColors[1], (Idx % 2 == 0 ? 270 : 295) + 240 - PromptPos, 40 + (Idx / 2 * 30));
			}
		}

		StackMill3DS::App->GData->DrawSprite(sprites_help_idx, this->Help.x, this->Help.y);
		Gui::Draw_Rect(0, 0, 320, 240, C2D_Color32(0, 0, 0, Alpha)); // Dim the bottom screen with the Alpha.

		/* Show the winner. */
		switch(this->Winner) {
			case 0:
				Gui::DrawStringCentered(0, 50 + PromptPos, 0.5f, TEXT_COLOR, StackMill3DS::App->LH->Translation(LangHandler::Strings::MatchTie));
				break;

			case 1:
			case 2:
				Gui::DrawStringCentered(0, 50 + PromptPos, 0.5f, TEXT_COLOR, StackMill3DS::App->LH->Translation(LangHandler::Strings::Player) + " " + std::to_string(this->Winner) + " " + StackMill3DS::App->LH->Translation(LangHandler::Strings::Wins));
				break;
		}

		Gui::DrawStringCentered(0, 70 + PromptPos, 0.5f, TEXT_COLOR, StackMill3DS::App->LH->Translation(LangHandler::Strings::NextRound));

		/* Display Prompt Buttons. */
		for (int8_t Idx = 0; Idx < 2; Idx++) {
			Gui::Draw_Rect(this->Prompt[Idx].x, this->Prompt[Idx].y + PromptPos, this->Prompt[Idx].w, this->Prompt[Idx].h, BAR_COLOR);
			Gui::DrawStringCentered(this->Prompt[Idx].x - 160 + this->Prompt[Idx].w / 2, this->Prompt[Idx].y + 15 + PromptPos, 0.6f, TEXT_COLOR, (Idx == 0 ? StackMill3DS::App->LH->Translation(LangHandler::Strings::No) : StackMill3DS::App->LH->Translation(LangHandler::Strings::Yes)), this->Prompt[Idx].w - 10);
		}

		C3D_FrameEnd(0);

		/* Swipe the Prompt in. */
		if (!SwipedIn && !EndIt) {
			if (Cubic < 240.0f) {
				Cubic = std::lerp(Cubic, 241.0f, 0.1f);
				PromptPos = 240 - (int)Cubic;
				Alpha = Cubic;

				if (Cubic >= 240.0f) Cubic = 0.0f, PromptPos = 0, Alpha = 240, SwipedIn = true;
			}
		}

		/* Handle Input for the prompt. */
		if (SwipedIn && !EndIt) {
			hidScanInput();
			const uint32_t Down = hidKeysDown();
			touchPosition T;
			hidTouchRead(&T);

			if (Down & KEY_A) State = true, EndIt = true; // New Game.
			if (Down & KEY_B) State = false, EndIt = true; // Exit.

			if (Down & KEY_TOUCH) {
				if (this->Prompt[0].Touched(T)) State = false, EndIt = true; // Exit.
				else if (this->Prompt[1].Touched(T)) State = true, EndIt = true; // New Game.
			}
		}

		/* Swipe the Prompt out. If cancel -> Fade the screen out, else fade the screen in again and move the prompt buttons away. */
		if (EndIt) {
			if (Cubic < 240.0f) {
				Cubic = std::lerp(Cubic, 241.0f, 0.1f);
				PromptPos = (int)Cubic;
			}

			if (CubicAlpha < (State ? 240.0f : 10.0f)) {
				CubicAlpha = std::lerp(CubicAlpha, (State ? 241.0f : 11.0f), 0.1f);
				Alpha = (State ? 240 - CubicAlpha : 240 + CubicAlpha);
			}

			if (Cubic >= 240.0f && CubicAlpha >= (State ? 240.0f : 10.0f)) Done = true;
		}
	}

	if (State) this->NewGame();
	else StackMill3DS::App->Running = false;
};