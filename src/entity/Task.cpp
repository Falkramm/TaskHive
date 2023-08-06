//
// Created by daniil on 6/18/23.
//
#include <iomanip>
#include <entity/Task.h>

namespace Entity {
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

    bool Task::operator==(const Task &rhs) const {
        return static_cast<const Entity &>(*this) == static_cast<const Entity &>(rhs) &&
               key == rhs.key &&
               title == rhs.title &&
               description == rhs.description &&
               completed == rhs.completed &&
               startDate == rhs.startDate &&
               deadlineDate == rhs.deadlineDate;
    }

    bool Task::operator!=(const Task &rhs) const {
        return !(rhs == *this);
    }

    std::ostream &operator<<(std::ostream &os, const Task &task) {
        os << static_cast<const Entity &>(task) << " key: " << task.key << " title: " << task.title << " description: "
           << task.description << " completed: " << task.completed << " startDate: " <<
           boost::posix_time::to_simple_string(
                   boost::posix_time::from_time_t(std::chrono::system_clock::to_time_t(task.startDate)))
           << " deadlineDate: "
           << boost::posix_time::to_simple_string(
                   boost::posix_time::from_time_t(std::chrono::system_clock::to_time_t(task.deadlineDate)));
        return os;
    }

    std::string Task::timeToString(const std::chrono::system_clock::time_point &point) {
        auto time_t = std::chrono::system_clock::to_time_t(point);
        std::stringstream ss;
        ss << std::put_time(std::gmtime(&time_t), "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }

    std::chrono::system_clock::time_point Task::stringToTime(const std::string& str) {
        std::tm tm = {};
        double fractional_seconds = 0.0;
        std::istringstream ss(str);
        ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
        ss >> fractional_seconds;

        std::time_t time_t = timegm(&tm);  // Используем timegm для преобразования в UTC
        std::chrono::system_clock::time_point point = std::chrono::system_clock::from_time_t(time_t);
        std::chrono::duration<double> duration(fractional_seconds);
        point += std::chrono::duration_cast<std::chrono::system_clock::duration>(duration);
        return point;
    }
}
