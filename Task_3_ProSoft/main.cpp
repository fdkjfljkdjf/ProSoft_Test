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

/*
 * В данном примере мы должны быть уверенны, что в классе MyBlah реализован
 * параметрический конструктор.
 *
 * legacy.c не подключен к modern.cpp. 
 * 
 * Объявление - extern int* values; и определение - int values[3]; имеют 
 * разную сигнатуру, препишем объявление - extern int values[LEGACY_SIZE], 
 * тогда перепишем и определение - int values[LEGACY_SIZE].
 * 
 * Довольно легко можно переписать значение map_ при совпадении значения 
 * values, что приведет к утечке памяти.
 * 
 * Отсутствие нетривиального деструктора приведет к утечки памяти.
 */
