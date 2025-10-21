


## Qt linuxdeployqt
```bash
SRC_ROOT_DIR=<src_dir>
cd ~/Downloads
wget https://github.com/probonopd/linuxdeployqt/releases/download/continuous/linuxdeployqt-continuous-x86_64.AppImage
chmod +x linuxdeployqt-continuous-x86_64.AppImage
rm -rf ~/Downloads/BibleBrainRing.AppDir
mkdir -p ~/Downloads/BibleBrainRing.AppDir/usr/bin
cp $SRC_ROOT_DIR/../build-BibleBrainRing-Desktop_Qt_5_15_2_GCC_64bit-Debug/BibleBrainRing ~/Downloads/BibleBrainRing.AppDir/usr/bin/
cp $SRC_ROOT_DIR/MaterialsGroupBoxes/BibleBrainRingIcon.png ~/Downloads/BibleBrainRing.AppDir
export PATH=~/Qt/5.15.2/gcc_64/bin:$PATH
qmake -v
cat > ~/Downloads/BibleBrainRing.AppDir/BibleBrainRing.desktop <<EOF
[Desktop Entry]
Name=BibleBrainRing
Exec=BibleBrainRing
Icon=BibleBrainRingIcon
Type=Application
Categories=Utility;
EOF
ls ~/Downloads/BibleBrainRing.AppDir/
~/Downloads/linuxdeployqt-continuous-x86_64.AppImage ~/Downloads/BibleBrainRing.AppDir/usr/bin/BibleBrainRing -appimage
echo $?
```