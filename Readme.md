# Zitrone
It's an app for writing notes for musical instrument called zither.
Should work on windows and linux.
In config file, you can customize:
    - language - english and polish are supported, if you want polish replace first line with polski
    - theme - dark, light or industrial
    - page dimensions - in cm, line 3 and 4
    - cut line position - in cm, line 5 and 6
    - first note offset - in cm, line 7
    - space between tones - in cm, line 8
    - space between notes - in cm, line 9
# Screenshots
![Dark Windows](screenshots/dark.jpg)
![Light Windows](screenshots/light.jpg)
![Industrial Windows](screenshots/industrial.jpg)
# Building
If you want to build it yourself, you'll need git, cmake and some c++ compiler.
Then, it's as simple as:
```
git clone https://github.com/K0M0D4/Zitrone.git
cd Zitrone
mkdir build
cmake . -B"build"
cmake --build build
```
And boom, you have compiled version in build directory!
# Licensing
Licenses are in "licenses" directory

This project is under zlib/libpng license: see in License.md