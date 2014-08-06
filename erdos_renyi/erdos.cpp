#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

int erdos_renyi(int nodes, int edges, vector<vector<bool> > &adj_mat)
{
    adj_mat.resize(nodes, vector<bool>(nodes, 0));
    double p_link_formation = (double) edges * 2 / ((double)nodes * (nodes-1));
    double r;
    srand(time(NULL));
    int edge = 0;

    for (int i=0; i < nodes; i++)
        for (int j=i+1; j < nodes; j++)
        {
            r = ((double) rand() / (RAND_MAX)); //0 < r < 1
            if (r <= p_link_formation)
            {
                adj_mat[i][j] = 1;
                adj_mat[j][i] = 1;
                edge++;
            }

        }
    return edge;
}

void erdos_renyi2(int nodes, int edges, vector<vector<bool> > &adj_mat)
{
    adj_mat.resize(nodes, vector<bool>(nodes, 0));
    int n1, n2;
    srand(time(NULL));
    int edge = 0;

    for (int i=0; i < edges; i++)
    {
        while(true)
        {
            n1 = rand()%nodes;
            n2 = rand()%nodes;
            if (n1 != n2 && !adj_mat[n1][n2])
            {
                adj_mat[n1][n2] = 1;
                adj_mat[n2][n1] = 1;
                edge++;
                break;
            }
        }
    }
}

int main()
{
    int nodes, edges, edge;
    vector<vector<bool> > graph;
    cout<<"Network Parameters: nodes and edges?: ";
    cin>>nodes>>edges;

    double avg=0;
    int iter = 100000;
    for(int k=0; k < iter; k++)
    {
        graph.clear();
        edge = erdos_renyi(nodes, edges, graph);
        //cout<<"edge: "<<edge<<'\n';
        avg += edge;
    }
    avg/=iter;
    cout<<"avg: "<<avg<<'\n';

    /*graph.clear();
    erdos_renyi(nodes, edges, graph);
    for (int i=0; i < nodes; i++)
    {
        for (int j=0; j < nodes; j++)
            cout<<graph[i][j]<<" ";
        cout<<'\n';
    }
    cout<<"edges: "<<edge<<'\n';*/

    return 0;
}