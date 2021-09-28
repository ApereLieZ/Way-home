#include "minilibmx.h"

void fill(int **arr, int dist, int x, int y, int width, int height) {
    if(x-1 >= 0 && arr[x-1][y] == -2) {
        arr[x-1][y] = dist + 1;
    } 
    if(x+1 < width && arr[x+1][y] == -2) {
        arr[x+1][y] = dist + 1;
    } 
    if(y-1 >= 0 && arr[x][y-1] == -2) {
        arr[x][y-1] = dist + 1;
    } 
    if(y+1 < height && arr[x][y+1] == -2) {
        arr[x][y+1] = dist + 1;
    } 
}

void make_road(int **arr, point *cursor, int width, int height) {
    int temp = arr[cursor->x][cursor->y];    
    if (cursor->x - 1 >= 0 && arr[cursor->x - 1][cursor->y] == temp - 1) {
        arr[cursor->x][cursor->y] = 0;
        cursor->x = cursor->x - 1;
        return;
    }    
    if (cursor->y - 1 >= 0 && arr[cursor->x][cursor->y - 1] == temp - 1) {
        arr[cursor->x][cursor->y] = 0;
        cursor->y = cursor->y - 1;
        return;
    }
    if (cursor->x + 1 < height && arr[cursor->x + 1][cursor->y] == temp - 1) {
        arr[cursor->x][cursor->y] = 0;
        cursor->x = cursor->x + 1;
        return;
    }      
    if (cursor->y + 1 < width && arr[cursor->x][cursor->y + 1] == temp - 1) {
        arr[cursor->x][cursor->y] = 0;
        cursor->y = cursor->y + 1;
        return;
    } 
}

void mx_find_path(int **arr,int ext ,int width, int height, point *end) {
    point *cursor = (point*)malloc(sizeof(point));
    cursor->x = end->x;
    cursor->y = end->y;
    for(int i = ext; i > 0; i--) {
        make_road(arr, cursor, width, height);
    } 
    free(cursor);
}

void mx_print_arr (int **arr, int width, int height, int dist, point *end, int ext) {
    int file_w = open("path.txt", O_WRONLY | O_CREAT, 0644);
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            
            if (arr[i][j] == -1) {
                write(file_w, "#", 1);
            }
            else if (j == end->y && i == end->x && ext == dist)
                write(file_w, "X", 1);
            else if (arr[i][j] == dist) {
                write(file_w, "D", 1);               
            }
            else if (arr[i][j] == 0) {
                write(file_w, "*", 1);
            }
            else 
                write(file_w, ".", 1);
        }
            write(file_w, "\n", 1);
            
        }
        close(file_w);
    }

void mx_alhororithm(int **arr, int width, int height ,point *begin, point *end) {
    
    int dist = 0;
    int ext = 0;

    if(arr[begin->x][begin->y] == -1) {
        mx_printerr("enter point cannot be an obstacle\n");
        exit(-1);
    }

    if(arr[end->x][end->y] == -1) {
        mx_printerr("exit point cannot be an obstacle\n");
        exit(-1);
    }
    
    arr[begin->x][begin->y] = 0;
    
    bool check = true;

    while(check) {
        check = false;
        for(int i = 0; i < width; i++) {
            for(int j = 0; j < height; j++) {
                if(arr[i][j] == dist) {
                    fill(arr, dist, i, j, width, height);
                    check = true;
                }
            }
        }
        dist++;
    }
    dist -= 2 ;

    if(arr[end->x][end->y] == -2) {
        mx_printerr("route not found\n");
        exit(-1);
    }
    

    ext = arr[end->x][end->y];

    
    
    mx_find_path(arr, ext, width, height, end);
    
    mx_print_arr(arr, width, height, dist, end, ext);

    mx_printstr("dist=");
    mx_printint(dist);
    mx_printchar('\n');

    mx_printstr("exit=");
    mx_printint(ext);
    mx_printchar('\n');
}


