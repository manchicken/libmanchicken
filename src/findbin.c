/*
 * Copyright (c) 2013, Michael D. Stemle, Jr.
 * libmanchicken - All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * Redistributions of source code must retain the above copyright notice, this list
 * of conditions and the following disclaimer.
 * 
 * Redistributions in binary form must reproduce the above copyright notice, this
 * list of conditions and the following disclaimer in the documentation and/or other
 * materials provided with the distribution.
 * Neither the name of Michael D. Stemle, Jr., notsosoft.net, nor the names of its
 * contributors may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
*/

#include <string.h>
#include <stdlib.h>

#ifdef __unix__
  #include <sys/param.h>
#endif

#if defined(__linux__)
  #include <unistd.h>
  #warning This is untested on this platform, please notify me if you have results to communicate.
#elif defined(__APPLE__) && defined(__MACH__)
  #include <mach-o/dyld.h>
#elif defined(BSD)
  #include <unistd.h>
  #warning This is untested on this platform, please notify me if you have results to communicate.
#elif defined(_WIN32) || define(_WIN64)
  #error Windows is unsupported. Sorry. If youd like to add support and contribute, please let me know.
#endif

#include <findbin.h>

mutable_string_t *findbin(mutable_string_t *buf) {
  char pathbuf[1536];
  unsigned long pathsize = sizeof(pathbuf);

  #if defined(__linux__) || defined(BSD)
    ssize_t outsize = 0;
  #endif

  #if defined(__linux__)
    outsize = readlink("/proc/self/exe", pathbuf, pathsize);
    if (outsize == 0) { return NULL; }
    pathbuf[outsize] = '\0';
  #elif defined(__APPLE__) && defined(__MACH__)
    if (_NSGetExecutablePath(pathbuf, &pathsize) != 0) {
      return NULL;
    }
  #elif defined(BSD)
    outsize = readlink("/proc/curproc/file", pathbuf, pathsize);
    if (outsize == 0) { return NULL; }
    pathbuf[outsize] = '\0';
  #elif defined(_WIN32) || define(_WIN64)
    #error Windows is unsupported.
  #endif

  mutable_string_assign(buf, pathbuf);

  return buf;
}
