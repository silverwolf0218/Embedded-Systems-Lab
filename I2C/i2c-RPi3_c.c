#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include<wiringPi.h>
// The arduino board i2c address (slave)
#define ADDRESS 0x04
#define PIN_forInterrupt 26
// The I2C bus: This is for V2 pi's. For V1 Model B you need i2c-0
static const char *devName = "/dev/i2c-1";
int file;
void my_callback(){
	char buf[1];
	if (read(file, buf, 1) == 1) {
		int temp = (int) buf[0];
		printf("Received %d\n", temp);
	}
	printf("Please enter a number 0 - 255: ");
}
int main(int argc, char** argv) {
	if(wiringPiSetupGpio()<0){
		 printf("wiringPi setup failed!\n");
		 return 1;
	}
	pinMode(PIN_forInterrupt,INPUT);
	pullUpDnControl(PIN_forInterrupt,PUD_UP);
	int  num;
	printf("I2C: Connecting\n");
	if ((file = open(devName, O_RDWR)) < 0) {
		fprintf(stderr, "I2C: Failed to access %d\n", devName);
		exit(1);
	}
	printf("I2C: acquiring buss to 0x%x\n", ADDRESS);
	if (ioctl(file, I2C_SLAVE, ADDRESS) < 0) {
		fprintf(stderr, "I2C: Failed to acquire bus access/talk to slave 0x%x\n", ADDRESS);
		exit(1);
	}
	if(wiringPiISR(PIN_forInterrupt,INT_EDGE_BOTH,my_callback) <0){
		printf("ISR setup failed!\n");
		return 1;
	}

	printf("Please enter a number 0 - 255: ");
	while (scanf("%d", &num) == 1) {
		printf("Sending %d\n", num);
		if (write(file, &num, 1) == 1) {
		// As we are not talking to direct hardware but a microcontroller we
		// need to wait a short while so that it can respond.
		//
		// 10ms seems to be enough but it depends on what workload it has
			usleep(100000);
		}
	}	
	return 0;
}
