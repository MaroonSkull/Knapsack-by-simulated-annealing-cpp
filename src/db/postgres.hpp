#include <userver/storages/postgres/cluster.hpp>
#include <userver/storages/postgres/component.hpp>

void SaveToDatabase(const KnapsackProblem& problem, 
                   const KnapsackSolution& solution) {
    auto result = pg_cluster_->Execute(
        storages::postgres::ClusterHostType::kMaster,
        "INSERT INTO history(request, solution) VALUES($1, $2)",
        problem.Serialize(), solution.Serialize());
}

std::vector<HistoryEntry> LoadHistory() {
    auto result = pg_cluster_->Execute(
        storages::postgres::ClusterHostType::kSlave,
        "SELECT request, solution, created_at FROM history");
    
    return result.AsContainer<std::vector<HistoryEntry>>();
}