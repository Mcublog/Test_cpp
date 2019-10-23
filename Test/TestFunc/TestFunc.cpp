// TestFunc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <time.h>       /* time */

using namespace std;

typedef enum {
	LIS3DH_FULLSCALE_2 = 0x00,
	LIS3DH_FULLSCALE_4 = 0x01,
	LIS3DH_FULLSCALE_8 = 0x02,
	LIS3DH_FULLSCALE_16 = 0x03
} LIS3DH_Fullscale_t;

typedef struct {
	int16_t AXIS_X;
	int16_t AXIS_Y;
	int16_t AXIS_Z;
} AxesRaw_t;

typedef enum {
	LIS3DH_ODR_1Hz = 0x01,
	LIS3DH_ODR_10Hz = 0x02,
	LIS3DH_ODR_25Hz = 0x03,
	LIS3DH_ODR_50Hz = 0x04,
	LIS3DH_ODR_100Hz = 0x05,
	LIS3DH_ODR_200Hz = 0x06,
	LIS3DH_ODR_400Hz = 0x07,
	LIS3DH_ODR_1620Hz_LP = 0x08,
	LIS3DH_ODR_1344Hz_NP_5367HZ_LP = 0x09
} LIS3DH_ODR_t;

typedef struct
{
	LIS3DH_ODR_t freq;
	LIS3DH_Fullscale_t full_scale;
	uint32_t acc_size;
	uint32_t th;
	uint32_t th_alert;
}lis_cfg_t;

float lis3d_get_axis_f(int16_t axis, LIS3DH_Fullscale_t fs)
{
	if (fs == LIS3DH_FULLSCALE_2)
	{
		return (float)axis / 15987;
	}
	if (fs == LIS3DH_FULLSCALE_4)
	{
		return (float)axis / 7840;
	}
	if (fs == LIS3DH_FULLSCALE_8)
	{
		return (float)axis / 3883;
	}
	if (fs == LIS3DH_FULLSCALE_16)
	{
		return (float)axis / 1280;
	}
	return 0;
}

int16_t lis3d_get_th_lis(uint32_t th_mg, LIS3DH_Fullscale_t s)
{
	uint16_t th = 0;
	switch (s)
	{
	case LIS3DH_FULLSCALE_2:
	{
		th = th_mg / 16;
	}break;
	case LIS3DH_FULLSCALE_4:
	{
		th = th_mg / 32;
	}break;
	case LIS3DH_FULLSCALE_8:
	{
		th = th_mg / 62;
	}break;
	case LIS3DH_FULLSCALE_16:
	{
		th = th_mg / 186;
	}break;
	}
	return th;
}

int32_t lis3d_get_th_mg(int16_t th, LIS3DH_Fullscale_t s)
{
	uint32_t th_mg = 0;
	switch (s)
	{
	case LIS3DH_FULLSCALE_2:
	{
		th_mg = th * 16;
	}break;
	case LIS3DH_FULLSCALE_4:
	{
		th_mg = th * 32;
	}break;
	case LIS3DH_FULLSCALE_8:
	{
		th_mg = th * 62;
	}break;
	case LIS3DH_FULLSCALE_16:
	{
		th_mg = th * 186;
	}break;
	}
	return th_mg;
}

uint32_t lis3d_check_alert(const AxesRaw_t* d, const lis_cfg_t* cfg)
{
	LIS3DH_Fullscale_t scale = cfg->full_scale;

	int tph_alert_mg = lis3d_get_th_mg(cfg->th_alert, scale);
	float tph_alert_g = tph_alert_mg / 1000;

	float x_g = lis3d_get_axis_f(d->AXIS_X, scale);
	float y_g = lis3d_get_axis_f(d->AXIS_Y, scale);
	float z_g = lis3d_get_axis_f(d->AXIS_Z, scale);

	float e = (int)sqrt((d->AXIS_X * d->AXIS_X) + (d->AXIS_Y * d->AXIS_Y) + (d->AXIS_Z * d->AXIS_Z));
	e = lis3d_get_axis_f((int)e, scale);

	printf("x: %.2f, y: %.2f, z: %.2f, e: %.2f \n", x_g, y_g, z_g, e);
	printf("alert th: %f\n", tph_alert_g);

	if (e >= tph_alert_g) return 1;

	if (x_g < 0) x_g *= -1;
	if (y_g < 0) y_g *= -1;
	if (z_g < 0) z_g *= -1;

	if (x_g >= tph_alert_g) return 1;
	if (y_g >= tph_alert_g) return 1;
	if (z_g >= tph_alert_g) return 1;

	return 0;
}


int main()
{
	srand(time(NULL));

	lis_cfg_t cfg =
	{
		LIS3DH_ODR_400Hz,
		LIS3DH_FULLSCALE_2,
		256,
		lis3d_get_th_lis(500, LIS3DH_FULLSCALE_2),
		lis3d_get_th_lis(1200, LIS3DH_FULLSCALE_2),
	};

	AxesRaw_t d = {
		-50,//.AXIS_X 
		200, //.AXIS_Y 
		-350  //.AXIS_Z 
	};
	int16_t e = sqrt((d.AXIS_X * d.AXIS_X) + (d.AXIS_Y * d.AXIS_Y) + (d.AXIS_Z * d.AXIS_Z));


	printf("x: %d, y: %d, z: %d, e: %d \n", d.AXIS_X, d.AXIS_Y, d.AXIS_Z, e);
	printf("alert th: %d\n", cfg.th_alert);

	uint32_t res = lis3d_check_alert(&d, &cfg);
	printf("res: %d\n", res);

	system("pause");
	return 0;
}
