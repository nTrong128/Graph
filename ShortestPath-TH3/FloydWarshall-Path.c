#include <stdio.h>
#define M 300
#define oo 123456689
#define NO_EDGE -1
int pi[M][M];
int next[M][M];

typedef struct {
    int n,m;
    int A[M][M];
}Graph;

void init_graph(Graph* pG, int n, int m) {
    pG->n = n;
    pG->m = 0;
    int i,j;
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++) {
            pG->A[i][j] = -1;
        }
}

void add_edge(Graph* pG, int u, int v, int w) {
    pG->A[u][v] = w;
    pG->m++;
}

void FloydWarshall(Graph* pG) {
    int u,v,k;
    for(u=1;u<=pG->n;u++) 
        for(v=1;v<=pG->n;v++) {
            pi[u][v] = oo;
            next[u][v] = -1;
        }

    for(u=1;u<=pG->n;u++) {
        pi[u][u] = 0;
    }

    for(u=1;u<=pG->n;u++)
        for(v=1;v<=pG->n;v++)
            if(pG->A[u][v] != NO_EDGE) {
                pi[u][v] = pG->A[u][v];
                next[u][v] = v;
            }
    

    for(k=1;k<=pG->n;k++)
        for(u=1;u<=pG->n;u++) 
            for(v=1;v<=pG->n;v++) {
                if(pi[u][k] == oo || pi[k][v] == oo) continue;
                if(pi[u][k] + pi[k][v] < pi[u][v]) {
                    pi[u][v] = pi[u][k] + pi[k][v];
                    next[u][v] = next[u][k];
                }
            }
}

int main() {
    Graph G;
    int i,j,n,m,u,v,w;
    // freopen("dothi.txt","r", stdin);
    scanf("%d%d", &n, &m);
    init_graph(&G, n, m);
    for(i=1;i<=m;i++) {
        scanf("%d%d%d", &u, &v, &w);
        add_edge(&G, u, v, w);
    }
    FloydWarshall(&G);
    for(i=1;i<=n;i++) {
        for(j=1;j<=n;j++) {
            printf("path(%d, %d): ",i,j);
            if(pi[i][j] == oo) printf("NO PATH");
            else  {
                printf("%d ", i);
                if(i!=j) {
                    u = i;
                    while(u != j) {
                        printf("-> %d ",next[u][j]);
                        u = next[u][j];
                    }
                }
            }
            printf("\n");
        }
    }
    return 0;
}