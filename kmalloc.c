#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL v2");
MODULE_VERSION("2.4");
MODULE_AUTHOR("h1Ryk0");
MODULE_DESCRIPTION("KMALLOC");

char *memory;

static int __init kernelInit(void)
{
    int count;
    static char buffer[] = "Testing";
    memory = kmalloc(strlen(buffer) + 1, GFP_DMA);
    if (memory == NULL)
    {
        printk(KERN_INFO "Not possible allocate memory\n");
        return -ENOMEM;
    }

    strcpy(memory, buffer);
    printk(KERN_ALERT "Allocating memory\n");
    printk("%zu Bytes Allocated\n", strlen(memory));

    pr_info("\t========================\n");
    for (count = 0; count < strlen(buffer); count++)
    {
        pr_info("\t|Kernel Address: %px|\n", &memory[count]);
    }
    pr_info("\t========================\n");
    return 0;
}

static void __exit kernelExit(void)
{
    printk(KERN_INFO "Deallocating kernel memory\n");
    kfree(memory);
    memory = NULL;
    if(memory == NULL)
    {
        pr_alert("\t\\__Deallocated Memory\n");
    }
    else{
        pr_info("Error\n");
    }
}

module_init(kernelInit);
module_exit(kernelExit);
