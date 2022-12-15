#include <linux/i2c.h>
#include <linux/slab.h>
#include <linux/export.h>
#include <linux/module.h>

static struct i2c_client *ft5x0x_client;

/* 传入iic的设备地址和name给iic驱动端 */
static const unsigned short ft5x0x_i2c[] = 
{
    0x2c, 0x38, I2C_CLIENT_END
};

static __init int ft5x0x_dev_init(void)
{
    struct i2c_adapter *i2c_adap;
    struct i2c_board_info ft5x0x_info;
	
    memset(&ft5x0x_info, 0, sizeof(struct i2c_board_info));
    strlcpy(ft5x0x_info.type, "ft5x0x", I2C_NAME_SIZE);
	
    i2c_adap = i2c_get_adapter(1);
	
    /* 注册iic设备 */
    ft5x0x_client = i2c_new_probed_device(i2c_adap, &ft5x0x_info, 
                                          ft5x0x_i2c, NULL);

	i2c_put_adapter(i2c_adap);
	
    return 0;
}

static __exit void ft5x0x_dev_exit(void)
{
    i2c_unregister_device(ft5x0x_client);
}

module_init(ft5x0x_dev_init);
module_exit(ft5x0x_dev_exit);
MODULE_LICENSE("GPL");

