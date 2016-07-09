# octave

Here is my attempt to contribute to the open-source GNU-Octave software.

Project 1: implement missing functions impixelinfo and impixelinfoval in the image package.

# Building Octave

Here are the steps that let me build octave (minus some dependency installation along the way...)
```
hg clone http://www.octave.org/hg/octave
cd octave
./bootstrap
./configure
make
make install
```
