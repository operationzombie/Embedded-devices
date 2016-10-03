These instructions assume you've downloaded the software in the zip file on the slackchat.
The URL is: https://undeadbaby.slack.com/files/layne/F16KMP02W/operation_zombie_embedded_toolchain.zip

This also assumes you're working with a USBAsp ISP device, if the university has provided others, the makefile will need to be updated.
If you're having trouble, let Layne know. 

0) plug in usbasp device
1) copy avr8-gnu-toolchain into a disk location, and add location/bin to path
2) copy avrdude to a disk location and add location to path
3) download/install make from http://gnuwin32.sourceforge.net/packages/make.htm
4) add C:\Program Files (x86)\GnuWin32\bin to path, or wherever make was installed
5) follow steps here:

http://oceanoptics.com/faq/windows-8-or-8-1-device-driver-issues/

to disable digital signiture requirement, in order to load usbasp driver, 
6) install the usbasp device driver, downloaded from DL from http://www.fischl.de/usbasp/, (device manager > usb asp > update driver > select file)
7) copy makefile into your project directory
8) run 'make' to build the project
9) run 'make flash' to program your avr chip
