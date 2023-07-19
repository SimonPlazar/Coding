#include "spo_module.h"

MODULE_AUTHOR("Simon Plazar");
MODULE_DESCRIPTION("Modul, ki implementira branje podatkov iz RTC modula in njihov izpis v tok sporočil iz jedra (dmegs)");
MODULE_LICENSE("GPL");

// Major številka znakovne naprave
static int major;

module_init(spo_driver_init);
module_exit(spo_driver_exit);

// Struktura/Tabela operacij
struct file_operations spo_fops = 
{
	read: spo_driver_read
};

static int spo_driver_init(void) {
    printk("SPO driver INIT\n");

    major = register_chrdev(0, "spo_device_1", &spo_fops);

    if (major < 0) {
        printk("SPO registering char device failed with %d\n", major);
        return major;
    } else {
        printk("SPO registering char device %d\n", major);
    }

    return 0;
}

static void spo_driver_exit(void) {
    printk("SPO driver EXIT\n");

    // Odstranitev registracije znakovne naprave
    unregister_chrdev(major, "spo_device_1");
}

// Branje podatka iz RTC
unsigned char readFromRTC(unsigned char address) {
    unsigned char data;
    outb(address, 0x70);
    data = inb(0x71);
    return data;
}

// Pretvorba binarne v decimalno število
unsigned char toDecimal(unsigned char bcd) {
    unsigned char enice = bcd & 0x0F;
    unsigned char desetice = (bcd >> 4) & 0x0F;
    return (desetice * 10) + enice;
}

ssize_t spo_driver_read(struct file *filep, char *buffer, size_t count, loff_t *offp) {
    unsigned char seconds, minutes, hours, day, month, year;

    // Branje trenutnega časa in datuma iz RTC
    seconds = readFromRTC(0x00);
    minutes = readFromRTC(0x02);
    hours = readFromRTC(0x04);
    day = readFromRTC(0x07);
    month = readFromRTC(0x08);
    year = readFromRTC(0x09);
    
    // Pretvorba v decimalno obliko
    seconds = toDecimal(seconds);
    minutes = toDecimal(minutes);
    hours = toDecimal(hours);
    day = toDecimal(day);
    month = toDecimal(month);
    year = toDecimal(year);

    // Izpis trenutnega časa in datuma
    printk("SPO date-time: 20%d-%d-%d %d:%d:%d\n", year, month, day, hours, minutes, seconds);
    return 0;
}