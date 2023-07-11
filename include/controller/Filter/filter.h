//
// Created by daniil on 7/10/23.
//

#ifndef TASKHIVE_FILTER_H
#define TASKHIVE_FILTER_H

#include <controller/controller.h>
#include <controller/Command/command.h>
#include <queue>
#include <controller/Filter/filterFactory.h>
#include <controller/dispatcher/dispatcher.h>
namespace controller {
    class FilterChain;

    class Filter {
    public:
        virtual void init() {}

        virtual void doFilter(std::shared_ptr<Request> request,
                              std::shared_ptr<Response> response, std::shared_ptr<FilterChain> filterChain) const = 0;

        virtual ~Filter() {}
    };


    class FilterChain : public std::enable_shared_from_this<FilterChain> {
    private:
        std::queue<std::string_view> chain;
        std::shared_ptr<Dispatcher> dispatcher;
    public:
        FilterChain(): dispatcher(std::make_shared<Dispatcher>()){}

        void addFilter(std::string_view filter) {
            chain.push(filter);
        }

        std::shared_ptr<Dispatcher> getDispatcher() const {
            return dispatcher;
        }

        void setDispatcher(std::shared_ptr<Dispatcher> dispatcher) {
            FilterChain::dispatcher = dispatcher;
        }

        virtual void doFilter(std::shared_ptr<Request> request,
                              std::shared_ptr<Response> response) {
            if (chain.empty()) {
                dispatcher->process(request, response);
                response->setCompleted(true);
            } else {
                auto filter = FilterFactory::getFilter(chain.front());
                chain.pop();
                filter->doFilter(request, response, shared_from_this());
            }
        }
    };

}


#endif //TASKHIVE_FILTER_H
