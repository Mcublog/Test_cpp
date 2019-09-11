// Crc_test.c : Defines the entry point for the console application.
//

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "example.h"
#include "inc/gas_math.h"


DeviceParameters_t DeviceParam;

#define TOROIDAL_42L (0)
#define TOROIDAL_54L (1)

int main()
{
	const uint16_t step = 1;
	TankParameters_t tank;
	
	int volume = 0;
	if (TOROIDAL_42L)
	{
		tank.Diameter = 600;
		tank.Height   = 200;
		volume = 42;
	}

	if (TOROIDAL_54L)
	{
		tank.Diameter = 660;
		tank.Height   = 220;
		volume = 54;
	}

	tank.Height = 200;
	tank.Lenght = 0;
	tank.Liquid = PROPANE;
	tank.mix = 0;
	tank.nominal_fill = 0;
	tank.Orientation = VERTICAL;
	tank.Shape = TOROIDAL;

	DeviceParam.debug_on = false;
	DeviceParam.DisplayValue = DISPLAY_PERCENT;
	DeviceParam.ScaleType = SCALE_DIGITS;
	DeviceParam.TankParameters = tank;

	uint16_t tof = 100;
	int temp = 23;
	float level = 0;

	float level_old = level;
	uint16_t num = 0;
	const float diff = 5.0;

	printf("Shape: %s_%dL\n",	"TOROIDAL", volume);
	printf("Height: %d\n",	tank.Height);
	printf("===============================\r\n");

	for (int t = 0; t < 30; t++)
	{
		printf("Temp: %d\n", t);
		for (uint16_t i = step; i < 10000; i += step)
		{
			num++;
			level = GetGasLevel(i, temp);
			if (i == step) level_old = level;
			printf("%d: level: %f\n", num, level);
			if (level >= (level_old + diff) || level <= (level_old - diff))
			{
				printf("%d: diff between steps too hight: %f >= max diff %f\n", num, fabs(level_old - level), diff);
				system("pause");
			}
			level_old = level;
			if (level > 100) break;
		}
		num = 0;
		printf("===============================\n\n");
	}

    system("pause");
    return 0;
}

