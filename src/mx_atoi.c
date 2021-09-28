#include "minilibmx.h"

int mx_atoi(const char *str, int *err) {
    int i = -1;
    int result = 0;
    int minus = 1;
    if(str[0] == '-') {
        minus = -1;
        i++;
    }else if(str[0] == '+'){
        i++;
    }
    
    while (str[++i]) {
        if (mx_isdigit(str[i]) && !mx_isspace(str[i]))
            result = (result * 10 + str[i]) - '0';
        else
            *err = 1;
            
    }
    return result * minus;
}
