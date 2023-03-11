// Course project 3 - Parser INI-files.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>

class DivisionByZeroException : public std::exception
{
public:
    const char* what() const override { return "Значение не найдено"; }
};

class ini_parser
{
protected:
    std::string section_name = "";
    std::string section_value = "";
    std::string value = "";
    std::string section_summary = "";

    int count = 0;

    char symbol = 0;

    std::vector<unsigned char> temp_vector;

    std::list<std::string> section;
    std::list<std::string> summary;
public:
    ini_parser() {};
    ini_parser(std::string path)
    {
        std::ifstream fin;
        fin.open(path);

        if (!fin.is_open())
        {
            std::cout << "файл не найден" << std::endl;
        }
        else
        {
            while (!fin.eof())
            {
                section_value.clear();
                value.clear();

                fin.get(symbol);
                count++;

                if (symbol == '[')
                {
                    section_name.clear();
                    fin.get(symbol);
                    while (symbol != ']')
                    {
                        temp_vector.push_back(symbol);
                        fin.get(symbol);
                    }
                    for (auto c : temp_vector)
                    {
                        section_name.push_back(c);
                    }
                    temp_vector.clear();
                    fin.get(symbol);
                    summary.push_back(section_name);
                }
                if (symbol == ';')
                {
                    while (symbol != '\n')
                    {
                        fin.get(symbol);
                    }
                    fin.get(symbol);
                }
                if (symbol != ';' && symbol != '[' && symbol != ' ' && symbol != '\n')
                {
                    while (symbol != '=')
                    {
                        temp_vector.push_back(symbol);
                        fin.get(symbol);
                    }
                    for (auto c : temp_vector)
                    {
                        section_value.push_back(c);
                    }
                    temp_vector.clear();
                    fin.get(symbol);
                    while (symbol != ';' && symbol != '\n' && symbol != ' ' && !fin.eof())
                    {
                        temp_vector.push_back(symbol);
                        fin.get(symbol);
                    }
                    for (auto c : temp_vector)
                    {
                        value.push_back(c);
                    }
                    temp_vector.clear();
                }
                if (section_value != "")
                {
                    section_summary = section_name + "." + section_value;
                    section.push_back(section_summary);
                    section.push_back(value);
                }
            }
            fin.close();
        }
    }
    std::string get_value_str(std::string parameter)
    {
        int count = 0;
        for (auto iter = section.begin(); iter != section.end(); iter++)
        {
            if (*iter == parameter)
            {
                iter++;
                count++;
                return *iter;
            }            
        }
        if (count == 0)
        {
            throw  DivisionByZeroException();
        }
    }
    template <class T>
    T get_value(std::string parameter)
    {
        std::string val_str = get_value_str(parameter);
        return static_cast<T>(std::stoi(val_str));
    }
    template<>
    std::string get_value(std::string parameter)
    {
        return get_value_str(parameter);
    }
    template<>
    double get_value(std::string parameter)
    {
        std::string val_str = get_value_str(parameter);
        return static_cast<double>(std::stoi(val_str));
    }
    template<>
    int get_value(std::string parameter)
    {
        std::string val_str = get_value_str(parameter);
        return static_cast<int>(std::stoi(val_str));
    }
    float get_value(std::string parameter)
    {
        std::string val_str = get_value_str(parameter);
        return static_cast<float>(std::stoi(val_str));
    }
};

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "Russian");

    ini_parser parser("test.ini");

    try
    {
        std::cout << "String: " << parser.get_value<std::string>("Section_3.Var_1") << std::endl;
        std::cout << "Int: " << parser.get_value<int>("Section_1.Var_1") << std::endl;
        std::cout << "Double: " << parser.get_value<double>("Section_3.Var_2") << std::endl;
        std::cout << "Float: " << parser.get_value<float>("Section_3.Var_3") << std::endl;
        std::cout << "When error happening: ";
        parser.get_value<float>("Section_2.Var_1");
    }
    catch (const DivisionByZeroException& ex) 
    { 
        std::cout << ex.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "Неизвестная ошибка" << std::endl;
    }

    return 0;
}
