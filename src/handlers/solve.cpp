#include <userver/components/component.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/storages/postgres/postgres.hpp>

namespace handlers {

class SolveKnapsack final : public server::handlers::HttpHandlerBase {
public:
    static constexpr std::string_view kName = "handler-solve";

    SolveKnapsack(const components::ComponentConfig& config,
                 const components::ComponentContext& context)
        : HttpHandlerBase(config, context),
          pg_cluster_(context.FindComponent<components::Postgres>("postgres-db")
                           .GetCluster()) {}

    std::string HandleRequestThrow(
        const server::http::HttpRequest& request,
        server::request::RequestContext&) const override {
        
        auto problem = ParseProblem(request.RequestBody());
        auto solution = simulated_annealing(problem.items, problem.capacity);
        
        SaveToDatabase(problem, solution);
        
        return SerializeSolution(solution);
    }

private:
    storages::postgres::ClusterPtr pg_cluster_;
};

} // namespace handlers