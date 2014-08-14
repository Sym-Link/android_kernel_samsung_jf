<<<<<<< HEAD
/* Copyright (c) 2011, The Linux Foundation. All rights reserved.
=======
/* Copyright (c) 2011, 2013, The Linux Foundation. All rights reserved.
>>>>>>> cm/cm-11.0
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef __LINUX_USB_DIAG_BRIDGE_H__
#define __LINUX_USB_DIAG_BRIDGE_H__

struct diag_bridge_ops {
	void *ctxt;
	void (*read_complete_cb)(void *ctxt, char *buf,
			int buf_size, int actual);
	void (*write_complete_cb)(void *ctxt, char *buf,
			int buf_size, int actual);
	int (*suspend)(void *ctxt);
	void (*resume)(void *ctxt);
};

<<<<<<< HEAD
#if defined(CONFIG_USB_QCOM_DIAG_BRIDGE) \
	|| defined(CONFIG_USB_QCOM_DIAG_BRIDGE_MODULE)

extern int diag_bridge_read(char *data, int size);
extern int diag_bridge_write(char *data, int size);
extern int diag_bridge_open(struct diag_bridge_ops *ops);
extern void diag_bridge_close(void);
=======
#if IS_ENABLED(CONFIG_USB_QCOM_DIAG_BRIDGE)

extern int diag_bridge_read(int id, char *data, int size);
extern int diag_bridge_write(int id, char *data, int size);
extern int diag_bridge_open(int id, struct diag_bridge_ops *ops);
extern void diag_bridge_close(int id);
>>>>>>> cm/cm-11.0
extern void request_autopm_lock(int status);

#else

<<<<<<< HEAD
static int __maybe_unused diag_bridge_read(char *data, int size)
=======
static int __maybe_unused diag_bridge_read(int id, char *data, int size)
>>>>>>> cm/cm-11.0
{
	return -ENODEV;
}

<<<<<<< HEAD
static int __maybe_unused diag_bridge_write(char *data, int size)
=======
static int __maybe_unused diag_bridge_write(int id, char *data, int size)
>>>>>>> cm/cm-11.0
{
	return -ENODEV;
}

<<<<<<< HEAD
static int __maybe_unused diag_bridge_open(struct diag_bridge_ops *ops)
=======
static int __maybe_unused diag_bridge_open(int id, struct diag_bridge_ops *ops)
>>>>>>> cm/cm-11.0
{
	return -ENODEV;
}

<<<<<<< HEAD
static void __maybe_unused diag_bridge_close(void) { }
=======
static void __maybe_unused diag_bridge_close(int id) { }
>>>>>>> cm/cm-11.0

#endif

#endif
