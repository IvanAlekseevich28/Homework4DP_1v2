#include <iostream>
#include <math.h>
#include <algorithm>
using namespace std;

struct point
{
    int x;
    int y;
};

struct triangel
{
    point* combs[3];
};

void printTriangel(struct triangel * obj)
{
    for (int i = 0; i < 3; i++)
    {
        cout << "Point #" << i + 1 << " (" << obj->combs[i]->x << ", " << obj->combs[i]->y << ")" <<  endl;
    }
    cout << endl;
}

int typeOfTriangel(double c, double a, double b)
{
    if (c >= a + b) return 2;
    if (pow(c,2) > pow(a,2) + pow(b,2)) return 1;
    if (pow(c,2) < pow(a,2) + pow(b,2)) return -1;
    return false;
}


bool check_obtuse_triangle(struct triangel & tr)
{
    double sides[3];
    for (int i = 0; i < 3; i++)
    {
        sides[i] = hypot((tr.combs[i]->x - tr.combs[(i + 1) % 3]->x), (tr.combs[i]->y - tr.combs[(i + 1) % 3]->y));
    }

      sort(sides, &sides[2]);
      if (typeOfTriangel(sides[2], sides[1], sides[0]) == 1) return true;
      return false;
}






void searcher_ofobtuse_triangels(struct point* array, const unsigned int SIZE)
{
    triangel testee;

    for (unsigned int i = 0; i < SIZE; i++)
    {
        testee.combs[0] = &array[i];
        testee.combs[1] = &array[(i + 1) % SIZE];
        for (unsigned int j = 0; j < SIZE - 3; j++)
        {
            if((j + 1) % SIZE == i) continue;
            testee.combs[2] = &array[(j+2) % SIZE];


          if(check_obtuse_triangle(testee))
          {
            printTriangel(&testee);
          }

        }
    }





}






int main()
{
    point array[5] = {{440, 340}, {360, 180}, {280, 20}, {40, 340}, {40, 140}};
    searcher_ofobtuse_triangels(array, 5);
    return 0;
}