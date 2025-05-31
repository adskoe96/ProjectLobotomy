Project Lobotomy is an entertaining desktop program that silently and suddenly displays a random image from your personal folders right on your screen.  
Supports Windows and Linux.

## Dependencies

### Linux (Debian/Ubuntu)
```bash
sudo apt update
sudo apt install qtbase5-dev qttools5-dev-tools qtmultimedia5-dev
```

### Windows
```
just store this program with dll files ;p
```

## Building from Source

```
git clone https://github.com/adskoe96/ProjectLobotomy.git
cd project-lobotomy
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
```
