//
// Created by daniil on 6/18/23.
//

#ifndef TASKHIVE_TASK_H
#define TASKHIVE_TASK_H

#include "entity/Entity.h"
#include <chrono>
#include <ostream>
#include <boost/date_time/posix_time/posix_time.hpp>
class Task : public Entity {
public:
    [[nodiscard]] std::string getKey() const;

    void setKey(std::string_view key);

    [[nodiscard]] std::string getTitle() const;

    void setTitle(std::string_view title);

    [[nodiscard]] std::string getDescription() const;

    void setDescription(std::string_view description);

    [[nodiscard]] bool isCompleted() const;

    void setCompleted(bool completed);

    [[nodiscard]] const std::chrono::system_clock::time_point &getStartDate() const;

    void setStartDate(const std::chrono::system_clock::time_point &startDate);

    [[nodiscard]] const std::chrono::system_clock::time_point &getDeadlineDate() const;

    bool operator==(const Task &rhs) const;

    bool operator!=(const Task &rhs) const;


    void setDeadlineDate(const std::chrono::system_clock::time_point &deadlineDate);

    Task() = default;

private:
    std::string key;//TODO not user id but user login
    std::string title;
    std::string description;
    bool completed;
    std::chrono::system_clock::time_point startDate;
    std::chrono::system_clock::time_point deadlineDate;
public:
    Task(std::string_view id, std::string_view key, std::string_view title, std::string_view description,
         const std::chrono::system_clock::time_point &startDate = std::chrono::system_clock::now(),
         const std::chrono::system_clock::time_point &deadlineDate = std::chrono::system_clock::now(),
         bool completed = false);//TODO make NEVER DATE
    friend std::ostream &operator<<(std::ostream &os, const Task &task);
};


#endif //TASKHIVE_TASK_H
