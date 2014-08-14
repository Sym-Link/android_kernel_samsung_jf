/*
 * Linux 2.6.32 and later Kernel module for VMware MVP Guest Communications
 *
<<<<<<< HEAD
 * Copyright (C) 2010-2012 VMware, Inc. All rights reserved.
=======
 * Copyright (C) 2010-2013 VMware, Inc. All rights reserved.
>>>>>>> cm/cm-11.0
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; see the file COPYING.  If not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
#line 5

/**
 * @file
 *
 * @brief Generic shared memory transport private API.
 */

#ifndef _COMM_TRANSP_IMPL_H_
#define _COMM_TRANSP_IMPL_H_

#define INCLUDE_ALLOW_PV
#define INCLUDE_ALLOW_MODULE
#define INCLUDE_ALLOW_MONITOR
#define INCLUDE_ALLOW_GPL
#include "include_check.h"

#include "comm_transp.h"


/* Shared memory opaque descriptor/handle. Only meaningful locally. */

typedef struct CommTranspPriv *CommTransp;


/* Asynchronous signaling initialization arguments. */

typedef enum CommTranspIOEvent {
<<<<<<< HEAD
   COMM_TRANSP_IO_DETACH = 0x0,
   COMM_TRANSP_IO_IN = 0x1,
   COMM_TRANSP_IO_OUT = 0x2,
   COMM_TRANSP_IO_INOUT = 0x3
} CommTranspIOEvent;

typedef struct CommTranspEvent {
   void (*ioEvent)(CommTransp transp, CommTranspIOEvent event, void *data);
   void *ioEventData;
=======
	COMM_TRANSP_IO_DETACH = 0x0,
	COMM_TRANSP_IO_IN = 0x1,
	COMM_TRANSP_IO_OUT = 0x2,
	COMM_TRANSP_IO_INOUT = 0x3
} CommTranspIOEvent;

typedef struct CommTranspEvent {
	void (*ioEvent)(CommTransp transp, CommTranspIOEvent event, void *data);
	void *ioEventData;
>>>>>>> cm/cm-11.0
} CommTranspEvent;


/*
 * Mechanism to detect and optionally attach to, created shared memory regions.
 */

typedef struct CommTranspListener {
<<<<<<< HEAD
   int (*probe)(CommTranspInitArgs *transpArgs, void *probeData);
   void *probeData;
=======
	int (*probe)(CommTranspInitArgs *transpArgs, void *probeData);
	void *probeData;
>>>>>>> cm/cm-11.0
} CommTranspListener;



/*
 * Function prototypes.
 */

int CommTranspEvent_Init(void);
void CommTranspEvent_Exit(void);
int CommTranspEvent_Process(CommTranspID *transpID, CommTranspIOEvent event);
int
CommTranspEvent_Raise(unsigned int peerEvID,
<<<<<<< HEAD
                      CommTranspID *transpID,
                      CommTranspIOEvent event);
=======
		      CommTranspID *transpID,
		      CommTranspIOEvent event);
>>>>>>> cm/cm-11.0

int CommTransp_Init(void);
void CommTransp_Exit(void);

int CommTransp_Register(const CommTranspListener *listener);
void CommTransp_Unregister(const CommTranspListener *listener);
int
CommTransp_Notify(const CommTranspID *notificationCenterID,
<<<<<<< HEAD
                  CommTranspInitArgs *transpArgs);

int
CommTransp_Open(CommTransp *transp,
                CommTranspInitArgs *transpArgs,
                CommTranspEvent *transpEvent);
=======
		  CommTranspInitArgs *transpArgs);

int
CommTransp_Open(CommTransp *transp,
		CommTranspInitArgs *transpArgs,
		CommTranspEvent *transpEvent);
>>>>>>> cm/cm-11.0
void CommTransp_Close(CommTransp transp);

int CommTransp_EnqueueSpace(CommTransp transp);
int CommTransp_EnqueueReset(CommTransp transp);
int CommTransp_EnqueueCommit(CommTransp transp);
int
CommTransp_EnqueueSegment(CommTransp transp,
<<<<<<< HEAD
                          const void *buf,
                          unsigned int bufLen,
                          int kern);
=======
			  const void *buf,
			  unsigned int bufLen,
			  int kern);
>>>>>>> cm/cm-11.0

int CommTransp_DequeueSpace(CommTransp transp);
int CommTransp_DequeueReset(CommTransp transp);
int CommTransp_DequeueCommit(CommTransp transp);
int
CommTransp_DequeueSegment(CommTransp transp,
<<<<<<< HEAD
                          void *buf,
                          unsigned int bufLen,
                          int kern);
=======
			  void *buf,
			  unsigned int bufLen,
			  int kern);
>>>>>>> cm/cm-11.0

unsigned int CommTransp_RequestInlineEvents(CommTransp transp);
unsigned int CommTransp_ReleaseInlineEvents(CommTransp transp);

<<<<<<< HEAD
#endif // _COMM_TRANSP_IMPL_H_
=======
#endif /* _COMM_TRANSP_IMPL_H_ */
>>>>>>> cm/cm-11.0
