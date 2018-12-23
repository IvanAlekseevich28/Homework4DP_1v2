#include <iostream>
#include <math.h>

using namespace std;

struct point            // хранит координаты
{
    int x;              //Поля структуры
    int y;
};

struct triangel         //Структура треушольника
{
    point* combs[3];        //Хранит указатели на объекты структуры point
};

void printTriangel(struct triangel * obj)       //Печатает треугольник
{
    for (int i = 0; i < 3; i++)
    {
        cout << "Point #" << i + 1 << " (" << obj->combs[i]->x << ", " << obj->combs[i]->y << ")" <<  endl;
    }
    cout << endl;
}

bool typeOfTriangel(double c, double a, double b)   //Проверяем на тупоугольность
{
  // cout << "typeOfTriangel " << c << "\t" << a << "\t" << b << endl;
    if (c >= a + b) return false;   // проверка на существование
    if (pow(c,2) > pow(a,2) + pow(b,2)) return true; //Проверяем на тупоугольность
    return false;   // тут можно было написать else или просто так
}


void sortSides (double * sides)
{
    double temp;

    if ( sides[0] >= sides[2])
    {
        temp = sides[0];            //Временная переменная
        sides[0] = sides[2];        //меняем местами
        sides[2] = temp;
    }

    if ( sides[1] >= sides[2])
    {
        temp = sides[1];
        sides[1] = sides[2];
        sides[2] = temp;
    }
}


bool check_obtuse_triangle(struct triangel & tr)
{
    double sides[3];        //Массив сторон треугольника
    for (int i = 0; i < 3; i++)     //заполняем стороны
    {
        sides[i] = sides[i] = sqrt(pow((tr.combs[i]->x - tr.combs[(i + 1) % 3]->x),2) + pow((tr.combs[i]->y - tr.combs[(i + 1) % 3]->y),2));
    }

      sortSides(sides); // Ставим наибольшую сторону на 2 позицию
    //  cout << "check_obtuse_triangle" <<endl;
//      for (int i = 0; i < 3; i++)
//      {
//          cout << sides[i] << endl;
//      }
      if (typeOfTriangel(sides[2], sides[1], sides[0])) return true;    //отправляем на проверку элементы массива
      return false;
}






void searcher_ofobtuse_triangels(struct point* array, const unsigned int SIZE)
{
    triangel testee;            //Создаём тестируемый треугольник

    for (unsigned int i = 0; i < SIZE; i++)
    {
        testee.combs[0] = &array[i];        //присваивам адрес i-той точки
        testee.combs[1] = &array[(i + 1) % SIZE];   //Прсваиваем адрес i+1 точки
        for (unsigned int j = (i + 2) % SIZE; j < (i + 2) % SIZE + 3; j++)  //Перебираем 3-ю точку
        {
            //cout << i << " " << (i + 1) % 3 << " " << (j+2) % SIZE << endl;
            if((j + 1) % SIZE == i) continue;       //Исключаем повторяющиеся треугольник
            testee.combs[2] = &array[(j+2) % SIZE];
            //cout << i << " " << (i + 1) % 3 << " " << (j+2) % SIZE << endl;

          if(check_obtuse_triangle(testee))     //отправляем на проверку и если вернулось 1, то распечатываем
          {
            printTriangel(&testee);
          }

        }
    }


}


int main()
{
    point array[5] = {{440, 340}, {360, 180}, {280, 20}, {40, 340}, {40, 140}};
    searcher_ofobtuse_triangels(array, 5);      //Ищем треугольники по массиву точек
    return 0;
}
