User Management System

Overview

This project is a simple user management system implemented in C. It allows users to register, manage their profiles, add friends, and create posts. The system supports operations such as adding and removing friends, posting and deleting posts, and displaying user details.

Features

User Registration: Add new users with a username and password.

Find Users: Search for a specific user in the database.

Friend Management:

Add friends to a user’s list.

Remove friends from a user’s list.

Display a user’s friends.

Post Management:

Create and add posts.

Delete posts.

Display posts of a user.

Menu System: A structured menu for interacting with the system.

CSV User Loading: Reads user data from a CSV file and initializes users with their posts and friends.

Memory Cleanup: Properly frees allocated memory to prevent memory leaks.

File Structure

a2_functions-2.c - Contains function implementations for managing users, posts, and friends.

a2_nodes.h - Header file defining data structures (not provided in this repository but required for compilation).

a2_functions.h - Header file containing function prototypes (not provided in this repository but required for compilation).

Compilation & Execution

To compile the program, use:

gcc -o user_management a2_functions-2.c -Wall -Wextra

Run the program:

./user_management

How to Use

Run the program and select an option from the menu.

Follow the prompts to register users, add friends, create posts, etc.

The program maintains a linked list structure to store user data dynamically.

Dependencies

Standard C libraries: stdlib.h, stdio.h, string.h, stdbool.h, assert.h, time.h

