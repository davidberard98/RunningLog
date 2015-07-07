Running Log
====

##Note:
I have been working on [this online running log software](https://github.com/Jeak/ggLog).  Check it out, as it is more useful and relevant than this!

Running with wxWidgets 2.8 as a GUI
and pugixml as a xml parser.

On Linux:
  Install g++, wxWidgets, and make
    On Ubuntu: 'sudo apt-get install libwxgtk2.8-dev libwxgtk2.8-dbg build-essential'
  run 'make' to compile

On Windows: (never tested this)
  Install cygwin, and make sure to include cvs, gcc-g++, and make in the installation.  Cygwin is a linux emulator that makes programming easier.
  Setup wxWidgets on cygwin, following these instructions: http://wiki.wxwidgets.org/Cygwin
  move 'Makefile.windows' to 'Makefile'
  run 'make' to compile.

  int StoreId = wxID\_ANY; will just result in StoreId = -1, except it will actually assign -1 to be the ID, not a random number, so you end up with a whole bunch of objects with ID = -1.

Also:
  This software uses pugixml as a xml parser (http://pugixml.org).
  pugixml is Copyright (C) 2006-2012 Arseny Kapoulkine. 

  Copyright (c) 2006-2012 Arseny Kapoulkine
 
