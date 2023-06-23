//
// Created by daniil on 6/23/23.
//

#ifndef TASKHIVE_GENERICDAO_H
#define TASKHIVE_GENERICDAO_H

#include <vector>
#include <string_view>
#include <memory>
#include "entity/identified.h"

template<typename T , typename PK> requires std::is_same<T, Identified<PK>>::value
class GenericDAO {
public:
    /** Creates a corresponding object */
    virtual std::unique_ptr<T> create() = 0;

    /** Creates a new record corresponding to the object */
    virtual std::unique_ptr<T> persist(T object) = 0;

    /** Returns the object corresponding to the record with the primary key 'key', or null */
    virtual std::unique_ptr<T> getByPrimaryKey(PK key) = 0;

    /** Saves the state of the object 'object' to the database */
    virtual void update(T object) = 0;

    /** Deletes the record of the object from the database */
    virtual void deleteObject(T object) = 0;

    /** Returns a list of objects corresponding to all records in the database */
    virtual std::vector<std::unique_ptr<T>> getAll() = 0;

    virtual ~GenericDAO() {}
};


#endif //TASKHIVE_GENERICDAO_H
