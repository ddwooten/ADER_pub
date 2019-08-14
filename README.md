# ADER
Welcome to the **A**dvanced **D**epletion **E**xtension for **R**eprocessing, 
ADER!

The best place to get started with ADER is the user manual -
The user manual can be found inside the ADER parent directory
( the folder which contains this file ) by navigating to ADER/docs/UM and
opening the file **UM.pdf**. Of immediate assistance should be the introduction
as well as chapter 12 - Installation.

ADER is distributed under the Eclipse Public Licence, the details of which can
be found in the file, LICENSE.txt, located in the ADER parent directory.

The directory /src **DOES NOT** contain all the files necessary to build and
use ADER. For that you will need to have access to the source code for the
Monte-Carlo code, SERPENT2 - details pertaining on how to obtain this source
code may be found at *serpent.vtt.ft/mediawiki/index.php/Main_Page*.

The directory /System\_Testing contains sub-directories, one for each system 
test in the ADER testing suite.

The directory /inputs contains a sub-directory, /Test\_Input, which itself
holds the unit test input for the ADER testing suite.

ADER makes extensive use of the CLP linear optimization library - details may
be found at *github.com/coin-or/Clp*.
