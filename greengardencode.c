CREATE DATABASE GreenGarden7_Unique;
USE GreenGarden7_Unique;

CREATE TABLE Branches (
    branch_id INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(100),
    location VARCHAR(150)
);

CREATE TABLE Floors (
    floor_id INT PRIMARY KEY AUTO_INCREMENT,
    branch_id INT,
    floor_number INT,
    purpose ENUM('food_service', 'event_space'),
    FOREIGN KEY (branch_id) REFERENCES Branches(branch_id)
);

CREATE TABLE Customers (
    customer_id INT PRIMARY KEY AUTO_INCREMENT,
    customer_name VARCHAR(100),
    customer_email VARCHAR(100) UNIQUE,
    customer_phone VARCHAR(15),
    customer_password VARCHAR(100),
    customer_type ENUM('student', 'teacher', 'employee', 'admin')
);

CREATE TABLE Meal_Types (
    meal_type_id INT PRIMARY KEY AUTO_INCREMENT,
    meal_type_name VARCHAR(50)
);

CREATE TABLE Menu_Items (
    menu_item_id INT PRIMARY KEY AUTO_INCREMENT,
    menu_item_name VARCHAR(100),
    menu_item_price DECIMAL(6,2),
    prep_duration INT,
    menu_item_status ENUM('available', 'unavailable', 'discontinued'),
    meal_type_id INT,
    FOREIGN KEY (meal_type_id) REFERENCES Meal_Types(meal_type_id)
);

CREATE TABLE Customers_Orders (
    customer_order_id INT PRIMARY KEY AUTO_INCREMENT,
    customer_id INT,
    branch_id INT,
    order_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    total_amount DECIMAL(7,2),
    payment_method ENUM('cash', 'onecard'),
    order_status ENUM('pending', 'preparing', 'ready', 'delivered', 'canceled'),
    FOREIGN KEY (customer_id) REFERENCES Customers(customer_id),
    FOREIGN KEY (branch_id) REFERENCES Branches(branch_id)
);

CREATE TABLE Order_Details (
    order_detail_id INT PRIMARY KEY AUTO_INCREMENT,
    customer_order_id INT,
    menu_item_id INT,
    quantity INT,
    FOREIGN KEY (customer_order_id) REFERENCES Customers_Orders(customer_order_id),
    FOREIGN KEY (menu_item_id) REFERENCES Menu_Items(menu_item_id)
);

CREATE TABLE Customers_Logins (
    login_id INT PRIMARY KEY AUTO_INCREMENT,
    customer_id INT,
    login_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (customer_id) REFERENCES Customers(customer_id)
);

CREATE TABLE Meal_Combos (
    meal_combo_id INT PRIMARY KEY AUTO_INCREMENT,
    meal_combo_name VARCHAR(100),
    meal_combo_price DECIMAL(6,2)
);

CREATE TABLE Combo_Items (
    meal_combo_id INT,
    menu_item_id INT,
    PRIMARY KEY (meal_combo_id, menu_item_id),
    FOREIGN KEY (meal_combo_id) REFERENCES Meal_Combos(meal_combo_id),
    FOREIGN KEY (menu_item_id) REFERENCES Menu_Items(menu_item_id)
);

CREATE TABLE EventBookings (
    booking_id INT PRIMARY KEY AUTO_INCREMENT,
    customer_id INT,
    floor_id INT,
    branch_id INT,
    event_name VARCHAR(100),
    event_date DATE,
    start_time TIME,
    end_time TIME,
    amount_paid DECIMAL(7,2),
    payment_method ENUM('cash', 'onecard'),
    FOREIGN KEY (customer_id) REFERENCES Customers(customer_id),
    FOREIGN KEY (floor_id) REFERENCES Floors(floor_id),
    FOREIGN KEY (branch_id) REFERENCES Branches(branch_id)
);

INSERT INTO Branches (name, location) VALUES
('Green Garden Main Campus', 'Daffodil International University'),
('Green Garden 2', 'Dhanmondi, Dhaka');

INSERT INTO Floors (branch_id, floor_number, purpose) VALUES
(1, 1, 'food_service'), (1, 2, 'event_space'), (1, 3, 'event_space'),
(2, 1, 'food_service'), (2, 2, 'event_space'), (2, 3, 'event_space');

INSERT INTO Customers (customer_name, customer_email, customer_phone, customer_password, customer_type) VALUES
('Aovinondon', 'Aovinondon@example.com', '1234567890', 'pass123', 'student'),
('Sajjad', 'sajjad@example.com', '2345678901', 'pass456', 'employee'),
('Meherab', 'meherab@example.com', '3456789012', 'adminpass', 'admin'),
('Nuhash', 'Nuhash@example.com', '4567890123', 'emilypass', 'teacher'),
('Sadia', 'sadia@example.com', '5678901234', 'davidpass', 'employee');
INSERT INTO Meal_Types (meal_type_name) VALUES
('Snacks'), ('Meals'), ('Drinks'), ('Desserts'), ('Specials');
INSERT INTO Menu_Items (menu_item_name, menu_item_price, prep_duration, menu_item_status, meal_type_id) VALUES
('Porota', 120.00, 10, 'available', 1),
('Dal Sobji', 150.00, 12, 'available', 2),
('Khicuri', 80.00, 5, 'available', 3),
('Chicken', 90.00, 7, 'available', 4),
('Plain Rice', 250.00, 20, 'available', 5),
('Mix Vegetables', 250.00, 20, 'available', 2),
('Egg Fry', 250.00, 20, 'available', 5);

INSERT INTO Customers_Orders (customer_id, branch_id, total_amount, payment_method, order_status) VALUES
(1, 1, 270.00, 'onecard', 'delivered'),
(4, 2, 90.00, 'cash', 'delivered'),
(1, 1, 230.00, 'onecard', 'preparing'),
(5, 2, 150.00, 'onecard', 'pending'),
(2, 1, 330.00, 'cash', 'delivered');

INSERT INTO Order_Details (customer_order_id, menu_item_id, quantity) VALUES
(1, 1, 1), (1, 2, 1), (1, 3, 1),
(2, 4, 1),
(3, 2, 1), (3, 5, 1),
(4, 2, 1),
(5, 1, 2), (5, 3, 1);

INSERT INTO Customers_Logins (customer_id) VALUES (1), (2), (3), (4), (5);

INSERT INTO Meal_Combos (meal_combo_name, meal_combo_price) VALUES
('Breakfast Combo', 200.00), ('Lunch Combo', 250.00), ('Dessert Combo', 180.00);

INSERT INTO Combo_Items (meal_combo_id, menu_item_id) VALUES
(1, 1), (1, 3), (2, 2), (2, 5), (3, 4);

INSERT INTO EventBookings (customer_id, floor_id, branch_id, event_name, event_date, start_time, end_time, amount_paid, payment_method) VALUES
(4, 2, 1, 'Science Club Meet', '2025-04-10', '10:00:00', '12:00:00', 500.00, 'cash'),
(1, 5, 2, 'Drama Rehearsal', '2025-04-11', '14:00:00', '17:00:00', 600.00, 'onecard');

SELECT
    co.customer_order_id,
    cu.customer_name,
    mi.menu_item_name,
    od.quantity,
    co.total_amount,
    b.name AS branch_name
FROM Customers_Orders co
JOIN Order_Details od ON co.customer_order_id = od.customer_order_id
JOIN Menu_Items mi ON od.menu_item_id = mi.menu_item_id
JOIN Customers cu ON co.customer_id = cu.customer_id
JOIN Branches b ON co.branch_id = b.branch_id
ORDER BY co.customer_order_id, mi.menu_item_name;

SELECT COUNT(*) AS total_orders FROM Customers_Orders;

SELECT SUM(total_amount) AS total_food_earnings FROM Customers_Orders;
SELECT SUM(amount_paid) AS total_event_earnings FROM EventBookings;

SELECT mt.meal_type_name, COUNT(mi.menu_item_id) AS total_items
FROM Meal_Types mt
LEFT JOIN Menu_Items mi ON mt.meal_type_id = mi.meal_type_id
GROUP BY mt.meal_type_name;
