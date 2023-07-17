//
// Created by daniil on 6/23/23.
//

#ifndef TASKHIVE_IDENTIFIED_H
#define TASKHIVE_IDENTIFIED_H
namespace Entity{
    template<typename PK>
    class Identified {
    public:
    /** Возвращает идентификатор объекта */
        virtual PK getId() const = 0;
    };
}

#endif //TASKHIVE_IDENTIFIED_H
