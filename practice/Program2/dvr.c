#include<stdio.h>

struct node
{
    int dist[20];
    int via[20] ;
};

int main()
{
    struct node router[20];
    int n;
    int cost[20][20];
    printf("Enter number of routers : ");
    scanf("%d",&n);
    printf("\nEnter cost matrix\n");
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
        {
            scanf("%d",&cost[i][j]);
            router[i].dist[j]=cost[i][j];
            router[i].via[j]=j;
        }
    printf("here\n");
    int count=0;    
    do
    {
        count=0;
        for(int i=0;i<n;i++)//for each router
        {
            for(int j=0;j<n;j++)
            {
                for(int k=0;k<n;k++)
                {
                    if(router[i].dist[j]>router[k].dist[j]+cost[i][k])
                    {
                        router[i].dist[j]=router[i].dist[k]+router[k].dist[j];
                        router[i].via[j]=k;
                        count++;
                    }
                }
            }   
        }
        printf("%d",count);
    }while(count);

    for(int i=0;i<n;i++)
    {
        printf("Router %d\n",i+1);
        for(int j=0;j<n;j++)
        {
            printf("%d -> %d : %d via %d\n",i+1,j+1,router[i].dist[j],router[i].via[j]+1);
        }
        printf("\n");
    }
    return 1;
}