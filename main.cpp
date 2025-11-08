#include <iostream>
#include <memory>
#include <vector>
#include "include/Array.h"
#include "include/Rhombus.h"
#include "include/Pentagon.h"
#include "include/Hexagon.h"

#ifdef _WIN32
#include <windows.h>
#endif

void demonstrate_requirements() {
    std::cout << "\n=== Демонстрация требований ===\n";
    
    Array<Figure<int>*> figure_array;
    
    Figure<int>* rhombus = new Rhombus<int>();
    Figure<int>* pentagon = new Pentagon<int>();
    Figure<int>* hexagon = new Hexagon<int>();
    
    figure_array.push_back(rhombus);
    figure_array.push_back(pentagon);
    figure_array.push_back(hexagon);
    
    std::cout << "Массив Figure<int>*:\n";
    for (size_t i = 0; i < figure_array.size(); ++i) {
        std::cout << i << ") ";
        figure_array[i]->print(std::cout);
        std::cout << "\n";
    }
    
    for (size_t i = 0; i < figure_array.size(); ++i) {
        delete figure_array[i];
    }
    
    Array<Rhombus<int>> rhombus_array;
    Rhombus<int> r1, r2;
    rhombus_array.push_back(r1);
    rhombus_array.push_back(r2);
    
    std::cout << "Массив Rhombus<int>:\n";
    for (size_t i = 0; i < rhombus_array.size(); ++i) {
        std::cout << i << ") ";
        rhombus_array[i].print(std::cout);
        std::cout << "\n";
    }
}

template<Scalar T>
void interactive_menu() {
    Array<std::shared_ptr<Figure<T>>> figures;
    int choice;

    while (true) {
        std::cout << "\n=== Меню ===\n"
                  << "1. Добавить ромб\n"
                  << "2. Добавить пятиугольник\n"
                  << "3. Добавить шестиугольник\n"
                  << "4. Показать все фигуры\n"
                  << "5. Общая площадь фигур\n"
                  << "6. Удалить фигуру по индексу\n"
                  << "7. Демонстрация\n"
                  << "0. Выход\n"
                  << "Выберите действие: ";
        std::cin >> choice;

        if (choice == 0) break;

        try {
            switch (choice) {
                case 1: {
                    auto rhomb = std::make_shared<Rhombus<T>>();
                    std::cout << "Введите 4 точки для ромба (x y для каждой точки): ";
                    std::cin >> *rhomb;
                    figures.push_back(rhomb);
                    std::cout << "Ромб добавлен.\n";
                    break;
                }
                case 2: {
                    auto pent = std::make_shared<Pentagon<T>>();
                    std::cout << "Введите 5 точек для пятиугольника (x y для каждой точки): ";
                    std::cin >> *pent;
                    figures.push_back(pent);
                    std::cout << "Пятиугольник добавлен.\n";
                    break;
                }
                case 3: {
                    auto hex = std::make_shared<Hexagon<T>>();
                    std::cout << "Введите 6 точек для шестиугольника (x y для каждой точки): ";
                    std::cin >> *hex;
                    figures.push_back(hex);
                    std::cout << "Шестиугольник добавлен.\n";
                    break;
                }
                case 4: {
                    if (figures.empty()) {
                        std::cout << "Нет фигур для отображения.\n";
                    } else {
                        std::cout << "\nСписок фигур:\n";
                        for (size_t i = 0; i < figures.size(); ++i) {
                            std::cout << i << ") " << *figures[i]
                                      << "\n   Центр: (" << figures[i]->center().x 
                                      << ", " << figures[i]->center().y << ")"
                                      << "\n   Площадь: " << static_cast<double>(*figures[i]) << "\n\n";
                        }
                    }
                    break;
                }
                case 5: {
                    double total_area = 0;
                    for (const auto& fig : figures)
                        total_area += static_cast<double>(*fig);
                    std::cout << "Общая площадь всех фигур: " << total_area << "\n";
                    break;
                }
                case 6: {
                    size_t index;
                    std::cout << "Введите индекс фигуры для удаления: ";
                    std::cin >> index;
                    if (index < figures.size()) {
                        figures.erase(index);
                        std::cout << "Фигура удалена.\n";
                    } else {
                        std::cout << "Неверный индекс!\n";
                    }
                    break;
                }
                case 7: {
                    demonstrate_requirements();
                    break;
                }
                default:
                    std::cout << "Неверный выбор!\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << "\n";
        }
    }
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    std::cout << "=== Программа для работы с геометрическими фигурами ===\n";
    
    int type_choice;
    std::cout << "Выберите тип координат:\n"
              << "1 - int (целые числа)\n"
              << "2 - double (вещественные числа)\n"
              << "Ваш выбор: ";
    std::cin >> type_choice;

    if (type_choice == 1) {
        interactive_menu<int>();
    } else if (type_choice == 2) {
        interactive_menu<double>();
    } else {
        std::cout << "Неверный выбор!\n";
    }

    return 0;
}