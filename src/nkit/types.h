/*
   Copyright 2010-2014 Boris T. Darchiev (boris.darchiev@gmail.com)

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#ifndef __NKIT__TYPES__H__
#define __NKIT__TYPES__H__

#include <nkit/detail/push_options.h>

#if defined(NKIT_POSIX_PLATFORM)
#  define __STDC_FORMAT_MACROS 1
#  include <inttypes.h>
#  include <cstdio>
#  include <unistd.h>
#  include <pwd.h>

#  define NKIT_FORMAT_I8  "%" PRIi8
#  define NKIT_FORMAT_I16 "%" PRIi16
#  define NKIT_FORMAT_I32 "%" PRIi32
#  define NKIT_FORMAT_I64 "%" PRIi64

#  define NKIT_FORMAT_U8  "%" PRIu8
#  define NKIT_FORMAT_U16 "%" PRIu16
#  define NKIT_FORMAT_U32 "%" PRIu32
#  define NKIT_FORMAT_U64 "%" PRIu64
#  define NKIT_FORMAT_DOUBLE "%F"

#  define NKIT_SSCANF(buf, ...) \
  ::sscanf(buf, __VA_ARGS__)

#  define NKIT_SNPRINTF(buf, len, ...) \
  ::std::snprintf((buf), (len), __VA_ARGS__)

#  define LOCALTIME_R(now, tm) \
  do { ::localtime_r(&(now), (tm)); } while(0)

#  define GMTIME_R(now, tm) \
  do { ::gmtime_r(&(now), (tm)); } while(0)

#  define CTIME_R(now, s, len)                \
  do                                          \
  {                                           \
    const char * _s = ::ctime_r(&(now), (s));       \
    if (unlikely(!_s)) abort_with_core("ctime_r"); \
    assert(strlen(_s) < len);                 \
  }                                           \
  while(0)

#  define NKIT_STRTOLL ::strtoll
#  define NKIT_STRTOULL ::strtoull
#  define NKIT_STRCASECMP  ::strcasecmp
#  define NKIT_STRNCASECMP  ::strncasecmp

#elif defined(NKIT_WINNT) && defined(HAVE_STD_CXX_11)
#  include <cstdint>
// pass
#elif defined(NKIT_WINNT) && defined(HAVE_BOOST)
#  include <boost/cstdint.hpp>
// pass
#elif defined(NKIT_WINNT)
#  error "int types unknown implemntation"
#endif

#if defined(NKIT_WINNT)
#  undef WIN32_LEAN_AND_MEAN
#  include <Ws2tcpip.h>
#  include <windows.h>
#  include <stdlib.h>
#  include <string.h>

#  define NKIT_FORMAT_I8  "%i"
#  define NKIT_FORMAT_I16 "%i"
#  define NKIT_FORMAT_I32 "%i"
#  define NKIT_FORMAT_I64 "%I64d"

#  define NKIT_FORMAT_U8  "%u"
#  define NKIT_FORMAT_U16 "%u"
#  define NKIT_FORMAT_U32 "%u"
#  define NKIT_FORMAT_U64 "%I64u"
#  define NKIT_FORMAT_DOUBLE "%f"

#  define NKIT_SSCANF(buf, ...) \
  ::sscanf_s(buf, __VA_ARGS__)

#  define NKIT_SNPRINTF(buf, len, ...) \
  ::sprintf_s((buf), (len), __VA_ARGS__)

#  define LOCALTIME_R(now, tm) \
  do { ::errno_t e__ = ::localtime_s((tm), &(now)); assert(e__ == 0); } while(0)

#  define GMTIME_R(now, tm) \
  do { ::errno_t e__ = ::gmtime_s((tm), &(now)); assert(e__ == 0); } while(0)

#  define CTIME_R(now, s, len) \
  do { ::errno_t e__ = ::ctime_s(s, len, &(now)); assert(e__ == 0); } while(0)

#  define NKIT_STRTOLL ::_strtoi64
#  define NKIT_STRTOULL ::_strtoui64
#  define NKIT_STRCASECMP  ::_stricmp
#  define NKIT_STRNCASECMP  ::_strnicmp

#  define __PRETTY_FUNCTION__ __FUNCTION__

#define SHUT_RDWR SD_BOTH

#endif // NKIT_WINNT

#include <map>
#include <set>
#include <list>
#include <string>
#include <vector>
#include <cassert>

#if defined(NKIT_USE_STD_CXX_11)

#  include <memory>

#  define NKIT_SHARED_PTR(T) ::std::shared_ptr<T >
#  define NKIT_ENABLE_SHARED_FROM_THIS(T) ::std::enable_shared_from_this<T >

#elif defined(NKIT_USE_BOOST)

#  include <boost/shared_ptr.hpp>

#  define NKIT_SHARED_PTR(T) ::boost::shared_ptr<T >
#  define NKIT_ENABLE_SHARED_FROM_THIS(T) ::boost::enable_shared_from_this<T >

#endif

namespace nkit
{
  typedef std::map<std::string, std::string> StringMap;
  typedef std::map<std::string, int64_t> StringIntMap;
  typedef std::map<std::string, uint64_t> StringUintMap;
  typedef std::map<int64_t, std::string> IntStringMap;
  typedef std::map<uint64_t, std::string> UintStringMap;
  typedef std::map<uint64_t, uint64_t> UintUintMap;
  typedef std::vector<std::string> StringVector;
  typedef std::vector<uint64_t> UintVector;
  typedef std::vector<int64_t> IntVector;
  typedef std::vector<uint16_t> Uint16Vector;
  typedef std::vector<int16_t> Int16Vector;
  typedef std::list<std::string> StringList;
  typedef std::list<uint64_t> UintList;
  typedef std::list<int64_t> IntList;
  typedef std::set<std::string> StringSet;
  typedef std::set<uint64_t> UintSet;
  typedef std::set<int64_t> IntSet;
  typedef std::set<uint16_t> Uint16Set;
  typedef std::set<int16_t> Int16Set;
  typedef std::set<size_t> SizeSet;
  typedef std::list<size_t> SizeList;
  typedef std::vector<size_t> SizeVector;
} // namespace nkit

#endif // __NKIT__TYPES__H__
