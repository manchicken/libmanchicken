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


## License ##
Copyright (c) 2013, Michael D. Stemle, Jr.
libmanchicken - All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
Neither the name of Michael D. Stemle, Jr., notsosoft.net, nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
