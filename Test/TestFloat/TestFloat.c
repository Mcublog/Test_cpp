// TestFloat.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <tchar.h>
#include <stdio.h>
#include <stdint.h>

int main()
{
    uint16_t data = 1024;
    float temp = ((uint16_t)(75 * 3.02 * data) / 4096);
    
    printf("temp: %f\r\n", temp);
    temp = (uint16_t)(147.5 - (uint16_t)((75 * 3.02 * data) / 4096));
    printf("temp: %f\r\n", temp);
    system("pause");
    return 0;
}

