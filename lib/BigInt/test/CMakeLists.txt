# Минимальная версия CMake
cmake_minimum_required(VERSION 3.29)
project(bigint-tests)

set(CMAKE_CXX_STANDARD 17)

# Подключаем директорию заголовков библиотеки
include_directories(${PROJECT_SOURCE_DIR}/../include)

# Добавляем исполняемый файл для тестов
add_executable(runBigIntTests tests-bigint.cpp)

# Подключаем Google Test и основную библиотеку
target_link_libraries(runBigIntTests BigInt gtest gtest_main)

# Регистрируем тесты для CTest
add_test(NAME BigIntTests COMMAND runBigIntTests)
