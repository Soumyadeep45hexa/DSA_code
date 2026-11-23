#include <stdio.h>
#define MAX 20
int n,adj[MAX][MAX];
void dfs(int start){
    int visited[MAX]={0};
    int stack[MAX * MAX];
    int top=-1;
     //visited[start]=1;
     stack[++top]=start;
    while(top!=-1){
        int v=stack[top];
        top--;
        if (visited[v]) continue;
        visited[v]=1;
        printf("%d ",v);
        for (int u=n-1;u>=0;u--){
            if(adj[v][u]==1 && !visited[u]){
                stack[++top]=u;
            }
        }
    }
}
int main(){
    
    printf("Enter the number of vertices (max %d)",MAX);
    scanf("%d",&n);
    if (n>MAX|| n<=0){ printf("invalid input\n"); return 0;}
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
  dfs(start);
  printf("\n");
  return 0;


}