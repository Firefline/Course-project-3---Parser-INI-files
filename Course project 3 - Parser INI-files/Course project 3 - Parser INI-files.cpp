// Course project 3 - Parser INI-files.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <list>

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
    template <class T>
    T get_value(std::string parameter)
    {
        int count = 0;
        for (auto iter = section.begin(); iter != section.end(); iter++)
        {
            if (*iter == parameter)
            {
                iter++;
                count++;
                std::cout << *iter;
                return *iter;
            }
        }
        if (count == 0)
        {
            std::cout << "Значение не найдено" << std::endl;
            return " ";
        }
    }
};

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "Russian");

    ini_parser parser("test.ini");

    auto values = parser.get_value<std::string>("Section_1.Var_1");

    return 0;
}
