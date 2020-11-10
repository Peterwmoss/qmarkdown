# qMarkdown

qMarkdown is a simple Qt-based markdown viewer, it's light-weight and easy to use.

## Screenshots

![Light](light.png)

## License

This software is provided under the
[GNU GLPv3](https://www.gnu.org/licenses/gpl-3.0.en.html) license.

## Dependencies

`qt` version `5.9.0` or above

### Pacman packages

* `qt5-base`
* `qt5-webengine`
* `qt5-webchannel`

#### Optional

* `ttf-roboto` - default font, but fallbacks to *sans-serif*

## Installation

### Compile dependencies

* `git` (to clone repository)
* `c++` or similar compiler with support for c++17
* `cmake` >= `3.1.0`
* `make`
* `sudo` or other way to grant root privileges (like `doas`)

To install:

```shell
git clone https://github.com/Peterkmoss/qmarkdown.git &&
cd qmarkdown &&
cmake . &&
make &&
sudo make install
```

### Arch based distros

There is an
[AUR package available](https://aur.archlinux.org/packages/qmarkdown/) for all
arch-based users

## Usage

`qmarkdown <file>`

### Keybindings

* `q` - Exits the program
* `g` - Go to TOP of file
* `G` - Go to BOTTOM of file
* `j` - Scroll DOWN
* `k` - Scroll UP
* `h` - Scroll LEFT
* `l` - Scroll RIGHT

#### WIP

* `o` - Opens a text field to enter filename of new file (WIP)

## More screenshots

![Dark](dark.png)

## Disclaimer

This software is provided AS-IS with all faults, security issues and alike that
might come with it.

By using this software product the user UNDERSTANDS and AGREES to that there is
NO WARRANTY on this product.
