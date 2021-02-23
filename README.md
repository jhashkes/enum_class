# C++ Enum Class


## Features

* C++17
* Header-only
* Dependency-free
* Enum to string
* String to enum
* Retrieve sequence of Enum values or names

## [Examples](example/example.cpp)

```cpp
ENUM_CLASS(Animal, int,
    CAT = -5, DOG, HORSE = 7);
```

* Enum value to string

  Access enum class metadata using enum_class namespace functions:

  ```cpp
  auto animal_str = enum_class::Name<Animal>(Animal::DOG);
  // animal_str == "DOG"
  ```
  
  Alternative method using automatically generated meta class:

  ```cpp
  auto animal_str = AnimalMeta::Name(Animal::DOG);
  // animal_str == "DOG"
  ```

* String to enum value

  ```cpp
  auto animal = enum_class::Value<Animal>("HORSE");
  if (animal) {
    // *animal == Animal::HORSE
  }
  ```

* Enum values sequence

  ```cpp
  auto animals = enum_class::Values<Animal>();
  // animals == { Animal::CAT, Animal::DOG, Animal::HORSE }
  // animals[0] == Animal::CAT
  ```

* Enum names sequence

  ```cpp
  auto animal_names = enum_class::Names<Animal>();
  // animal_names == { "CAT", "DOG", "HORSE" }
  // animal_names[0] == "CAT"
  ```

## Remarks

## Integration

* Include [enum_class.hpp](include/enum_class.hpp).

## Compiler compatibility

## Licensed under the [MIT License](LICENSE)
