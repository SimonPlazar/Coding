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

MODULE_AUTHOR("Vaje SPO");
MODULE_DESCRIPTION("Drugi Linux modul");
MODULE_LICENSE("GPL");

// Major številka znakovne naprave
static int major;

static int spo_driver_init(void);
static void spo_driver_exit(void);
static ssize_t spo_driver_read(struct file *filep, char *buffer, size_t count, loff_t *offp);

module_init(spo_driver_init);
module_exit(spo_driver_exit);

// Struktura/Tabela operacij
// Več: https://tldp.org/LDP/lkmpg/2.6/html/x569.html
struct file_operations spo_fops = 
{
	read: spo_driver_read
};

static int spo_driver_init(void)
{
	printk("SPO driver INIT\n");

	// Registriramo znakovno napravo za "pogovor" z gonilnikom
	// Prvi parameter 0 nakazuje, da bo major številka 
	// gonilnika dinamično dodeljena
	// Parameter spo_fops je kazalec na file_operations strukturo/tabelo
	major = register_chrdev(0, "spo_device", &spo_fops);

	if (major < 0)
	{
		printk("SPO registering char device failed with %d\n", major);
		return major;
	}
	else
	{
		printk("SPO registering char device %d\n", major);
	}

	return 0;
}

static void spo_driver_exit(void)
{
	printk("SPO driver EXIT\n");

	// Odstranitev registracije znakovne naprave
	unregister_chrdev(major, "spo_device");
}

ssize_t spo_driver_read(struct file *filep, char *buffer, size_t count, loff_t *offp)
{
	// Več o registrih RTC
	// https://web.fe.up.pt/~pfs/aulas/lcom2017/at/19rtc.pdf

	// Trenutna ura iz RTC
	outb(4, 0x70);
    uint8_t val = inb(0x71);
	printk("SPO hour-rtc: %02X", val);

	// Kontrast z uporabo C-jevske knjižnice
	// Ta način ni dovoljen pri reševanju naloge!
    struct rtc_time rtc_td = rtc_ktime_to_tm(ktime_get_real());
    printk("SPO whole-rtc: %ptRs", &rtc_td);

	return 0;
}