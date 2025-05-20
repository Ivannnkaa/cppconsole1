#include "processing.h"
#include <vector>

    double process(const std::vector<CallRecord>&records) {
        double totalCost = 0.0;
        int totalDuration = 0;

        for (const auto& record : records) {
            totalCost += record.cost_per_minute * (record.duration_seconds() / 60.0);
            totalDuration += record.duration_seconds();
        }

        if (totalDuration == 0) {
            throw std::invalid_argument("Total duration cannot be zero.");
        }

        return totalCost / totalDuration;
    }