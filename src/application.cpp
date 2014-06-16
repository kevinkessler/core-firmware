#include "application.h"

#define MAX_ONEWIRE 9

DS18B20 *ds1,*ds2;

uint8_t addr1[]={0x28,0xfb,0x21,0xb7,0x03,0x00,0x00,0x52};
uint8_t addr2[]={0x28,0xae,0x31,0x61,0x03,0x00,0x00,0xe3};

void setup()
{
	i2cInitialize();
	bmp085Calibration();

#if defined (DEBUG_BUILD)
	DEBUG("One Wire Device Addresses");

	OneWire *search=new OneWire(D2);
	search->reset();
	uint8_t addr[8];
	while(search->search(addr))
	{
		DEBUG("%X %X %X %X %X %X %X %X", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5], addr[6], addr[7]);
	}

	delete search;
#endif

	ds1=new DS18B20(D2,addr1);
	ds2=new DS18B20(D2,addr2);

}

// This routine loops forever
void loop()
{

    delay(10000);

	char rom[35];
	ds1->getROM(rom);
	float celsius = ds1->getTemperature();
	float fahrenheit = ds1->convertToFahrenheit(celsius);

	DEBUG("Temperature: %2.2f Celsius, %2.2f Fahrenheit (Chip Name: %s %s)", celsius, fahrenheit, ds1->getChipName(),rom);

	ds2->getROM(rom);
	celsius = ds2->getTemperature();
	fahrenheit = ds2->convertToFahrenheit(celsius);

	DEBUG("Temperature: %2.2f Celsius, %2.2f Fahrenheit (Chip Name: %s %s)", celsius, fahrenheit, ds1->getChipName(),rom);


	float temp=getBMP085Temperature();
	float press=getBMP085Pressure();

	DEBUG("BMP085 T=%f Press=%f",temp,press);

	float lux=max44009GetLux();
	DEBUG("Lux=%f",lux);

	uint8_t status=mpl3115Measure();
	if(status==MPL3115_SUCCESS)
	{
		temp=mpl3115GetTemperature();
		press=mpl3115GetPressure();
		DEBUG("MPL3115 T=%f Press=%f",temp,press);
	}
	else
		DEBUG("MPL3115 Failure");

}

