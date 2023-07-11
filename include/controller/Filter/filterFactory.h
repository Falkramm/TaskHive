//
// Created by daniil on 7/10/23.
//

#ifndef TASKHIVE_FILTERFACTORY_H
#define TASKHIVE_FILTERFACTORY_H
#include <controller/Filter/filter.h>
namespace controller{
    class FilterFactory {

    public:
        static std::shared_ptr<Filter> getFilter(std::string_view) {
            return nullptr;//TODO
        }
    };
}


#endif //TASKHIVE_FILTERFACTORY_H
