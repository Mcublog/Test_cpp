// TestFunc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

#define MAX(x, y, r) do{\
                        int X = x;\
                        int Y = y;\
                        X > Y? r=X:r=Y;\
                     }while(0)

int power(int x, unsigned p) {
	int answer = x;
	/* считаем answer */
	if (p != 0)
	{
		if (p & 1 == 0)
		{
			for (int i = 0; i < (p - 1); i++) answer = answer << 1;
		}
		else
		{
			for (int i = 0; i < (p - 1); i++) answer = answer * x;
		}
	}
	else return 1;
	return answer;
}

int foo(int n) {
	static int i = 0;
	cout << i << endl;
	i++;
	if (n <= 0)
		return 1;
	return foo((n * 2) / 3) + foo(n - 2);
}

unsigned GCD(unsigned a, unsigned b) {

	if (a != 0 && b != 0)
	{
		if (a > b) a = a % b;
		else b = b % a;
		GCD(a, b);
	}
	else return a + b;
}

#define MEM_MAX_SIZE (32)
#define LAST_KEY	 (0xAA)
#define FREE_KEY	 (0xFF)

typedef struct
{
	uint8_t opt;
	uint8_t data[4];
}odo_rec_t;

uint8_t mem[MEM_MAX_SIZE];

odo_rec_t* read_record(uint32_t adr, uint8_t* mem, uint32_t max_size)
{
	//check max size
	if (adr + sizeof(odo_rec_t) > max_size) return NULL;
	return (odo_rec_t*)(&mem[adr]);
}

uint32_t find_last_record()
{
	odo_rec_t* rec = NULL;
	for (int i = 0; i < MEM_MAX_SIZE; i = i + sizeof(odo_rec_t))
	{
		rec = read_record(i, mem, MEM_MAX_SIZE);
		if (rec != NULL)
		{
			if (rec->opt == LAST_KEY)
			{
				//cout << "adr: " << i << '\n';
				//cout << "rec->opt: " << rec->opt << '\n';
				return i;
			}
			else if (rec->opt == FREE_KEY)
			{
				return MEM_MAX_SIZE;
			}
		}
	}
	return MEM_MAX_SIZE;
}

uint32_t write_rec(uint32_t adr, odo_rec_t* rec, uint8_t* mem, uint32_t max_size)
{
	if (adr + sizeof(odo_rec_t) > max_size) return 0;

	uint8_t* data = (uint8_t*)rec;

	for (int i = 0; i < sizeof(odo_rec_t); i++) mem[adr + i] = data[i];
	return 1;
}

void write_odo(uint32_t odo)
{
	uint32_t adr = find_last_record();
	uint32_t* d = NULL;
	odo_rec_t* rec = NULL;

	if (adr != MEM_MAX_SIZE)
	{
		rec = read_record(adr, mem, MEM_MAX_SIZE);
		d = (uint32_t*)rec->data;
		//clear opt
		rec->opt = 0x00;
		write_rec(adr, rec, mem, MEM_MAX_SIZE);
		adr += sizeof(odo_rec_t);
	}
	else adr = 0;

	//mark opt
	odo_rec_t rec_wr;
	rec_wr.opt = LAST_KEY;
	d = (uint32_t*)&rec_wr.data;
	*d = odo;
	
	if (write_rec(adr, &rec_wr, mem, MEM_MAX_SIZE) == 0)
	{
		adr = 0;
		write_rec(adr, &rec_wr, mem, MEM_MAX_SIZE);
	}
}

uint32_t read_odo()
{
	uint32_t adr = find_last_record();
	odo_rec_t* rec = read_record(adr, mem, MEM_MAX_SIZE);
	if (rec == NULL) return 0;
	uint32_t *odo = (uint32_t*)rec->data;
	return *odo;
}

int main() {
	
	for (int i = 0; i < sizeof(mem); i++) mem[i] = 0xFF;

	uint32_t odo = 0;
	for (int i = 0; i < 127; i++)
	{
		write_odo(odo);
		cout << "read_odo: " << read_odo() << '\n';
		odo++;
	}

    system("pause");
    return 0;
}

void test (void)
{
    cout << "power " << power(2, 5) << endl;

    vector<int> srcVec;
    for (int val = 0; val < 10; val++)
    {
        srcVec.push_back(val);
    }

    for_each(srcVec.begin(), srcVec.end(), [](int _n)
    {
        _n++;
        cout << _n << " ";
    });
    cout << endl << endl;

    int a = 10;
    int b = 20;
    int c = 0;

    MAX(--a, b, c);

    cout << "c = " << c << endl;

    system("pause");
}

