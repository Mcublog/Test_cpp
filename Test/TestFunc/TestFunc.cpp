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
    cout << i<<endl;
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

typedef struct __epd_frame_t
{
	uint16_t width;          // width of frame
	uint16_t height;         // height of frame
	uint16_t bytes_per_line; // bytes per line
	//const uint8_t* ac;       // pointer to a storage
} epd_frame_t;

// See parameter of figure in image_struct.c
void get_button_coord(const int x, const int y, epd_frame_t *f)
{
	const int screen_w = 800;
	const int screen_h = 600;

	int touch_x = 0;
	int touch_y = 0;

	cout << "----------- Touch coord ------------\n";
	
	touch_x = screen_w - x;
	if (touch_x < 0) cout << "out of border: " << touch_x << '\n';
	cout << "x1: " << x + 20 << '\n';
	cout << "x2: " << x + f->width + 10 << '\n';

	//touch_x = dw - x;
	//if (touch_x < 0) cout << "out of border: " << touch_x << '\n';
	//cout << "x1: " << touch_x << '\n';

	touch_y = screen_h - y;
	if (touch_y < 0) cout << "out of border: " << touch_y << '\n';
	cout << "y1: " << touch_y - 10 << '\n';
	cout << "y2: " << touch_y - f->height + 10 << '\n';
	cout << "------------------------------------\n";
}

int main() 
{

	epd_frame_t epd_colibrate_tank_button = {
	  240, /* XSize */
	  80, /* YSize */
	  60, /* BytesPerLine */
	  //acColibrateTankButton    /* Pointer to picture data (indices) */
	};

	get_button_coord(90, 140, &epd_colibrate_tank_button);

	cout << endl;
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

