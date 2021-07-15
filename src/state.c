#include "state.h"
#include <string.h>

int state1[2021][2021];
int m,n;
int dis[2021][2021];
int dir[8][2] = {{-1, -1}, {-1, 1}, {-1, 0}, {0, -1}, {0, 1}, {1, 0}, {1, -1}, {1, 1}};
int l,r;
int flag[2021][2021];
int secdis[2021][2021];

struct front
{
    int x;
    int y;
}pre[2021][2021];

struct node
{
    int x;
    int y;
}q[10000];

int in(int x, int y)
{
    return (x >= 0 && x < n && y >= 0 && y < m);
}

void init_State(struct State *s) {
    // TODO
}
void delete_State(struct State *s) {
    // TODO
}

void parse(struct State *s, struct PNG *p) {
    for(int i = 6; i < p->height; i = i + 8)
    {
        n = 0;
        for(int j = 1; j < p->width; j = j + 8)
        {
            struct PXL *colour = get_PXL(p, j, i);
            //printf("i = %d, j = %d\n",i,j);
            //printf("(%d,%d,%d)\t", colour->red, colour->green, colour->blue);
            int industry = 255 * 255 * 3 - colour->red * colour->red - colour->green * colour->green - colour->blue * colour->blue;
            state1[m][n] = industry;
            n++;
        }
        //puts("");
        m++;
    }
}

int solve1(struct State *s) {
    memset(dis,0x3f,sizeof(dis));
    memset(pre,-1,sizeof(pre));
    dis[0][0] = 0;
    q[r].x = 0;
    q[r].y = 0;
    r = (r + 1) % 10000;
    flag[0][0] = 1;
    while(l < r)
    {
        int nowx = q[l].x;
        int nowy = q[l].y;
        l = (l + 1) % 10000;
        flag[nowy][nowx] = 0;
        if(nowy % 2 == 0){
            for(int i = 2; i < 8; i++)
            {
                int tx = nowx + dir[i][0];
                int ty = nowy + dir[i][1];
                if(state1[ty][tx] != 0 && in(tx, ty) && dis[nowy][nowx] + state1[ty][tx] < dis[ty][tx])
                {
                    dis[ty][tx] = dis[nowy][nowx] + state1[ty][tx];
                    if(flag[ty][tx] == 0){
                        q[r].x = tx;
                        q[r].y = ty;
                        r = (r + 1) % 10000;
                        flag[ty][tx] = 1;
                    }
                    pre[ty][tx].x = nowx;
                    pre[ty][tx].y = nowy;
                }
            }
        }
        if(nowy % 2 == 1){
            for(int i = 0; i < 6; i++)
            {
                int tx = nowx + dir[i][0];
                int ty = nowy + dir[i][1];
                if(state1[ty][tx] != 0 && in(tx, ty) && dis[nowy][nowx] + state1[ty][tx] < dis[ty][tx])
                {
                    dis[ty][tx] = dis[nowy][nowx] + state1[ty][tx];
                    if(flag[ty][tx] == 0){
                        q[r].x = tx;
                        q[r].y = ty;
                        r = (r + 1) % 10000;
                        flag[ty][tx] = 1;
                    }
                    pre[ty][tx].x = nowx;
                    pre[ty][tx].y = nowy;
                }
            }
        }
    }
    /*for(int i = 0; i < m; i++)
    {
        printf("%d:",i);
        for(int j = 0; j < n; j++)
        {
            printf("%d ",state1[i][j]);
        }
        printf("\n");
    }*/
    //printf("m = %d, n = %d\n",m,n);
    return dis[m-1][n-1];
}

int solve2(struct State *s) {
    int min = 0x3f3f3f3f;
    int p = m - 1;
    int t = n - 1;
    while(p != 0 || t != 0)
    {
        memset(secdis,0x3f,sizeof(secdis));
        secdis[0][0] = 0;
        l = r = 0;
        q[r].x = 0;
        q[r++].y = 0;
        flag[0][0] = 1;
        while(l < r)
        {
            int nowx = q[l].x;
            int nowy = q[l].y;
            l = (l + 1) % 10000;
            flag[nowy][nowx] = 0;
            if(nowy % 2 == 0){
                for(int i = 2; i < 8; i++)
                {
                    int tx = nowx + dir[i][0];
                    int ty = nowy + dir[i][1];
                    if(in(tx, ty) && (tx!=t || ty!=p || nowx!=pre[p][t].x || nowy!=pre[p][t].y) && state1[ty][tx] != 0 && secdis[nowy][nowx] + state1[ty][tx] < secdis[ty][tx])
                    {
                        secdis[ty][tx] = secdis[nowy][nowx] + state1[ty][tx];
                        if(flag[ty][tx] == 0){
                           q[r].x = tx;
                            q[r].y = ty;
                            r = (r + 1) % 10000;
                            flag[ty][tx] = 1;
                        }
                    }
                }
            }
            if(nowy % 2 == 1){
                for(int i = 0; i < 6; i++)
                {
                    int tx = nowx + dir[i][0];
                    int ty = nowy + dir[i][1];
                    if(in(tx,ty) && (tx!=t || ty!=p || nowx!=pre[p][t].x || nowy!=pre[p][t].y) && state1[ty][tx] != 0 && secdis[nowy][nowx] + state1[ty][tx] < secdis[ty][tx])
                    {
                        secdis[ty][tx] = secdis[nowy][nowx] + state1[ty][tx];
                        if(flag[ty][tx] == 0){
                            q[r].x = tx;
                            q[r].y = ty;
                            r = (r + 1) % 10000;
                            flag[ty][tx] = 1;
                        }
                    }
                }
            }
        }
        if(secdis[m-1][n-1] > dis[m-1][n-1]){
            min = min < secdis[m-1][n-1] ? min : secdis[m-1][n-1];
        } 
        int a = p, b = t;
        p = pre[a][b].y;
        t = pre[a][b].x;
    }
    return min;
}