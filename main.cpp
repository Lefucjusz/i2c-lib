#include "i2c-lib.h"
#include <stdio.h>

#define DS1307_ADDR 0x68
#define SECS_REG 0x00
#define MINS_REG 0x01
#define HRS_REG 0x02

unsigned char bcd2dec(unsigned char bcd)
{
	return 10*(bcd>>4)+(bcd&0x0F);
}

unsigned char dec2bcd(unsigned char dec)
{
	return ((dec/10*16)+(dec%10));
}

int main()
{
	char choice;
	int hr, min, sec;
	i2c_t i2c;
	printf("I2C bus test...\n");
	if(i2c.InitBus() < 0)
	{
		printf("Bus initialisation error!\n");
		return -1;
	}
	if(i2c.SetAddress(DS1307_ADDR) < 0)
	{
		printf("Failed to acquire bus access!\n");
		return -1;
	}
	printf("Do you wanna set time?: ");
	scanf("%c", &choice);
	if(choice == 'y')
	{
		printf("Enter time in HH MM format: ");
		scanf("%d%d", &hr, &min);
		i2c.SendByte(SECS_REG, 0x00);
		i2c.SendByte(MINS_REG, dec2bcd(min));
		i2c.SendByte(HRS_REG, dec2bcd(hr));
	}
	while(1)
	{
		sec = bcd2dec(i2c.ReadByte(SECS_REG));
		min = bcd2dec(i2c.ReadByte());
		hr = bcd2dec(i2c.ReadByte());
		printf("Time: %02d:%02d:%02d\n", hr, min, sec);
		usleep(1000000);
	}
	i2c.CloseBus();
	return 0;
}
