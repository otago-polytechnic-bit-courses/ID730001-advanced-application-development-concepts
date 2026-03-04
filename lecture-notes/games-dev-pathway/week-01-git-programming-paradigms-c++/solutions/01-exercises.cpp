#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>

struct User {
    int id;
    std::string name;
    int age;
    std::vector<int> purchases;
    int member_since;
    std::string status;
};

struct ProcessedUser {
    std::string name;
    int total_spent;
    int loyalty_years;
    std::string tier;
};

struct PipelineResult {
    std::vector<ProcessedUser> processed_users;
    int total_revenue;
    int user_count;
    double average_spending;
};

PipelineResult process_data_pipeline(const std::vector<User>& users) {

    std::vector<User> filtered;
    std::copy_if(users.begin(), users.end(), std::back_inserter(filtered), [](const User& user) {
        return user.status == "active" && user.age >= 25;
    });

    std::vector<ProcessedUser> processed_users;
    std::transform(filtered.begin(), filtered.end(), std::back_inserter(processed_users), [](const User& user) {
        ProcessedUser pu;
        pu.name = user.name;
        pu.total_spent = std::accumulate(user.purchases.begin(), user.purchases.end(), 0);
        pu.loyalty_years = 2026 - user.member_since;

        if (pu.total_spent < 500) {
            pu.tier = "Bronze";
        } else if (pu.total_spent < 1000) {
            pu.tier = "Silver";
        } else {
            pu.tier = "Gold";
        }

        return pu;
    });

    int total_revenue = std::accumulate(processed_users.begin(), processed_users.end(), 0, [](int sum, const ProcessedUser& user) {
        return sum + user.total_spent;
    });

    PipelineResult result;
    result.processed_users = processed_users;
    result.total_revenue = total_revenue;
    result.user_count = processed_users.size();
    result.average_spending = result.user_count > 0 ? static_cast<double>(total_revenue) / result.user_count : 0.0;

    return result;
}

int main() {
    std::vector<User> users = {
        {1, "Alice", 30, {200, 400, 150}, 2019, "active"},
        {2, "Bob", 22, {100, 50}, 2021, "active"},
        {3, "Charlie", 28, {500, 600}, 2020, "inactive"},
        {4, "Diana", 35, {300, 200, 100}, 2018, "active"}
    };

    auto result = process_data_pipeline(users);

    std::cout << "Processed Users:\n";
    for (const auto& user : result.processed_users) {
        std::cout << user.name << ", total_spent: " << user.total_spent
                  << ", loyalty_years: " << user.loyalty_years
                  << ", tier: " << user.tier << "\n";
    }
    std::cout << "Total Revenue: " << result.total_revenue << "\n";
    std::cout << "User Count: " << result.user_count << "\n";
    std::cout << "Average Spending: " << result.average_spending << "\n";

    return 0;
}