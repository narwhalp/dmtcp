/****************************************************************************
 *   Copyright (C) 2006-2013 by Jason Ansel, Kapil Arya, and Gene Cooperman *
 *   jansel@csail.mit.edu, kapil@ccs.neu.edu, and gene@ccs.neu.edu          *
 *                                                                          *
 *   This file is part of the dmtcp/src module of DMTCP (DMTCP:dmtcp/src).  *
 *                                                                          *
 *  DMTCP:dmtcp/src is free software: you can redistribute it and/or        *
 *  modify it under the terms of the GNU Lesser General Public License as   *
 *  published by the Free Software Foundation, either version 3 of the      *
 *  License, or (at your option) any later version.                         *
 *                                                                          *
 *  DMTCP:dmtcp/src is distributed in the hope that it will be useful,      *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *  GNU Lesser General Public License for more details.                     *
 *                                                                          *
 *  You should have received a copy of the GNU Lesser General Public        *
 *  License along with DMTCP:dmtcp/src.  If not, see                        *
 *  <http://www.gnu.org/licenses/>.                                         *
 ****************************************************************************/

#pragma once
#ifndef PTYCONNLIST_H
#define PTYCONNLIST_H

// THESE INCLUDES ARE IN RANDOM ORDER.  LET'S CLEAN IT UP AFTER RELEASE. - Gene
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <mqueue.h>
#include <stdint.h>
#include <signal.h>
#include "jfilesystem.h"
#include "jbuffer.h"
#include "jconvert.h"
#include "connectionlist.h"
#include "ptyconnection.h"
#include "procmapsarea.h"

namespace dmtcp
{
  class PtyConnList : public ConnectionList
  {
    public:
      static PtyConnList& instance();

      static void drainFd() { instance().drain(); }

      static void resumeRefill() { instance().refill(false); }

      static void restart() { instance().postRestart(); }
      static void restartRefill() { instance().refill(true); }

      virtual void drain();
      virtual void resume(bool isRestart) {};
      virtual void refill(bool isRestart);
      virtual void postRestart();
      virtual int protectedFd() { return -1; }
      //examine /proc/self/fd for unknown connections
      virtual void scanForPreExisting();

      virtual Connection *createDummyConnection(int type) {
        return new PtyConnection();
      }

      void processPtyConnection(int fd, const char *path, int flags, mode_t mode);
  };
}
#endif
