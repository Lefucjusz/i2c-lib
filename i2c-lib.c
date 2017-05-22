#include "i2c-lib.h"


int i2c_t::InitBus() //creates handler to i2c bus used later for every operation
{
	i2cHandle = open("/dev/i2c-1", O_RDWR);
	if (i2cHandle < 0)
		return -1;
	return 0;
}

int i2c_t::CloseBus() //releases handler to i2c bus
{
	if(close(i2cHandle))
		return -1;
	return 0;
}

int i2c_t::SetAddress(uint8_t addr) //addresses device connected to i2c bus
{
	if(ioctl(i2cHandle, I2C_SLAVE, addr))
		return -1;
	return 0;
}

int i2c_t::SendByte(uint8_t reg, uint8_t byte) //sends byte (8 bits) to specified register
{
	if(i2c_smbus_write_byte_data(i2cHandle, reg, byte))
		return -1;
	return 0;
}

int i2c_t::SendByte(uint8_t byte) //sends byte (8 bits) to device without specifying register
{
	if(i2c_smbus_write_byte(i2cHandle, byte))
		return -1;
	return 0;
}

uint8_t i2c_t::ReadByte(uint8_t reg) //reads byte (8 bits) from specified register
{
	return i2c_smbus_read_byte_data(i2cHandle, reg);
}

uint8_t i2c_t::ReadByte() //reads byte (8 bits) without specifying register
{
	return i2c_smbus_read_byte(i2cHandle);
}

int i2c_t::SendWord(uint8_t reg, uint16_t word) //sends word (16 bits) to specified register
{
	if(i2c_smbus_write_word_data(i2cHandle, reg, word))
		return -1;
	return 0;
}

uint16_t i2c_t::ReadWord(uint8_t reg) //reads word (16 bits) from specified register
{
	return i2c_smbus_read_word_data(i2cHandle, reg);
}
