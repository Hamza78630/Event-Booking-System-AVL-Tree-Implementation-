# Self-Balancing Event Scheduler

I developed this project during my 4th semester to explore the practical applications of Data Structures and Algorithms (DSA). The goal was to build a system that doesn't just store data, but organizes it efficiently to solve real-world problems like scheduling conflicts.

## What it is
It’s a console-based application that allows users to book events and manage recurring schedules (daily or weekly). The standout feature is the "Conflict Detector"—if you try to book a time that is already taken, the system uses a recursive search to find and suggest the next available 30-minute slot.

## Why I built it this way (The DSA Choice)
For the core engine, I chose an **AVL Tree** (a self-balancing binary search tree). 
* **Efficiency:** Unlike a standard Binary Search Tree that can become "unbalanced," the AVL tree automatically rearranges itself using rotations. This ensures that even with a massive schedule, searching for a specific time always happens in O(log n) time.
* **Rotations:** I implemented the Left-Left, Right-Right, Left-Right, and Right-Left rotations manually to maintain the tree's balance factor after every insertion.



## Technical Highlights
* **Self-Balancing Logic:** Automatic height updates and balance factor checks to trigger rotations.
* **Recurring Event Engine:** Used a Linked List structure to handle sequences of events, validating each one against the AVL tree before adding them to the schedule.
* **Custom Date Handling:** I built an `EventDate` class from scratch to handle leap years, month-end rollovers, and chronological comparisons.
* **Memory Management:** Focused on using pointers and dynamic memory allocation for tree nodes and list elements.

## How to run
1. Download the `main.cpp` file.
2. Open your terminal in that folder.
3. Compile it: `g++ main.cpp -o scheduler`
4. Run it: `./scheduler`
