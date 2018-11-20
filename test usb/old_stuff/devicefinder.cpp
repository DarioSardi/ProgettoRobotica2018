/* compile with gcc -o boost devicefinder.cpp  -I /usr/include/libusb-1.0/ -lusb */

#include <stdio.h>
#include <libusb-1.0/libusb.h>
#include <cassert>

 uint8_t  VENDOR=0x2341;
 uint8_t  PRODID=0x0242;
int main(){
	libusb_context *ctx=NULL;
	libusb_init(&ctx);
	libusb_device **list;
	libusb_get_device_list(ctx, &list); // Returns 11 USB devices which is correct.
	for (size_t idx = 0; list[idx] != NULL; idx ++)
	{
    		libusb_device *dev = list[idx];
   		libusb_device_descriptor desc = {0};
    		int rc = libusb_get_device_descriptor(dev, &desc);
		assert(rc==0);
		printf("Vendor:Device = %04x:%04x %04x\n", desc.idVendor, desc.idProduct,desc.iManufacturer);
		printf("	INFO: %04x\n",libusb_get_device_address(dev));
}
	printf("target device vendor:%04x id=%04x\n", VENDOR,PRODID);
	return 0;
}
