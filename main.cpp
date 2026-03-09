#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream f("input.txt");   // open file

    int p , r;
    f >> p;   // number of processes
    f >> r;   // number of resources

    int E[10];        // existing resources
    int C[10][10];    // allocation
    int R[10][10];    // requests

    int i , j;

    // read existing resources
    for(i=0;i<r;i++)
        f >> E[i];

    // read allocation matrix
    for(i=0;i<p;i++)
        for(j=0;j<r;j++)
            f >> C[i][j];

    // read request matrix
    for(i=0;i<p;i++)
        for(j=0;j<r;j++)
            f >> R[i][j];


    int avail[10];

    // calculate available resources
    for(i=0;i<r;i++)
    {
        int used = 0;

        for(j=0;j<p;j++)
            used += C[j][i];

        avail[i] = E[i] - used;
    }


    bool done[10];

    // mark all processes unfinished
    for(i=0;i<p;i++)
        done[i] = false;


    bool change = true;

    while(change)
    {
        change = false;

        for(i=0;i<p;i++)
        {
            if(done[i] == false)
            {
                bool ok = true;

                for(j=0;j<r;j++)
                {
                    if(R[i][j] > avail[j])
                        ok = false;
                }

                if(ok)
                {
                    // release resources
                    for(j=0;j<r;j++)
                        avail[j] += C[i][j];

                    done[i] = true;
                    change = true;
                }
            }
        }
    }


    bool deadlock = false;

    for(i=0;i<p;i++)
        if(done[i] == false)
            deadlock = true;


    if(deadlock == false)
        cout<<"No deadlock in the system"<<endl;
    else
    {
        cout<<"Deadlock detected\n";
        cout<<"Processes: ";

        for(i=0;i<p;i++)
            if(done[i] == false)
                cout<<"P"<<i<<" ";

        cout<<endl;
    }

}