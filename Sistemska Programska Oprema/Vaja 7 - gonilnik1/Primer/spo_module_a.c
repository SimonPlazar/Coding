#include<linux/module.h>
#include<linux/init.h>

MODULE_AUTHOR("Vaje SPO");
MODULE_DESCRIPTION("Prvi Linux modul");
MODULE_LICENSE("GPL");

static int spo_module_init(void);
static void spo_module_exit(void);

module_init(spo_module_init);
module_exit(spo_module_exit);

static int spo_module_init(void)
{
	// Za izpis lahko uporabimo funkcijo printk, 
	// ki sporočilo zapiše v dnevnik (logfile). 
	// Dnevnik se privzeto nahaja v zbirki /var/log/messages
	printk("SPO module INIT\n");

	return 0;
}

static void spo_module_exit(void)
{
	// Za izpis lahko uporabimo funkcijo printk, 
	// ki sporočilo zapiše v dnevnik (logfile). 
	// Dnevnik se privzeto nahaja v zbirki /var/log/messages

	printk("SPO module EXIT\n");
}

