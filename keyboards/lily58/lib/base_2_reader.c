#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

char keylog_b2_str[22] = {};
char keylog_b2_raw[17] = {};
uint16_t sum = 0;

void set_keylog_b10(uint16_t keycode) {
    int cur = 0;
    // Numbers 30 to 39 are the numbers 1 to 0 (through 9)
    // skip 39 as 0 is already in cur
    if ((29 < keycode) && (keycode < 39)) {
        cur = keycode - 29;
    } else if (keycode == 39) {
        cur = 0;
    } else {
        sum = 0;

        // Clear keylog string
        sprintf(keylog_b2_str, " ");
        return;
    }

    // Check the we aren't going to overflow
    if (((sum * 10) + cur) <= UINT16_MAX) {
        // Update sum by multiplying by 10 and adding the new cur
        sum = (sum * 10) + cur;
    } else {
        // If we are going to overflow, reset sum
        sum = 0;
    }

    // Itterate through the chars of keylog_b2_raw
    // replace each char with the base 2 representation of sum
    // in the correct order
    for (int i = 0; i < 16; i++) {
        keylog_b2_raw[i] = (sum & (1 << (15 - i))) ? '1' : '0';
    }
    // Null terminate the string
    keylog_b2_raw[16] = '\0';

    sprintf(keylog_b2_str, "BIN: %s", keylog_b2_raw);
}

const char *read_base_2(void) {
    return keylog_b2_str;
}