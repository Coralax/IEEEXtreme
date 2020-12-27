/*Written by Coral Ifergan*/
#include <iostream>
#include<algorithm> 

using namespace std;

int cardValue(char card)
{
    if (card == 'T')
        return 10 * 2;
    if (card == 'J' || card == 'Q' || card == 'K')
        return 15 * 2;
    if (card == 'A')
        return 20 * 2;

    return (card - '0') * 2;
}

int points(char card1, char card2)
{
    if (card1 == 'R' && card2 == 'R')
        return 50 * 2;

    if (card1 == 'R')
        return cardValue(card2);

    if (card2 == 'R')
        return cardValue(card1);

    if (card1 == card2)
        return cardValue(card1);

    return 0;
}

/*Used a modified version of the LCS algorithm. The difference is that we're looking for max sum and not max length, therefore 
our comparisons will be adjusted*/
int calculateMaxPts(char* upperCards, char* lowerCards, int size)
{
    int sum = 0;

    //Initialize 2D dynamic int matrix (LCS) of size N+1xN+1 due to the native of the algorithm, first row & col are skipped
    int** LCSMatrix = new int* [size + 1]();
    for (int i = 0; i < size + 1; ++i)
        LCSMatrix[i] = new int[size + 1]();


    for (int i = 1; i <= size; i++) {

        for (int j = 1; j <= size; j++)
        {
            LCSMatrix[i][j] = max(LCSMatrix[i - 1][j], LCSMatrix[i][j - 1]);
            if (upperCards[i] == lowerCards[j] || upperCards[i] == 'R' || lowerCards[j] == 'R')
            {
                sum = points(upperCards[i], lowerCards[j]);
                LCSMatrix[i][j] = max(LCSMatrix[i][j], sum + LCSMatrix[i - 1][j - 1]);
            }
        }
    }

    return LCSMatrix[size][size];
}

int main()
{
    char* upperCards, * lowerCards;
    int n;
    cin >> n;

    while (n != 0) {

        upperCards = new char[n + 1]; //n+1 since we want to start counting from index 1, which will ease things later. 
        lowerCards = new char[n + 1];
        upperCards[0] = '0';
        lowerCards[0] = '0';

        for (int j = 1; j <= n; j++) //User input for n top cards
            cin >> upperCards[j];

        for (int k = 1; k <= n; k++) //User input for n lower cards
            cin >> lowerCards[k];

        cout << calculateMaxPts(upperCards, lowerCards, n) << endl;

        delete[]upperCards;
        delete[]lowerCards;
        cin >> n;
    }
    return 0;
}
