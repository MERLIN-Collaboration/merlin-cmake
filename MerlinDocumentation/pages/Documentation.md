# Introduction {#mainpage}

This is the introduction.

## Installation {#install_sec}

### Linux
The current method is to use cmake to build makefiles for Merlin

1. make a "build" folder outside the folder where Merlin was extracted.

2. run "cmake /path/to/merlin/folder"

3. run "ccmake /path/to/buildfolder"

4. Pick the options you wish to use.

5. run make -j < ncpu >

6. This will make the merlin library

### Windows

Needs to be updated.

### OSX

The optimal way to use Merlin on OSX is to get cmake to generate build files for Xcode.
This of course requires that xcode is installed.
By default cmake will generate unix makefiles.
To generate Xcode files the appropriate generator must be specified when using cmake as:

cmake -G Xcode

One can then run:

xcodebuild

which will compile merlin.
Other options exist such as "xcodebuild clean", which will clear out built files.

\author Robert Appleby
\author Roger Barlow
\author Adriana Bungau
\author James Fallon
\author Dirk Kruecker
\author James Molson
\author Haroon Rafique
\author Scott Rowan
\author Maurizio Serluca
\author Adina Toader
\author Sam Tygier
\author Nick Walker
\author Andy Wolski

\date 2001-2018

