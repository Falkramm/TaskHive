//
// Created by daniil on 6/23/23.
//

#ifndef TASKHIVE_SERIALIZABLE_H
#define TASKHIVE_SERIALIZABLE_H


#include <string_view>
namespace Entity{
    class Serializable {
    public:
        static std::string_view getClass();
    };

    std::string_view Serializable::getClass() {
        return {};
    }
}

#endif //TASKHIVE_SERIALIZABLE_H
