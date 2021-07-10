# StackMill GameDataStructure

StackMill is able to save the current match to a `GameData.dat` file at `sdmc:/3ds/StackMill/` and load it from there. If you want to know how it is structured, then you are right here!

| Offset      | DataType | Size | Content                                                        |
| ----------- | -------- | ---- | -------------------------------------------------------------- |
| 0x0 - 0x2D  | uint8_t  | 0x2E | Size of the GameData.                                          |
|             |          |      |                                                                |
| 0x0 - 0x0   | int8_t   | 0x1  | Current Player (Starting at `0x1` NOT at `0x0`).               |
| 0x1 - 0x1   | BOOL     | 0x1  | Is the Stone remove phase activated? 0x0 for NO, 0x1 for YES). |
| 0x2 - 0x19  | int8_t   | 0x18 | Field Stone States. See `Field Stones` below for more.         |
| 0x1A - 0x22 | int8_t   | 0x9  | Player 1 Stones. See `Player Stones` below for more.           |
| 0x23 - 0x23 | int8_t   | 0x1  | Player 1 Phase. See `Phases` below for more.                   |
| 0x24 - 0x2C | int8_t   | 0x9  | Player 2 Stones. See `Player Stones` below for more.           |
| 0x2D - 0x2D | int8_t   | 0x1  | Player 2 Phase. See `Phases` below for more.                   |


### Field Stones
The field is very easy structured in the GameData.

| Value | Field State                                           |
| ----- | ----------------------------------------------------- |
| 0x0   | The Position is empty / no Stone is set there.        |
| 0x1   | The Position contains a White Stone / Player 1 Stone. |
| 0x2   | The Position contains a Black Stone / Player 2 Stone. |


### Player Stones
The Player Stones are a bit more complex than the Field Stones. It can contain the Position where it's being set in the field, or contain that it's not played yet at all OR that it's already collected / gone by the opponent.

| Value      | Stone State                                                                               |
| ---------- | ----------------------------------------------------------------------------------------- |
| 0x0 - 0x17 | The Position where it's being placed at the GameField. See `GameFieldPos` below for more. |
| 0x19       | That Stone hasn't been played yet.                                                        |
| 0x1A       | That Stone got already collected / is gone by the opponent.                               |


### Phases
The Phases are as simple as the table below:

| Value | Current Phase                                           |
| ----- | ------------------------------------------------------- |
| 0x0   | The current Phase is the Place / Set a Stone Phase.     |
| 0x1   | The current Phase is the Move a Stone Phase.            |
| 0x2   | The current Phase is the 'Flying' / Jump a Stone Phase. |


### GameFieldPos
To make the Field index more clear, here is a graphically example how the positions are handled:

![](https://github.com/SuperSaiyajinStackZ/StackMill/blob/main/resources/field.png)