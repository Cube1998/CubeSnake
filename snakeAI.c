
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define maxn 30
#define maxm 40

int map[maxn][maxm];

const int Alert_range ;


void get_map(){
    for(int i = 0 ; i<maxm ; i++)
        for(int j = 0 ; j<maxn ; j++)
            scanf("%d", &map[i][j]);
    
}


