#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <algorithm>
#include "clusterGraph.h"

using std::cout;

int main()
{
    // Step1: generating number serialization
    int n = 60;
    std::vector<int> numbers;
    numbers.reserve(n);

    for (int i = 0; i < n; ++i)
    {
        numbers.push_back(i);
    }

    for (int i = 0; i < n/4; ++i)
    {
        int j = rand()%n;
        numbers[j] = rand()%n;
    }

    // Step2: find all triplets whose element is ascending
    std::vector<int> triplets;  // candidate triplets

    for (int i = 1; i < n-1; ++i)
    {
        if (numbers[i] - numbers[i-1] == 1 &&
            numbers[i+1] - numbers[i] == 1)
        {
            triplets.push_back(i);
        }
    }

    if (triplets.empty())
    {
        for (int i = 1; i < n; ++i)
        {
            if (numbers[i] - numbers[i-1] == 1)
            {
                cout << "n is too small, only two ascending numbers exist";

                return 0;
            }
        }

        cout << "n is too small, no ascending numbers exist, pls set n >=10 at least";

        return 0;
    }

    // Step3: cluster the connected triplets
    int numTrip = triplets.size();
    std::vector<std::pair<int, int>> A;

    for (int i = 0; i < numTrip; ++i)
    {
        int fID = triplets[i];

        for (int j = 0; j < numTrip; ++j)
        {
            int bID = triplets[j];

            if (abs(fID-bID) == 1)
            {
                A.push_back(std::pair<int, int>(i, j));
                A.push_back(std::pair<int, int>(j, i));
            }
        }
    }

    cluGraph graph(numTrip);
    std::vector<std::pair<int, int>>::iterator iter = A.begin();
    for (; iter != A.end(); iter++)
    {
        std::pair<int, int> edge = *iter;
        int a = graph.findCluID(edge.first);
        int b = graph.findCluID(edge.second);

        if (a != b)
        {
            graph.join(a, b);
        }
    }

    std::map<int, std::vector<int>> clusteredNumbers;

    for (int i = 0; i < numTrip; ++i)
    {
        int clusterID = graph.findCluID(i);
        clusteredNumbers[clusterID].push_back(i);
    }

    // Step4: find the longest cluster
    int longestSize = 0;
    int longestID = 0;

    for (auto cluster : clusteredNumbers)
    {
        if (cluster.second.size() > longestSize)
        {
            longestSize = cluster.second.size();
            longestID = cluster.first;
        }
    }

    // Step5: output result
    cout << "The initial number sequence is:\n";

    for (auto number: numbers)
    {
        cout << number << " ";
    }

    std::vector<int> sequence;
    sequence.assign(clusteredNumbers[longestID].begin(),
                    clusteredNumbers[longestID].end());

    int a = *(std::min_element(sequence.begin(), sequence.end()));
    int b = *(std::max_element(sequence.begin(), sequence.end()));
    cout << "\n\nThe longset ascending number sequence is:\n";

    for (int i = numbers[triplets[a]]-1; i <= numbers[triplets[b]]+1; ++i)
    {
        cout << i << " ";
    }

    return 0;
}