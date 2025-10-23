



## Option 1: QtCreator build
1. ```Open QtCreator``` -> ```Load Project...``` -> ```Make Changes in src code``` -> ```Release build```


## Option 2 (TODO: finishme): Qt windeployqt (Use Git Bash in Windows)
```bash
SRC_ROOT_DIR=<src_dir>
BUILD_RELEASE_DIR=$SRC_ROOT_DIR/../build-BibleBrainRing-Desktop_Qt_5_15_2_MinGW_64_bit-Release/
rm -rf ~/Downloads/BibleBrainRing.Win
mkdir -p ~/Downloads/BibleBrainRing.Win
cp $BUILD_RELEASE_DIR/release/BibleBrainRing.exe ~/Downloads/BibleBrainRing.Win/
cd ~/Downloads/BibleBrainRing.Win/
ls .
export PATH=/d/Qt/5.15.2/mingw81_64/bin:$PATH
/d/Qt/5.15.2/mingw81_64/bin/windeployqt.exe --release --no-translations --plugindir /d/Qt/5.15.2/mingw81_64/plugins ~/Downloads/BibleBrainRing.Win/BibleBrainRing.exe
```

## Create Portable
```bash
# Download 'Enigma Virtual Box': https://enigmaprotector.com/
# See youtube: https://www.youtube.com/watch?v=8S1L0HugWOU
```
