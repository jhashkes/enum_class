// Licensed under the MIT License <http://opensource.org/licenses/MIT>.
// SPDX-License-Identifier: MIT
// Copyright (c) 2019 - 2021 Jonathan Hashkes <jon_repo@hashkes.com>.
//
// Permission is hereby  granted, free of charge, to any  person obtaining a copy
// of this software and associated  documentation files (the "Software"), to deal
// in the Software  without restriction, including without  limitation the rights
// to  use, copy,  modify, merge,  publish, distribute,  sublicense, and/or  sell
// copies  of  the Software,  and  to  permit persons  to  whom  the Software  is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR
// IMPLIED,  INCLUDING BUT  NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
// FITNESS FOR  A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
// AUTHORS  OR COPYRIGHT  HOLDERS  BE  LIABLE FOR  ANY  CLAIM,  DAMAGES OR  OTHER
// LIABILITY, WHETHER IN AN ACTION OF  CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE  OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <iostream>
#include <optional>

#include "enum_class.hpp"

// Output enum name and value
template<typename ENUM_VALUE>
void print_enum(enum_class::EnumName name, std::optional<ENUM_VALUE> optional_value)
{
    if (optional_value)
        std::cout << name << " = " << static_cast<int>(*optional_value) << std::endl;
    else
        std::cout << name << " Not Found" << std::endl;
}

// Define Animal enum class
ENUM_CLASS(Animal, int,
    CAT = -5, DOG, HORSE = 7);

// Define OuterClass::Car enum class
struct OuterClass
{
    bool x;
    ENUM_CLASS(Car, int,
        BMW = -1, CHEVY, NISSAN = 6, MAZDA);
    int y;
};

// Demonstrate the various functions
int main()
{
    // Output: DOG = -6
    {
        Animal animal{ Animal::DOG };
        auto animal_name = enum_class::Name<Animal>(animal);            // access using enum_class namespace
        print_enum(animal_name, std::optional(animal));
    }

    // Output: HORSE = 7
    {
        std::string animal_name{ "HORSE" };
        auto optional_animal = AnimalMeta::Value(animal_name);          // access using automatically generated meta class
        print_enum(animal_name, optional_animal);
    }

    // Output: CAMEL = Not Found
    {
        std::string animal_name{ "CAMEL" };
        auto optional_animal = enum_class::Value<Animal>(animal_name);  // access using enum_class namespace
        print_enum(animal_name, optional_animal);
    }
    std::cout << std::endl;

    // Output: Animal Count = 3, CAT = -5, DOG = -4, HORSE = 7
    {
        auto animals = AnimalMeta::Values();
        std::cout << "Animal Count = " << animals.size() << std::endl;
        for (auto animal : animals)
            print_enum(AnimalMeta::Name(animal), std::optional(animal));
    }
    std::cout << std::endl;

    // Output: Animal Count = 3, CAT = -5, DOG = -4, HORSE = 7
    {
        auto animal_names = AnimalMeta::Names();
        std::cout << "Animal Count = " << animal_names.size() << std::endl;
        for (const auto& animal_name : animal_names)
            print_enum(animal_name, AnimalMeta::Value(animal_name));
    }
    std::cout << std::endl;

    // Output: Car Count = 4, BMW = -1, CHEVY = 0, NISSAN = 6, MAZDA = 7
    {
        auto car_names = OuterClass::CarMeta::Names();
        std::cout << "Car Count = " << car_names.size() << std::endl;
        for (const auto& car_name : car_names)
            print_enum(car_name, OuterClass::CarMeta::Value(car_name));
    }

    return 0;
}
