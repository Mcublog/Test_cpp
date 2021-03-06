// Crc_test.c : Defines the entry point for the console application.
//

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "example.h"

#define ACC_BUFFER_SIZE (16)
#define ACC_BUFFER_MASK (ACC_BUFFER_SIZE - 1)

typedef struct
{
    uint32_t    collected_cnt;
    uint32_t    modulo;

    uint32_t    win_len;
    uint32_t    repeat_num;
    float       overlap;

    uint32_t    idxIn;
    uint32_t    idxOut;

    uint32_t acc_samples[ACC_BUFFER_SIZE];
} test_proccesing_t;

uint32_t idxDiff(uint32_t idxIN, uint32_t idxOUT);
uint32_t idxDiff(uint32_t idxIN, uint32_t idxOUT)
{
    if (idxIN >= idxOUT)
        return (idxIN - idxOUT);
    else
        return ((ACC_BUFFER_SIZE - idxOUT) + idxIN);
}

int main()
{
    uint32_t repeate = 0;
    test_proccesing_t _alg_procces =
    {
        .collected_cnt = 0,

        .win_len       = 8,
        .repeat_num    = 5,
        .overlap       = 0.25,

        .idxIn = 0,
        .idxOut =0,

        .acc_samples = {0}
    };


    for (repeate = 0; repeate < 3 * 8; repeate++)
    {
        for (uint32_t i = 0; i < 5; i++)
        {
            _alg_procces.acc_samples[_alg_procces.idxIn++] = i;
            _alg_procces.idxIn &= ACC_BUFFER_MASK;
        }
        _alg_procces.collected_cnt += 5;

        if (_alg_procces.collected_cnt >= _alg_procces.win_len)
        {
            float data = 0;
            // process alg
            printf("\r\n");
            for (uint32_t i = 0; i < _alg_procces.win_len; i++)
            {
                uint32_t temp = _alg_procces.acc_samples[_alg_procces.idxOut++];
                _alg_procces.idxOut &= ACC_BUFFER_MASK;
                printf("_alg_procces.acc_samples_old[%d]: %d\r\n", i, temp);
                data += temp;
            }
            data = (data / _alg_procces.win_len);
            _alg_procces.collected_cnt = 0;
            
            printf("===============================\r\n");
            printf("idxIn: %d\r\n", _alg_procces.idxIn);
            printf("idxOut: %d\r\n", _alg_procces.idxOut);
            printf("Modulo: %d\r\n", idxDiff(_alg_procces.idxIn, _alg_procces.idxOut));
            printf("data: %#f\r\n", data);
            printf("_alg_procces.collected_cnt after proccess: %d\r\n", _alg_procces.collected_cnt);
            printf("===============================\r\n");
        }
    }

    system("pause");
    return 0;
}

