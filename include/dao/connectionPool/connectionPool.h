//
// Created by daniil on 6/22/23.
//

#ifndef TASKHIVE_CONNECTIONPOOL_H
#define TASKHIVE_CONNECTIONPOOL_H

#include <pqxx/pqxx>
#include <queue>
#include <unordered_set>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <string>
#include <string_view>
#include <log4cpp/Category.hh>
#include <dao/DAO.h>
namespace DAO{
    class ConnectionPool;

    class PooledConnection : public pqxx::connection, public std::enable_shared_from_this<PooledConnection> {
    public:
        PooledConnection(const std::string &connection_string, std::shared_ptr<ConnectionPool> pool);

        virtual ~PooledConnection();

        void close();

        std::shared_ptr<pqxx::connection> get_base_connection();


    private:
        std::shared_ptr<ConnectionPool> pool_;
        static log4cpp::Category &logger_;
    };




    class ConnectionPool : public std::enable_shared_from_this<ConnectionPool> {
    public:
        static std::shared_ptr<ConnectionPool> instance;
        ConnectionPool() = default;
        ConnectionPool(std::string_view connection_string, int pool_size);

    public:
        void setFreeConnections(const std::queue<std::shared_ptr<PooledConnection>> &freeConnections);

        void setUsedConnections(const std::unordered_set<std::shared_ptr<PooledConnection>> &usedConnections);

        ConnectionPool(ConnectionPool &other) = delete;

        void operator=(const ConnectionPool &) = delete;

        static std::shared_ptr<ConnectionPool> getInstance();

        void setConnectionString(std::string_view connectionString);

        void setPoolSize(int poolSize);

        void init(std::string_view connection_string = "host=localhost port=5432 dbname=postgres user=root password=root", int pool_size = 10);

        ~ConnectionPool();

        std::shared_ptr<PooledConnection> getConnection();

        void free_connection(const std::shared_ptr<PooledConnection> &connection);
        void destroy();
    private:
        std::shared_ptr<PooledConnection> create_connection();

        void close_all();

        std::string connection_string_;
        int pool_size_;
        std::queue<std::shared_ptr<PooledConnection>> free_connections_;
        std::unordered_set<std::shared_ptr<PooledConnection>> used_connections_;
        std::mutex mutex_;
        std::condition_variable cv_;
        static log4cpp::Category &logger_;
    };

}
#endif //TASKHIVE_CONNECTIONPOOL_H
