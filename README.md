<img src="https://github.com/user-attachments/assets/e53b5fe8-993c-42d7-80e2-f91ce0498316" style="width:100px; height:auto;" alt="icon" />
  
# Project Lobotomy

[Download latest releaase](https://github.com/adskoe96/ProjectLobotomy/releases)  
Entertaining desktop program that silently and suddenly displays a random image from your personal folders right on your screen.  
Supports Windows and Linux.

## Dependencies

### Linux (Debian/Ubuntu)
```bash
sudo apt update
sudo apt install qtbase5-dev qttools5-dev-tools qtmultimedia5-dev
```

### Windows
```
Visual C++ Redistributable i guess??
```

## Building from Source

```
git clone https://github.com/adskoe96/ProjectLobotomy.git
cd project-lobotomy
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
```

## How to escape from this???!!
bruh, just look at your tray
