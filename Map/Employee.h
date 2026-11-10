#pragma once

#include <string>
#include <iostream>

class Employee {

    public:
        std::string fullName;
        std::string position;
        int age;

    Employee(std::string fullName, std::string position, int age) : fullName(fullName), position(position), age(age) {}

    friend std::ostream& operator<<(std::ostream& os, const Employee& employee) {
          os << employee.fullName << ", " << employee.position << ", " << employee.age;
          return os;
    }
};
