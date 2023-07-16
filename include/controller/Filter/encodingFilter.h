//
// Created by daniil on 7/10/23.
//

#ifndef TASKHIVE_ENCODINGFILTER_H
#define TASKHIVE_ENCODINGFILTER_H
#include <controller/Filter/filter.h>
namespace controller {
    class EncodingFilter : Filter {
        void init() override {
            Filter::init();
        }

        void doFilter(std::shared_ptr<Request> request, std::shared_ptr<Response> response,
                      std::shared_ptr<FilterChain> filterChain) const override {
            request->set(http::field::content_type, "application/json; charset=UTF-8");
            filterChain->doFilter(request, response);
        }

        ~EncodingFilter() override {

        }
    };
}

#endif //TASKHIVE_ENCODINGFILTER_H
