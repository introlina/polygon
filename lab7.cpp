#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;


// ЗАДАЧА 632, НУЖНО НАЙТИ НАИМЕНЬШИЙ ИНТЕРВАЛ ОТ А ДО В (вкл)
// КОТОРЫЙ ЗАХВАТИТ ХОТЯ БЫ ПО ЭЛЕМЕНТУ ИЗ ВСЕХ k МАССИВОВ

//O(N*logN)

// функция для проверки, является ли новый диапазон лучше
bool isBetterRange(int minA, int maxA, int minB, int maxB) {
    // o(1) - фиксированное количество операций
    if (maxA - minA < maxB - minB) {
        return true;
    } else if (maxA - minA == maxB - minB) {
        return minA < minB;
    }
    return false;
}

vector<int> smallestRange(vector<vector<int>>& nums) {
    // o(1) - фиксированное количество операций
    int bestMin = -1e5, bestMax = 1e5; 
    int totalLists = nums.size(); // o(1) - количество списков

    // вектор для пар (значение, индекс списка)
    vector<pair<int, int>> sortedValues; // o(n), где n - общее количество элементов во всех списках
    for (int i = 0; i < totalLists; i++) {
        for (int j = 0; j < nums[i].size(); j++) {
            sortedValues.push_back({nums[i][j], i}); // o(1)
        }
    }

    // сортируем значения
    sort(sortedValues.begin(), sortedValues.end()); // o(n log n), где n - размер sortedValues

    unordered_map<int, int> countMap; // для подсчета элементов из каждого списка. o(k), k - кол-во списков
    int left = 0, right = 0; // o(1) - фиксированное количество операций
    int n = sortedValues.size(); // o(1)

    while (right < n) { // o(n)
        int currentValue = sortedValues[right].first; // o(1)
        int currentListIndex = sortedValues[right].second; // o(1)

        countMap[currentListIndex]++; // увеличиваем счетчик для текущего списка. o(1) в среднем

        // проверяем, есть ли элементы из всех списков
        while (countMap.size() >= totalLists) { // в худшем случае o(n)
            // проверяем, является ли текущий диапазон лучше
            if (isBetterRange(sortedValues[left].first, currentValue, bestMin, bestMax)) { 
                bestMin = sortedValues[left].first; // o(1)
                bestMax = currentValue; // o(1)
            }

            // уменьшаем счетчик для элемента на позиции left
            int oldListIndex = sortedValues[left].second; // o(1)
            countMap[oldListIndex]--; // o(1)

            left++; // увеличиваем указатель left. o(1)

            // если счетчик стал нулевым, удаляем его из карты
            if (countMap[oldListIndex] == 0) { 
                countMap.erase(oldListIndex); // o(1) в среднем
            }
        }

        right++; // увеличиваем указатель right. o(1)
    }

    return {bestMin, bestMax}; // o(1)
}

int main() {
    vector<vector<int>> nums = {{4,10,15,24,26},{0,9,12,20},{5,18,22,30}};
    vector<int> range = smallestRange(nums);
    cout << "[" << range[0] << "," << range[1] << "]" << endl; 
    return 0;
}