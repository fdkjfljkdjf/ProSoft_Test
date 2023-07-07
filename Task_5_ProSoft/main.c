#include <stdio.h>

void array_search_int(int *Arr, int kay, int Size){
    for(int i = 0; i < Size; i++){
        if(kay == *(Arr + i)){
            printf("%d ", i);
        }
        if((i == Size - 1) && (kay != *(Arr + i))){
            printf("element not found");
        }
    }
    printf("\n");
}

void array_search_double(double *Arr, double kay, int Size){
    for(int i = 0; i < Size; i++){
        if(kay == *(Arr + i)){
            printf("%d ", i);
        }
        if((i == Size - 1) && (kay != *(Arr + i))){
            printf("element not found");
        }
    }
    printf("\n");
}

void array_search_char(char *Arr, char kay, int Size){
    for(int i = 0; i < Size; i++){
        if(kay == *(Arr + i)){
            printf("%d ", i);
        }
        if((i == Size - 1) && (kay != *(Arr + i))){
            printf("element not found");
        }
    }
    printf("\n");
}

void array_search_unknown(){
    printf("unknown type\n");
}


// _Generic макрос
#define array_search(Arr, kay, Size) _Generic((Arr), \
    int *: array_search_int, \
    double *: array_search_double, \
    char *: array_search_char, \
    default: array_search_unknown) (Arr, kay, Size)

int main(void){

    // создаем массив int
    int size = 5;
    int key_int = 3;
    int Arr_int[] = {1, 2, 3, 4 ,3};

    printf("Arr_int[] array indexes: ");
    array_search(Arr_int, key_int, size);

    // создаем массив char
    size = 5;
    char key_char = 'H';
    char Arr_char[] = {'h', 'e', 'l', 'l' ,'o'};

    printf("Arr_char[] array indexes: ");
    array_search(Arr_char, key_char, size);

    // создаем массив double
    size = 3;
    double key_double = 1.2;
    double Arr_double[] = {1.0, 1.1, 1.2};

    printf("Arr_double[] array indexes: ");
    array_search(Arr_double, key_double, size);
    
    // создаем массив float
    size = 3;
    float key_float = 2.2;
    float Arr_float[] = {2.0, 2.1, 2.2};

    printf("Arr_float[] array indexes: ");
    array_search(Arr_float, key_float, size);
    return 0;
}

/*
Функция array_search принимает в качестве параметра указатель на массив, искомый 
элемент и длину массива, при этом выводит в консоль индексы нужных элементов,
если искомого элемента не нашлось, то выводит сообщение "element not found", если 
передан параметр с неизвестным типом, то выведет сообщение "unknown type".

Основным элементом программы является _Generic макрос, который сравнивает тип 
указателя на массив и далее применяет соответствующую функцию.

Было решено для каждого типа прописать отдельную функцию, так как в этом случае 
проще поддерживать код.

Для реализации линейного поиска в любом случае придется знать тип передаваемых 
переменных, поэтому существенно уменьшить код скорее всего не получиться.

Необходимо использовать стандарт C11 и выше
*/