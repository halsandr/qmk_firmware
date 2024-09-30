#include <stdio.h>
#include "wpm.h"

char wpm_str[9];

const char *read_wpm(void) {
    sprintf(wpm_str, "WPM: %i", get_current_wpm());
    return wpm_str;
}