#ifndef I2C_LIB_H
#define I2C_LIB_H
#include <unistd.h>			//Needed for I2C port
#include <fcntl.h>			//Needed for I2C port
#include <sys/ioctl.h>			//Needed for I2C port
#include <linux/i2c-dev.h>		//Needed for I2C port
#include <stdint.h>

class i2c_t
{
	public:
		int InitBus(); //creates handler to i2c bus used later for every operation
		int CloseBus(); //releases handler to i2c bus
		int SetAddress(uint8_t addr); //addresses device connected to i2c bus
		int SendByte(uint8_t reg, uint8_t byte); //sends byte (8 bits) to specified register
		int SendByte(uint8_t byte); //sends byte (8 bits) to device without specifying register
		uint8_t ReadByte(uint8_t reg); //reads byte (8 bits) from specified register
		uint8_t ReadByte(); //reads byte (8 bits) without specifying register
		int SendWord(uint8_t reg, uint16_t word); //sends word (16 bits) to specified register
		uint16_t ReadWord(uint8_t reg); //reads word (16 bits) from specified register
	private:
		int i2cHandle; //handler declaration
};
#endif
