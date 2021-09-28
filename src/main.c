#include "minilibmx.h"


char **read_map(char* file_name, int *row, int *cols) {
    char *str = mx_file_to_str(file_name);
    if(mx_strlen(str) < 2){
        mx_printerr("map does not exist\n");
        exit(-1);
    }
    int rows = mx_count_substr(str, "\n") + 1;
    int columns = 0;
    if(((double)mx_strlen(str) / rows) - (mx_strlen(str) / rows) != 0){ //проверка на длину строк
        mx_printerr("map error\n");
        exit(-1);
    }

    for (int i = 0; i < mx_strlen(str); i++) { //проверка на правильность символов 
        if(str[i] != '#' && str[i] != '.' && str[i] != ',' && str[i] != '\n'){
            mx_printerr("map error\n");
            exit(-1);
        }
    }
    
    for(int i = 0; str[i] != '\n'; i++){ //длина строки
        if(str[i] != ',')
            columns++;
    }  
    char **map = malloc(sizeof(char*) * rows);
    for (int i = 0; i < rows; i++) {
        map[i] = malloc(sizeof(char) * columns);
    }
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if(*str == '\n'){
                str++;
                break;
            }
            if(*str == ',')
                str++;
            map[i][j] = *str;
            str++;
        }
        str++;
    }
    *row = rows;
    *cols = columns;
    return map;
}

int **map_to_matrix(char **map, int rows, int cols){
    int **matrix = malloc(sizeof(int*) * rows);
    for (int i = 0; i < rows; i++) {
        matrix[i] = malloc(sizeof(int) * cols);
    }
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(map[i][j] == '#')
                matrix[i][j] = -1;
            if(map[i][j] == '.')
                matrix[i][j] = -2;
        }
    }
    return matrix;
}


int main(int argc, char *argv[]) {
    int rows = 0;
    int cols = 0;
    if (argc != 6) { 
        mx_printerr("usage: ./way_home [file_name] [x1] [y1] [x2] [y2]\n");
        exit(-1);
    }
    int at_err = 0;
    point *start = (point*)malloc(sizeof(point));
    point *end = (point*)malloc(sizeof(point));
    start->x = mx_atoi(argv[3], &at_err);
    start->y = mx_atoi(argv[2], &at_err);

    end->x = mx_atoi(argv[5], &at_err);
    end->y = mx_atoi(argv[4], &at_err);

    if(at_err) {
        mx_printerr("error\n");
        exit(-1);
    }

   

    char **map = read_map(argv[1], &rows, &cols);
    int **map_int = map_to_matrix(map, rows, cols);

     if(start->x < 0 || start->y < 0 || start->y >= cols || start->x >= rows || 
        end->x < 0 || end->y < 0 || end->y >= cols || end->x >= rows) {
        mx_printerr("points are out of map range\n");
        exit(-1);
    }

    mx_alhororithm(map_int, rows, cols, start, end);

    for (int i = 0; i < rows; i++) {
        free(map[i]);
        free(map_int[i]);
        map[i] = NULL;
        map_int[i] = NULL;
    }
    free(start);
    free(end);
    free(*map);
    free(*map_int);
    return 0;
}


