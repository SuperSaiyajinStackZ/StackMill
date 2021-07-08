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

#ifndef _STACKMILL_LANG_HANDLER_HPP
#define _STACKMILL_LANG_HANDLER_HPP

#include <string>


class LangHandler {
public:
	enum class Strings : int8_t {
		Game = 0, Settings = 1, Credits = 2, GameSettings = 3, Language = 4, ImportExport = 5,
		Player1Color = 6, Player2Color = 7, PreviewColor = 8, Computer = 9, ImportGame = 10, ExportGame = 11,

		Splash = 12, DevBy = 13, Graphics = 14, SmilCore = 15, UnivCore = 16,
		Player = 17, StonesAvailable = 18, RemoveStone = 19, SetStone = 20, MoveStone = 21, JumpStone = 22, MatchTie = 23,
		Wins = 24, NextRound = 25, Yes = 26, No = 27,

		Rules1 = 28, Rules2 = 29, Rules3 = 30, Rules4 = 31, Rules5 = 32, Rules6 = 33, Rules7 = 34,
		Rules_1 = 35, Rules_2 = 36, Rules_3 = 37, Rules_4 = 38, Rules_5 = 39, Rules_6 = 40, Rules_7 = 41,

		Rules_1T = 42, Rules_2T = 43, Rules_3T = 44, Rules_4T = 45, Rules_5T = 46, Rules_6T = 47, Rules_7T = 48
	};

	enum class Langs : int8_t { English = 0, German = 1, Japanese = 2 };

	LangHandler(const LangHandler::Langs Lng);
	void LoadLang(const LangHandler::Langs Lng);

	std::string Translation(const LangHandler::Strings STR) const;
	int8_t GetLang() const { return (int8_t)this->ActiveLang; };
private:
	LangHandler::Langs ActiveLang = LangHandler::Langs::English;

	const std::string TranslationStrings[2][49] = {
		/* English. */
		{
			"Game", "Settings", "Credits", "Game Settings", "Language", "Import / Export",
			"Player 1 Stone Color", "Player 2 Stone Color", "Preview Play Color", "Computer Opponent (Disabled, Random, 50:50)",
			"Import Game", "Export Game",
			"StackMill developed by SuperSaiyajinStackZ.\nCopyright (c) 2021",
			"StackMill developed by SuperSaiyajinStackZ.", "Graphics: SuperSaiyajinStackZ",
			"StackMill-Core: SuperSaiyajinStackZ", "Universal-Core: Universal-Team",
			"Player", "Stones available: ", "Remove a Stone from your opponent.", "Set a Stone to a free intersection.",
			"Move a Stone around.", "Jump a Stone to a free intersection.",
			"This match is a tie!", "wins!", "Do you want to play another match?", "\uE000 Yes", "\uE001 No",

			"Main", "How to Play", "Phase 1", "Phase 2", "Phase 3", "Win Conditions", "Instructions",

			"Main ( 1 / 7 )", "How to Play ( 2 / 7 )", "Phase 1: Placing Stones ( 3 / 7 )", "Phase 2: Moving Stones ( 4 / 7 )",
			"Phase 3: 'Flying' / Jumping Stones ( 5 / 7 )", "Win conditions ( 6 / 7 )", "Instructions ( 7 / 7 )",

			/* Rule 1. */
			"StackMill is a clone of the Mill game.\n\n"
			"The game is also known under the following Synonym(s):\n"
			"Nine men's morris, or Nine-man morris\n"
			"Mill, mills, or the mill game\n"
			"Merels or merrills\n"
			"Merelles, marelles, or morelles\n"
			"Ninepenny marl\n"
			"Cowboy checkers\n\n"
			"Check out the other pages to read more about how the game works or also see the wikipedia site here: https://en.wikipedia.org/wiki/Nine_men%27s_morris.",

			/* Rule 2. */
			"Shortly explained the rules:\n"
			"- Both Players try to get 3 Stones in a row to form a so called 'Mill'.\n\n"
			"- After a Mill is formed, the Player can remove a Stone from the opponent.\n\n"
			"Keep in mind however, that you can not remove a Stone from a formed Mill from your opponent, except all the Stones are inside a Mill.\n\n"
			"The game contains 3 Phases, the next pages will explain those Phases.",

			/* Rule 3. */
			"This is the first Phase of the game which will be the case until all 9 Stones have been played.\n\n"
			"The first Player starts by placing a Stone on an intersection of the lines. Then the second Player does the same until all 9 Stones have been played.\n\n"
			"The goal in this Phase is to form a good way for the next Phase, so you can easilly move the Stones around.\n\n"
			"If all Stones are played, then the Game Phase will switch to the second Phase: Move.",

			/* Rule 4. */
			"This is the second Phase of the game which will be the case until a Player only has 3 Stones left.\n\n"
			"The first Player starts by moving a Stone to the left, right, up or down. Then the next Player will do the same as well.\n\n"
			"The same process happens the whole time now, and the goal in this Phase is to move the Stones in a good way, so the opponent possibly can not move anymore or will have 3 or less Stones.\n\n"
			"If a Player only has 3 Stones left, then it will switch to an exclusive Phase for that Player, and the Phase is: Jump.",

			/* Rule 5. */
			"This is the last Phase and is exclusive for Players with 3 Stones left.\n\n"
			"The Player can now jump Stones to any available Position.\n"
			"With this way, the Player is basically on the limits, because when the other Player reached a Mill, the Player lose.\n\n"
			"The goal of this Phase is to stop your opponent from forming Mills and try to reach a tie, by reducing the Stones from the opponent to 3 as well.\n\n"
			"The next page contains possible ways how to win a match",

			/* Rule 6. */
			"To win a match, one of the following conditions needs to happen:\n\n"
			"- Your opponent can not do a valid turn anymore and hence is basically locked.\n\n"
			"- Your opponent has 3 Stones left and you got a Mill, then you basically take one Stone away and your opponent can not form a Mill anymore.\n\n"
			"Keep in mind however, that a tie is also possible, if both Players have 3 Stones left.",

			/* Rule 7. */
			"The Instructions how to play the game are quite easy.\n\n"
			"- Phase 1: Tap a intersection from the lines to play a Stone.\n\n"
			"- Phase 2 & 3: Tap a Stone and tap on one of the highlighted Intersections to move / jump the Stone.\n\n"
			"- Remove: Tap a highlighted Stone to remove it.\n\n"
			"Keep in mind, that you can also use the D-Pad optionally, if you don't want to use touch."
		},

		/* German. */
		{
			"Spiel", "Einstellungen", "Credits", "Spiel-Einstellungen", "Sprache",
			"Import / Export",
			"Spieler 1 Steinfarbe", "Spieler 2 Steinfarbe", "Spielvorschau-Farbe", "Computer Gegner (Deaktiviert, Zufall, 50:50)",
			"Spiel Importieren", "Spiel Exportieren",
			"StackMill entwickelt von SuperSaiyajinStackZ.\nCopyright (c) 2021",
			"StackMill entwickelt von SuperSaiyajinStackZ.", "Grafiken: SuperSaiyajinStackZ",
			"StackMill-Core: SuperSaiyajinStackZ", "Universal-Core: Universal-Team",

			"Spieler", "Steine verfügbar: ", "Entferne einen Stein deines Gegners.", "Setze einen Stein zu einem freien Schnittpunkt.",
			"Bewege einen Stein.", "Springe einen Stein zu einem freien Schnittpunkt.",
			"Dieses Spiel ist ein Unentschieden!", "gewinnt!", "Willst du eine weitere Runde spielen?", "\uE000 Ja", "\uE001 Nein",

			"Haupt", "Spielanleitung", "Phase 1", "Phase 2", "Phase 3", "Gewinnbedingungen", "Anweisungen",

			"Haupt ( 1 / 7 )", "Spielanleitung ( 2 / 7 )", "Phase 1: Steine Platzieren ( 3 / 7 )", "Phase 2: Steine bewegen ( 4 / 7 )",
			"Phase 3: Steine 'Fliegen' / Springen ( 5 / 7 )", "Gewinnbedingungen ( 6 / 7 )", "Anweisungen ( 7 / 7 )",

			/* Rule 1. */
			"StackMill ist ein klon des Mühlen Spiels.\n\n"
			"Das Spiel ist ebenfalls unter den folgenden Synonymen bekannt:\n"
			"Nine men's morris, oder Nine-man morris\n"
			"Mill, mills, oder the mill game\n"
			"Merels oder merrills\n"
			"Merelles, marelles, oder morelles\n"
			"Ninepenny marl\n"
			"Cowboy checkers\n\n"
			"Schau dir die anderen Seiten an um zu erfahren wie das Spiel funktioniert oder schau dir die Wikipedia Seite hier an: https://de.wikipedia.org/wiki/M%C3%BChle_(Spiel).",

			/* Rule 2. */
			"Die Regeln kurz erklärt:\n"
			"- Beide Spieler versuchen 3 Steine in einer Reihe zu bilden um eine sogenannte 'Mühle' zu erhalten.\n\n"
			"- Nachdem eine Mühle geformt worden ist, kann der Spieler einen Stein des Gegners entfernen.\n\n"
			"Behalte jedoch im Kopf, dass du keinen Stein der in einer Mühle ist entfernen kannst, es sei denn, alle Steine sind in einer Mühle.\n\n"
			"Das Spiel besitzt 3 Phasen, die nächsten Seiten erklären die Phasen.",

			/* Rule 3. */
			"Dies ist die erste Phase des Spiels, welches der fall sein wird, bis alle 9 Steine gespielt worden sind.\n\n"
			"Der erste Spieler startet mit dem platzieren des ersten Steins an einem Schnittpunkt der Linien. Danach macht der zweite Spieler das selbe bis alle 9 Steine gespielt worden sind.\n\n"
			"Das Ziel in dieser Phase ist es eine gute Form zu bilden für die nächste Phase, damit du einfach deine Steine bewegen kannst.\n\n"
			"Falls alle Steine gespielt worden sind, geht es mit der nächsten Phase weiter: Bewegen.",

			/* Rule 4. */
			"Dies ist die zweite Phase des Spiels, welches der fall sein wird, bis ein Spieler nur noch 3 Steine übrig hat.\n\n"
			"Der erste Spieler startet mit dem bewegen eines Steines nach Links, Rechts, Oben oder Unten. Danach macht der nächste Spieler das selbe.\n\n"
			"Der selbe Prozess passiert die ganze zeit und das Ziel dieser Phase ist es die Steine in einem guten Weg zu bewegen, damit der Gegner möglicherwise nicht mehr bewegen kann oder nur noch 3 oder weniger Steine übrig hat.\n\n"
			"Falls ein Spieler nur noch 3 Steine übrig hat, wird der Spieler in einer exklusiven Phase gewechselt und die Phase ist: Springen.",

			/* Rule 5. */
			"Dies ist die letze Phase und ist exklusiv für Spieler die 3 Steine übrig haben.\n\n"
			"Der Spieler kann nun die Steine springen lassen zu jeder verfügbaren Position.\n"
			"Mit diesem weg, der Spieler ist quasi an seine Grenzen, weil wenn der andere Spieler eine Mühle erreicht ist das Spiel verloren.\n\n"
			"Das Ziel dieser Phase ist es den Gegner beim bilden von Mühlen zu stoppen und zu versuchen ein Unentschieden zu erreichen, in dem man die Steine des Gegners ebenfalls auf 3 Steine reduziert.\n\n"
			"Die nächste Seite besitzt mögliche wege, wie man das Spiel gewinnt.",

			/* Rule 6. */
			"Um das Spiel zu gewinnen, müssen die folgenden Bedienungen passieren:\n\n"
			"- Dein Gegner kann keinen validen zug mehr durchführen und ist damit blockiert.\n\n"
			"- Dein Gegner hat nur noch 3 Steine übrig und du bekommst eine Mühle, dann nimmst du theoretisch einen Stein weg und dein Gegner kann keine Mühle mehr bilden.\n\n"
			"Behalte jedoch im Kopf, dass ein Unentschieden ebenfalls möglich ist, falls beide Spieler 3 Steine übrig haben.",

			/* Rule 7. */
			"Die Anweisungen wie das Spiel funktioniert sind ziemlich einfach.\n\n"
			"- Phase 1: Berühre einen Schnittpunkt um einen Stein zu platzieren.\n\n"
			"- Phase 2 & 3: Berühre einen Stein und dann eine der hervorgehobenen Schnittpunkte zum bewegen / springen eines Steines.\n\n"
			"- Entfernen: Berühre einen hervorgehobenen Stein um ihn zu entfernen.\n\n"
			"Behalte jedoch im Kopf, dass du ebenfalls das Steuerkreuz benutzen kannst, falls du nicht den touchscreen benutzen willst."
		}
	};
};

#endif