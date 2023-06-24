//
// Created by daniil on 6/23/23.
//

#ifndef TASKHIVE_GENERICDAO_H
#define TASKHIVE_GENERICDAO_H
#include <boost/type_index.hpp>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <memory>
#include <entity/identified.h>

template<typename T, typename PK>
concept DerivedFromIdentified = std::derived_from<T, Identified<PK>>;

template<typename T, typename PK> requires DerivedFromIdentified<T, PK>
class GenericDAO {
public:
    virtual ~GenericDAO() = default;

    /** Creates a new instance of the corresponding object */
    virtual std::unique_ptr<T> create() = 0;

    /** Creates a new record in the database that corresponds to the given object */
    virtual std::unique_ptr<T> persist(const T& object) = 0;

    /** Retrieves the object corresponding to the record with the given primary key */
    virtual std::unique_ptr<T> getByPrimaryKey(const PK& key) = 0;

    /** Updates the state of the given object in the database */
    virtual void update(const T& object) = 0;

    /** Deletes the record corresponding to the given object from the database */
    virtual void remove(const T& object) = 0;

    /** Retrieves all objects corresponding to all records in the database */
    virtual std::vector<std::unique_ptr<T>> getAll() = 0;
};


#endif //TASKHIVE_GENERICDAO_H
