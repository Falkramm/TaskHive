//
// Created by daniil on 6/26/23.
//
#include <gtest/gtest.h>
#include <dao/postgres/factory.h>
#include <dao/postgres/postgresUserDAO.h>
// A simple test case
std::shared_ptr<PostgresUserDAO> dao;
PostgresDAOFactory factory;
void init(){
    std::cout << "Start Testing" << std::endl;
    ConnectionPool::getInstance()->init();//TODO test init setup
    dao = boost::any_cast<std::shared_ptr<PostgresUserDAO>>(factory.getDao(typeid(User).name()));
}
void destroy(){

    factory.close();
    ConnectionPool::getInstance()->destroy();
}

//class PostgresUserDAOTest: public ::testing::TestWithParam<User> {};
//INSTANTIATE_TEST_SUITE_P(UserTestData, PostgresUserDAOTest, ::testing::Values(
//        User("user2", "password2"),
//        User("user3", "password3"),
//        User("user4", "password4"),
//        User("user5", "password5")
//        ));
TEST(PostgresUserDAOTest, PersistTest) {
    std::shared_ptr<User> user = std::make_shared<User>("login", "password");
    auto PersistUser= dao->persist(user);
    EXPECT_EQ(user->getLogin(), PersistUser->getLogin());
    EXPECT_EQ(user->getPassword(), PersistUser->getPassword());
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    init();
    int result = RUN_ALL_TESTS();
    destroy();
    return result;
}