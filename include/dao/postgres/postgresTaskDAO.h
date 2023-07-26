//
// Created by daniil on 6/25/23.
//

#ifndef TASKHIVE_POSTGRESTASKDAO_H
#define TASKHIVE_POSTGRESTASKDAO_H
#include <dao/DAO.h>
#include <dao/abstractPQXXDao.h>
#include <utility>
#include <entity/Task.h>
#include <entity/User.h>
namespace DAO{
    class PostgresTaskDAO : public AbstractPQXXDao<Task, std::string> {
    private:
        static std::string selectQ;
        static std::string selectALlQ;
        static std::string insertQ;
        static std::string updateQ;
        static std::string deleteQ;

        class PersistTask : public Task {
        public:
            void setId(std::string_view id) override;
        };

        std::string getSelectQuery() const override;

        std::string getSelectAllQuery() const override;

        std::string getCreateQuery() const override;

        std::string getUpdateQuery() const override;

        std::string getDeleteQuery() const override;

        std::shared_ptr<Task> create() override;

    //    boost::posix_time::ptime pTimeFromString(std::string str)const {
    //        boost::posix_time::ptime datetime = boost::posix_time::time_from_string(str);
    //        boost::posix_time::ptime epoch(boost::gregorian::date(1970,1,1));
    //        boost::posix_time::time_duration duration = datetime - epoch;
    //        auto start_time = std::chrono::high_resolution_clock::now();
    //
    //        // Execute a SELECT query to read data from a table
    //        pqxx:: my_timestamp = result_set.at(0).at("mytimestamp").as<pqxx::timestamp>();
    //
    //        // End the timer and calculate the elapsed time in milliseconds
    //        auto end_time = std::chrono::high_resolution_clock::now();
    //        auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    //
    //        return datetime;
    //    }
        std::vector<std::shared_ptr<Task>> parseResultSet(const pqxx::result &rs) const override;

    protected:


        std::shared_ptr<pqxx::result>
        prepareStatementForInsert(pqxx::work &work, std::shared_ptr<Task> object) const override;

        std::shared_ptr<pqxx::result>
        prepareStatementForUpdate(pqxx::work &work, std::shared_ptr<Task> object) const override;

    public:
        std::vector<std::shared_ptr<Task>> getByUser(std::shared_ptr<User> user);

    public:
        [[maybe_unused]] explicit PostgresTaskDAO(std::shared_ptr<PooledConnection> connection_);

    public:
        class TaskCreator: public DaoCreator{
        public:
            [[nodiscard]] boost::any create(std::shared_ptr<PooledConnection> pooledConnection)const override;
        };
    };
}
#endif //TASKHIVE_POSTGRESTASKDAO_H
