#include "SimulationController.h"
#include <iostream>
#include <locale>
#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <random>
#include <memory>

int main() {
    setlocale(LC_ALL, "Russian");

    std::cout << "    МОДЕЛЬ СИСТЕМЫ УМНОГО ЛИФТА" << std::endl;
    std::cout << "Вариант 12: Система управления умным лифтом" << std::endl;

    // Настройки
    int bufferCapacity = 5;
    int numElevators = 2;

    std::cout << "\nКонфигурация системы:" << std::endl;
    std::cout << " - Размер буфера: " << bufferCapacity << std::endl;
    std::cout << " - Количество лифтов: " << numElevators << std::endl;

    SimulationController simulator(bufferCapacity, numElevators);

    std::cout << "\nПошаговая симуляция" << std::endl;

    simulator.runStepByStep();

    return 0;
}