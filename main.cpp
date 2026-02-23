#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <map>
#include <mutex>
#include <sstream>

using namespace std;

map<string,int> finalCount;

mutex mtx;

string cleanWord(string w)

{
    string result="";

    for(char c : w)
    {
        if(isalpha(c))
            result += tolower(c);
    }


    return result;
}

void countWords(string part,int id)
{
    map<string,int> localCount;

    stringstream ss(part);

    string word;

    while(ss >> word)
    {
        word = cleanWord(word);

        if(word!="")
            localCount[word]++;

    }

    mtx.lock();

    cout << "\nThread " << id << " result:\n";

    for(auto p : localCount)
        cout << p.first << " -> " << p.second << endl;


    mtx.unlock();


    mtx.lock();

    for(auto p : localCount)
        finalCount[p.first] += p.second;


    mtx.unlock();
}

int main()


{
    ifstream file("input.txt");

    if(!file)
    {
        cout << "input.txt not found\n";
        return 0;
    }

    string text(
            (istreambuf_iterator<char>(file)),
            istreambuf_iterator<char>()
    );

    int N;
    cout << "Enter number of threads: ";

    cin >> N;


    vector<thread> threads;


    int partSize = text.size() / N;


    for(int i=0;i<N;i++)
    {
        int start = i * partSize;
        int end;

        if(i == N-1)

            end = text.size();
        else
            end = (i+1) * partSize;

        if(i != 0)

        {
            while(start < text.size() && text[start] != ' ')
                start++;
        }

        while(end < text.size() && text[end] != ' ')
            end++;

        string part = text.substr(start,end-start);

        threads.push_back(thread(countWords,part,i+1));
    }

    for(int i=0;i<threads.size();i++)
        threads[i].join();

    cout << " Final Word Frequency \n";

    for(auto p : finalCount)
        cout << p.first << " : " << p.second << endl;

    return 0;
}