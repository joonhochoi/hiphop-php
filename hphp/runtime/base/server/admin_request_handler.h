/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010-2013 Facebook, Inc. (http://www.facebook.com)     |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
*/

#ifndef incl_HPHP_ADMIN_REQUEST_HANDLER_H_
#define incl_HPHP_ADMIN_REQUEST_HANDLER_H_

#include "hphp/runtime/base/server/access_log.h"
#include "hphp/runtime/base/server/server.h"

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

class AdminRequestHandler : public RequestHandler {
public:
  static AccessLog &GetAccessLog() { return s_accessLog; }

public:
    AdminRequestHandler();
  // implementing RequestHandler
  virtual void handleRequest(Transport *transport);

private:
  bool handleCheckRequest  (const std::string &cmd, Transport *transport);
  bool handleStatusRequest (const std::string &cmd, Transport *transport);
  bool handleStatsRequest  (const std::string &cmd, Transport *transport);
  bool handleProfileRequest(const std::string &cmd, Transport *transport);
  bool handleLeakRequest   (const std::string &cmd, Transport *transport);
  bool handleAPCSizeRequest (const std::string &cmd, Transport *transport);
  bool handleDumpCacheRequest (const std::string &cmd, Transport *transport);
  bool handleConstSizeRequest (const std::string &cmd, Transport *transport);
  bool handleStaticStringsRequest(const std::string &cmd,
                                  Transport *transport);
  bool handleVMRequest      (const std::string &cnd, Transport *transport);

#ifdef GOOGLE_CPU_PROFILER
  bool handleCPUProfilerRequest (const std::string &cmd, Transport *transport);
#endif
#ifdef GOOGLE_HEAP_PROFILER
  bool handleHeapProfilerRequest(const std::string &cmd, Transport *transport);
#endif

  static DECLARE_THREAD_LOCAL(AccessLog::ThreadData, s_accessLogThreadData);
  static AccessLog s_accessLog;

  static AccessLog::ThreadData* getAccessLogThreadData() {
    return s_accessLogThreadData.get();
  }
};

///////////////////////////////////////////////////////////////////////////////
}

#endif // incl_HPHP_ADMIN_REQUEST_HANDLER_H_
