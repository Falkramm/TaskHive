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

class ConnectionPool;

class PooledConnection : public pqxx::connection, public std::enable_shared_from_this<PooledConnection> {
public:
    PooledConnection(const std::string &connection_string, std::shared_ptr<ConnectionPool> pool)
            : pqxx::connection(connection_string), pool_(std::move(pool)) {
        logger_.debug("PooledConnection constructor called");
    }


    virtual ~PooledConnection() {
        if (is_open()) {
            close();
        }
        logger_.debug("PooledConnection destructor called");
    }

    void close() {
        logger_.debug("Closing connection");
        pqxx::connection::close();
    }

    std::shared_ptr<pqxx::connection> get_base_connection() {
        return shared_from_this();
    }


private:
    std::shared_ptr<ConnectionPool> pool_;
    static log4cpp::Category &logger_;
};

log4cpp::Category &PooledConnection::logger_ = log4cpp::Category::getInstance("PooledConnection");


class ConnectionPool : public std::enable_shared_from_this<ConnectionPool> {
public:
    static std::shared_ptr<ConnectionPool> instance;
    ConnectionPool() = default;
    ConnectionPool(std::string_view connection_string, int pool_size)
            : connection_string_(connection_string), pool_size_(pool_size) {
        logger_.debug(
                "Initializing ConnectionPool with connection string: " + static_cast<std::string>(connection_string) +
                " and pool size: " +
                std::to_string(pool_size));
    }

public:
    void setFreeConnections(const std::queue<std::shared_ptr<PooledConnection>> &freeConnections) {
        free_connections_ = freeConnections;
    }

    void setUsedConnections(const std::unordered_set<std::shared_ptr<PooledConnection>> &usedConnections) {
        used_connections_ = usedConnections;
    }

    ConnectionPool(ConnectionPool &other) = delete;

    void operator=(const ConnectionPool &) = delete;

    static std::shared_ptr<ConnectionPool> getInstance() {
        return instance;
    }

    void setConnectionString(std::string_view connectionString){
        this->connection_string_ = connectionString;
    }

    void setPoolSize(int poolSize){
        this->pool_size_ = poolSize;
    }

    void init(std::string_view connection_string = "host=localhost port=5432 dbname=postgres user=root password=root", int pool_size = 10) {
        setConnectionString(connection_string);
        setPoolSize(pool_size);
        for (int i = 0; i < pool_size_; ++i) {
            free_connections_.push(create_connection());
        }
        logger_.debug("Initialized ConnectionPool with " + std::to_string(pool_size_) + " connections");
    }

    ~ConnectionPool() {
        close_all();
        logger_.debug("Destroyed ConnectionPool");
    }

    std::shared_ptr<PooledConnection> getConnection() {
        std::unique_lock<std::mutex> lock(mutex_);
        while (free_connections_.empty()) {
            cv_.wait(lock);
        }
        auto connection = free_connections_.front();
        free_connections_.pop();
        used_connections_.insert(connection);

        logger_.debug(
                "Got connection from ConnectionPool. Current pool size: " + std::to_string(free_connections_.size()) +
                " free connections; " + std::to_string(used_connections_.size()) + " used connections");

        return connection;
    }

    void free_connection(const std::shared_ptr<PooledConnection> &connection) {
        std::unique_lock<std::mutex> lock(mutex_);

        used_connections_.erase(connection);
        free_connections_.push(connection);

        logger_.debug(
                "Freed connection from ConnectionPool. Current pool size: " + std::to_string(free_connections_.size()) +
                " free connections; " + std::to_string(used_connections_.size()) + " used connections");

        cv_.notify_one();
    }
    void destroy() {
        std::unique_lock<std::mutex> lock(mutex_);
        while (!free_connections_.empty()){
            used_connections_.insert(free_connections_.front());
            free_connections_.pop();
        }
        for(auto &connection : used_connections_) {
            try {
                connection->close();
            } catch(std::exception e) {
                logger_.error("Can't close connection" + static_cast<std::string>(e.what()));
            }
        }
        used_connections_.clear();
    }
private:
    std::shared_ptr<PooledConnection> create_connection() {
        return std::make_shared<PooledConnection>(connection_string_, shared_from_this());
    }

    void close_all() {
        std::unique_lock<std::mutex> lock(mutex_);

        for (auto &connection: used_connections_) {
            connection->close();
        }
        used_connections_.clear();
        while (!free_connections_.empty()) {
            free_connections_.front()->close();
            free_connections_.pop();
        }

        logger_.debug("Closed all connections in ConnectionPool");
    }

    std::string connection_string_;
    int pool_size_;
    std::queue<std::shared_ptr<PooledConnection>> free_connections_;
    std::unordered_set<std::shared_ptr<PooledConnection>> used_connections_;
    std::mutex mutex_;
    std::condition_variable cv_;
    static log4cpp::Category &logger_;
};
std::shared_ptr<ConnectionPool> ConnectionPool::instance = std::shared_ptr<ConnectionPool>(new ConnectionPool);//TODO

log4cpp::Category &ConnectionPool::logger_ = log4cpp::Category::getInstance("ConnectionPool");

#endif //TASKHIVE_CONNECTIONPOOL_H
