<div align="center">

# ALISCUT

Minimal CLI show alias table

</div>

---

## Motivation

I usually define many aliases to avoid repeating long command-line instructions in the terminal. However, one day I opened the terminal and completely forgot what aliases I had created. I had to open the terminal configuration files and use cat just to check them, which became really annoying when I wanted to stay focused and work continuously. That frustration is exactly why this project exists.

---

## Features

* Show the aliásés table with the one command line
* Color support for terminals

---

## Install

```bash
# clone the repo
git clone git@github.com:NhanPhan159/aliscut.git
```

#### Install g++
```bash
# for Linux (ubuntu distro)
sudo apt update (optional)
sudo apt upgrade (optional)
sudo apt install g++

# for MacOS
# If you have x-code just skip this step
brew install gcc
```

#### Install make
```bash
# for macOS
brew install make
```

#### Build the application
``` bash
make
```

#### Move to a directory in your PATH
``` bash
sudo mv aliscut /usr/local/bin/
```

---

## Usage

```bash
# Basic usage
aliscut
```

---

## License

MIT License © 2026 Nhan Phan  
See [LICENSE](LICENSE) for more information.

---
