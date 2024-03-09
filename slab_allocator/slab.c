#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("_int0x80");
MODULE_VERSION("1.1");
MODULE_DESCRIPTION("Test for SLAB allocator");

struct object{
    int value;
};

static struct kmem_cache *slab_cache = NULL;

struct object *my_obj = NULL;

static int __init kernelInit(void)
{
    slab_cache = kmem_cache_create("slab_cache", sizeof(struct object), 0, 0, NULL);
    if(!slab_cache)
    {
        printk(KERN_ERR "Unable to create cache in SLAB\n");
        return -ENOMEM;
    }

    my_obj = kmem_cache_alloc(slab_cache, GFP_KERNEL);
    if(!my_obj)
    {
        printk(KERN_ERR "Error allocating object\n");
        kmem_cache_destroy(slab_cache);
        return -ENOMEM;
    }

    my_obj->value = 60;

    printk("Valor: %d\n", my_obj->value);

    return 0;
}

static void __exit kernelExit(void)
{
    printk(KERN_INFO "Deallocating SLAB cache\n");
    kmem_cache_free(slab_cache, my_obj);

    kmem_cache_destroy(slab_cache);

    printk(KERN_INFO "FINISHED!");
}

module_init(kernelInit);
module_exit(kernelExit);
