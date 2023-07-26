-- Create the customers table
CREATE TABLE customers (
                           id SERIAL PRIMARY KEY,
                           login VARCHAR(20) UNIQUE NOT NULL,
                           password VARCHAR(20)
);

-- Create the task table with a foreign key constraint on user_id
CREATE TABLE task (
                      id SERIAL PRIMARY KEY,
                      user_id SERIA NOT NULL REFERENCES customers(id) ON DELETE CASCADE,
                      title TEXT NOT NULL,
                      description TEXT,
                      completed BOOLEAN NOT NULL DEFAULT FALSE,
                      startDate TIMESTAMPTZ,
                      deadlineDate TIMESTAMPTZ
);