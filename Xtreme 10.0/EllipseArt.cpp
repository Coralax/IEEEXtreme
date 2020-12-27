/*Written by Coral Ifergan*/

/*Instead of using complicated mathematical formulas, I have divided the canvas into pixels which also prevent a situation where  
 an Ellipse area out of the Canvas borders is counted. I've defined two nested for loops running on each pixel (given by x,y), 
checking if it is painted by asking if it fulfills one of the Ellipse's known property, |PF1|+|PF2| <= 2a = r, in at least one of 
the Ellipse on the canvas. If it does, count it and break the current inner loop ( go to the next x-axis) to avoid double counting 
(overlap case). 
*/
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;
double g_resolution = 10;
double findDistance(double x1, double y1, double x2, double y2);

//Class of Ellipse containing two focus cordinates and r (=2a) 
class Ellipse {
public:
    double x1, y1, x2, y2, r;
    Ellipse(double x1, double y1, double x2, double y2, double r) {
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
        this->r = r;
    }
};

void unpaintedCanvasPercentage(vector<Ellipse> el);
bool isPointInsideAGivenEllipse(double x, double y, Ellipse e1);

double findDistance(double x1, double y1, double x2, double y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
}

void unpaintedCanvasPercentage(vector<Ellipse> el)
{
    int paintedArea = 0;
    int count = 0;// Counting the area in terms of 1 cm^2 = 1 pixel. 

    /*Going over all x-axis and y-axis as given to us in the question (100x100 cm -> 50 to -50 for both). 
     +0.5 to -0.5 to start in the middle of the pixel. Higher resolution (-50*10 to 50*10) so that the pixels
     follows the Ellipse contour better*/
    for (double x = -50 * g_resolution + 0.5; x <= 50 * g_resolution - 0.5; x++)
    {
        for (double y = -50 * g_resolution + 0.5; y <= 50 * g_resolution - 0.5; y++) {

            for (Ellipse e : el)
            {
                if (isPointInsideAGivenEllipse(x, y, e)) {
                    count++;
                    goto OUTER;
                    //Skip to the second for loop (y-axis) to prevent double count in case of overlapping ellipses
                }
            }
        OUTER: continue;
        }

    }

    paintedArea = (int)(round((((double)count / (10000.0 * g_resolution * g_resolution)) * 100)));
    cout << 100 - paintedArea << "%" << endl;
}

//Check if a point (x,y) fullfils the Ellipse formula: |PF1|+|PF2| <= 2a = r 
bool isPointInsideAGivenEllipse(double x, double y, Ellipse e1) {

    if (findDistance(x, y, e1.x1 * g_resolution, e1.y1 * g_resolution) + findDistance(x, y, e1.x2 * g_resolution, e1.y2 * g_resolution) <= (e1.r * g_resolution))
        return true;
    return false;
}

int main()
{
    int t, n, x1, y1, x2, y2, r;
    vector<Ellipse> listOfEllipses;
    cin >> t;

    //No. of test cases
    for (int i = 0; i < t; i++)
    {
        //No. of Ellipses
        cin >> n;
        for (int j = 0; j < n; j++) {
            cin >> x1 >> y1 >> x2 >> y2 >> r;
            Ellipse e1(x1, y1, x2, y2, r);
            listOfEllipses.push_back(e1);
        }
        unpaintedCanvasPercentage(listOfEllipses);
        listOfEllipses.clear();
    }

}


