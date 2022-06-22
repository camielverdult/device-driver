//
// Created by Camiel Verdult & Marnix Laar on 22/06/2022.
//

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

static int my_init(void)
{
    struct cdev *my_cdev = cdev_alloc();
    my_cdev->ops = &my_fops;

    return 0;
}

static void my_exit(void)
{
    return;
}

module_init(my_init);
module_exit(my_exit);