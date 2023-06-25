//
// Created by daniil on 6/18/23.
//
#include "entity/Task.h"

std::string Task::getKey() const {
    return key;
}

void Task::setKey(std::string_view key) {
    Task::key = key;
}

std::string Task::getTitle() const {
    return title;
}

void Task::setTitle(std::string_view title) {
    Task::title = title;
}

std::string Task::getDescription() const {
    return description;
}

void Task::setDescription(std::string_view description) {
    Task::description = description;
}

bool Task::isCompleted() const {
    return completed;
}

void Task::setCompleted(bool completed) {
    Task::completed = completed;
}

const std::chrono::system_clock::time_point &Task::getStartDate() const {
    return startDate;
}

void Task::setStartDate(const std::chrono::system_clock::time_point &startDate) {
    Task::startDate = startDate;
}

const std::chrono::system_clock::time_point &Task::getDeadlineDate() const {
    return deadlineDate;
}

void Task::setDeadlineDate(const std::chrono::system_clock::time_point &deadlineDate) {
    Task::deadlineDate = deadlineDate;
}

Task::Task(std::string_view id, std::string_view key, std::string_view title, std::string_view description,
           const std::chrono::system_clock::time_point &startDate,
           const std::chrono::system_clock::time_point &deadlineDate, bool completed)
        : Entity(id), key(key), title(title), description(description), completed(completed), startDate(startDate),
          deadlineDate(deadlineDate) {}
