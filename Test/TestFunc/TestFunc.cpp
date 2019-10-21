// TestFunc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <time.h>       /* time */

using namespace std;

typedef struct {
	int16_t AXIS_X;
	int16_t AXIS_Y;
	int16_t AXIS_Z;
} AxesRaw_t;

uint32_t lis3d_check_alert(const AxesRaw_t* d, const int16_t tph_alert_max)
{
	//int16_t tph_alert_max = cfg->th_alert;
	int16_t tph_alert_min = tph_alert_max * (-1);
	int16_t e = sqrt((d->AXIS_X * d->AXIS_X) + (d->AXIS_Y * d->AXIS_Y) + (d->AXIS_Z * d->AXIS_Z));

	if (e >= tph_alert_max) return 1;

	if (d->AXIS_X >= tph_alert_max || d->AXIS_X <= tph_alert_min) return 1;
	if (d->AXIS_Y >= tph_alert_max || d->AXIS_Y <= tph_alert_min) return 1;
	if (d->AXIS_Z >= tph_alert_max || d->AXIS_Z <= tph_alert_min) return 1;

	return 0;
}


int main()
{
	AxesRaw_t d = {
		-50,//.AXIS_X 
		200, //.AXIS_Y 
		-350  //.AXIS_Z 
	};
	int16_t e = sqrt((d.AXIS_X * d.AXIS_X) + (d.AXIS_Y * d.AXIS_Y) + (d.AXIS_Z * d.AXIS_Z));

	srand(time(NULL));
	int16_t alert = rand() % 300 + 500;

	printf("x: %d, y: %d, z: %d, e: %d \n", d.AXIS_X, d.AXIS_Y, d.AXIS_Z, e);
	printf("alert th: %d\n", alert);

	uint32_t res = lis3d_check_alert(&d, alert);
	printf("res: %d\n", res);

	system("pause");
	return 0;
}
