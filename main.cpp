#include "mbed.h"
#include <chrono>

using namespace std::chrono_literals;

BusInOut ROWS(PA_0, PA_1, PA_2, PA_3);
BusInOut COLS(PA_5, PA_6, PA_7);
BusOut LEDS(PB_5, PB_4, PB_3, PA_15);

int get_button()
{
    ROWS.input();
    COLS.output();

    int row_btn = ROWS & ROWS.mask();
    if (row_btn == 0xE) row_btn = 0;
    else if (row_btn == 0xD) row_btn = 1;
    else if (row_btn == 0xB) row_btn = 2;
    else if (row_btn == 0x7) row_btn = 3;
    else row_btn = -15;

    COLS.input();
    ROWS.output();

    int col_btn = COLS & COLS.mask();
    if (col_btn == 0x1) col_btn = 0;
    else if (col_btn == 0x2) col_btn = 1;
    else if (col_btn == 0x4) col_btn = 2;
    else col_btn = -15;

    return row_btn * 3 + col_btn;
}

int main() {
    ROWS.mode(PullUp);
    COLS.mode(PullDown);

    while (true) {
        int mask = get_button();
        if (mask > -1 && mask < 16) {
            LEDS = mask;
        }
        ThisThread::sleep_for(250ms);
    }
}