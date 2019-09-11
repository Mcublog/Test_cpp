// Crc_test.c : Defines the entry point for the console application.
//

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "example.h"
#include "inc/gas_math.h"

#define ACC_BUFFER_SIZE (16)
#define ACC_BUFFER_MASK (ACC_BUFFER_SIZE - 1)


DeviceParameters_t DeviceParam;

int main()
{
	TankParameters_t tank;
	tank.Diameter = 20;
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
	int temp = 12;
	float level = 0;

	printf("Shape: %s\n", "TOROIDAL");
	printf("Diameter: %d\n", tank.Diameter);
	printf("Height: %d\n", tank.Height);
	printf("Temp: %d\n", temp);
	printf("Height: %d\n", tank.Height);
	printf("===============================\r\n");

	for (uint16_t i = 5; i < 350; i += 5)
	{
		level = GetGasLevel(i, temp);
		printf("level: %f\n", level);
		if (level > 100) break;
	}

	printf("===============================\r\n");

    system("pause");
    return 0;
}

