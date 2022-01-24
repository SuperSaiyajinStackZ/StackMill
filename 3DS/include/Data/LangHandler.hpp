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

		Rules_1T = 42, Rules_2T = 43, Rules_3T = 44, Rules_4T = 45, Rules_5T = 46, Rules_6T = 47, Rules_7T = 48,
		Translators = 49
	};

	enum class Langs : int8_t { English = 0, German = 1, Japanese = 2, Italian = 3 };

	LangHandler();
	void LoadLang(const LangHandler::Langs Lng);

	std::string Translation(const LangHandler::Strings STR) const;
	int8_t GetLang() const { return (int8_t)this->ActiveLang; };
	LangHandler::Langs GetLangEnum() const { return this->ActiveLang; };
private:
	LangHandler::Langs ActiveLang = LangHandler::Langs::English;

	const std::string TranslationStrings[4][50] = {
		/* English. */
		{
			"Game", "Settings", "Credits", "Game Settings", "Language", "Import / Export",
			"Player 1 Stone Color", "Player 2 Stone Color", "Play Preview Color", "Computer Opponent (Disabled, Random, 50:50)",
			"Import Game", "Export Game",
			"StackMill developed by SuperSaiyajinStackZ.\nCopyright (c) 2021-2022",
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
			"The game is also known under the following Synonyms:\n"
			"Nine Men's Morris, Nine-Man Morris,\n"
			"Mill, Mills, The Mill Game,\n"
			"Merels, Merrills,\n"
			"Merelles, Marelles, Morelles,\n"
			"Ninepenny Marl,\n"
			"and Cowboy Checkers.\n\n"
			"Check out the other pages to read more about how the game works or also see the wikipedia site here: https://en.wikipedia.org/wiki/Nine_men%27s_morris.",

			/* Rule 2. */
			"Shortly explained the rules:\n"
			"- Both Players try to get 3 Stones in a row to form a so called 'Mill'.\n\n"
			"- After a Mill is formed, the Player can remove a Stone from the opponent.\n\n"
			"Keep in mind however, you cannot remove a Stone from a formed Mill unless all of the Stones are inside a Mill.\n\n"
			"The game contains 3 Phases, the next pages will explain those Phases.",

			/* Rule 3. */
			"This is the first Phase of the game which will be the case until all 9 Stones have been played.\n\n"
			"The first Player starts by placing a Stone on an intersection of the lines. Then the second Player does the same until all 9 Stones have been played.\n\n"
			"The goal in this Phase is to form a good layout for the next Phase, so you can easily move the Stones around.\n\n"
			"If all Stones are played, then the Game Phase will switch to the second Phase: Move.",

			/* Rule 4. */
			"This is the second Phase of the game which will be the case until a Player only has 3 Stones left.\n\n"
			"The first Player starts by moving a Stone to the left, right, up or down. Then the next Player will do the same as well.\n\n"
			"That process is now repeated for the rest of the Phase, and the goal in this Phase is to move the Stones such that the opponent cannot possibly move anymore or will have 3 or fewer Stones.\n\n"
			"If a Player only has 3 Stones left, then it will switch to an exclusive Phase for that Player, and the Phase is: Jump.",

			/* Rule 5. */
			"This is the last Phase and is exclusive for Players with 3 Stones left.\n\n"
			"The Player can now jump Stones to any available Position.\n"
			"This is to give the Player a chance to recover, as the other Player only needs to reach one more Mill to win the game.\n\n"
			"The goal of this Phase is to stop your opponent from forming Mills and try to reach a tie, by reducing the opponent's Stones to 3 as well.\n\n"
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
			"Keep in mind, that you can also use the D-Pad optionally, if you don't want to use touch.",

			"Translators"
		},

		/* German. */
		{
			"Spiel", "Einstellungen", "Credits", "Spiel-Einstellungen", "Sprache", "Import / Export",
			"Spieler 1 Steinfarbe", "Spieler 2 Steinfarbe", "Spielvorschau-Farbe", "Computer Gegner (Deaktiviert, Zufall, 50:50)",
			"Spiel Importieren", "Spiel Exportieren",
			"StackMill entwickelt von SuperSaiyajinStackZ.\nCopyright (c) 2021-2022",
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
			"Nine men's morris, Nine-man morris\n"
			"Mill, mills, the mill game\n"
			"Merels merrills\n"
			"Merelles, marelles, morelles\n"
			"Ninepenny marl\n"
			"und Cowboy checkers.\n\n"
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
			"Behalte jedoch im Kopf, dass du ebenfalls das Steuerkreuz benutzen kannst, falls du nicht den touchscreen benutzen willst.",

			"Übersetzer"
		},

		/* Japanese. */
		{
			"ゲーム", "設定", "クレジット", "ゲーム設定", "言語", "インポート・エクスポート",
			"プレイヤー1の石の色", "プレイヤー2の石の色", "プレイプレビューの色", "コンピューター対戦相手（無効、ランダム、50:50）",
			"ゲームをインポート", "ゲームをエクスポート",
			"StackMillはSuperSaiyajinStackZによって開発しました。\n著作権 © 2021-2022",
			"StackMillはSuperSaiyajinStackZによって開発しました。", "グラフィックス: SuperSaiyajinStackZ",
			"StackMill-Core: SuperSaiyajinStackZ", "Universal-Core: Universal-Team",
			"プレイヤー", "利用可能な石: ", "対戦相手から石を取り除く。", "自由な交差点に石を置きます。",
			"石を動かします。", "石を自由な交差点にジャンプします。",
			"この試合は引き分けです！", "が勝ちます！", "もう1つの試合がしたいですか？", "\uE000 はい", "\uE001 いいえ",

			"メイン", "プレイ方法", "第1段階", "第2段階", "第3段階", "勝利条件", "手順",

			"メイン（1/7）", "プレイ方法（2/7）", "第1段階: 石を置く（3/7）", "第2段階: 石を動かす（4/7）",
			"第3段階: 「フライング」／石をジャンプ（5/7）", "勝利条件（6/7）", "手順（7/7）",

			/* Rule 1. */
			"StackMillは『ミル(Mill)』ゲームのクローンです。\n\n"
			"英語にはゲームが以下の同意語でも知られています:\n"
			"Nine Men's Morris、Nine-Man Morris、\n"
			"Mill、Mills、The Mill Game、\n"
			"Merels、Merrills、\n"
			"Merelles、Marelles、Morelles、\n"
			"Ninepenny Marl、\n"
			"およびCowboy Checkers。\n\n"
			"ゲームの仕組みについて詳しくは、\n他のページまたは次のウィキペディアのページもご覧ください: https://ja.wikipedia.org/wiki/ナイン・メンズ・モリス",

			/* Rule 2. */
			"簡単に説明すると、ルールは:\n"
			"- 両方のプレイヤーは、いわゆる「ミル」を形成するために\n3つの石を続けて取得しようします。\n\n"
			"- ミルが形成された後に、プレイヤーが対戦相手から\n石を取り除くことができます。\n\n"
			"ただし、すべての石がミルの中に入っていない限り、\n形成されたミルから石を取り除くことができませんにご注意してください。\n\n"
			"ゲームに3段階があり、次のページではその段階について説明します。",

			/* Rule 3. */
			"これはゲームの最初の段階であり、\n9つの石がすべてプレイされるまで続きます。\n\n"
			"最初のプレイヤーは線の交差点に石を置くことから始めます。\n次に2番目のプレイヤーは9つの石がすべて\nプレイされるまで同じことを行います。\n\n"
			"この段階の目標は、次の段階に向けて良い配置を形成することです。\nこれにより、石を簡単に動かされます。\n\n"
			"すべての石がプレイされると、ゲーム段階は第2段階に切り替わります: 動かす",

			/* Rule 4. */
			"これはゲームの第2段階であり、\nどちらかのプレイヤーの石が3つしか残っていないまで続きます。\n\n"
			"最初のプレイヤーは石を左・右・上・下で動かすことから始めます。\n次に2番目のプレイヤーは同じことを行います。\n\n"
			"それは段階の終わりまで繰り返し、\n段階の目標は対戦相手がこれ以上動かすことができないように、\nまたは3つ以下の石を持つように石を動かすことです。\n\n"
			"プレイヤーの石が3つしか残っていないと、\nそのプレイヤー専用の段階に切り替わります。その段階は: ジャンプ",

			/* Rule 5. */
			"これはゲームの最終の段階であり、\n3つの石しか残っていないプレイヤーで専用です。\n\n"
			"今では、プレイヤーは石を利用可能な任意の\n位置にジャンプすることができます。\n"
			"これは、他のプレイヤーがゲーム勝つにもう1つのミルに到達する\nだけでため、プレイヤーにカムバックする機会を与えるためです。\n\n"
			"この段階の目標は、対戦相手がミルを形成するを防ぎ、\n対戦相手の石を3つに減らすことで引き分けに到達しようとすることです。\n\n"
			"次のページには、試合に勝つための可能な方法が含まれています。",

			/* Rule 6. */
			"試合に勝つには、次のいずれかの条件が発生する必要があります:\n\n"
			"- 対戦相手は有効なターンを行うことができなかったため、\n閉じ込められました。\n\n"
			"- 対戦相手の石が3つしか残っていて、\nミルを形成した場合には、1つの石を奪うと、\n対戦相手はもうミルを形成できなくなります。\n\n"
			"ただし、両方のプレイヤーの石が3つしか残っていないと、\n引き分け可能性がありますにご注意してください。",

			/* Rule 7. */
			"ゲームをプレイする手順はとても簡単です。\n\n"
			"- 第1段階: 交差点をタップして石をプレイします。\n\n"
			"- 第2と第3段階: 石をタップし、強調表示される交差点を1つタップして、\n石を動かします・ジャンプします。\n\n"
			"- 取り除く: 強調表示される石をタップして取り除きます。\n\n"
			"タッチを使用したくない場合は、\nオプションで十字キーを使用できますにご注意してください。",

			"翻訳者"
		},
		
		/* Italian. */
		{
			"Gioco", "Impostazioni", "Crediti", "Impostazioni del gioco", "Lingua", "Importa / Esporta",
			"Colore del pezzo del giocatore 1", "Colore del pezzo del giocatore", "Colore anteprima", "Avversario CPU (Disabilitato, Casuale, 50:50)",
			"Importa partita", "Esporta partita",
			"StackMill sviluppato da SuperSaiyajinStackZ.\nCopyright (c) 2021-2022",
			"StackMill sviluppato da SuperSaiyajinStackZ.", "Grafica: SuperSaiyajinStackZ",
			"StackMill-Core: SuperSaiyajinStackZ", "Universal-Core: Universal-Team",
			"Giocatore", "Pezzi disponibili: ", "Rimuovi uno dei pezzi dell'avversario.", "Posiziona un pezzo in un incrocio.",
			"Muovi un pezzo.", "Posiziona un pezzo in un incrocio.", // I've found no difference between "Jump" and "Move" in Italian
			"Pareggio!", "vince!", "Vuoi giocare ancora?", "\uE000 Sì", "\uE001 No",

			"Inizio", "Come si gioca", "Fase 1", "Fase 2", "Fase 3", "Come vincere", "Istruzioni",

			"Inizio ( 1 / 7 )", "Come si gioca ( 2 / 7 )", "Fase 1: piazzamento pezzi ( 3 / 7 )", "Fase 2: spostamento pezzi ( 4 / 7 )",
			"Fase 3: 'volo' / spostamento libero dei pezzi ( 5 / 7 )", "Come vincere ( 6 / 7 )", "Istruzioni ( 7 / 7 )",

			/* Rule 1. */
			"StackMill è un clone del gioco Mulino.\n\n"
			"Il gioco è conosciuto anche come:\n"
			"Nine Men's Morris, Nine-Man Morris,\n"
			"Mill, Mills, The Mill Game,\n"
			"Merels, Merrills,\n"
			"Merelles, Marelles, Morelles,\n"
			"Ninepenny Marl\n"
			"e Cowboy Checkers.\n\n"
			"Vedi le altre schede per le regole del gioco o controlla su Wikipedia: https://it.wikipedia.org/wiki/Mulino_(gioco).",

			/* Rule 2. */
			"Le regole in breve:\n"
			"- Entrambi i giocatori devono provare a posizionare 3 pezzi in una fila.\n\n"
			"- Dopo aver ottenuto una fila, il giocatore può rimuovere un pezzo dell'avversario.\n\n"
			"Perché la fila sia valida, tutti i pezzi devono farne parte.\n\n"
			"Il gioco è formato da tre fasi, spiegate di seguito.",

			/* Rule 3. */
			"Questa è la prima fase del gioco, che dura fino al posizionamento di tutti e 9 i pezzi.\n\n"
			"Il primo giocatore posiziona un pezzo su un incrocio. Dopodiché il secondo giocatore fa lo stesso fino a che non sono stati posizionati tutti i pezzi.\n\n"
			"L'obiettivo è quello di formare un buon layout per la fase successiva.\n\n"
			"Se tutti i pezzi sono stati posizionati, il gioco passa alla fase 2: spostamento.",

			/* Rule 4. */
			"Questa è la seconda fase del gioco, che dura fino a che i giocatori hanno più di tre pezzi.\n\n"
			"Il primo giocatore muove un pezzo in una casella adiacente. Il secondo giocatore fa lo stesso.\n\n"
			"Questo processo è ripetuto per tutto il resto della fase, e l'obiettivo è di muovere i pezzi in modo tale che l'avversario non possa più muovere i suoi (o che rimanga con tre o meno pezzi).\n\n"
			"Se un giocatore rimane con tre pezzi, passerà ad una fase esclusiva a lui, la fase 3.",

			/* Rule 5. */
			"Questa è l'ultima fase, esclusiva ai giocatori con tre o meno pezzi.\n\n"
			"Il giocatore può muovere i pezzi in qualunque posizione.\n"
			"Questo lascia al giocatore possibilità di riprendersi, in quanto all'altro giocatore serve solo una fila per vincere.\n\n"
			"L'obiettivo di questa fase è impedire al giocatore di fare una fila e provare a pareggiare, riducendo i pezzi dell'avversario a 3.\n\n"
			"La pagina seguente illustra alcune modalità di vittoria",

			/* Rule 6. */
			"Per vincere una partita, deve essere rispettata almeno una delle seguenti condizioni:\n\n"
			"- L'avversario non può più muoversi e rimane bloccato.\n\n"
			"- L'avversario è rimasto con tre pezzi e tu ottieni una fila, rimuovendo un pezzo dall'avversario che con due pezzi non può formare file.\n\n"
			"È anche possibile pareggiare, se entrambi i giocatori rimangono con tre pezzi.",

			/* Rule 7. */
			"Le istruzioni su come giocare sono semplici.\n\n"
			"- Fase 1: Tocca un incrocio per posizionare un pezzo.\n\n"
			"- Fasi 2 & 3: Tocca un pezzo e tocca uno spazio evidenziato per spostare il pezzo.\n\n"
			"- Rimuovi: Tocca un pezzo evidenziato per rimuoverlo.\n\n"
			"Se preferisci, puoi usare il DPad anziché il touch screen.",

			"Traduttori"
		}
	};
};

#endif
