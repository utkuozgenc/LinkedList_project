# CS204 Homework 3 - Web Browser Simulation

This project is an implementation of a web browser simulation using doubly linked lists and dynamic stacks, created as part of the **CS204 Advanced Programming** course at Sabancı University (Spring 2025). The program simulates a web browser that manages multiple tabs, where each tab contains a history of visited web pages managed by a stack.

## Project Overview

The project consists of the following key components:

- **HW3main.cpp**  
  This file contains the main function, which handles user interaction. It reads commands from a file (e.g., "01.txt", "02.txt", etc.) and calls various functions of the `TabsDLL` class to simulate browser actions like opening pages, navigating back, closing tabs, displaying current tabs, and quitting the browser.

- **DynPageStack.h** and **DynPageStack.cpp**  
  These files implement a simple dynamic stack for storing web page URLs. Each tab uses an instance of `DynPageStack` to manage its pages in a stack (LIFO) fashion. The stack provides basic operations such as push, pop, and checking if it is empty.

- **TabsDLL.h** and **TabsDLL.cpp**  
  These files contain the implementation of the `TabsDLL` class. This class is responsible for managing the tabs in the browser. Each tab is represented by a node in a doubly linked list that holds:
  - A unique tab ID.
  - A dynamic page stack (`DynPageStack`) to store the pages visited in that tab.
  - A count of open pages.

  The tabs are maintained in sorted order, based on the number of pages open (and by tab ID when counts are equal). The class includes public member functions that are called by the main program:
  - `tabExists(int tab_id)`
  - `newTab(int tab_id, string page)`
  - `update(int tab_id, string page)`
  - `backTab(int tab_id)`
  - `closeTab(int tab_id)`
  - `display()`
  - `quitAndDisplay()`

  These functions manage the browser’s operations, including error handling, maintaining the correct order of tabs, and proper memory management.

## Features

- **Simulated Browser Tabs:**  
  Each tab holds a history of web pages, allowing for operations like going back (removing the latest page) and closing a tab.

- **Dynamic Memory Management:**  
  The program uses dynamic memory allocation for both the stack and the doubly linked list. It ensures that all memory is properly freed upon closing tabs or quitting the program.

- **Sorted Order of Tabs:**  
  Tabs are always maintained in ascending order based on the number of pages open. If two tabs have the same number of pages, they are further sorted by their tab ID
