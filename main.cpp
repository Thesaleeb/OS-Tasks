#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


// each frame stores a page and its aging counter
struct Frame
{
    int page;
    unsigned int age;
};


// simulate paging using Aging algorithm
int simulate(vector<int> refs , int framesCount)
{
    vector<Frame> memory;   // represents RAM
    int faults = 0;         // counts page faults

    // go through all page references
    for(int page : refs)
    {
        // ---- aging step ----
        // shift all counters right (older pages lose importance)
        for(auto &f : memory)
            f.age >>= 1;

        int hit = -1;

        // check if page already exists in memory
        for(int i = 0 ; i < memory.size() ; i++)
        {
            if(memory[i].page == page)
                hit = i;
        }

        // ---- PAGE HIT ----
        if(hit != -1)
        {
            // mark page as recently used (set MSB)
            memory[hit].age |= 128;
        }
        else
        {
            // ---- PAGE FAULT ----
            faults++;

            // if free frame available
            if(memory.size() < framesCount)
            {
                // add new page
                memory.push_back({page,128});
            }
            else
            {
                // find page with smallest age (oldest page)
                int victim = 0;

                for(int i = 1 ; i < memory.size() ; i++)
                {
                    if(memory[i].age < memory[victim].age)
                        victim = i;
                }

                // replace oldest page
                memory[victim] = {page,128};
            }
        }
    }

    return faults;
}



int main()
{
    ifstream file("pages.txt");   // input file
    vector<int> refs;
    int x;

    // read page references from file
    while(file >> x)
        refs.push_back(x);

    cout<<"Frames\tFaults/1000\n";

    // test different numbers of frames
    for(int f = 1 ; f <= 10 ; f++)
    {
        int faults = simulate(refs , f);

        // normalize faults per 1000 references
        cout<<f<<"\t"
            << (double)faults / refs.size() * 1000
            << endl;
    }
}