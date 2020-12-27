/*Written by Coral Ifergan*/
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

const int letters = 26;
void freeMemory(int** multiiArray, int size);
void checkDictionaryStrings(int* masterArray, int** allDictsMultiArray, int numDicts);
int* createMasterArray(int** allWordMultiArray, int numWords);

int main() {
    std::ios_base::sync_with_stdio(false);
    int testCase, numWords, numDictionaries, i, k, n;
    int** allWordMultiArray, ** allDictsMultiArray;
    int* masterArr;
    string input;
    cin >> testCase;

    //Repeat for N test cases
    for (n = 0; n < testCase; n++) {

        cin >> numWords;
        cin >> numDictionaries;

        allWordMultiArray = new int* [numWords];
        allDictsMultiArray = new int* [numDictionaries];

        //Filling out a matrix for all D words where rows represents the "short" words and cols represents the Alphabet           (a-z).   
        for (i = 0; i < numWords; i++) {
            cin >> input;
            allWordMultiArray[i] = new int[letters] {}; //For each word, initialize 26 letter cols
            for (unsigned long int j = 0; j < input.size(); j++)

                allWordMultiArray[i][input[j] - 'a']++; //Count the letters in each word and plus the corresponding spot                    in the matrix
        }

        //Filling out a matrix for all S potential dictionary strings where rows represent the strings and cols                 represent the alphabet (a-z). 
        for (k = 0; k < numDictionaries; k++) {
            cin >> input;
            allDictsMultiArray[k] = new int[letters] {};
            for (unsigned long int j = 0; j < input.size(); j++)
                allDictsMultiArray[k][(input[j] - 'a')]++; //" " 
        }

        masterArr = createMasterArray(allWordMultiArray, numWords);
        checkDictionaryStrings(masterArr, allDictsMultiArray, numDictionaries);

        //Free all dynamic allocated memory
        freeMemory(allWordMultiArray, numWords);
        freeMemory(allDictsMultiArray, numDictionaries);
        delete[] masterArr;
    }

    return 0;
}

//The master array takes the maximum number of a particular letter (a-z) from the words matrix, allWordMultiArray. For example, if there is a word with 3 a's and a word with 2 a's, the corresponding spot for a (0) will be 3.  
int* createMasterArray(int** allWordMultiArray, int numWords)
{
    int* masterArr = new int[letters] {};
    for (int i = 0; i < numWords; i++)
    {
        for (int j = 0; j < letters; j++)
        {
            if (allWordMultiArray[i][j] > masterArr[j])
                masterArr[j] = allWordMultiArray[i][j];
        }
    }
    return masterArr;
}

void freeMemory(int** multiiArray, int size)
{
    for (int i = 0; i < size; i++)
        delete[] multiiArray[i];
    delete[]multiiArray;
}
void checkDictionaryStrings(int* masterArray, int** allDictsMultiArray, int numDicts)
{

    bool flag, perfect;
    int missingChars;
    for (int i = 0; i < numDicts; i++)
    {
        missingChars = 0;
        flag = true;
        perfect = true;
        for (int j = 0; j < letters; j++)
        {
            if (masterArray[j] != allDictsMultiArray[i][j]) {

                if (masterArray[j] > allDictsMultiArray[i][j]) {
                    flag = false;
                    missingChars += (masterArray[j] - allDictsMultiArray[i][j]);
                }

                //Else: flag remains true meaning masterArray[j] < allDictsMultiArray[i][j], hence it might be a dictionary                 string but not perfect

                perfect = false;

            } //End of if(!=) condition

        }
        //If flag is true, it is a potential dictionary string: Check if it is perfect
        if (flag)
        {
            cout << "Yes ";
            if (perfect)
                cout << "Yes" << endl; // A1A2 = Yes Yes
            else
                cout << "No" << endl; //A1A2 = Yes No
        }
        else
            cout << "No " << missingChars << endl; //A1A2 = No <num of chars>
    }
}