/* Copyright (c) 2011-2012, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/err.h>
#include <linux/slab.h>
#include <linux/io.h>
#include <linux/mutex.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/kernel.h>
#include <linux/irq.h>
#include <linux/ioctl.h>
#include <linux/delay.h>
#include <linux/reboot.h>
#include <linux/debugfs.h>
#include <linux/completion.h>
#include <linux/workqueue.h>
<<<<<<< HEAD
=======
#include <linux/clk.h>
>>>>>>> cm/cm-11.0
#include <linux/mfd/pmic8058.h>
#include <asm/mach-types.h>
#include <asm/uaccess.h>
#include <mach/mdm2.h>
#include <mach/restart.h>
#include <mach/subsystem_notif.h>
#include <mach/subsystem_restart.h>
#include <linux/msm_charm.h>
#include "msm_watchdog.h"
#include "devices.h"
<<<<<<< HEAD
#include "mdm_private.h"
#define MDM_PBLRDY_CNT		20

static int mdm_debug_mask = 0xFF;
static int power_on_count;
static int hsic_peripheral_status;
static DEFINE_MUTEX(hsic_status_lock);
=======
#include "clock.h"
#include "mdm_private.h"
#define MDM_PBLRDY_CNT		20

static int mdm_debug_mask;
>>>>>>> cm/cm-11.0

static void mdm_peripheral_connect(struct mdm_modem_drv *mdm_drv)
{
	if (!mdm_drv->pdata->peripheral_platform_device)
		return;

<<<<<<< HEAD
	mutex_lock(&hsic_status_lock);
	if (hsic_peripheral_status)
		goto out;
	platform_device_add(mdm_drv->pdata->peripheral_platform_device);
	hsic_peripheral_status = 1;
out:
	mutex_unlock(&hsic_status_lock);
=======
	mutex_lock(&mdm_drv->peripheral_status_lock);
	if (mdm_drv->peripheral_status)
		goto out;
	platform_device_add(mdm_drv->pdata->peripheral_platform_device);
	mdm_drv->peripheral_status = 1;
out:
	mutex_unlock(&mdm_drv->peripheral_status_lock);
>>>>>>> cm/cm-11.0
}

static void mdm_peripheral_disconnect(struct mdm_modem_drv *mdm_drv)
{
	if (!mdm_drv->pdata->peripheral_platform_device)
		return;

<<<<<<< HEAD
	mutex_lock(&hsic_status_lock);
	if (!hsic_peripheral_status)
		goto out;
	platform_device_del(mdm_drv->pdata->peripheral_platform_device);
	hsic_peripheral_status = 0;
out:
	mutex_unlock(&hsic_status_lock);
=======
	mutex_lock(&mdm_drv->peripheral_status_lock);
	if (!mdm_drv->peripheral_status)
		goto out;
	platform_device_del(mdm_drv->pdata->peripheral_platform_device);
	mdm_drv->peripheral_status = 0;
out:
	mutex_unlock(&mdm_drv->peripheral_status_lock);
>>>>>>> cm/cm-11.0
}

/* This function can be called from atomic context. */
static void mdm_toggle_soft_reset(struct mdm_modem_drv *mdm_drv)
{
	int soft_reset_direction_assert = 0,
	    soft_reset_direction_de_assert = 1;

	if (mdm_drv->pdata->soft_reset_inverted) {
		soft_reset_direction_assert = 1;
		soft_reset_direction_de_assert = 0;
	}
	gpio_direction_output(mdm_drv->ap2mdm_soft_reset_gpio,
			soft_reset_direction_assert);
	/* Use mdelay because this function can be called from atomic
	 * context.
	 */
	mdelay(10);
	gpio_direction_output(mdm_drv->ap2mdm_soft_reset_gpio,
			soft_reset_direction_de_assert);
}

/* This function can be called from atomic context. */
static void mdm_atomic_soft_reset(struct mdm_modem_drv *mdm_drv)
{
	mdm_toggle_soft_reset(mdm_drv);
}

static void mdm_power_down_common(struct mdm_modem_drv *mdm_drv)
{
	int i;
	int soft_reset_direction =
		mdm_drv->pdata->soft_reset_inverted ? 1 : 0;

<<<<<<< HEAD
	if (mdm_debug_mask & MDM_DEBUG_MASK_SHDN_LOG)
		pr_info("%s: Start mdm power down\n", __func__);

=======
>>>>>>> cm/cm-11.0
	mdm_peripheral_disconnect(mdm_drv);

	/* Wait for the modem to complete its power down actions. */
	for (i = 20; i > 0; i--) {
		if (gpio_get_value(mdm_drv->mdm2ap_status_gpio) == 0) {
			if (mdm_debug_mask & MDM_DEBUG_MASK_SHDN_LOG)
<<<<<<< HEAD
				pr_info("%s: mdm2ap_status went low, i = %d\n",
					__func__, i);
=======
				pr_info("%s:id %d: mdm2ap_statuswent low, i=%d\n",
					__func__, mdm_drv->device_id, i);
>>>>>>> cm/cm-11.0
			break;
		}
		msleep(100);
	}

<<<<<<< HEAD
	if (i != 0) {
		pr_err("%s: MDM2AP_STATUS went low successfully.\n", __func__);
		return;
	}

	/* Shutdown the MDM9K gracefully.
	 * It seems that the MDM9K does not shutdown properly
	 * with shutdown command sent by system monitor via HSIC channel.
	 * The GPIO_27 of APQ named AP2MDM_PON_RESET_N is connected
	 * to PON_TRIG of PMIC8018 and PS_HOLD of PMIC8018 with a diode and
	 * a registor. So if GPIO_27 is pulled low the PS_HOLD input of
	 * PMIC8018 is low. The full powerdown sequence will be executed.*/

	pr_err("%s: MDM2AP_STATUS never went low. Doing a hard reset\n",
			__func__);
	pr_info("Hold PS_HOLD of MDM9K low for the reset to fully take place.\n");

	/* Q : Why we should hold the PS_HOLD low of PMIC 8018 for 1500ms?
	 * A : To overcome WDOG, we must hold PS_HOLD low for longer than the
	 * t(pshold) timer. This timer is 300ms MAX. To overcome SMPL, we must
	 * hold PS_HOLD low for longer thatn the SMPL timer setting. Since the
	 * SMPL timer is 1000ms which is greater thant the maximum t(pshold)
	 * timer, we just need to hold PS_HOLD low for longer than the SMPL
	 * timer to shut down the device with WDOG and SMPL.
	 * We added 500ms duration for margin of safety.
	 */
	gpio_direction_output(mdm_drv->ap2mdm_soft_reset_gpio,
				soft_reset_direction);
	msleep(1500);

=======
	/* Assert the soft reset line whether mdm2ap_status went low or not */
	gpio_direction_output(mdm_drv->ap2mdm_soft_reset_gpio,
					soft_reset_direction);
	if (i == 0) {
		pr_err("%s: MDM2AP_STATUS never went low. Doing a hard reset\n",
			   __func__);
		/*
		* Currently, there is a debounce timer on the charm PMIC. It is
		* necessary to hold the PMIC RESET low for ~3.5 seconds
		* for the reset to fully take place. Sleep here to ensure the
		* reset has occured before the function exits.
		*/
		msleep(4000);
	}
>>>>>>> cm/cm-11.0
}

static void mdm_do_first_power_on(struct mdm_modem_drv *mdm_drv)
{
	int i;
	int pblrdy;
<<<<<<< HEAD
	if (power_on_count != 1) {
		pr_err("%s: Calling fn when power_on_count != 1\n",
			   __func__);
		return;
	}

	pr_err("%s: Powering on modem for the first time\n", __func__);
=======
	int kpd_direction_assert = 1,
		kpd_direction_de_assert = 0;

	if (mdm_drv->pdata->kpd_not_inverted) {
		kpd_direction_assert = 0;
		kpd_direction_de_assert = 1;
	}

	if (mdm_drv->power_on_count != 1) {
		pr_err("%s:id %d: Calling fn when power_on_count != 1\n",
			   __func__, mdm_drv->device_id);
		return;
	}

	pr_err("%s:id %d: Powering on modem for the first time\n",
		   __func__, mdm_drv->device_id);
>>>>>>> cm/cm-11.0
	mdm_peripheral_disconnect(mdm_drv);

	/* If this is the first power-up after a panic, the modem may still
	 * be in a power-on state, in which case we need to toggle the gpio
	 * instead of just de-asserting it. No harm done if the modem was
	 * powered down.
	 */
<<<<<<< HEAD
	mdm_toggle_soft_reset(mdm_drv);
=======
	if (!mdm_drv->pdata->no_reset_on_first_powerup)
		mdm_toggle_soft_reset(mdm_drv);

>>>>>>> cm/cm-11.0
	/* If the device has a kpd pwr gpio then toggle it. */
	if (GPIO_IS_VALID(mdm_drv->ap2mdm_kpdpwr_n_gpio)) {
		/* Pull AP2MDM_KPDPWR gpio high and wait for PS_HOLD to settle,
		 * then	pull it back low.
		 */
		pr_debug("%s: Pulling AP2MDM_KPDPWR gpio high\n", __func__);
		gpio_direction_output(mdm_drv->ap2mdm_kpdpwr_n_gpio, 1);
<<<<<<< HEAD
		msleep(1000);
		gpio_direction_output(mdm_drv->ap2mdm_kpdpwr_n_gpio, 0);
	}
=======
		gpio_direction_output(mdm_drv->ap2mdm_status_gpio, 1);
		msleep(1000);
		gpio_direction_output(mdm_drv->ap2mdm_kpdpwr_n_gpio, 0);
	} else
		gpio_direction_output(mdm_drv->ap2mdm_status_gpio, 1);
>>>>>>> cm/cm-11.0

	if (!GPIO_IS_VALID(mdm_drv->mdm2ap_pblrdy))
		goto start_mdm_peripheral;

	for (i = 0; i  < MDM_PBLRDY_CNT; i++) {
		pblrdy = gpio_get_value(mdm_drv->mdm2ap_pblrdy);
		if (pblrdy)
			break;
		usleep_range(5000, 5000);
	}
<<<<<<< HEAD
	pr_debug("%s: i:%d\n", __func__, i);
=======
	pr_debug("%s: id %d: pblrdy i:%d\n", __func__,
			 mdm_drv->device_id, i);
>>>>>>> cm/cm-11.0

start_mdm_peripheral:
	mdm_peripheral_connect(mdm_drv);
	msleep(200);
}

static void mdm_do_soft_power_on(struct mdm_modem_drv *mdm_drv)
{
	int i;
	int pblrdy;

<<<<<<< HEAD
	pr_err("%s: soft resetting mdm modem\n", __func__);
=======
	pr_err("%s: id %d:  soft resetting mdm modem\n",
		   __func__, mdm_drv->device_id);
>>>>>>> cm/cm-11.0
	mdm_peripheral_disconnect(mdm_drv);
	mdm_toggle_soft_reset(mdm_drv);

	if (!GPIO_IS_VALID(mdm_drv->mdm2ap_pblrdy))
		goto start_mdm_peripheral;

	for (i = 0; i  < MDM_PBLRDY_CNT; i++) {
		pblrdy = gpio_get_value(mdm_drv->mdm2ap_pblrdy);
		if (pblrdy)
			break;
		usleep_range(5000, 5000);
	}

<<<<<<< HEAD
	pr_debug("%s: i:%d\n", __func__, i);
=======
	pr_debug("%s: id %d: pblrdy i:%d\n", __func__,
			 mdm_drv->device_id, i);
>>>>>>> cm/cm-11.0

start_mdm_peripheral:
	mdm_peripheral_connect(mdm_drv);
	msleep(200);
}

static void mdm_power_on_common(struct mdm_modem_drv *mdm_drv)
{
<<<<<<< HEAD
	power_on_count++;
=======
	mdm_drv->power_on_count++;
>>>>>>> cm/cm-11.0

	/* this gpio will be used to indicate apq readiness,
	 * de-assert it now so that it can be asserted later.
	 * May not be used.
	 */
	if (GPIO_IS_VALID(mdm_drv->ap2mdm_wakeup_gpio))
		gpio_direction_output(mdm_drv->ap2mdm_wakeup_gpio, 0);

	/*
	 * If we did an "early power on" then ignore the very next
	 * power-on request because it would the be first request from
	 * user space but we're already powered on. Ignore it.
	 */
	if (mdm_drv->pdata->early_power_on &&
<<<<<<< HEAD
			(power_on_count == 2))
		return;

	if (power_on_count == 1)
=======
			(mdm_drv->power_on_count == 2))
		return;

	if (mdm_drv->power_on_count == 1)
>>>>>>> cm/cm-11.0
		mdm_do_first_power_on(mdm_drv);
	else
		mdm_do_soft_power_on(mdm_drv);
}

static void debug_state_changed(int value)
{
	mdm_debug_mask = value;
}

static void mdm_status_changed(struct mdm_modem_drv *mdm_drv, int value)
{
<<<<<<< HEAD
	pr_debug("%s: value:%d\n", __func__, value);
=======
	pr_debug("%s: id %d: value:%d\n", __func__,
			 value, mdm_drv->device_id);
>>>>>>> cm/cm-11.0

	if (value) {
		mdm_peripheral_disconnect(mdm_drv);
		mdm_peripheral_connect(mdm_drv);
		if (GPIO_IS_VALID(mdm_drv->ap2mdm_wakeup_gpio))
			gpio_direction_output(mdm_drv->ap2mdm_wakeup_gpio, 1);
	}
}

static void mdm_image_upgrade(struct mdm_modem_drv *mdm_drv, int type)
{
	switch (type) {
	case APQ_CONTROLLED_UPGRADE:
<<<<<<< HEAD
		pr_debug("%s APQ controlled modem image upgrade\n", __func__);
		mdm_drv->mdm_ready = 0;
		mdm_toggle_soft_reset(mdm_drv);
		break;
	case MDM_CONTROLLED_UPGRADE:
		pr_debug("%s MDM controlled modem image upgrade\n", __func__);
		mdm_drv->mdm_ready = 0;
=======
		pr_debug("%s: id %d: APQ controlled modem image upgrade\n",
				 __func__, mdm_drv->device_id);
		atomic_set(&mdm_drv->mdm_ready, 0);
		mdm_toggle_soft_reset(mdm_drv);
		break;
	case MDM_CONTROLLED_UPGRADE:
		pr_debug("%s: id %d: MDM controlled modem image upgrade\n",
				 __func__, mdm_drv->device_id);
		atomic_set(&mdm_drv->mdm_ready, 0);
>>>>>>> cm/cm-11.0
		/*
		 * If we have no image currently present on the modem, then we
		 * would be in PBL, in which case the status gpio would not go
		 * high.
		 */
		mdm_drv->disable_status_check = 1;
		if (GPIO_IS_VALID(mdm_drv->usb_switch_gpio)) {
<<<<<<< HEAD
			pr_info("%s Switching usb control to MDM\n", __func__);
			gpio_direction_output(mdm_drv->usb_switch_gpio, 1);
		} else
			pr_err("%s usb switch gpio unavailable\n", __func__);
		break;
	default:
		pr_err("%s invalid upgrade type\n", __func__);
	}
}
=======
			pr_info("%s: id %d: Switching usb control to MDM\n",
					__func__, mdm_drv->device_id);
			gpio_direction_output(mdm_drv->usb_switch_gpio, 1);
		} else
			pr_err("%s: id %d: usb switch gpio unavailable\n",
				   __func__, mdm_drv->device_id);
		break;
	default:
		pr_err("%s: id %d: invalid upgrade type\n",
			   __func__, mdm_drv->device_id);
	}
}

>>>>>>> cm/cm-11.0
static struct mdm_ops mdm_cb = {
	.power_on_mdm_cb = mdm_power_on_common,
	.reset_mdm_cb = mdm_power_on_common,
	.atomic_reset_mdm_cb = mdm_atomic_soft_reset,
	.power_down_mdm_cb = mdm_power_down_common,
	.debug_state_changed_cb = debug_state_changed,
	.status_cb = mdm_status_changed,
	.image_upgrade_cb = mdm_image_upgrade,
};

<<<<<<< HEAD
static int __init mdm_modem_probe(struct platform_device *pdev)
{
	return mdm_common_create(pdev, &mdm_cb);
}

static int __devexit mdm_modem_remove(struct platform_device *pdev)
{
	return mdm_common_modem_remove(pdev);
}

static void mdm_modem_shutdown(struct platform_device *pdev)
{
	mdm_common_modem_shutdown(pdev);
}

static struct platform_driver mdm_modem_driver = {
	.remove         = mdm_modem_remove,
	.shutdown	= mdm_modem_shutdown,
	.driver         = {
		.name = "mdm2_modem",
		.owner = THIS_MODULE
	},
};

static int __init mdm_modem_init(void)
{
#ifdef CONFIG_SAMSUNG_LPM_MODE
	if (poweroff_charging)
		return 0;
#endif
#ifdef CONFIG_WIFI_NOMODEM
	return 0;
#endif
	return platform_driver_probe(&mdm_modem_driver, mdm_modem_probe);
}

static void __exit mdm_modem_exit(void)
{
	platform_driver_unregister(&mdm_modem_driver);
}

module_init(mdm_modem_init);
module_exit(mdm_modem_exit);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("mdm modem driver");
MODULE_VERSION("2.0");
MODULE_ALIAS("mdm_modem");
=======
int mdm_get_ops(struct mdm_ops **mdm_ops)
{
	*mdm_ops = &mdm_cb;
	return 0;
}


>>>>>>> cm/cm-11.0
