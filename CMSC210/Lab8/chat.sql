DROP TABLE IF EXISTS messages;
CREATE TABLE messages(id INTEGER PRIMARY KEY, username TEXT, topic TEXT, message TEXT);
INSERT INTO messages(username, topic, message) VALUES ('System Administrator', 'Welcome', 'Welcome to the chat system.');
