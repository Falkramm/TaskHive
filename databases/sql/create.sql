create table customers(
    id serial primary key,
    login varchar(20) unique not null,
    password varchar(20)
);