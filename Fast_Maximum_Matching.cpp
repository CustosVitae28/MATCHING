// Fast_Maximum_Matching.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <iostream>
#include <queue>

using namespace std;
#define MAX 150007
#define NIL 0
#define INF (1<<28)

vector< int > G[MAX];
int n, m, match[MAX], dist[MAX];

bool bfs() {
	int i, u, v, len;
	queue< int > Q;
	for (i = 1; i <= n; i++) {
		if (match[i] == NIL) {
			dist[i] = 0;
			Q.push(i);
		}
		else dist[i] = INF;
	}
	dist[NIL] = INF;
	while (!Q.empty()) {
		u = Q.front(); Q.pop();
		if (u != NIL) {
			len = G[u].size();
			for (i = 0; i<len; i++) {
				v = G[u][i];
				if (dist[match[v]] == INF) {
					dist[match[v]] = dist[u] + 1;
					Q.push(match[v]);
				}
			}
		}
	}
	return (dist[NIL] != INF);
}

bool dfs(int u) {
	int i, v, len;
	if (u != NIL) {
		len = G[u].size();
		for (i = 0; i<len; i++) {
			v = G[u][i];
			if (dist[match[v]] == dist[u] + 1) {
				if (dfs(match[v])) {
					match[v] = u;
					match[u] = v;
					return true;
				}
			}
		}
		dist[u] = INF;
		return false;
	}
	return true;
}

int edmonds_karp() {
	int matching = 0, i;
	while (bfs())
		for (i = 1; i <= n; i++)
			if (match[i] == NIL && dfs(i))
				matching++;
	return matching;
}
int main() {
	int pairs;
	scanf("%d %d %d", &n, &m, &pairs);
	while (pairs--) {
		int x, y;
		scanf("%d %d", &x, &y);
		G[x].push_back(y + n);
		G[y + n].push_back(x);
	}
	printf("%d\n", edmonds_karp());
}

