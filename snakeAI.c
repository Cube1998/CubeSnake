
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define maxn 30
#define maxm 40

//Group
int ME_HEAD = 2 ;
int ME_BODY = 1 ;
int Enemy_Body =  10;
int Enemy_Head =  11;


int CurDirection;

int map[maxn][maxm];
int DirX[4] = {0,-1,0,1};
int DirY[4] = {-1,0,1,0};
int HeadX;
int HeadY;

//const int Alert_range ;

void encodeMap(){
    
    for(int i = 0;i<maxn;i++)
        for(int j = 0 ;j<maxm;j++){
            if(map[i][j] == 2017202034){
                map[i][j] = ME_BODY;
            }
            else if(map[i][j] >= 70340 && map[i][j] <=70343){
                CurDirection = map[i][j] - 70340;
                map[i][j] = ME_HEAD;
                HeadX = i;
                HeadY = j;
               
            }
            else if(map[i][j] <= 0 ){
                //Nothing happen
            }
            else if(map[i][j] >= 2000000000){
                map[i][j] = Enemy_Body;
            }
            else {
                map[i][j] = Enemy_Head;
            }
            
        }
}
int isAtWall(int x,int y){
    return (x == 0 || x == maxn-1||y ==0 || y ==maxm -1);
}

//判断到某一点之间有没有障碍物
int judgeToPoint(int xx,int yy){
    return 1;
}

//判断能否前往墙壁
int dirToWall(){
    int flag = 1;
    if(((CurDirection+2)%4) != 0){
        flag = 1;
        for(int y = 0 ; y < HeadY ; y++){
            if(map[HeadX][y]>0 && map[HeadX][y]!=ME_BODY){
                flag = 0;
            }
        }
        if(flag == 1) return 0;
    }
    if(((CurDirection+2)%4) != 1){
        flag = 1;
        for(int x = 0 ; x < HeadX ; x++){
            if(map[x][HeadY]>0 && map[x][HeadY]!=ME_BODY){
                flag = 0;
            }
        }
        if(flag == 1) return 1;
    }
    
    if(((CurDirection+2)%4) != 2){
        flag = 1;
        for(int y = maxm ; y > HeadY ; y--){
            if(map[HeadX][y]>0 && map[HeadX][y]!=ME_BODY){
                flag = 0;
            }
        }
        if(flag == 1 ) return 2;
    }
    
    if(((CurDirection+2)%4) != 3){
        flag = 1;
        for(int x = maxn ; x > HeadX ; x--){
            if(map[x][HeadY]>0 && map[x][HeadY]!=ME_BODY){
                flag = 0;
            }
        }
        if(flag == 1) return 3;
    }
    
    return -1;
    
}

//TODO : 报警函数
int isAlert(){
    return 1;
}

int isAvaluble(int x,int y){
    return (x>-1 && x < maxn && y>-1 && y<maxm && (map[x][y] != Enemy_Head) && (map[x][y]!=Enemy_Body)) ;
}

//决策
int Solve(){
    
    
    //未达到墙
    if(!isAtWall(HeadX,HeadY)){
        int ToWall = dirToWall();
        if(ToWall != -1)return ToWall;
        else {
            srand((unsigned)time(NULL));
            return rand()%4;
        }
    }
    else if (isAtWall(HeadX,HeadY)){
        int x_next = HeadX + DirX[CurDirection];
        int y_next = HeadY + DirY[CurDirection];
        if(isAvaluble(x_next,y_next))return CurDirection;
        else if(HeadX == 0 && HeadY == 0){
            if(CurDirection == 0)return 3;
            if(CurDirection == 1)return 2;
        }
        else if(HeadX == maxn-1 && HeadY == 0){
            if(CurDirection == 3)return 2;
            if(CurDirection == 0)return 1;
        }
        else if(HeadX == maxn-1 && HeadY == maxm -1){
            if(CurDirection == 2)return 1;
            if(CurDirection == 3)return 0;
        }
        else if(HeadX == 0 && HeadY == maxm -1){
            if(CurDirection == 1)return 0;
            if(CurDirection == 2)return 3;
        }
        else {
            int tmp_x = HeadX + DirX[(CurDirection+1)%4];
            int tmp_y = HeadY + DirY[(CurDirection+1)%4];
            if(isAvaluble(tmp_x,tmp_y))
                return (CurDirection+1)%4;
            else return (CurDirection-1)%4;
        }
        
    }
    return 0;
}

//输入地图
void get_map(){
    
    for(int i = 0 ; i<maxm ; i++)
        for(int j = 0 ; j<maxn ; j++)
            scanf("%d", &map[i][j]);
    
    
}

void print(){
    printf("=========================\n");
    for(int i = 0 ; i<maxn ; i++){
        
        for(int j = 0 ; j<maxm ; j++){
            
            if(map[i][j]==2) printf("%c ",map[i][j]+'A');
            else printf("  ");
        }
        printf("\n");

            }
    printf("=========================\n");
}

void solve2(){
    int k = Solve();
    print();
    map[HeadX+DirX[k]][HeadY+DirY[k]] = 70340 + k;
    map[HeadX][HeadY] = 0 ;
}
int main(){
    
    get_map();
    
    
    //printf("%d\n", Solve());

    printf("%d\n", rand()%4);
    
    return 0;
    
    
}