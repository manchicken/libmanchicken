# libmanchicken #
This is just a simple library with my collection of useful C routines.

## mutable_string ##
This is a simple interface for mutable strings. The functions here all deal with allocation, assignment, etc.

## findbin ##
This is a simple function to get the full path and filename of the current executable. This is a little tricky since it is rather OS-specific. Current OS support:

 - [X] OS X (Mountain Lion tested only, others probably work too)
 - [ ] GNU/Linux (probably works, untested though)
 - [ ] BSD (probably works, untested though)
 - [ ] Windows (*DOES NOT* work, please contribute if desired)

If you have any experiences you'd like to share, please let me know and I'd be happy to include your changes and/or test results.