#include "minilibmx.h"

bool mx_isspace(char c) {
    if (((int)c > 8 && (int)c < 14) || (int) c == 32) {
        return 1;
    }
    return 0;
}
