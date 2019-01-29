// TestApp.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

/**
* @brief  NAND Memory address Structure definition
*/
#define PAGE_NMBR	(64)
#define BLOCK_NMBR	(1024)
#define PLANE_NMBR  (2)

#define PLANE_SIZE (BLOCK_NMBR * PAGE_NMBR)//Plane size in page
#define BLOCK_SIZE (PAGE_NMBR)//Block size in page

typedef struct
{
	uint16_t Page;   /*!< NAND memory Page address    */
	uint16_t Block;  /*!< NAND memory Block address   */
	uint16_t Plane;   /*!< NAND memory Plane address  */
}NAND_AddressTypeDef;

uint32_t flash_adr_to_uint32(NAND_AddressTypeDef *adr);
uint32_t flash_adr_to_uint32(NAND_AddressTypeDef *adr)
{
	uint32_t a = (adr->Plane *  PLANE_SIZE) + (adr->Block * BLOCK_SIZE) + adr->Page;
	return a;
}

NAND_AddressTypeDef uint32_to_flash_adr(uint32_t adr);
NAND_AddressTypeDef uint32_to_flash_adr(uint32_t adr)
{
	NAND_AddressTypeDef a;
	a.Plane = adr / PLANE_SIZE;
	a.Block = (adr - a.Plane * PLANE_SIZE) / PAGE_NMBR;
	a.Page = adr - (a.Plane * PLANE_SIZE) - (a.Block * BLOCK_SIZE);

	return a;
}

void adr_flash_print(NAND_AddressTypeDef *adr);
void adr_flash_print(NAND_AddressTypeDef *adr)
{
	printf("Plane: %d\r\n", adr->Plane);
	printf("Block: %d\r\n", adr->Block);
	printf("Page: %d\r\n", adr->Page);
	printf("\r\n");
}

void adr_print(uint32_t *adr);
void adr_print(uint32_t *adr)
{
	printf("Adr: %d\r\n", *adr);
	printf("\r\n");
}

uint32_t adr_check(NAND_AddressTypeDef *a0, NAND_AddressTypeDef *a1);
uint32_t adr_check(NAND_AddressTypeDef *a0, NAND_AddressTypeDef *a1)
{
	if (a0->Plane != a1->Plane) return 0;
	if (a0->Block != a1->Block) return 0;
	if (a0->Page != a1->Page)	return 0;
	return 1;
}

int main()
{
	NAND_AddressTypeDef adr = { 5, 57, 0 };
	NAND_AddressTypeDef adr_new = { 0 };
	NAND_AddressTypeDef nand = { PAGE_NMBR, BLOCK_NMBR, PLANE_NMBR };
	uint32_t adr_uint = 0;

	printf("NAND Flash Adr:\r\n");
	adr_flash_print(&adr);

	adr_uint = flash_adr_to_uint32(&adr);
	adr_print(&adr_uint);

	adr_new = uint32_to_flash_adr(adr_uint);
	adr_flash_print(&adr_new);

	if	(adr_check(&adr, &adr_new)) printf("Adr check... OK\r\n");
	else printf("Adr check... Error\r\n");

    system("pause");
    return 0;
}
