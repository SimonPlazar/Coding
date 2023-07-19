#ifndef SPO_MODULE_H
#define SPO_MODULE_H

#include <asm/current.h>
#include <asm/io.h>
#include <asm/segment.h>
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/ioport.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/uaccess.h>
#include <linux/init.h>
#include <linux/ktime.h>
#include <linux/rtc.h>

static int spo_driver_init(void);
static void spo_driver_exit(void);
static ssize_t spo_driver_read(struct file *filep, char *buffer, size_t count, loff_t *offp);

#endif
