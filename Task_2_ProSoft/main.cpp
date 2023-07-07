#include <iostream>

using namespace std;

class Сode
{
    public:
    virtual string generateCode() = 0;
    virtual string someCodeRelatedThing() = 0;
    virtual ~Сode() {}
};

class JAVA_Code : public Сode
{
    string generateCode() override
    {
        return "generated code in JAVA";
    }
    string someCodeRelatedThing() override
    {
        return "someCodeRelatedThing_JAVA";
    }

};

class C_PLUS_PLUS_Code : public Сode
{
    string generateCode() override
    {
        return "generated code in C++";
    }
    string someCodeRelatedThing() override
    {
        return "someCodeRelatedThing_C++";
    }
};

class PHP_Code : public Сode
{
    string generateCode() override
    {
        return "generated code in PHP";
    }
    string someCodeRelatedThing() override
    {
        return "someCodeRelatedThing_PHP";
    }
};

class ProgrammingLanguage
{
    public:
    enum Language {JAVA, C_PLUS_PLUS, PHP};

    ProgrammingLanguage()
    {
        code = new C_PLUS_PLUS_Code;
    }

    ProgrammingLanguage(Language language)
    {
        switch (language)
        {
        case JAVA:
            code = new JAVA_Code;
            break;
        case C_PLUS_PLUS:
            code = new C_PLUS_PLUS_Code;
            break;
        case PHP:
            code = new PHP_Code;
            break;
        }
    }

    ~ProgrammingLanguage(){
        delete code;
    }

    string generator_code()
    {
        return code->generateCode();
    }
    string code_RelatedThing ()
    {
        return code->someCodeRelatedThing();
    }
    private:
    Сode *code;
};

int main(){

    ProgrammingLanguage PL_1;
    cout << PL_1.generator_code() << endl;
    cout << PL_1.code_RelatedThing() << endl;

    ProgrammingLanguage PL_2(ProgrammingLanguage::PHP);
    cout << PL_2.generator_code() << endl;
    cout << PL_2.code_RelatedThing() << endl;
    return 0;
}

/*
для более удобного поддержания кода необходимо реализовать полиморфизм

благодаря указателю типа базового класса возможно хранить указатели на нужный класс
*/