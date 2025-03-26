#ifndef TABSDLL_H
#define TABSDLL_H

#include <string>
#include "DynPageStack.h"
#include <iostream>
using namespace std;

class TabsDLL {
private:
    // Node structure representing each tab
    struct TabNode {
        int tab_id;
        DynPageStack page_stack;
        int count_of_open_pages;
        TabNode* next;
        TabNode* prev;

        // Constructor: initializes a new tab with one page.
        TabNode(int id, const string& page)
            : tab_id(id), count_of_open_pages(1), next(nullptr), prev(nullptr) {
            page_stack.push(page);
        }
    };

    TabNode* head;
    TabNode* tail;

    // Helper functions

    // try to find the node with the given tab_id; returns nullptr if not found.
    TabNode* findNode(int tab_id);

    // removing a node from the doubly linked list (w/o deleting the node).
    void removeNode(TabNode* node);

    // Inserts a node into the list so that the list is sorted in ascending order
    // by count_of_open_pages; if equal, then by ascending tab_id.
    void insertSorted(TabNode* node);

    // Repositions a node after its page count has changed.
    void repositionNode(TabNode* node);

public:
    TabsDLL();
    ~TabsDLL();

    // Checks if a tab with the given tab_id exists.
    bool tabExists(int tab_id);

    // creating a new tab with the specified tab_id and initial page.
    std::string newTab(int tab_id, std::string page);

    // Updates an existing tab by adding a new page.
    std::string update(int tab_id, std::string page);

    // Navigates back in the specified tab ( removes the top page)
    void backTab(int tab_id);

    // Closes the specified tab and removes all its pages.
    void closeTab(int tab_id);

    // displaying all tabs from head to tail and from tail to head.
    void display();

    // Closes all tabs (from head to tail) and displays the removed pages.
    void quitAndDisplay();
};

#endif
