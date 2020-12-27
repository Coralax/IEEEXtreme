/*Writen by Coral Ifergan*/
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

double calculateRave(vector<int> ri, int size);
double calculateXave(vector<double> xi, int size);
bool processResults(vector<int> dataPoints, double centerLine, double upControlLimit, double lowControlLimit);

int main() {

    int testCases, numOfDataPoints, sizeOfSubgroup, counter, data, sumData, i, j, max, min, size;
    vector<int> dataPoints, ri; //vector of ri's= the ranges (max process var- min proccess var) of each subgroup
    vector<double> xi; //vector of xi's = the average of all process variables in each subgroup 
    bool res;
    double A2Array[11] = { 0,0,1.880,1.023,0.729,0.577,0.483,0.419,0.373,0.337,0.308 };
    double centerLine, lowControlLimit, upControlLimit, allSubgroupAvgX, allSubgroupRangeR;
    cin >> testCases;

    for (j = 0; j < testCases; j++) {
        cin >> numOfDataPoints >> sizeOfSubgroup; //(numOfDataPoints= x),(sizeOfSubgroup = n, num of elements inside each subgroup ). Each such sub-group has it's own ri and xi.
        size = (numOfDataPoints + sizeOfSubgroup - 1) / (sizeOfSubgroup); //Size is the total number of sub-groups (Using ceiling function)

        //Initialize variables for each test case
        max = -10000;
        min = 10000;
        data = 0;
        sumData = 0;
        counter = 0;
        for (i = 0; i < numOfDataPoints; i++)
        {
            cin >> data;
            dataPoints.push_back(data);

            //Calculate max and min for each subgroup in order to find their corresponding Ri
            if (data > max)
                max = data;
            if (data < min)
                min = data;
            sumData += data; //sumData is used to calculate the average of values (xi) in each subgroup
            counter++; //A counter to distinguish between each sub-group

            //Calculate Xi and Ri for each subgroup
            if (counter == sizeOfSubgroup || i == numOfDataPoints - 1) { // " " or if we reached the end of the data points ( since it is possible that the last subgroup is incomplete)

                xi.push_back(sumData / counter);
                ri.push_back(max - min);
                max = -10000;
                min = 10000;
                counter = 0;
                sumData = 0;
            }
        }

        allSubgroupAvgX = calculateXave(xi, size); //Calculate total average of all subgroups in the current test case (average of xi's vector values)
        allSubgroupRangeR = calculateRave(ri, size);//Calculate total average of ranges of all subgroups in the current test case (average of ri's vector values)
        centerLine = allSubgroupAvgX;
        upControlLimit = allSubgroupAvgX + (A2Array[sizeOfSubgroup] * allSubgroupRangeR); //Formula given by the question
        lowControlLimit = allSubgroupAvgX - (A2Array[sizeOfSubgroup] * allSubgroupRangeR);

        res = processResults(dataPoints, centerLine, upControlLimit, lowControlLimit);

        if (!res)
            cout << "Out of Control" << endl;
        else
            cout << "In Control" << endl;

        //Clear all vectors before each test case
        dataPoints.clear();
        ri.clear();
        xi.clear();
    }
    return 0;
}

double calculateXave(vector<double> xi, int size) {
    double sumXi = 0;
    for (int i = 0; i < size; i++) {
        sumXi += xi[i];
    }
    return (sumXi / size);
}

double calculateRave(vector<int> ri, int size) {
    double sumRi = 0;
    for (int i = 0; i < size; i++) {
        sumRi += ri[i];
    }
    return (sumRi / size);
}

bool processResults(vector<int> dataPoints, double centerLine, double upControlLimit, double lowControlLimit)
{
    int eightCounterAbove = 0, eightCounterBelow = 0, twoOutOfThreeBelow2S = 0, twoOutOfThreeAbove2S = 0,
        twoOutOfThreeLast2SAbove = 0, twoOutOfThreeLast2SBelow = 0, fourOutOfFiveBelow1S = 0,
        fourOutOfFiveAbove1S = 0, fourOutOfFiveLast1SAbove = 0, fourOutOfFiveLast1SBelow = 0;

    double sigma = (upControlLimit - centerLine) / 3;
    for (long unsigned int i = 0; i < dataPoints.size(); i++)
    {

        //Condition 1
        if (dataPoints[i]<lowControlLimit || dataPoints[i]>upControlLimit) {
            return false;
        }

        //Condition 4
        if (dataPoints[i] > centerLine) {
            eightCounterAbove++;
            eightCounterBelow = 0;
        }

        if (dataPoints[i] < centerLine) {
            eightCounterBelow++;
            eightCounterAbove = 0;
        }

        if (eightCounterAbove == 8 || eightCounterBelow == 8) {
            return false;
        }

        //Condition 2- two out of three values, can also be the first and the last for example 
        if (dataPoints[i] > centerLine + 2 * sigma) {
            twoOutOfThreeAbove2S++;
            if (twoOutOfThreeAbove2S + twoOutOfThreeLast2SAbove == 2) //fulfills two in a row or not in a row
                return false;
        }
        else {
            twoOutOfThreeLast2SAbove = twoOutOfThreeAbove2S; //We want to memorize the last one that was 2 sigma above in twoOutOfThreeLast2SAbove  before we set twoOutOfThreeAbove2S to 0
            twoOutOfThreeAbove2S = 0;
        }

        if (dataPoints[i] < centerLine - 2 * sigma) {
            twoOutOfThreeBelow2S++;
            if (twoOutOfThreeBelow2S + twoOutOfThreeLast2SBelow == 2)
                return false;
        }
        else {
            twoOutOfThreeLast2SBelow = twoOutOfThreeBelow2S;
            twoOutOfThreeBelow2S = 0;
        }

        //Condition 3
        if (dataPoints[i] > centerLine + sigma) {
            fourOutOfFiveAbove1S++;
            if (fourOutOfFiveAbove1S + fourOutOfFiveLast1SAbove == 4)
                return false;
        }

        else {
            fourOutOfFiveLast1SAbove = fourOutOfFiveAbove1S;
            fourOutOfFiveAbove1S = 0;
        }

        if (dataPoints[i] < centerLine - sigma) {
            fourOutOfFiveBelow1S++;
            if (fourOutOfFiveBelow1S + fourOutOfFiveLast1SBelow == 4)
                return false;
        }
        else {
            fourOutOfFiveLast1SBelow = fourOutOfFiveBelow1S;
            fourOutOfFiveBelow1S = 0;
        }
    }
    return true;
}