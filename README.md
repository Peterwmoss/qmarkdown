# qMarkdown

qMarkdown is a simple QT-based markdown viewer, it's light-weight and easy to use.

## License

This software is provided under the
[GNU GLPv3](https://www.gnu.org/licenses/gpl-3.0.en.html) license.

## Dependencies

### Ubuntu packages

* `qt5-default`
* `qtwebengine5-dev`

#### Ubuntu Optional

* `fonts-roboto` - default font, but fallbacks to *sans-serif*

### Arch packages

* `qt5-base`
* `qt5-webengine`
* `qt5-webchannel`

#### Arch Optional

* `ttf-roboto` - default font, but fallbacks to *sans-serif*

## Installation

```bash
git clone https://github.com/Peterkmoss/qmarkdown.git &&
cd qmarkdown &&
cmake . &&
make &&
sudo make install
```

### Make dependencies (in addition to normal dependencies)

* c++ compiler with support for c++17
* `git` (to clone repository)
* `cmake`

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

* `o` - Opens textfield to enter filename of new file (WIP)

## Disclaimer

This software is provided AS-IS with all faults, security issues and alike that
might come with it.

By using this software product the user UNDERSTANDS and AGREES to that there is
NO WARRANTY on this product.
