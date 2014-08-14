/*
 * Linux 2.6.32 and later Kernel module for VMware MVP Hypervisor Support
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
 * @brief mvpkm kernel hooks for Comm event signaling
 */

#include <linux/module.h>
#include "comm_transp_impl.h"

<<<<<<< HEAD
int (*CommTranspEvProcess)(CommTranspID* id, CommTranspIOEvent event);
=======
int (*CommTranspEvProcess)(CommTranspID *id, CommTranspIOEvent event);
>>>>>>> cm/cm-11.0


/**
 * @brief Register a processing callback for the host when a signal
 *      is received from the guest. Supports only a single comm "service"
 *      on the host.
 * @param commProcessFunc function pointer to process a signal
 */

void
Mvpkm_CommEvRegisterProcessCB(int (*commProcessFunc)(CommTranspID*,
<<<<<<< HEAD
                                                     CommTranspIOEvent))
{
   CommTranspEvProcess = commProcessFunc;
}
=======
						     CommTranspIOEvent))
{
	CommTranspEvProcess = commProcessFunc;
}
EXPORT_SYMBOL(Mvpkm_CommEvRegisterProcessCB);
>>>>>>> cm/cm-11.0

/**
 * @brief Unregister the processing callback for the host when a signal
 *      is received from the guest.
 */

void
Mvpkm_CommEvUnregisterProcessCB(void)
{
<<<<<<< HEAD
   CommTranspEvProcess = NULL;
}


EXPORT_SYMBOL(Mvpkm_CommEvRegisterProcessCB);
=======
	CommTranspEvProcess = NULL;
}
>>>>>>> cm/cm-11.0
EXPORT_SYMBOL(Mvpkm_CommEvUnregisterProcessCB);


