# ProSoft_Test
## Task 1
Перечислите все проблемы, которые вы видите в данном коде:
```cpp
class Foo
{
public:
    Foo(int j) { i=new int[j]; }
    ~Foo() { delete i; }
private:
     int* i;
};

class Bar: Foo
{
public:
    Bar(int j) { i=new char[j]; }
    ~Bar() { delete i; }
private:
    char* i;
};


void main()
{
    Foo* f=new Foo(100);
    Foo* b=new Bar(200);
    *f=*b;
    delete f;
    delete b;
}
```



1. Для базового класса и класса наследника не прописаны конструкторы по умолчанию

2. В деструкторе необходимо писать `delete [] i`, чтобы избежать утечек памяти

3. Рекомендуется использовать `nullptr` после освобождения памяти оператором `delete`

4. В строчке `Foo* b = new Bar(200);` указателю типа базового класса `b` присваивается ссылка на объект дочернего класса, при этом выделяется динамически память. Так как указатель `b` типа `Foo`, то при осовобождении ресурсов будет вызываться диструктор базового класса `~Foo()`, а нам нужен диструктор дочернего класса `~Bar()`. Необходимо сделать диструктор виртуальным в базовом классе `virtual ~Foo()`

5. В данном примере отсутствует код возврата. Необходимо дописать  `return 0;` и заменить `void main()` на `int main()`

6. Отсутствует проверка аргументов передаваймых в параметрический конструктор

7. Сначала надо написать опреатор `delete` для объекта `b`, а затем для объекта `f`, так как `b` является наследником класса `f`

8. После выполнения строки `*f=*b` два объекта ссылаются на одну и ту же область памяти. Как следствие получим падение программы при выполнении `delete b`
___
## Task 2
Есть класс CodeGenerator, который умеет генерить код на разных языках. Предложите рефакторинг с учетом, что количество языков будет расширяться.
```cpp
class CodeGenerator
{
public:
    enum Lang {JAVA, C_PLUS_PLUS, PHP};
    CodeGenerator(Lang language) { _language=language; }
    std::string generateCode()
    {
        switch(_language) {
        case JAVA:        //return generated java code
        case C_PLUS_PLUS: //return generated C++ code
        case PHP:         //return generated PHP code
        }
        throw new std::logic_error("Bad language");
    }
    std::string someCodeRelatedThing() // used in generateCode()
    {
        switch(_language) {
        case JAVA:        //return generated java-related stuff
        case C_PLUS_PLUS: //return generated C++-related stuff
        case PHP:         //return generated PHP-related stuff
        }
        throw new std::logic_error("Bad language");
    }

private:
    Lang _language;
}
```
1. Для более удобного поддержания кода необходимо реализовать полиморфизм
   
2. Благодаря указателю типа базового класса возможно хранить указатели на нужный класс
   
3. реализация в папке Task_2_ProSoft

___
## Task 3
Все ли хорошо в этом коде?
```cpp
Файл legacy.c


int values[3];


Файл modern.cpp


#define LEGACY_SIZE 3
extern int *values;

class MyBlah {...};

class Adapter
{
public:
    Adapter()
    {
for (int i = 0; i < LEGACY_SIZE; ++i)
    		map_[values[i]] = new MyBlah (values[i]);
    }
private:
    std::map<int, MyBlah *> map_;
};
```

1. В данном примере мы должны быть уверенны, что в классе `MyBlah` реализован параметрический конструктор.

2. legacy.c не подключен к modern.cpp. 

3. Объявление - `extern int* values;` и определение - `int values[3];` имеют разную сигнатуру, препишем объявление - `extern int value [LEGACY_SIZE]`, тогда перепишем и определение - `int value [LEGACY_SIZE]`.

4. Довольно легко можно переписать значение `map_` при совпадении значения `values`, что приведет к утечке памяти.

5. Отсутствие нетривиального деструктора приведет к утечки памяти.
___
## Task 4
Что не так в этом коде? Перечислите, какие недостатки вы видите. Предложите свой вариант рефакторинга.
```cpp
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
```
1. В деструкторе удаляем массив, а не один элемент `delete[] points;`

2. Для проверки открытия файла можно дописать: `if (file != NULL)`

3. Отсутствует закрытие Файла: `fclose(file);`

4. Условие `fread(&type, sizeof(FeatureType), 1, file) != sizeof(FeatureType)` это полная бессмыслица, `sizeof(FeatureType)` возвращает нам 4 байт, а функция `fread` в данном примере разого считывает 4 байта, и это количество возвращает при успешном считывании. Тогда получается выражение всегда выполняется, если только в файле не лежит меньше четырех символов. Также не понятно, какой результат считывания мы вообще хотим получить. В поле type мы записываем набор непонятных символов.

5. Магические числа: n = 3, n = 6, n = 8 — это зло.

* Рефакторить код можно подобно примеру, приведенному во втором задании, для этого пропишем базовый класс, в котором отобразим интерфейс работы с фигурами, метод `draw()` сделаем виртуальным.

* Метод `read(FILE* file)` можно приписать отдельной функцией которая каким то образом будет возвращать ссылку на класс наследника.

* Таким образом мы можем разнести  фигуры по разным классам и работать с каждым классом по отдельности будет гораздо удобнее, чем если бы мы часть код описывали в рамках одного класса. 
___
## Task 5
Имеем чистый C. Напишите generic функцию линейного поиска в массиве. И приведите пример использования вашей функции.

Реализация в папке Task_5_ProSoft
___
## Task 6
Имеем чистый С. Напишите reusable API для работы со связным списком структур. Структуры могу быть разного типа, но в одном списке будут структуры одного типа. Приведите пример использования вашего API.

Реализация в папке Task_6_ProSoft
