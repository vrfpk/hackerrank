/*
Title	:	Repair Roads
Auhtor	:	Shahid Hussain Khan
*/
#include<stdio.h>
#include<string.h>

#define MAX_VERTICES 10000+5
#define MAX_EDGES 2*10000+5

typedef struct vertex_t
{
	int start;
    int end;	// used for finding adjacent vertices
} vertex_t; vertex_t V[MAX_VERTICES]; int vertices;

typedef struct edge_t
{
	int v;      // second vertex of edge (u,v), 
    int next;   // index of node u's next edge
} edge_t; edge_t E[MAX_EDGES]; int edges;

// if some value is also associated with each node/edge, update following functions accordingly
static int graph_init(int n) { vertices = n; edges = 0; memset(V, 0, sizeof(V)); }
static int add_directed_edge(int u, int v)
{
	edges++; E[edges].v = v; E[edges].next = 0;
	if (V[u].start == 0) V[u].start = edges;
	else E[V[u].end].next = edges;
	V[u].end = edges;
}
static int add_undirected_edge(int u, int v) { add_directed_edge(u, v); if(u != v) add_directed_edge(v, u); }

/* ------------------- Graph implementation ends here ------------------ */

typedef struct res_t    // R : no of robots required for edges below this node (excluding the edge with the calling function node)
{				        // S : whether this robot will be available for upper edges or not
	int R;		        // S=1   =>   available for all upper edges (wherever one robot can go)
	int S;		        // S=0   =>   available for only the edge with the calling function node
} res_t;			    // S=-1  =>   not available for edges above this node not even for edge with the calling function node

static res_t solve(int u, int par)	// 'par' is the node that has called this function with its adjacent node 'u'
{							// for sake of convenience, we call this function first time with par=0 (a node that does not exist)
	int i, leaf = 0, zero = 0, one = 0; res_t r = { 0, 0 };
	for (i = V[u].start; i; i = E[i].next) if (E[i].v != par) {
		res_t rr = solve(E[i].v, u);
		r.R += rr.R;
		if(rr.R == 0 || rr.S == -1) leaf++;
		else if (rr.S) one++;
		else zero++;
	}
	if (leaf && !one) { r.R++; r.S = 1; }
	else if (one) { r.R -= (one >> 1); r.S = one & 1; }
	else if (zero) r.S = -1;
	return r;
}

int test_repair_roads2()
{
	int T;
    freopen("repair_roads.txt", "r", stdin);
	scanf("%d", &T);
	while(T--)
	{
		int N, M;
        scanf("%d", &N);
		graph_init(N);
		int i, u, v;
        for (i = 0; i < N - 1; i++) {
            scanf("%d%d", &u, &v);
            add_undirected_edge(u+1, v+1);
        }
		res_t res = solve(1, 0);
		printf("%d\n", res.R);
	}
	return 0;
}