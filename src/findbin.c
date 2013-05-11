/*
 * libmanchicken - Copyright (C) 2012 Michael D. Stemle, Jr.
 *
 * This file is part of libmanchicken.
 *
 * libmanchicken is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libmanchicken is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libmanchicken. If not, see <http://www.gnu.org/licenses/>.
*/

#include <string.h>
#include <stdlib.h>
#include <findbin.h>

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
  #error Windows is unsupported. Sorry. If you'd like to add support and contribute, please let me know.
#endif

mutable_string_t *findbin(mutable_string_t *buf) {
  char pathbuf[1536];
  uint32_t pathsize = sizeof(pathbuf);
  ssize_t outsize = 0;

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
  #endif

  mutable_string_assign(buf, pathbuf);

  return buf;
}
