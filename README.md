<h1 align="center">Aliscut</h1>

<p align="center">
Minimal CLI show alias in system, written in C++
</p>

<div align="center">
  <img src="./assets/aliscut-general-rounded.png" alt="screenshot" width="70%">
</div>

<br>

---

## Motivation

I usually define many aliases to avoid repeating long command-line instructions in the terminal. However, one day I opened the terminal and completely forgot what aliases I had created. I had to open the terminal configuration files and use cat just to check them, which became really annoying when I wanted to stay focused and work continuously. That frustration is exactly why this project exists.

---

## Features

- Show the aliases with the one command line
- Color support for terminals
- Support TUI

---

## Install

### Dependences

#### For Ubuntu
```bash

sudo apt update (optional)
sudo apt upgrade (optional)
sudo apt install cmake g++ make libftxui-dev
```

#### For MacOS
```bash

# If you have x-code just skip this step
brew install gcc

brew install make
brew install cmake
brew install --HEAD ftxui
```

#### Build the application
``` bash
# clone the repo
git clone git@github.com:NhanPhan159/aliscut.git

# build app
cd aliscut
mkdir build
cd build
cmake ..
make
```

#### Move to a directory in your PATH
``` bash
sudo mv aliscut /usr/local/bin/
```

---

## Usage

```bash
# Basic usage, this show the TUI app
aliscut

# Show simple table aliases to quick look
aliscut -s
```
---

## License

MIT License © 2026 Nhan Phan  
See [LICENSE](LICENSE) for more information.

---
