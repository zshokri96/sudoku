#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int table[10][10], soduku_bt[100][2][10], cnt, tmp, mark[10][10], col[10][10];

int ans[10][10] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 2, 3, 9, 5, 6, 7, 4, 8, 1},
    {0, 4, 7, 5, 3, 8, 1, 9, 2, 6},
    {0, 1, 6, 8, 4, 2, 9, 7, 3, 5},
    {0, 9, 1, 3, 6, 4, 8, 2, 5, 7},
    {0, 7, 2, 6, 9, 1, 5, 8, 4, 3},
    {0, 5, 8, 4, 7, 3, 2, 1, 6, 9},
    {0, 3, 4, 2, 1, 7, 6, 5, 9, 8},
    {0, 8, 5, 7, 2, 9, 3, 6, 1, 4},
    {0, 6, 7, 1, 8, 5, 4, 3, 7, 2}
};

void setcol (int value){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), value);
}

void Soduku_print (){
    setcol(15);
    int i, j;
    for(i=1;i<=9;i++)
        printf("   %d", i);
    printf("\n ");
    for(i=1;i<=9;i++)
        printf(" ---");
    printf("\n");
    for(i=1;i<=9;i++){
        printf("%d :", i);
        for(j=1;j<=9;j++)
            if (table[i][j])
                printf("_"), setcol(col[i][j]), printf("%d", table[i][j]), setcol(15), printf("_:");
            else
                printf("_ _:");
        printf("\n");
    }
}

void Soduku_check(){
    int i, j, now;
    for (i=1;i<=9;i++)
        for (j=1;j<=9;j++)
            mark[i][j] = 0;
    for (i=1;i<=9;i++)
        for (j=1;j<=9;j++)
            mark[i][table[i][j]] = 1;
    for (i=1;i<=9;i++)
        for (j=1;j<=9;j++)
            if (!mark[i][j])
                return;

    for (i=1;i<=9;i++)
        for (j=1;j<=9;j++)
            mark[i][j] = 0;
    for (i=1;i<=9;i++)
        for (j=1;j<=9;j++)
            mark[i][table[j][i]] = 1;
    for (i=1;i<=9;i++)
        for (j=1;j<=9;j++)
            if (!mark[i][j])
                return;

    for (i=1;i<=9;i++)
        for (j=1;j<=9;j++)
            mark[i][j] = 0;
    for (i=1;i<=9;i++)
        for (j=1;j<=9;j++)
            now = ((i-1)/3)*3 + (j+2)/3, mark[now][table[i][j]] = 1;
    for (i=1;i<=9;i++)
        for (j=1;j<=9;j++)
            if (!mark[i][j])
                return;
    tmp++;
}

void Soduku_solver (int now){
    if (now > cnt){
        Soduku_check();
        return;
    }
    int mark2[10], i, j, x = soduku_bt[now][0][0], y = soduku_bt[now][1][0], fi, se;
    for (i=1;i<=9;i++)
        mark2[i] = 0;
    for (i=1;i<=9;i++)
        mark2[table[x][i]] = 1;
    for (i=1;i<=9;i++)
        mark2[table[i][y]] = 1;
    fi = ((x-1)/3)*3+1, se = ((y-1)/3)*3+1;
    for (i=fi;i<fi+3;i++)
        for (j=se;j<se+3;j++)
            mark2[table[i][j]] = 1;
    for (i=1;i<=9;i++)
        if (!mark2[i]){
            table[x][y] = i;
            Soduku_solver(now+1);
            table[x][y] = 0;
        }
}

int main (){
    srand(time(NULL));
    int i, j, x, y, now, fi, se, th, k;
    for (i=1;i<=3;i++){
        x = rand()%3+1, y = rand()%3+1;
        for (j=1;j<=9;j++){
            now = ans[j][x];
            ans[j][x] = ans[j][y];
            ans[j][y] = now;
        }
    }
    for (i=1;i<=3;i++){
        x = rand()%3+4, y = rand()%3+4;
        for (j=1;j<=9;j++){
            now = ans[j][x];
            ans[j][x] = ans[j][y];
            ans[j][y] = now;
        }
    }
    for (i=1;i<=3;i++){
        x = rand()%3+7, y = rand()%3+7;
        for (j=1;j<=9;j++){
            now = ans[j][x];
            ans[j][x] = ans[j][y];
            ans[j][y] = now;
        }
    }

    for (i=1;i<=3;i++){
        x = rand()%3+1, y = rand()%3+1;
        for (j=1;j<=9;j++){
            now = ans[x][j];
            ans[x][j] = ans[y][j];
            ans[y][j] = now;
        }
    }
    for (i=1;i<=3;i++){
        x = rand()%3+4, y = rand()%3+4;
        for (j=1;j<=9;j++){
            now = ans[x][j];
            ans[x][j] = ans[y][j];
            ans[y][j] = now;
        }
    }
    for (i=1;i<=3;i++){
        x = rand()%3+7, y = rand()%3+7;
        for (j=1;j<=9;j++){
            now = ans[x][j];
            ans[x][j] = ans[y][j];
            ans[y][j] = now;
        }
    }

    for(i=1;i<=9;i++){
        for(j=1;j<=9;j++)
            table[i][j] = ans[i][j];
    }
    while (85 > 0){
        fi = rand()%9+1, se = rand()%9+1;
        if(!table[fi][se])
            continue;
        cnt++;
        i = table[fi][se];
        table[fi][se] = 0;
        soduku_bt[cnt][0][0] = fi, soduku_bt[cnt][1][0] = se, tmp = 0;
        Soduku_solver(1);
        if (tmp > 1 || cnt > 45)
            break;
    }
    if (tmp > 1)
        table[fi][se] = i;
    for (i=1;i<=9;i++)
        for (j=1;j<=9;j++)
            col[i][j] = 15;
    Soduku_print();
    while (cnt > 0){
        scanf("%d%d%d", &fi, &se, &th);
        system("cls");
        if (ans[fi][se] == th && table[fi][se] != th)
        {
            col[fi][se] = 10, table[fi][se] = th, cnt--;
        }
        else if (table[fi][se] != ans[fi][se])
        {
            col[fi][se] = 12, table[fi][se] = th;
        }
        Soduku_print();
    }
    printf("Nice ...\n");
    return 0;
}
