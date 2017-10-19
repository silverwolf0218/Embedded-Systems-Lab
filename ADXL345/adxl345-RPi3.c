#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

// The ADXL345 i2c address (slave)
#define ADDRESS 0x53
// Some registers to be used
// Data
#define Data_reg 0x32
// Bandwidth rate with Hz
#define BWRate_reg 0x2C
#define RATE_25HZ 0x09
#define RATE_50HZ 0x0A
#define RATE_100HZ 0x0B
#define RATE_200HZ 0x0C
#define RATE_400HZ 0x0D
#define RATE_800HZ 0x0E
#define RATE_1600HZ 0x0F
// Power control with mode
#define PWCtl_reg 0x2D
#define MEASURE 0x08 

// Data format with range in full resolution
#define DataFormat_reg 0x31
#define RANGE_2G 0x08
#define RANGE_4G 0x09
#define RANGE_8G 0x0A
#define RANGE_16G 0x0B
// The I2C bus: This is for V2 pi's. For V1 Model B you need i2c-0
static const char *devName = "/dev/i2c-1";

int main(int argc, char** argv) {
	int  file,num;
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
	char command[2];
	command[0]=BWRate_reg;
	command[1]=RATE_100HZ;
	write(file,command,2);
	
	command[0]=PWCtl_reg;
	command[1]=MEASURE;
	write(file,command,2);

	command[0]=DataFormat_reg;
	command[1]=RANGE_4G;
	write(file,command,2);
	sleep(1);
	
	char data[6];
	double Acc[3];
	char reg[1]={Data_reg};
	write(file,reg,1);
	while (true) {
		read(file,data,6);
		for(int i=0;i<3;i++){
			Acc[i]=((data[i+1] & 0x07)*256 + (data[i] & 0xFF));
			if(Acc[i]>1023)
				Acc[i]-=2048;
			Acc[i]*=0.004;
		}
		printf("Acceleration in X-Axis: %5.3fG /Y-Axis: %5.3fG /Z-Axis: %5.3fG \r",Acc[0],Acc[1],Acc 
                [2]);
		fflush(stdout);
		usleep(5000);
	}	
	return 0;
}
