import Utils.Json;

#include <iostream>

int main()
{
    utils::json::Document doc{R"json({"name": "Slava","age": 30})json"};
    std::cout << doc.getString("name") << " " << doc.getString("age") << std::endl;
}
