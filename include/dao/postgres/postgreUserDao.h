//
// Created by daniil on 6/24/23.
//

#ifndef TASKHIVE_POSTGREUSERDAO_H
#define TASKHIVE_POSTGREUSERDAO_H

#include <dao/abstractPQXXDao.h>
#include <entity/User.h>

class MySqlUserDAO : public AbstractPQXXDao<User, std::string_view> {
private:
    static std::string_view selectQ = "SELECT * FROM water.user";
    static std::string_view selectALlQ = "SELECT * FROM water.user";
    static std::string_view insertQ = "INSERT INTO water.user (username, password_hash) \n" + "VALUES (?, ?);";
    static std::string_view updateQ = "UPDATE water.user SET username=?, password_hash=? WHERE id= ?;";
    static std::string_view deleteQ = "DELETE FROM water.user WHERE id= ?;";

    class PersistUser : public User {
    public:
        void setId(std::string_view id) override {
            User::setId(id);
        }
    }


    std::string_view getSelectQuery() {
        return selectQ;
    }


    std::string_view getSelectAllQuery() {
        return selectALlQ;
    }

    std::string_view getCreateQuery() {
        return insertQ;
    }


    std::string_view getUpdateQuery() {
        return updateQ;
    }

    std::string_view getDeleteQuery() {
        return deleteQ;
    }


    std::shared_ptr<User> create(){
            User user = new User();
            return std::make_shared<User>(persist(user));
    }


    MySqlUserDAO(DAOFactory <Connection> parentFactory, Connection connection) {
        super(parentFactory, connection);
    }

    @Override
protected

    List <User> parseResultSet(ResultSet rs)

    throws PersistException{
            LinkedList < User > result = new LinkedList<User>();
            try {
                while (rs.next()) {
                    MySqlUserDAO.PersistUser
                    user = new MySqlUserDAO.PersistUser();
                    user.setId(rs.getString("id"));
                    user.setUsername(rs.getString("username"));
                    user.setPasswordHash(rs.getString("password_hash"));
                    result.add(user);
                }
            } catch (Exception e) {
                throw new PersistException(e);
            }
            return result;
    }

    @Override
protected

    void prepareStatementForInsert(PreparedStatement statement, User object)

    throws PersistException{
            try {
                statement.setString(1, object.getUsername());
                statement.setString(2, object.getPasswordHash());
            } catch (Exception e) {
                throw new PersistException(e);
            }
    }

    @Override
protected

    void prepareStatementForUpdate(PreparedStatement statement, User object)

    throws PersistException{
            try {
                statement.setString(1, object.getUsername());
                statement.setString(2, object.getPasswordHash());
                statement.setString(3, object.getId());
            } catch (Exception e) {
                throw new PersistException(e);
            }
    }

public

    User getByUsername(String username)

    throws PersistException{
            List < User > list;
            String sql = getSelectQuery() + " WHERE username = ?";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, username);
                ResultSet rs = statement.executeQuery();
                list = parseResultSet(rs);
            } catch (Exception e) {
                throw new PersistException(e);
            }
            if (list == null || list.size() == 0) {
                return null;
            }
            if (list.size() > 1) {
                throw new PersistException("Received more than one record.");
            }
            return list.iterator().next();
    }
}


#endif //TASKHIVE_POSTGREUSERDAO_H
