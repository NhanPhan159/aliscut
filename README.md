<div align="center">

# ALISCUT

Minimal CLI show alias in terminal

</div>

---

## Motivation

I usually define many aliases to avoid repeating long command-line instructions in the terminal. However, one day I opened the terminal and completely forgot what aliases I had created. I had to open the terminal configuration files and use cat just to check them, which became really annoying when I wanted to stay focused and work continuously. That frustration is exactly why this project exists.

---

## Features

* Show the aliases with the one command line
* Color support for terminals
* Support TUI
* Searching alias (in developing)

---

## Install

```bash
# clone the repo
git clone git@github.com:NhanPhan159/aliscut.git
```

#### Install dependencies for Linux (ubuntu distro)
```bash
sudo apt update (optional)
sudo apt upgrade (optional)
sudo apt install cmake g++ make libftxui-dev

# for MacOS
# If you have x-code just skip this step
brew install gcc
```

#### Install dependencies for MacOS
```bash
brew install make
brew install cmake
brew install --HEAD ftxui
```

#### Build the application
``` bash
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

### Basic usage
Just type : ```bash aliscut ``` <br/>
For simple table you need add -s option : ```bash aliscut -s ```

---

## License

MIT License © 2026 Nhan Phan  
See [LICENSE](LICENSE) for more information.

---
