#include "minilibmx.h"

void mx_printint(int num) {
    if (num < 0) {
        mx_printchar('-');
        num *= -1;
    }
    if (num > 9)
        mx_printint(num / 10);
        
    char temp = (num % 10 + 48) + '\0';
    mx_printchar(temp);
}

