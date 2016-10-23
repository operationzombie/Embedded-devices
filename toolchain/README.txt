These instructions will allow you to use the raw C code in this reporitory to program an arduino based board.
The firmware in this repository depends on the following pieces of software:

Make    - a linux tool, availible for windows
gcc-avr - linux tool, or part of the arduino ide
avrdude  - linux tool, or part of the arduino ide

The build process is powered by a 'makefile', which can be found in the root of the project. This make file 
requires the use of the standard linux 'make' tool. If you are attempting to build this software on ubuntu/debian
flavour of linux you can install make by running the command "sudo apt-get install build-essential". On windows, 
you can obtain make as part of the MinGW package, availible here: https://sourceforge.net/projects/mingw/files/

with make installed, you will also need gcc-avr and avrdude, on ubuntu linux these can be installed with the command

sudo apt-get install avrdude gcc-avr

if you're on windows, we have included these files in a zip to make working with them easier that zip is located here:

https://undeadbaby.slack.com/files/layne/F16KMP02W/operation_zombie_embedded_toolchain.zip

on windows, unzip the contents of that zip and ensure that the the bin folder of each of the subdirectories is included 
in your PATH variable, with instructions to do so found here: 

http://windowsitpro.com/systems-management/how-can-i-add-new-folder-my-system-path

If make, gcc-avr and avrdude are all in your PATH variable, the commands will be availible from a command shell. 
If all of these commands are found, then most of the work setting up the build process is complete.

The final step is to modify the makefile in the root to point to the relevant files. 

The modifications you need to make to the makefile are as follows:

==================================================================================================================
Line number  |    Variable         |  Change
==================================================================================================================
28           |    PROGRAMMER_ARGS  |  change -P flag to point to the arduino port, remove -C if not needed
             |                     |  or change the path following -C to point to the config file
------------------------------------------------------------------------------------------------------------------
35           |    CC               |  should contain "avr-gcc" unless avr-gcc is not found in the PATH, 
             |                     |  in which case, this should be the absolute path to the avr-gcc executable
------------------------------------------------------------------------------------------------------------------
39           |    AVRDUDE          |  should be "avrdude", unless avrdude is no in the path, in which this 
             |                     |  should be the absolute path to the executable
==================================================================================================================

with these changes made to the makefile, you should then be able to run the following commands

make clean   - removes build artifacts, ready for a clean build
make         - compiles the project, produces build artifacts ready for flashing the device
make flash   - programs the arduino device connected to the port specified in line 28.

"make flash" will also build the project, if no build artifacts have been produced, so with a properly modified 
makefile, all you will only need to run "make flash" if you aren't modifying the code base. 

