<img src="https://github.com/user-attachments/assets/e53b5fe8-993c-42d7-80e2-f91ce0498316" style="width:100px; height:auto;" alt="icon" />
  
# Project Lobotomy

[Download latest releaase](https://github.com/adskoe96/ProjectLobotomy/releases)  
Entertaining desktop program that silently and suddenly displays a random image from your personal folders right on your screen.  
Supports Windows and Linux.

## Important information
Don't use this on stream if you have personal data on your computer. You download the program knowing this, releasing us from responsibility for what happens.

## Privacy Policy
Your data is not tracked, the program runs locally on your computer and does not send anyone's data, it is not identified or sent.

## Dependencies

### Windows
```
Visual C++ Redistributable and necessary that the .exe file be located next to the .dll files
```

### Linux (Debian/Ubuntu)
```bash
sudo apt install qtbase5-dev qttools5-dev-tools qtmultimedia5-dev
```

### Linux (Arch)
```bash
sudo pacman -S qt5-base qt5-tools qt5-multimedia
```

## Building from Source

```
-- if windows
-- install cmake: https://cmake.org/download/
-- install git: https://git-scm.com/downloads
vcpkg install qt5

-- if arch
sudo pacman -S git cmake

-- if ubuntu/debian
sudo apt install git && sudo apt install cmake && sudo apt-get install -y build-essential

-- both platforms
git clone https://github.com/adskoe96/ProjectLobotomy.git
cd ProjectLobotomy

-- if windows
mkdir build && buildRelease

-- if linux
mkdir build && chmod +x ./buildRelease.sh && ./buildRelease.sh
```

## How to escape from this???!!
bruh, just look at your tray
