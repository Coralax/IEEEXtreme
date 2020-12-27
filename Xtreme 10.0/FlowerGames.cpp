///*Written by Coral Ifergan*/
//#include <math.h>
//#include <cstdio>
//#include <vector>
//#include <iostream>
//#include <algorithm>       
//
//using namespace std;
//void flowerGame();
//
//
////The logic behind it is as follows: if the total number of petals(N) is a power of two we print 1. For the rest of the test cases where N is not a power of two, we would count from 3 and add 2 , until we reach a power of two number and then restart to 1. So, if N=7, the last time it was restarted  to 1 is at 4=2^2 so 4=1,5=3,6=5,7=7. We'd always print an odd number (1 for 2^x and 3,5,7... for the rest)
////Note that 1 is 2^0 hence we print 1. 
//void flowerGame()
//{
//    unsigned long long n = 0;
//    unsigned long long powerOfTwo = 1;
//
//    cin >> n;
//
//    //Bit manipulation: multiply by 2 by shifting left till we reach the smallest - bigger or equal than N - power of two       product. Later, we shift one right to balance due to the nature of such while loop
//    //which goes out of bound for one element. 
//    while (powerOfTwo <= n) {
//        powerOfTwo <<= 1;
//    }
//    powerOfTwo >>= 1;
//
//    //If N is a power of two, then (N-powerOfTwo will be 0 hence 2*0 =0. Then we add 1 and print it.
//    cout << 2 * (n - powerOfTwo) + 1 << endl; //multiply by 2 and add 1 to make it an odd number. N-powerOfTwo is the remainder
//}
//
//int main() {
//    int T;
//    cin >> T;
//    for (int i = 0; i < T; i++)
//        flowerGame();
//
//    return 0;
//}