#include <vector>
#include <random>
#include <cmath>

struct Item {
    double weight;
    double value;
};

struct Solution {
    double total_value;
    std::vector<Item> items;
};

Solution simulated_annealing(const std::vector<Item>& items, double capacity) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    // Инициализация
    auto current_solution = generate_initial_solution(items, capacity);
    Solution best_solution = current_solution;
    
    double temp = 1000.0;
    const double cooling_rate = 0.003;

    while (temp > 1) {
        auto neighbor = generate_neighbor(current_solution, items, capacity);
        
        if (acceptance_probability(current_solution.total_value, 
                                  neighbor.total_value, 
                                  temp) > dis(gen)) {
            current_solution = neighbor;
        }
        
        if (current_solution.total_value > best_solution.total_value) {
            best_solution = current_solution;
        }
        
        temp *= 1 - cooling_rate;
    }
    
    return best_solution;
}