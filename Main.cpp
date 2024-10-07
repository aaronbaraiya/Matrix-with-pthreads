#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
struct arg{
    int r;
    int c;
    int array[100][100];

    int col[30];
    int row[30];
};

int *dotproduct(void* argument);
int main(void){
    struct arg struc;
    //set row and col's value as 0
    for(int i=0;i<30;i++){
        struc.row[i]=0;
        struc.col[i]=0;
    }
    //get some input for A matrix
    int m1,n1;
    printf("A\'s row: ");
    scanf("%d",&m1);
    printf("A\'s column: ");
    scanf("%d",&n1);
    int array1[m1][n1];
    for(int i=0;i<m1;i++){
        for(int j=0;j<n1;j++){
            scanf("%d ",&array1[i][j]);
        }
    }
    //get some input for B matrix
    int m2,n2;
    printf("B\'s row: ");
    scanf("%d",&m2);
    printf("B\'s column: ");
    scanf("%d",&n2);

    int array21[m2][n2];
    for(int i=0;i<m2;i++){
        for(int j=0;j<n2;j++){
            scanf("%d ",&array21[i][j]);
        }
    }
    //traverse B matrix
    int array22[n2][m2];
    for(int i=0;i<n2;i++){
        for(int j=0;j<m2;j++){
            array22[i][j]=array21[j][i];
        }
    }
    //put row and col values into row and col attributions and current row and col index to r and c
    pthread_t pthread;
    int result[m1][n2];
    for(int i=0;i<m1;i++){
        for(int j=0;j<n2;j++){
            struc.r=i;
            struc.c=j;
            for(int k=0;k<sizeof(array1[i])/sizeof(int);k++)
                struc.row[k]=array1[i][k];
            for(int k=0;k<sizeof(array22[j])/sizeof(int);k++)
                struc.col[k]=array22[j][k];
            pthread_create(&pthread,NULL,dotproduct,(void*)&struc);
            sleep(0.7);
        }
    }
    //print struc.array's values out
    for(int i=0;i<m1;i++){
        for(int j=0;j<n2;j++){
            printf("%d ",struc.array[i][j]);
        }
        printf("\n");
    }
    pthread_join(pthread,NULL);

  return 0;
}
//multiply values in row and col and sum it up and put it into current index
int *dotproduct(void* argument){
    arg *myarg=(arg*)argument;
    int sum=0;
    for(int i=0;i<sizeof(myarg->row)/sizeof(int);i++){
        sum+=myarg->row[i]*myarg->col[i];
    }
    myarg->array[myarg->r][myarg->c]+=sum;
}
