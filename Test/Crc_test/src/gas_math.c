// All regarding level measurement
#include "gas_math.h"

#define wr_trace printf

//#include "main.h"
//#include "custom.h"
#include <math.h>


#define TANK_42L_VOLUME 42
#define TANK_54L_VOLUME 54
#define TANK_42L_MAX_FILL_PERCENT 0.8
#define tank_42l_1liter 100/TANK_42L_VOLUME//TANK_42L_MAX_FILL_PERCENT

#define FILTER_SIZE 20
uint32_t filter_data[FILTER_SIZE];

extern DeviceParameters_t DeviceParam;

//static CalibTable_t Tank_toroid_42L[] = 
//{
//	{0,     00*tank_42l_1liter}, {0,      01*tank_42l_1liter}, {11.544, 02*tank_42l_1liter}, {27.935,  03*tank_42l_1liter}, {34.04,  04*tank_42l_1liter}, {38.57, 05*tank_42l_1liter}, {43.29,  06*tank_42l_1liter}, {48.19,  07*tank_42l_1liter}, {52.725, 8*tank_42l_1liter}, {57,     9*tank_42l_1liter},
//	{62.53, 10*tank_42l_1liter}, {66.97,  11*tank_42l_1liter}, {71.41,  12*tank_42l_1liter}, {76.035,  13*tank_42l_1liter}, {80.5675,14*tank_42l_1liter}, {85,    15*tank_42l_1liter}, {90,     16*tank_42l_1liter}, {94,     17*tank_42l_1liter}, {99,    18*tank_42l_1liter}, {104.34,19*tank_42l_1liter},
//	{108.78,20*tank_42l_1liter}, {113.035,21*tank_42l_1liter}, {117.105,22*tank_42l_1liter}, {120.5275,23*tank_42l_1liter}, {124.32, 24*tank_42l_1liter}, {128.76,25*tank_42l_1liter}, {133.015,26*tank_42l_1liter}, {137.085,27*tank_42l_1liter}, {140.5, 28*tank_42l_1liter}, {144.3, 29*tank_42l_1liter},
//	{148.74,30*tank_42l_1liter}, {153,    31*tank_42l_1liter}, {157,    32*tank_42l_1liter}, {160,     33*tank_42l_1liter}, {164.28, 34*tank_42l_1liter}, {168.72,35*tank_42l_1liter}, {173,    36*tank_42l_1liter}, {177,    37*tank_42l_1liter}, {180.46,38*tank_42l_1liter}, {184.26,39*tank_42l_1liter},
//	{188.7, 40*tank_42l_1liter}, {193,    41*tank_42l_1liter}, {200,    42*tank_42l_1liter}
//};

//static CalibTable_t Tank_toroid_42L[] = 
//{
//	{00,00*tank_42l_1liter}, {00,01*tank_42l_1liter}, {17,02*tank_42l_1liter}, {22,03*tank_42l_1liter}, {28,04*tank_42l_1liter}, {32,05*tank_42l_1liter}, {35,06*tank_42l_1liter}, {39,07*tank_42l_1liter}, {44, 8*tank_42l_1liter}, {47,9*tank_42l_1liter},
//	{51,10*tank_42l_1liter}, {56,11*tank_42l_1liter}, {59,12*tank_42l_1liter}, {63,13*tank_42l_1liter}, {66,14*tank_42l_1liter}, {71,15*tank_42l_1liter}, {75,16*tank_42l_1liter}, {78,17*tank_42l_1liter}, {82,18*tank_42l_1liter}, {85,19*tank_42l_1liter},
//	{90,20*tank_42l_1liter}, {93,21*tank_42l_1liter}, {96,22*tank_42l_1liter}, {101,23*tank_42l_1liter}, {104,24*tank_42l_1liter}, {108,25*tank_42l_1liter}, {111,26*tank_42l_1liter}, {115,27*tank_42l_1liter}, {120, 28*tank_42l_1liter}, {123, 29*tank_42l_1liter},
//	{127,30*tank_42l_1liter}, {130,31*tank_42l_1liter}, {135,32*tank_42l_1liter}, {139,33*tank_42l_1liter}, {142,34*tank_42l_1liter}, {147,35*tank_42l_1liter}, {151,36*tank_42l_1liter}, {154,37*tank_42l_1liter}, {158,38*tank_42l_1liter}, {164,39*tank_42l_1liter},
//	{169,40*tank_42l_1liter}, {184,41*tank_42l_1liter}, {200,42*tank_42l_1liter}
//};

//static CalibTable_t Tank_toroid_42L[] = 
//{
//	{000,00*tank_42l_1liter}, {000,01*tank_42l_1liter}, {010,02*tank_42l_1liter}, {022,03*tank_42l_1liter}, { 29,04*tank_42l_1liter}, {031,05*tank_42l_1liter}, {035,06*tank_42l_1liter}, { 39,07*tank_42l_1liter}, {042, 8*tank_42l_1liter}, {047, 9*tank_42l_1liter},
//	{051,10*tank_42l_1liter}, {056,11*tank_42l_1liter}, { 59,12*tank_42l_1liter}, {063,13*tank_42l_1liter}, { 68,14*tank_42l_1liter}, {071,15*tank_42l_1liter}, {075,16*tank_42l_1liter}, { 79,17*tank_42l_1liter}, { 84,18*tank_42l_1liter}, { 87,19*tank_42l_1liter},
//	{ 91,20*tank_42l_1liter}, { 96,21*tank_42l_1liter}, {100,22*tank_42l_1liter}, {109,23*tank_42l_1liter}, {113,24*tank_42l_1liter}, {116,25*tank_42l_1liter}, {121,26*tank_42l_1liter}, {125,27*tank_42l_1liter}, {129,28*tank_42l_1liter}, {132,29*tank_42l_1liter},
//	{141,30*tank_42l_1liter}, {144,31*tank_42l_1liter}, {149,32*tank_42l_1liter}, {153,33*tank_42l_1liter}, {158,34*tank_42l_1liter}, {161,35*tank_42l_1liter}, {165,36*tank_42l_1liter}, {169,37*tank_42l_1liter}, {171,38*tank_42l_1liter}, {178,39*tank_42l_1liter},
//	{184,40*tank_42l_1liter}, {190,41*tank_42l_1liter}, {200,42*tank_42l_1liter}
//};

static CalibTable_t Tank_toroid_42L[] = 
{
	{000,00*tank_42l_1liter}, {12,01*tank_42l_1liter}, {25.2,02*tank_42l_1liter}, {30.34,03*tank_42l_1liter}, { 31.08,04*tank_42l_1liter}, {35.52,05*tank_42l_1liter}, {39.96,06*tank_42l_1liter}, { 43.66,07*tank_42l_1liter}, {48.10, 8*tank_42l_1liter}, {51.80, 9*tank_42l_1liter},
	{56.24,10*tank_42l_1liter}, {59.94,11*tank_42l_1liter}, { 63.64,12*tank_42l_1liter}, {68.08,13*tank_42l_1liter}, { 71.78,14*tank_42l_1liter}, {76.22,15*tank_42l_1liter}, {79.92,16*tank_42l_1liter}, { 84.36,17*tank_42l_1liter}, { 88.06,18*tank_42l_1liter}, { 92.5,19*tank_42l_1liter},
	{ 96.20,20*tank_42l_1liter}, { 100.64,21*tank_42l_1liter}, {104.34,22*tank_42l_1liter}, {108.78,23*tank_42l_1liter}, {112.48,24*tank_42l_1liter}, {116.92,25*tank_42l_1liter}, {120.62,26*tank_42l_1liter}, {125.06,27*tank_42l_1liter}, {128.76,28*tank_42l_1liter}, {133.20,29*tank_42l_1liter},
	{136.90,30*tank_42l_1liter}, {141.34,31*tank_42l_1liter}, {145.04,32*tank_42l_1liter}, {149.48,33*tank_42l_1liter}, {153.18,34*tank_42l_1liter}, {157.62,35*tank_42l_1liter}, {161.32,36*tank_42l_1liter}, {165.76,37*tank_42l_1liter}, {169.46,38*tank_42l_1liter}, {173.9,39*tank_42l_1liter},
	{181,40*tank_42l_1liter}, {187.8,41*tank_42l_1liter}, {200,42*tank_42l_1liter}
};

struct velo
{
  int t;
  int prop;
  int but;
};

#define WATER_C     1480

struct velo V[] =
{
  { 0,  1224, 1321 },
  { -50,  1224, 1321 },
  { -40,  1159, 1264 },
  { -30,  1093, 1207 },
  { -20,  1028, 1150 },
  { -10,   963, 1093 },
  {   0,   897, 1036 },
  {  10,   832,  979 },
  {  20,   767,  922 },
  {  30,   702,  865 },
  {  40,   636,  808 },
  {  50,   571,  751 },
  { INT32_MAX, 0,    0 }
};

#define V_SZ  (sizeof(V)/sizeof(struct velo))
	
int get_velocity(int T, what G)
{
  int k;
	int v;
	
  for(k=0; ; k++)
    if(T > V[k].t && T <= V[k+1].t)
      break;

  switch(G)
  {
		case WATER:
			return WATER_C;
		
    case PROPANE:
      v = V[k+1].prop;
      break;

    case BUTANE:
      v = V[k+1].but;
      break;
		
		case MIX:
			v = V[k+1].prop * (DeviceParam.TankParameters.mix/100);
			v += V[k+1].but * (1-DeviceParam.TankParameters.mix/100);			
			break;
  }
	
	//if (DeviceParam.debug_on)		wr_trace("Speed %d\r\n", v);
	
  return (int) round(v);
}

float GetGasLevel(uint16_t tof, int temp)
{
	float dist;
	float level_in_mm=0;
	
	dist = (tof / 2) * 1000.0f;
	switch (DeviceParam.TankParameters.Liquid) {
		case WATER:
			level_in_mm = dist*get_velocity(temp, WATER)*1e-6;
			//if (DeviceParam.debug_on)				wr_trace_rtc("%d %.2f ", tof, level_in_mm);
			break;
		case PROPANE:
			level_in_mm = dist*get_velocity(temp, PROPANE)*1e-6;
			//wr_trace("PropaneLevel: TOF %d Temp %d dist %.1f level %d\r\n", tof, temp, dist, level_in_mm);
			break;
		case BUTANE:
			level_in_mm = dist*get_velocity(temp, BUTANE)*1e-6;
			//wr_trace("ButaneLevel: TOF %d Temp %d dist %.1f level %d\r\n", tof, temp, dist, level_in_mm);
			break;
		case MIX:
			level_in_mm = dist*get_velocity(temp, MIX)*1e-6;
			//wr_trace("MixLevel: TOF %d Temp %d dist %.1f level %d\r\n", tof, temp, dist, level_in_mm);
			break;

		default:
			//wr_trace("Liquid level undefined\r\n");
			break;
	}
	return level_in_mm;
}

float Calib_42l(float GasLevel)
{
	int i;
	float RetVal, tmp;
	
		for (i=0; i<sizeof(Tank_toroid_42L)/sizeof(CalibTable_t); i++) {
			if (GasLevel <= Tank_toroid_42L[i].Level)
				break;
		}
		
		if (GasLevel == Tank_toroid_42L[i].Level) {
			RetVal = (uint32_t)round(Tank_toroid_42L[i].Percent);
			//if (DeviceParam.debug_on) wr_trace("%.2f\r\n", Tank_toroid_42L[i].Percent);
			return (uint32_t)round(RetVal*DeviceParam.TankParameters.nominal_fill/100);
		}
		if (i>0) {
			tmp = (Tank_toroid_42L[i].Percent - Tank_toroid_42L[i-1].Percent);
			tmp /= (Tank_toroid_42L[i].Level - Tank_toroid_42L[i-1].Level);
			tmp*= (GasLevel - Tank_toroid_42L[i-1].Level);
			tmp+= Tank_toroid_42L[i-1].Percent;
			//if (DeviceParam.debug_on) wr_trace("%.2f\r\n", tmp);
			RetVal = (uint32_t)round(tmp)*DeviceParam.TankParameters.nominal_fill/100;
		} /*else {
			RetVal = (uint32_t)round(DeviceParam.CustomTable[i].Percent);
		}	*/
		//if (DeviceParam.debug_on) wr_trace("%.2f\r\n", Tank_toroid_42L[i].Percent);
		return RetVal;	
}
uint32_t CalculateFilling(float GasLevel)
{
	uint32_t RetVal=0;
	float tmp=0;
	
	// Check what we want to display: %, litres etc
	switch (DeviceParam.DisplayValue) {
		case DISPLAY_PERCENT:
			// check for the tank shape
			switch (DeviceParam.TankParameters.Shape) {
				case CYLINDRICAL:
					if (DeviceParam.TankParameters.Orientation == VERTICAL) {
						// Percent is easy to calculate
						// Maybe make some normalization as 80% are full tank
						RetVal = DeviceParam.TankParameters.Height*100/GasLevel;
						//if (DeviceParam.debug_on)							wr_trace("Calculated filling %d%%\r\n", RetVal);
						return RetVal;
					} else {
						// put some math here for round-shaped tank
						// or use custom table here
						return RetVal=0;
					}
					
				case TOROIDAL:
					
					// use 42L tank measured table here
					tmp = Calib_42l(GasLevel);
					
					// 42L toroidal tank
					if ((DeviceParam.TankParameters.Diameter == 600) && (DeviceParam.TankParameters.Height == 200)) {
						return tmp;
					}
					
					// 54L toroidal tank
					if ((DeviceParam.TankParameters.Diameter == 660) && (DeviceParam.TankParameters.Height == 220)) {
						return tmp*TANK_54L_VOLUME/TANK_42L_VOLUME;
					}
											
					// unknown tank, just do some math
					RetVal = (uint32_t)round(DeviceParam.TankParameters.nominal_fill*GasLevel/DeviceParam.TankParameters.Height);
					//wr_trace("Calculated filling %.1f%%\r\n", tmp);
					return RetVal;
				
				case UNDEFINED:
					break;
			}
			break;
		
		case DISPLAY_LITERS:
			// check for the tank shape
			switch (DeviceParam.TankParameters.Shape) {
				case CYLINDRICAL:
					//if (DeviceParam.debug_on) wr_trace("Calculated filling %dL\r\n", RetVal);
					return RetVal;
				
				case TOROIDAL:
					tmp = Calib_42l(GasLevel);
					if ((DeviceParam.TankParameters.Diameter == 600) && (DeviceParam.TankParameters.Height == 200)) {
						// 42-L tank, 5 mm is 1 liter
						RetVal = GasLevel/5;
					}
					//wr_trace("Calculated filling %dL\r\n", RetVal);
					return RetVal;
				
				case UNDEFINED:
					break;
			}
			break;
		case DISPLAY_CONSUMPTION:
			//wr_trace("Consumption TBD %dL/h\r\n", RetVal);
			break;
		
		default:
			//wr_trace("Value to display undefined\r\n");
			return 0;
	}
	return RetVal;
}
#ifdef USE_SCREEN_FILTER
uint32_t FilterValue(uint32_t ScreenValue)
{
	static uint32_t index;
	static bool filter_empty = true;
	
	uint32_t i;
	uint32_t RetVal=0;
	
	// quick fill on first run
	if (filter_empty) {
		filter_empty = false;
		for (i=0; i<FILTER_SIZE; i++) {
			filter_data[i] = ScreenValue;
		}
	}
	
	filter_data[index] = ScreenValue;
	
	for (i=0; i<FILTER_SIZE-2; i++) {
		filter_data[i+1] = ((filter_data[i] + filter_data[i+2])/2);
	}
	
	for (i=0; i<FILTER_SIZE; i++) {
		RetVal += filter_data[i];
	}	
	RetVal = round(RetVal/FILTER_SIZE);
	
	//RetVal = filter_data[index];
	
	index++;
	if (index >= FILTER_SIZE)
		index = 0;

	//wr_trace("ScreenValue: %02d FilteredValue: %02d\r\n", ScreenValue, RetVal);
	return RetVal;
}
#endif
