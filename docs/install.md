# Installation

## Dependencies

`qt` version `5.9.0` or above, for all the following parts of the library:

- Core
- Widgets
- WebChannel
- WebView
- WebEngine

All development libraries should be installed before compiling.

## Packages

### Ubuntu

* `build-essential`
* `qt5-default`
* `qtbase5-dev`
* `qtwebengine5-dev`

Sometimes the following packages are also needed:

* `libqt5webengine5`
* `libqt5webenginecore5`
* `g++10`

### Arch based (Pacman)

* `qt5-base`
* `qt5-webengine`
* `qt5-webchannel`

#### Optional

* `ttf-roboto` - default font, but fallbacks to *sans-serif*

## Installation

### Additional Compile dependencies

* `git` (to clone repository)
* `c++` or similar compiler with support for c++17
* `cmake` >= `3.1.0`
* `make`
* `sudo` or other way to grant root privileges (like `doas`)

### Clone and compile

```shell
git clone https://github.com/Peterkmoss/qmarkdown.git
cd qmarkdown
mkdir build
cd build
cmake ..
make
```

### Install

```shell
sudo make install
```

### Distribution Packages

#### AUR package

There is an
[AUR package available](https://aur.archlinux.org/packages/qmarkdown/) for all
arch-based users
