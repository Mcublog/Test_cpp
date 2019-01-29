/**
 * \file
 *
 * \brief Implementation of debug trace related stuff
 *
 */


#include "hb_trace.h"             // definitions for TRACE0x macros

#if defined(HB_TRACE) || defined (HB_UNIT_TESTS)

#if !defined(HBPRINT)
#define HBPRINT printf
#endif

/********************************************************************
*  Debug flags
********************************************************************/

static uint32_t _dbg_mask1 = 0x00000000          /* comment out the following lines to disable */
                      /**/  | BIT_00000001       /* DBG_ERR   - the most critical errors */
                      /**/  | BIT_00000002       /* DBG_WARN  - critical warnings */
                      /**/  | BIT_00000004       /* DBG_INIT  - initialization information */
                      /**/  | BIT_00000008       /* DBG_INFO  - other useful information */

                      /*  | BIT_00000010*/       /* DBG_IMP   - impedance meter 1st level - START/STOP metering */
                      /*  | BIT_00000020*/       /* DBG_IMP2  - impedance meter 2nd level - in-depth data       */
                      /*  | BIT_00000040*/       /* DBG_IMP3  - real time output of measured impedance data     */
                      /**/  | BIT_00000080       /* DBG_BATT  - battery charge control                          */

                      /**/  | BIT_00000100       /* DBG_PM    - pulse meter START/STOP, etc. */
                      /*  | BIT_00000200*/       /* DBG_PM2   - module Heart profiler */
                      /*  | BIT_00000400*/       /* DBG_PM3   - additional info */
                      /*  | BIT_00000800*/       /* DBG_PROF  - performance profiler for various modules*/

                      /*  | BIT_00001000*/       /* DBG_ACC   - accmeter START/STOP, etc. */
                      /*  | BIT_00002000*/       /* DBG_ACC2  -  */     /* not in use */
                      /*  | BIT_00004000*/       /* DBG_ACC3  -  */     /* not in use */
                      /*  | BIT_00008000*/       /* DBG_ADC   - in-depth ADC debugging */

                      /**/  | BIT_00010000       /* DBG_STOR  - hb_storage operation details     */
                      /*  | BIT_00020000*/       /* DBG_STOR2 - hb_storage errors                */
                      /*  | BIT_00040000*/       /* DBG_COM   - data exchange over COM interface */
                      /*  | BIT_00080000*/       /* DBG_COM2  - HB core data exchange handlers   */

                      /*  | BIT_00100000*/       /* DBG_IO    - IO commands over serial */
                      /*  | BIT_00200000*/       /* DBG_IO2   -  */     /* not in use */
                      /*  | BIT_00400000*/       /* DBG_IO3   -  */     /* not in use */
                      /*  | BIT_00800000*/       /* DBG_FW    - Firmware loader and flasher */

                      /*  | BIT_01000000*/       /* DBG_LOG   - logging related features        */
                      /*  | BIT_02000000*/       /* DBG_I2C   - I2C related messages            */
                      /*  | BIT_04000000*/       /* DBG_DSP   - Display related messages        */
                      /*  | BIT_08000000*/       /* DBG_HE    - History Editor related messages */

                      /*  | BIT_10000000*/       /* DBG_MOD1  -  */     /* not in use */
                      /*  | BIT_20000000*/       /* DBG_TEST  - Core Tests */
#ifdef HB_UNIT_TESTS
                      /**/  | BIT_40000000       /* DBG_UTEST - Unit Tests */
#endif // HB_UNIT_TESTS
                      /*  | BIT_80000000*/       /* DBG_CTRL  - PIN-model control output */
               ; /* BE CAREFUL!, there's a semicolon in this row */


static uint32_t _dbg_mask2 = 0x00000000    /* comment out the following lines to disable */
                      /*  | BIT_00000001*/       /* DBG2_BIT1 -  */     /* not in use */
                      /*  | BIT_00000002*/       /* DBG2_BIT2 -  */     /* not in use */
                      /*  | BIT_00000004*/       /* DBG2_BIT3 -  */     /* not in use */
                      /*  | BIT_00000008*/       /* DBG2_BIT4 -  */     /* not in use */
               ; /* BE CAREFUL!, there's a semicolon in this row */


uint32_t hb_dbg_getmask(void)
{
    return _dbg_mask1;
}
uint32_t hb_dbg_getmask2(void)
{
    return _dbg_mask2;
}


void hb_dbg_setmask(uint32_t new_mask)
{
    _dbg_mask1 = new_mask;
    return;
}

void hb_dbg_setmask2(uint32_t new_mask)
{
    _dbg_mask2 = new_mask;
    return;
}
/*=================================================================*/



/********************************************************************
*  arm-gcc workaround to print out float numbers
********************************************************************/
extern void print_buf(uint8_t* buf, uint32_t len, uint32_t add_new_line);
extern void print_vartype32(void* pval);

// void new_printDouble(double v, uint32_t decDigits)
void printDouble(double v, uint32_t decDigits)
{
  uint32_t i = 1;
  uint32_t digits = decDigits;
  uint32_t intPart;
  uint32_t fractPart;
//   uint32_t diff;

  char sign = ' ';

  if (digits > 16) {
    digits = 16;
  }

  if (v < 0) {
      sign = '-';
      v = -v;
  }

  for (; decDigits != 0; i *= 10, decDigits--);

  intPart = (uint32_t)(v);

//   diff = (uint32_t)(1000 * (v - ((double)intPart)));
//   fractPart = ((uint32_t)(1000 * (v * i - ((double)intPart) * i))) / 1000;
  fractPart = (uint32_t)((v - (double)intPart) * i);

  TRACE04("%c%lu.%0*lu", sign, intPart, (int)digits, fractPart);

//   TRACE04(";  (i = %lu, intPart = %12lu, fractPart = %lu, diff = %lu)\n", i, intPart, fractPart, diff);
// //   HBPRINT("v         ["); print_buf((uint8_t*)&v, sizeof(v), 0); HBPRINT("]\n");
// //   HBPRINT("-v        ["); v = -v; print_buf((uint8_t*)&v, sizeof(v), 0); HBPRINT("]\n");
//   HBPRINT("int(v) = %12lu, uint(v) = %12lu\n", (uint32_t)((int32_t)v), (uint32_t)v);
//   HBPRINT("intPart   ["); print_vartype32(&intPart); HBPRINT("]\n");
//   HBPRINT("fractPart ["); print_vartype32(&fractPart); HBPRINT("]\n");
}
/*=================================================================*/



/********************************************************************
*  Various Buffer Print Functions
********************************************************************/

#define CHARS_PER_ROW 16

static void _print_row(char* pRow, int len);
static void _print_row2(char* pRow, int len);


static void _print_row(char* pRow, int len)
{
    static const char nib2char[16] = "0123456789abcdef";
    static char buf[52];
    int i = 0, j = 0;

    for (; i < len; i++)
    {
        buf[j++] = nib2char[(pRow[i] >> 4) & 0x0F];
        buf[j++] = nib2char[ pRow[i] & 0x0F];
        buf[j++] = ' ';

        if (j == 24) {buf[j++] = ' ';} // separator between 2 halves (8th and 9th chars)
    }

    //printf("j = %d", j - 1);
    buf[--j] = 0;
    HBPRINT("    %s\n", buf);
}

static void _print_row2(char* pRow, int len)
{
    int i = 0;

#if 0
    if ((nChars < 0) || (nChars > 16))
    {
        TRACE01("Wrong usage of _print_row(): nChars = %d", nChars);
    }
#endif

    TRACE00("    ");
    if (len > 8)
    {
        for (; i < 8; i++)
        {
            TRACE01("%.02X ", pRow[i]);
        }
        TRACE00(" ");
    }
    for (; i < len; i++)
    {
        TRACE01("%.02X ", pRow[i]);
    }
    TRACE00("\n");
}

void hb_print_buf(char* pBuf, int len)
{
    int i;

    for (i = 0; i < len; i++)
    {
        HBPRINT("%c", pBuf[i]);
    }
    HBPRINT("\n");
}

void hb_print_buf_as_hex(char* pBuf, int len)
{
    while (len > 16)
    {
        _print_row(pBuf, 16);
        pBuf += 16;
        len -= 16;
    }

    _print_row(pBuf, len);
}

void hb_print_buf_as_hex2(char* pBuf, int size)
{
    while (size > 16)
    {
        _print_row2(pBuf, 16);
        pBuf += 16;
        size -= 16;
    }

    _print_row2(pBuf, size);
}
#endif // HB_TRACE
/*=================================================================*/
