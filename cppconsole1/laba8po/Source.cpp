
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <queue>


struct CallRecord {
    std::string number;
    std::string called_number;
    std::string date;
    std::string time;
    std::string duration;
    std::string tariff;
    double cost_per_minute;

    int duration_seconds() const {
        int h, m, s;
        sscanf_s(duration.c_str(), "%d:%d:%d", &h, &m, &s);
        return h * 3600 + m * 60 + s;
    }

    bool is_mobile() const {
        return tariff == "мобильный";
    }

    bool is_november_2021() const {
        return date.substr(3, 7) == "11.2021";
    }

    bool operator<(const CallRecord& other) const {
        if (duration_seconds() != other.duration_seconds()) {
            return duration_seconds() < other.duration_seconds();
        }
        if (number != other.number) {
            return number < other.number;
        }
        return cost_per_minute > other.cost_per_minute;
    }

    bool operator>(const CallRecord& other) const {
        if (duration_seconds() != other.duration_seconds()) {
            return duration_seconds() > other.duration_seconds();
        }
        if (number != other.number) {
            return number > other.number;
        }
        return cost_per_minute < other.cost_per_minute;
    }
};

void heapify(std::vector<CallRecord>& records, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && records[left] < records[largest]) {
        largest = left;
    }
    if (right < n && records[right] < records[largest]) {
        largest = right;
    }

    if (largest != i) {
        std::swap(records[i], records[largest]);
        heapify(records, n, largest);
    }
}

void heapSort(std::vector<CallRecord>& records) {
    int n = records.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(records, n, i);
    }
    for (int i = n - 1; i > 0; i--) {
        std::swap(records[0], records[i]);
        heapify(records, i, 0);
    }
}

void quickSort(std::vector<CallRecord>& records, int low, int high) {
    if (low < high) {
        CallRecord pivot = records[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (!(records[j] > pivot)) {
                i++;
                std::swap(records[i], records[j]);
            }
        }
        std::swap(records[i + 1], records[high]);
        int pi = i + 1;
        quickSort(records, low, pi - 1);
        quickSort(records, pi + 1, high);
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    std::ifstream file("input.txt");
    std::vector<CallRecord> records;
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        CallRecord record;
        ss >> record.number >> record.called_number >> record.date >> record.time >> record.duration >> record.tariff >> record.cost_per_minute;
        records.push_back(record);
    }
    file.close();

    std::cout << "Все звонки на мобильные номера:\n";
    for (const auto& record : records) {
        if (record.is_mobile()) {
            std::cout << record.number << " -> " << record.called_number << " | " << record.date << " | " << record.time << " | " << record.duration << "\n";
        }
    }

    std::cout << "\nВсе звонки в ноябре 2021 года:\n";
    for (const auto& record : records) {
        if (record.is_november_2021()) {
            std::cout << record.number << " -> " << record.called_number << " | " << record.date << " | " << record.time << " | " << record.duration << "\n";
        }
    }

    heapSort(records);
    std::cout << "\nЗвонки после пирамидальной сортировки (по убыванию продолжительности):\n";
    for (const auto& record : records) {
        std::cout << record.number << " -> " << record.called_number << " | " << record.duration << " | " << record.cost_per_minute << "\n";
    }

    quickSort(records, 0, records.size() - 1);
    std::cout << "\nЗвонки после быстрой сортировки (по возрастанию номера и убыванию стоимости):\n";
    for (const auto& record : records) {
        std::cout << record.number << " -> " << record.called_number << " | " << record.duration << " | " << record.cost_per_minute << "\n";
    }
    std::cout << "Nice!!!";
    return 0;
}
