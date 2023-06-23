//
// Created by daniil on 6/22/23.
//
#include <dao/connectionPool/connectionPool.h>
#include <log4cpp/PropertyConfigurator.hh>
int main(){
    std::shared_ptr<ConnectionPool> pool = std::make_shared<ConnectionPool>
            ("host=localhost port=5432 dbname=postgres user=root password=root", 2);
    pool->init();
    std::cout << "Connected\n";
    std::shared_ptr<PooledConnection> connection = pool->get_connection();
    std::cout << "Connected\n";
    pqxx::work work(*(connection->get_base_connection()));
    pqxx::result rs = work.exec("SELECT * FROM customers");
    std::cout << "Execed\n";
    for(auto vec : rs) {
        for (auto v: vec)
            std::cout << v << ' ';
        std::cout << '\n';
    }
}