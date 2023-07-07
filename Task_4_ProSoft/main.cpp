#include <stdio.h>
 
class Feature
{
public:
    enum FeatureType {eUnknown, eCircle, eTriangle, eSquare};
 
    Feature() : type(eUnknown), points(0) {    }
 
    ~Feature()
    {
        if (points)
            delete points;
    }
 
    bool isValid() 
    {
        return type != eUnknown;
    }
 
    bool read(FILE* file)
    {        
        if (fread(&type, sizeof(FeatureType), 1, file) != sizeof(FeatureType))
            return false;
        short n = 0;
        switch (type) 
        {
        case eCircle: n = 3; break;
        case eTriangle:    n = 6; break;
        case eSquare: n = 8; break;
        default: type = eUnknown; return false;
        }
        points = new double[n];
        if (!points)
            return false;
        return fread(&points, sizeof(double), n, file) == n*sizeof(double);
    }
    void draw()
    {
        switch (type)
        {
        case eCircle: drawCircle(points[0], points[1], points[2]); break;
        case eTriangle:    drawPoligon(points, 6); break;
        case eSquare: drawPoligon(points, 8); break;
        }
    }
 
protected:
    void drawCircle(double centerX, double centerY, double radius);
    void drawPoligon(double* points, int size);
 
    double* points;
    FeatureType type;        
};
 
int main(int argc, char* argv[])
{
    Feature feature;
    FILE* file = fopen("features.dat", "r");
    feature.read(file);
    if (!feature.isValid())
        return 1;
    return 0;
}

/*
 * В деструкторе удаляем массив, а не один элемент (delete[] points;)
 *
 * Для проверки открытия файла можно дописать: if (file != NULL)
 *
 * Отсутствует закрытие Файла: fclose(file);
 *
 * Условие (fread(&type, sizeof(FeatureType), 1, file) != sizeof(FeatureType))
 * это полная бессмыслица, sizeof(FeatureType) возвращает нам 4 байт, а функция
 * fread в данном примере разого считывает 4 байта, и это количество возвращает
 * при успешном считывании. Тогда получается выражение всегда выполняется, если
 * только в файле не лежит меньше четырех символов. Также не понятно, какой
 * результат считывания мы вообще хотим получить. В поле type мы записываем
 * набор непонятных символов.
 *
 * Магические числа: n = 3, n = 6, n = 8 — это зло.
*/

/*
 * Рефакторить код можно подобно примеру, приведенному во втором задании, для
 * этого пропишем базовый класс, в котором отобразим интерфейс работы с фигурами,
 * метод draw() сделаем виртуальным.
 * 
 * Метод read(FILE* file) можно приписать отдельной функцией, кторая каким то 
 * образом будет возращать ссылку на класс наследника.
 * 
 * Таким образом мы можем разнисти фигуры по разным классам и работать с каждым
 * классом по отдельности будет гораздо удобнее, чем если бы мы чесь код описывали
 * в рамках одного класса. 
*/

