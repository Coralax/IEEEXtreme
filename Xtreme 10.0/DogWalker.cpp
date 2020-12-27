/*Written by Coral Ifergan*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


void minRangeSum()
{
    int N, K;
    long long dog, sum;
    vector<long long> diff;
    vector<long long> dogsSize;
    cin >> N >> K;

    //If the number of dogs are equal to the number of walkers, the range is 0 because every walker is promised to walk at least one dog
    if (N == K)
    {
        cout << "0" << endl;
        return;
    }

    else
    {
        for (int i = 0; i < N; i++)
        {
            cin >> dog;
            dogsSize.push_back(dog);
        }

        //Sort the array from the smallest to the biggest so that we can easily consider the smallest possible difference 
        std::sort(dogsSize.begin(), dogsSize.end());

        //Push the differences from each pair of dogs into different vector; Running from 1 to N-2 to avoid overflow
        for (int i = 0; i < N - 1; i++)
            diff.push_back(dogsSize[i + 1] - dogsSize[i]); //--> diff vector size is N-1

        //" " "
        std::sort(diff.begin(), diff.end());

        //Take the largest difference between the smallest dog and the biggest dog and later substract the K-1 "big gaps" on a number line to cluster and sum the smallest ranges. 
        sum = dogsSize[N - 1] - dogsSize[0];

        //Remove K-1 big gaps
        for (int i = 1; i < K; i++)
            // Diff array has a size of N-1. We already considered the first element(dogsSize[0]) and the last element (dogsSize[N - 1]) when sum was initialized, hence running on diff from N-1-i to (N-1)-(K-1). 
            sum -= diff[N - 1 - i];

        //Since the task is only about printing the sum of the minimal ranges, we don't care about which dog walker gets what but about the grouping of them - print the ranges sum of such grouping 
        cout << sum << endl;
    }
}
int main()
{
    int t;
    cin >> t;
    for (int i = 0; i < t; i++)
        minRangeSum();

    return 0;
}