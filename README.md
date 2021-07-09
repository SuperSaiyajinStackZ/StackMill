# StackMill
<p align="center">
	<a href="https://github.com/SuperSaiyajinStackZ/StackMill/releases/latest"><img src="https://github.com/SuperSaiyajinStackZ/StackMill/blob/main/resources/logos/v0.1.0-v0.3.0/ReadMeCover.png"></a><br>
	<b>A clone of the mill game for Nintendo 3DS.</b><br>
</p>


This is just a simple `The Mill` game clone i created for Nintendo 3DS, because i haven't found one yet and thought, why not.

The name `StackMill` is basically just a mix from my name `Stack(Z)` and `Mill`, hence -> `StackMill`.

You can read more about that game on the wikipedia page [here](https://en.wikipedia.org/wiki/Nine_men%27s_morris).

## Features
StackMill includes the following features right now:

* Select a color from 10 for the Stones from Player 1, Player 2 and a highlighted color for possible plays.

* Play together with a friend on a single console, with a random Computer / AI or with a 50:50 Computer / AI. The random AI is enabled by default, so if you want to play with a friend, disable it in the second tab `Settings`, so that `Computer Opponent` has the Red Stone.

## Screenshots

<details><summary>Screenshots</summary>

### Credits Tab
![](https://github.com/SuperSaiyajinStackZ/StackMill/blob/main/resources/screenshots/creditsTab.png)

### Game Tab
![](https://github.com/SuperSaiyajinStackZ/StackMill/blob/main/resources/screenshots/gameTab.png)

### Rules
![](https://github.com/SuperSaiyajinStackZ/StackMill/blob/main/resources/screenshots/rules1.png)
![](https://github.com/SuperSaiyajinStackZ/StackMill/blob/main/resources/screenshots/rules2.png)
![](https://github.com/SuperSaiyajinStackZ/StackMill/blob/main/resources/screenshots/rules3.png)
![](https://github.com/SuperSaiyajinStackZ/StackMill/blob/main/resources/screenshots/rules4.png)
![](https://github.com/SuperSaiyajinStackZ/StackMill/blob/main/resources/screenshots/rules5.png)
![](https://github.com/SuperSaiyajinStackZ/StackMill/blob/main/resources/screenshots/rules6.png)
![](https://github.com/SuperSaiyajinStackZ/StackMill/blob/main/resources/screenshots/rules7.png)

### Settings Tab
![](https://github.com/SuperSaiyajinStackZ/StackMill/blob/main/resources/screenshots/settingsTabMain.png)
![](https://github.com/SuperSaiyajinStackZ/StackMill/blob/main/resources/screenshots/settingsTabGameSettings.png)
![](https://github.com/SuperSaiyajinStackZ/StackMill/blob/main/resources/screenshots/settingsTabLanguage.png)
![](https://github.com/SuperSaiyajinStackZ/StackMill/blob/main/resources/screenshots/settingsTabImportExport.png)


### Splash
![](https://github.com/SuperSaiyajinStackZ/StackMill/blob/main/resources/screenshots/splash.png)


</details>

## Compilation

### Setting up your environment

To build StackMill from source, you will need to install devkitARM, libctru, citro2d and citro3d. Follow devkitPro's [Getting Started](https://devkitpro.org/wiki/Getting_Started) page to install pacman, then run the following command to install everything you need:
```
(sudo dkp-)pacman -S 3ds-dev
```
(The `sudo dkp-` may not be needed depending on your OS).

You will also need [bannertool](https://github.com/Steveice10/bannertool/releases/latest) and [makerom](https://github.com/profi200/Project_CTR/releases/latest) in your PATH.

### Cloning the repository

To download the source you will need to clone the repository with submodules, this can be done by running:
```
git clone --recursive https://github.com/SuperSaiyajinStackZ/StackMill.git
```

If you've already cloned it, you can use the following command to update all of the submodules:
```
git submodule update --init --recursive
```

### Building

Once you've cloned the repository (with submodules), simply run `make` in the `3DS` directory. You will find `StackMill.cia` and `StackMill.3dsx` inside the `3DS` directory and you can run the 3dsx version from the Homebrew Launcher and or install the cia with FBI for the HOME Menu.


## Credits
### Main Developer
- [SuperSaiyajinStackZ](https://github.com/SuperSaiyajinStackZ)

### Others
- [Universal-Team](https://github.com/Universal-Team): Universal-Core.

### Translators
- [SuperSaiyajinStackZ](https://github.com/SuperSaiyajinStackZ): German & English.
- [Pk11](https://github.com/Epicpkmn11): Japanese & English.