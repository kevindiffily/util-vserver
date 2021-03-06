// $Id$    --*- c++ -*--

// Copyright (C) 2003 Enrico Scholz <enrico.scholz@informatik.tu-chemnitz.de>
//  
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; version 2 of the License.
//  
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//  
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.


#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include "compat.h"
#include "vserver.h"
#include "internal.h"
#include "src/util.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  char			buf[sizeof(int)*3+2];
  xid_t			xid;
  struct vc_vx_info	info;
  
  if (argc==1) xid = vc_get_task_xid(0);
  else         xid = vc_get_task_xid(atoi(argv[1]));

  if (xid==VC_NOCTX) {
    perror("vc_get_task_xid()");
    return EXIT_FAILURE;
  }

  if (vc_get_vx_info(xid, &info)==-1) {
    perror("vc_get_vx_info()");
    return EXIT_FAILURE;
  }

  utilvserver_fmt_int(buf, info.initpid);

  WRITE_STR(1, buf);
  WRITE_MSG(1, "\n");

  return 0;
}
