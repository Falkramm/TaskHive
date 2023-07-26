-- Insert sample data into the customers table
INSERT INTO customers (login, password) VALUES
                                            ('user1', '1'),
                                            ('alice', 'password1'),
                                            ('bob', 'password2'),
                                            ('charlie', 'password3'),
                                            ('david', 'password4'),
                                            ('emma', 'password5'),
                                            ('frank', 'password6'),
                                            ('grace', 'password7'),
                                            ('harry', 'password8'),
                                            ('isabel', 'password9'),
                                            ('jacob', 'password10');

-- Insert sample data into the task table
INSERT INTO task (user_id, title, description, completed, startDate, deadlineDate) VALUES
                                                                                       -- User alice tasks
                                                                                       (1, 'Buy groceries', 'Milk, bread, and eggs', false, '2022-01-01 12:00:00', '2022-01-03 12:00:00'),
                                                                                       (1, 'Clean the house', 'Sweep and mop the floors', false, '2022-01-02 12:00:00', '2022-01-04 12:00:00'),
                                                                                       (1, 'Do laundry', 'Wash and fold the clothes', false, '2022-01-03 12:00:00', '2022-01-05 12:00:00'),
                                                                                       -- User bob tasks
                                                                                       (2, 'Finish project report', 'Write and edit the report', false, '2022-01-01 12:00:00', '2022-01-07 12:00:00'),
                                                                                       (2, 'Attend meeting', 'Discuss project progress with team', true, '2022-01-03 12:00:00', '2022-01-03 14:00:00'),
                                                                                       -- User charlie tasks
                                                                                       (3, 'Go for a run', 'Jog for 30 minutes', false, '2022-01-01 12:00:00', '2022-01-02 12:00:00'),
                                                                                       (3, 'Read a book', 'Finish chapter 4 of "War and Peace"', false, '2022-01-02 12:00:00', '2022-01-04 12:00:00'),
                                                                                       (3, 'Watch a movie', 'Watch "The Shawshank Redemption"', false, '2022-01-03 12:00:00', '2022-01-04 12:00:00'),
                                                                                       (3, 'Cook dinner', 'Make spaghetti and meatballs', false, '2022-01-04 12:00:00', '2022-01-04 18:00:00'),
                                                                                       -- User david tasks
                                                                                       (4, 'Buy a birthday gift', 'Find a gift for Sarah', false, '2022-01-01 12:00:00', '2022-01-06 12:00:00'),
                                                                                       (4, 'Call mom', 'Catch up with mom on the phone', false, '2022-01-02 12:00:00', '2022-01-02 14:00:00'),
                                                                                       (4, 'Go to the gym', 'Lift weights and run on the treadmill', false, '2022-01-03 12:00:00', '2022-01-03 14:00:00'),
                                                                                       (4, 'Clean the car', 'Wash and vacuum the car', false, '2022-01-04 12:00:00', '2022-01-04 16:00:00'),
                                                                                       -- User emma tasks
                                                                                       (5, 'Finish painting', 'Complete the landscape painting', false, '2022-01-01 12:00:00', '2022-01-07 12:00:00'),
                                                                                       (5, 'Update resume', 'Revise the work experience section', false, '2022-01-02 12:00:00', '2022-01-04 12:00:00'),
                                                                                       (5, 'Water the plants', 'Give the plants enough water', false, '2022-01-03 12:00:00', '2022-01-03 14:00:00'),
                                                                                       (5, 'Attend yoga class', 'Stretch and relax', false, '2022-01-04 12:00:00', '2022-01-04 14:00:00'),
                                                                                       -- User frank tasks
                                                                                       (6, 'Go on a hike', 'Hike to the top of the mountain', false, '2022-01-01 12:00:00', '2022-01-01 18:00:00'),
                                                                                       (6, 'Clean the garage', 'Organize and sweep the garage', false, '2022-01-02 12:00:00', '2022-01-02 14:00:00'),
                                                                                       -- User grace tasks
                                                                                       (7, 'Study for exam', 'Review notes and practice problems', false, '2022-01-01 12:00:00', '2022-01-04 12:00:00'),
                                                                                       (7, 'Attend study group', 'Collaborate with classmates on review', true, '2022-01-02 12:00:00', '2022-01-02 14:00:00'),
                                                                                       (7, 'Submit homework', 'Turn in completed homework', false, '2022-01-03 12:00:00', '2022-01-03 23:59:59'),
                                                                                       -- User harry tasks
                                                                                       (8, 'Plan vacation', 'Research and book flights and hotel', false, '2022-01-01 12:00:00', '2022-01-06 12:00:00'),
                                                                                       (8, 'Buy travel insurance', 'Purchase insurance for the trip', false, '2022-01-02 12:00:00', '2022-01-04 12:00:00'),
                                                                                       (8, 'Pack suitcase', 'Gather and organize items for the trip', false, '2022-01-05 12:00:00', '2022-01-05 18:00:00'),
                                                                                       -- User isabel tasks
                                                                                       (9, 'Attend doctor appointment', 'Get annual check-up', true, '2022-01-01 12:00:00', '2022-01-01 14:00:00'),
                                                                                       (9, 'Pay bills', 'Submit payments for utilities and rent', false, '2022-01-02 12:00:00', '2022-01-04 12:00:00'),
                                                                                       (9, 'Go to the grocery store', 'Buy groceries for the week', false, '2022-01-03 12:00:00', '2022-01-03 14:00:00'),
                                                                                       -- User jacob tasks
                                                                                       (10, 'Attend job interview', 'Meet with potential employer', false, '2022-01-01 12:00:00', '2022-01-01 14:00:00'),
                                                                                       (10, 'Send follow-up email', 'Thank interviewer and express continued interest', false, '2022-01-02 12:00:00', '2022-01-02 14:00:00'),
                                                                                       (10, 'Complete coding challenge', 'Write and test code for challenge', false, '2022-01-03 12:00:00', '2022-01-03 16:00:00'),
                                                                                       (10, 'Attend networking event', 'Meet and connect with professionals in the industry', false, '2022-01-04 12:00:00', '2022-01-04 14:00:00');