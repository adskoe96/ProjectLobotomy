<img src="https://github.com/user-attachments/assets/e53b5fe8-993c-42d7-80e2-f91ce0498316" style="width:100px; height:auto;" alt="icon" />
  
# Project Lobotomy

[Download latest releaase](https://github.com/adskoe96/ProjectLobotomy/releases)  
Entertaining desktop program that silently and suddenly displays a random image from your personal folders right on your screen.  
Supports Windows and Linux.

## Dependencies

### Linux (Debian/Ubuntu)
```bash
sudo apt install qtbase5-dev qttools5-dev-tools qtmultimedia5-dev
```

### Windows
```
Visual C++ Redistributable and necessary that the .exe file be located next to the .dll files
```

## Building from Source

```
-- if windows
vcpkg install qt5

git clone https://github.com/adskoe96/ProjectLobotomy.git
cd ProjectLobotomy

-- if windows
mkdir build && buildRelease

-- if ubuntu/debian
mkdir build && chmod +x ./buildRelease.sh && ./buildRelease.sh
```

## How to escape from this???!!
bruh, just look at your tray
