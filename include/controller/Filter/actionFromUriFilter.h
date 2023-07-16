//
// Created by daniil on 7/10/23.
//

#ifndef TASKHIVE_ACTIONFROMURIFILTER_H
#define TASKHIVE_ACTIONFROMURIFILTER_H
#include <controller/Filter/filter.h>
#include <controller/Action/action.h>
namespace controller {
    class ActionFromUriFilter: public Filter{
    private:
        static std::unordered_map<std::string_view, std::shared_ptr<ActionCreator>> actions;//TODO need to init
    public:
        void init() override {
            Filter::init();
        }

        void doFilter(std::shared_ptr<Request> request, std::shared_ptr<Response> response,
                      std::shared_ptr<FilterChain> filterChain) const override {
            std::string actionName = request->target().to_string();
            try{
                auto creator = actions.at(actionName);
                request->setAction(creator->create());
            }catch(...){
                auto creator = actions.at("errorAction");//TODO need to Error Action
                request->setAction(creator->create());
                //TODO log that
            }
            filterChain->doFilter(request, response);
        }

        ~ActionFromUriFilter() override {

        }
    };
}


#endif //TASKHIVE_ACTIONFROMURIFILTER_H
