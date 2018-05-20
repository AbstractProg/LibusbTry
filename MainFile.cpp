#include <stdio.h>
#include <stdlib.h>
#include <libusb-1.0/libusb.h>

void printDevices(libusb_device *dev)
{
    struct libusb_device_descriptor descr;
    struct libusb_config_descriptor *config;

    const struct libusb_interface *inter;
    const struct libusb_interface_descriptor *interdesc;
    const struct libusb_endpoint_descriptor *endpointdesc;

    int ret;
    int i, j, k;

    int ret1 = libusb_get_device_descriptor(dev, &descr);

    if (ret < 0)
    {
        printf("error in getting device descriptor\n");
        return;
    }

    libusb_get_config_descriptor(dev, 0, &config);
    
    printf("Class = %d, ID = %d, no. of configs = %d, no. of interfaces = %d\n",
           descr.idVendor, descr.idProduct, descr.bNumConfigurations, config->bNumInterfaces);
}

int main()
{
    libusb_device **devs;
    libusb_context *context = NULL;

    int ret = libusb_init(&context);

    if (ret < 0)
    {
        perror("libusb_init");
        exit(1);
    }

    size_t numOfDevices = libusb_get_device_list(context, &devs);

    if (numOfDevices < 0)
    {
        printf("Error in getting device list\n");
        libusb_free_device_list(devs, 1);
        libusb_exit(context);
        exit(1);
    }

    printf("%d Devices found\n", (int)numOfDevices);

    for (int i = 0; i < numOfDevices; i++)
    {
        printDevices(devs[i]);
    }

    libusb_free_device_list(devs, 1);
    libusb_exit(context);

    return 0;
}