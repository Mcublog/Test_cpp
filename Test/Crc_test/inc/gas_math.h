
#ifndef __gas_math_H
#define __gas_math_H
#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

typedef enum
{
	CLI_CMD_NONE = 0,
	GET_DID,
	GET_DEVICE,
	SET_TANK_SHAPE,
	GET_TANK_SHAPE,
	SET_TANK_HEIGHT,
	GET_TANK_HEIGHT,
	SET_TANK_LENGHT,
	GET_TANK_LENGHT,
	SET_TANK_DIAMETER,
	GET_TANK_DIAMETER,
	SET_DISPLAY_VALUE,
	GET_DISPLAY_VALUE,
	SET_TANK_ORIENTATION,
	GET_TANK_ORIENTATION,
	SET_CUSTOM_TABLE,
	GET_CUSTOM_TABLE,
	SET_LIQUID,
	GET_LIQUID,
	SET_VALUE,
	SET_DEBUG,
	SET_MIX,
	GET_MIX,
	SET_NOMINAL,
	GET_NOMINAL
} CliCommands_t;

typedef enum
{
	WATER = 0,
	PROPANE,
	BUTANE,
	MIX
} what;

typedef enum
{
	VERTICAL = 0,
	HORIZONTAL,
} CliTankOrientation_t;

typedef enum
{
	CYLINDRICAL = 0,
	TOROIDAL,
	UNDEFINED
} CliTankShape_t;

typedef enum
{
	DISPLAY_PERCENT = 0,
	DISPLAY_LITERS,
	DISPLAY_CONSUMPTION,
} DisplayValue_t;

typedef enum
{
	SCALE_DIGITS = 0,
	SCALE_BARS,
	SCALE_ARROW
} ScaleType_t;

typedef struct
{
	CliTankShape_t Shape;
	CliTankOrientation_t Orientation;
	uint32_t	Height;
	uint32_t	Lenght;
	uint32_t	Diameter;
	what			Liquid;
	uint8_t		mix;
	uint8_t   nominal_fill;
} TankParameters_t;

typedef struct
{
	float Level;
	float Percent;
} CalibTable_t;

typedef struct
{
	TankParameters_t TankParameters;
	DisplayValue_t DisplayValue;
	ScaleType_t ScaleType;
	//CalibTable_t CustomTable[11];
	bool debug_on;
}	DeviceParameters_t;

int get_velocity(int T, what G);
float GetGasLevel(uint16_t tof, int temp);
float Calib_42l(float GasLevel);
uint32_t CalculateFilling(float GasLevel);


#ifdef __cplusplus
}
#endif
#endif /*__gas_math_H */
