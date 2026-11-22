#include <stdio.h>
#define MAX 20
int adj[MAX][MAX];
int n;
void bfs(int start){
int visited[MAX]={0};
int queue[MAX];
int front=0,rear=0;
visited[start]=1;
queue[rear++]=start;
while(front<rear){
    int v=queue[front++];
    printf("%d ",v);
    for (int u=0;u<n;u++){
        if (adj[v][u]==1 && !visited[u]){
            visited[u]=1;
            queue[rear++]=u;
        }
    }
}
}
int main(){
    
    printf("Enter the number of vertices (max %d)",MAX);
    scanf("%d",&n);
    if (n>=MAX|| n<=0){ printf("invalid input\n"); return 0;}
    int e,start;
   printf("Enter number of edges: ");
   scanf("%d",&e);
  for(int i=0;i<e;i++){
    int a,b;
    scanf("%d %d",&a,&b);
    adj[a][b]=1;
    adj[b][a]=1;
  }
  printf("Enter the starting vertex: ");
  scanf("%d",&start);
  if(start<0 || start>=n){ printf("Invalid_Input\n"); return 0;}
  printf("BFS traversal\n");
  bfs(start);
  printf("\n");
  return 0;


}