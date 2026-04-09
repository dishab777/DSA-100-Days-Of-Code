#include <stdio.h>
#include <string.h>

#define MAX 26

char* alienOrder(char words[][100], int n) {
    static char result[27];
    int adj[MAX][MAX] = {0};
    int indegree[MAX] = {0};
    int present[MAX] = {0};

    for(int i = 0; i < n; i++){
        for(int j = 0; words[i][j]; j++)
            present[words[i][j] - 'a'] = 1;
    }

    for(int i = 0; i < n - 1; i++){
        char *w1 = words[i];
        char *w2 = words[i+1];
        int len1 = strlen(w1), len2 = strlen(w2);
        int found = 0;

        for(int j = 0; j < len1 && j < len2; j++){
            if(w1[j] != w2[j]){
                int u = w1[j] - 'a';
                int v = w2[j] - 'a';
                if(!adj[u][v]){
                    adj[u][v] = 1;
                    indegree[v]++;
                }
                found = 1;
                break;
            }
        }

        if(!found && len1 > len2)
            return "";
    }

    int queue[MAX], front = 0, rear = -1;

    for(int i = 0; i < MAX; i++){
        if(present[i] && indegree[i] == 0)
            queue[++rear] = i;
    }

    int idx = 0;

    while(front <= rear){
        int u = queue[front++];
        result[idx++] = u + 'a';

        for(int v = 0; v < MAX; v++){
            if(adj[u][v]){
                indegree[v]--;
                if(indegree[v] == 0)
                    queue[++rear] = v;
            }
        }
    }

    int total = 0;
    for(int i = 0; i < MAX; i++)
        if(present[i]) total++;

    if(idx != total)
        return "";

    result[idx] = '\0';
    return result;
}

int main(){
    int n;
    scanf("%d",&n);

    char words[n][100];
    for(int i=0;i<n;i++)
        scanf("%s",words[i]);

    char* ans = alienOrder(words,n);

    printf("%s\n",ans);

    return 0;
}