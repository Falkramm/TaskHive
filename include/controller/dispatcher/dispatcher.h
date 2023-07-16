//
// Created by daniil on 7/10/23.
//

#ifndef TASKHIVE_DISPATCHER_H
#define TASKHIVE_DISPATCHER_H

#include <controller/controller.h>
#include <controller/Filter/filter.h>
#include <controller/Action/actionManager.h>

namespace controller {
    class Dispatcher {
    public:
        std::shared_ptr<ServiceFactory> getFactory() {
            return std::make_shared<ServiceFactory>();
        }

        virtual void process(std::shared_ptr<Request> request,
                             std::shared_ptr<Response> response) {
            std::shared_ptr<Action> action = request->getAction();
            std::shared_ptr<ActionManager> actionManager = nullptr;
            try {
//                HttpSession session = request.getSession();
//                if (session != null) {
//                    @SuppressWarnings("unchecked")
//                    Map<String, Object> attributes = (Map<String, Object>) session.getAttribute("redirectedData");
//                    if (attributes != null) {
//                        for (String key : attributes.keySet()) {
//                            request.setAttribute(key, attributes.get(key));
//                        }
//                        session.removeAttribute("redirectedData");
//                    }
//                }
                actionManager = ActionManagerFactory::getManager(getFactory());
                actionManager->execute(action, request, response);

            } catch (PersistException e) {
//                logger.error("It is impossible to process request", e);
                request->set("error", "Ошибка обработки данных");
                response.reset();
                //SenderManager.sendObject(response, e);TODO
            }
            if (actionManager != nullptr) {
                try {
                    actionManager->close();
                } catch (pqxx::sql_error e) {
                    throw std::runtime_error(e);
                }
            }
        }
    };
}


#endif //TASKHIVE_DISPATCHER_H
