#include "application.h"

#define MAX_ONEWIRE 9

DS18B20 *ds1,*ds2;
SI7021 *si;
MPL3115 *mpl;
BMP085 *bmp;
MAX44009 *max;

uint8_t addr1[]={0x28,0xfb,0x21,0xb7,0x03,0x00,0x00,0x52};
uint8_t addr2[]={0x28,0xae,0x31,0x61,0x03,0x00,0x00,0xe3};

void setup()
{

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
	si=new SI7021();
	mpl=new MPL3115();
	bmp=new BMP085();
	max=new MAX44009();
}

// This routine loops forever
void loop()
{

	uint8_t status;

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

	status=bmp->measure();
	if(status==BMP085_SUCCESS)
		DEBUG("BMP085 T=%f Press=%f",bmp->getTemperature(),bmp->getPressure());
	else
		DEBUG("BMP085 Failed");

	status=max->measure();
	if(status==MAX44009_SUCCESS)
		DEBUG("Lux=%f",max->getLux());
	else
		DEBUG("MAX44009 Failed");

	status=mpl->measure();
	if(status==MPL3115_SUCCESS)
	{
		DEBUG("MPL3115 T=%f Press=%f",mpl->getTemperature(),mpl->getPressure());
	}
	else
		DEBUG("MPL3115 Failure");

	status=si->measure();
	if(status==SI7021_SUCCESS)
		DEBUG("Si7021 Temperature=%f Humidity=%f",si->getTemperature(),si->getHumidity());
	else
		DEBUG("SI7021 Fail");

}

