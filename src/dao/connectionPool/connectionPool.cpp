#include <dao/connectionPool/connectionPool.h>

namespace DAO {
    PooledConnection::PooledConnection(const std::string &connection_string, std::shared_ptr<ConnectionPool> pool)
            : pqxx::connection(connection_string), pool_(std::move(pool)) {
        logger_.debug("PooledConnection constructor called");
    }

    PooledConnection::~PooledConnection() {
        if (is_open()) {
            close();
        }
        logger_.debug("PooledConnection destructor called");
    }

    void PooledConnection::close() {
        logger_.debug("Closing connection");//TODO 1 connection use and i dont know where
        ConnectionPool::getInstance()->free_connection(shared_from_this());
    }

    std::shared_ptr<pqxx::connection> PooledConnection::get_base_connection() {
        return shared_from_this();
    }
    log4cpp::Category &PooledConnection::logger_ = log4cpp::Category::getInstance("PooledConnection");

    std::shared_ptr<ConnectionPool> ConnectionPool::instance = std::shared_ptr<ConnectionPool>(
            new ConnectionPool);//TODO
    log4cpp::Category &ConnectionPool::logger_ = log4cpp::Category::getInstance("ConnectionPool");

    ConnectionPool::ConnectionPool(std::string_view connection_string, int pool_size)
            : connection_string_(connection_string), pool_size_(pool_size) {
        logger_.debug(
                "Initializing ConnectionPool with connection string: " + static_cast<std::string>(connection_string) +
                " and pool size: " +
                std::to_string(pool_size));
    }

    void ConnectionPool::setFreeConnections(const std::queue<std::shared_ptr<PooledConnection>> &freeConnections) {
        free_connections_ = freeConnections;
    }

    void
    ConnectionPool::setUsedConnections(const std::unordered_set<std::shared_ptr<PooledConnection>> &usedConnections) {
        used_connections_ = usedConnections;
    }

    std::shared_ptr<ConnectionPool> ConnectionPool::getInstance() {
        return instance;
    }

    void ConnectionPool::setConnectionString(std::string_view connectionString) {
        this->connection_string_ = connectionString;
    }

    void ConnectionPool::setPoolSize(int poolSize) {
        this->pool_size_ = poolSize;
    }

    void ConnectionPool::init(std::string_view connection_string, int pool_size) {
        setConnectionString(connection_string);
        setPoolSize(pool_size);
        for (int i = 0; i < pool_size_; ++i) {
            free_connections_.push(create_connection());
        }
        logger_.debug("Initialized ConnectionPool with " + std::to_string(pool_size_) + " connections");
    }

    ConnectionPool::~ConnectionPool() {
        close_all();
        logger_.debug("Destroyed ConnectionPool");
    }

    std::shared_ptr<PooledConnection> ConnectionPool::getConnection() {
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

    void ConnectionPool::free_connection(const std::shared_ptr<PooledConnection> &connection) {
        std::unique_lock<std::mutex> lock(mutex_);

        used_connections_.erase(connection);
        free_connections_.push(connection);

        logger_.debug(
                "Freed connection from ConnectionPool. Current pool size: " + std::to_string(free_connections_.size()) +
                " free connections; " + std::to_string(used_connections_.size()) + " used connections");
        cv_.notify_one();
    }

    void ConnectionPool::destroy() {
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

    std::shared_ptr<PooledConnection> ConnectionPool::create_connection() {
        return std::make_shared<PooledConnection>(connection_string_, shared_from_this());
    }

    void ConnectionPool::close_all() {
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

}
