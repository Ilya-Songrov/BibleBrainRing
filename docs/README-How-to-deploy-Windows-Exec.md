


## Qt windeployqt (Use Git Bash in Windows)
```bash
SRC_ROOT_DIR=<src_dir>
BUILD_RELEASE_DIR=$SRC_ROOT_DIR/../build-BibleBrainRing-Desktop_Qt_5_15_2_GCC_64bit-Release/
cd ~/Downloads
rm -rf ~/Downloads/BibleBrainRing.Win
mkdir -p ~/Downloads/BibleBrainRing.Win
cp $BUILD_RELEASE_DIR/BibleBrainRing ~/Downloads/BibleBrainRing.Win/
cp $SRC_ROOT_DIR/MaterialsGroupBoxes/BibleBrainRingIcon.png ~/Downloads/BibleBrainRing.Win
export PATH=~/Qt/5.15.2/gcc_64/bin:$PATH
qmake -v
cat > ~/Downloads/BibleBrainRing.Win/BibleBrainRing.desktop <<EOF
[Desktop Entry]
Name=BibleBrainRing
Exec=BibleBrainRing
Icon=BibleBrainRingIcon
Type=Application
Categories=Utility;
EOF
ls ~/Downloads/BibleBrainRing.Win/
~/Downloads/linuxdeployqt-continuous-x86_64.AppImage ~/Downloads/BibleBrainRing.Win/BibleBrainRing -appimage
echo $?

windeployqt --release --no-translations MyApp.exe
```