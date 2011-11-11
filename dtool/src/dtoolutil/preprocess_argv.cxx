// Filename: preprocess_argv.cxx
// Created by:  drose (08Nov11)
//
////////////////////////////////////////////////////////////////////
//
// PANDA 3D SOFTWARE
// Copyright (c) Carnegie Mellon University.  All rights reserved.
//
// All use of this software is subject to the terms of the revised BSD
// license.  You should have received a copy of this license along
// with this source code in a file named "LICENSE."
//
////////////////////////////////////////////////////////////////////

#include "preprocess_argv.h"
#include "win32ArgParser.h"

////////////////////////////////////////////////////////////////////
//     Function: preprocess_argv
//  Description: Processes the argc, argv pair as needed before
//               passing it to getopt().  If this program is running
//               on Windows, but not within Cygwin, this ignores the
//               incoming argv, argv values, replacing them from the
//               GetCommandLine() string, and expanding glob patterns
//               like *.egg to a list of all matching egg files.  On
//               other platforms, this function does nothing and
//               returns argc, argv unchanged.
//
//               The argc and argv values are modified by this
//               function, if necessary, to point to
//               statically-allocated memory that will be valid until
//               the next call to preprocess_argv().
////////////////////////////////////////////////////////////////////
void
preprocess_argv(int &argc, char **&argv) {
#ifndef _WIN32
  // Not Windows: do nothing.
#else  // _WIN32
  static Win32ArgParser parser;
  if (parser.is_cygwin_shell()) {
    // Running within Cygwin: do nothing.
    return;
  }

  // On Windows, and not within Cygwin.  Process the args.
  parser.set_system_command_line();
  argc = parser.get_argc();
  argv = parser.get_argv();
#endif  // _WIN32
}