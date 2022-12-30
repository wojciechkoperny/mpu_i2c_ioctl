// #include <linux/i2c-dev.h>
//  #include <i2c/smbus.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <unistd.h>        //Needed for I2C port
#include <fcntl.h>         //Needed for I2C port
#include <sys/ioctl.h>     //Needed for I2C port
#include <linux/i2c-dev.h> //Needed for I2C port
#include <linux/i2c.h>

#define I2C_PI_ADAPTER "/dev/i2c-1"
#define I2C_MPU_DEVICE 0x68U

#define PWR_MGMT_1_ADDR 0x6B
#define PWR_MGMT_1_VAL 0x00

#define ACCEL_XOUT_H_ADDR 0x3B
#define ACCEL_YOUT_H_ADDR 0x3D
#define ACCEL_ZOUT_H_ADDR 0x3F

int dev;
int ret;
int err;
char buf[10];

int value;

__u8 i2c_read_register(int file, __u8 command)
{

    union i2c_smbus_data data;
    data.byte = 0;
    data.word = 0;
    int err;

    struct i2c_smbus_ioctl_data args;

    args.read_write = I2C_SMBUS_READ;
    args.command = command;
    args.size = I2C_SMBUS_BYTE_DATA;
    args.data = &data;

    err = ioctl(file, I2C_SMBUS, &args);
    if (err == -1)
    {
        fprintf(stderr, "Error while trying to send i2c: %s\n", strerror(errno));
        return err;
    }
    else
    {
        return 0xFF & data.byte;
    }
}

void main()
{
    dev = open(I2C_PI_ADAPTER, O_RDWR);
    if (dev < 0)
    {
        /* ERROR HANDLING; you can check errno to see what went wrong */
        // printf("did not open - ret %d", dev);
        err = errno;
        fprintf(stderr, "Error while trying to open i2c: %s\n", strerror(errno));
        // printf("Error while trying to open: %s\n", strerror(errno));
        exit(1);
    }
    else
    {
        printf("\nok otwarte %d", dev);
        // int addr = 0x40; /* The I2C address */
        ret = ioctl(dev, I2C_SLAVE, I2C_MPU_DEVICE);
        if (ret < 0)
        {
            /* ERROR HANDLING; you can check errno to see what went wrong */
            fprintf(stderr, "Error while trying to set up i2c: %s\n", strerror(errno));
            exit(1);
        }
        printf("\nchange slave dev id %d", ret);

        buf[0] = PWR_MGMT_1_ADDR;
        buf[1] = PWR_MGMT_1_VAL;

        if (write(dev, buf, 2) != 2)
        {
            printf("Cos Poslo nie tak");
            /* ERROR HANDLING: i2c transaction failed */
        }
        while (1)
        {

            usleep(500000);

            value = i2c_read_register(dev, ACCEL_XOUT_H_ADDR);
            value = value << 8;
            value += i2c_read_register(dev, ACCEL_XOUT_H_ADDR + 1);
            if (value >= 0x8000)
            {
                value = -(65536 - value);
            }
            printf("\nodczytaem wartosc %d", value);
        }
    }

    close(dev);
}