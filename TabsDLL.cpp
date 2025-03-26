#include "TabsDLL.h"

// Constructor
TabsDLL::TabsDLL() : head(nullptr), tail(nullptr) {}

// Destructor
TabsDLL::~TabsDLL() {
    TabNode* current = head;
    while (current != nullptr) {
        TabNode* next = current->next;
        string dummy;
        // Empty the page stack.
        while (!current->page_stack.isEmpty()) {
            current->page_stack.pop(dummy);
        }
        delete current;
        current = next;
    }
}

// Helper finds node using tab_id
TabsDLL::TabNode* TabsDLL::findNode(int tab_id) {
    TabNode* current = head;
    while (current != nullptr) {
        if (current->tab_id == tab_id) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

bool TabsDLL::tabExists(int tab_id) {
    return (findNode(tab_id) != nullptr);
}

// Helper: removes node from list
void TabsDLL::removeNode(TabNode* node) {
    if (node == nullptr) {
        return;
    }
    if (node == head && node == tail) {
        head = nullptr;
        tail = nullptr;
    } else if (node == head) {
        head = node->next;
        if (head != nullptr) {
            head->prev = nullptr;
        }
    } else if (node == tail) {
        tail = node->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        }
    } else {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    node->next = nullptr;
    node->prev = nullptr;
}

// Helper: insert a node into the list sorted by count_of_open_pages and tab_id
void TabsDLL::insertSorted(TabNode* node) {
    if (head == nullptr) { // Empty list.
        head = node;
        tail = node;
        return;
    }
    // Insert before head if needed.
    if ((node->count_of_open_pages < head->count_of_open_pages) ||
        (node->count_of_open_pages == head->count_of_open_pages && node->tab_id < head->tab_id)) {
        node->next = head;
        head->prev = node;
        head = node;
        return;
    }
    TabNode* current = head;
    // iterating until found
    while (current->next != nullptr &&
           ((node->count_of_open_pages > current->next->count_of_open_pages) ||
           (node->count_of_open_pages == current->next->count_of_open_pages && node->tab_id >= current->next->tab_id))) {
        current = current->next;
    }
    node->next = current->next;
    node->prev = current;
    current->next = node;
    if (node->next != nullptr) {
        node->next->prev = node;
    } else {
        tail = node;
    }
}

// Helper: reposition a node (remove and then reinsert it in sorted order
void TabsDLL::repositionNode(TabNode* node) {
    if (node == nullptr) {
        return;
    }
    removeNode(node);
    insertSorted(node);
}

// creating a new tab with the given tab_id and page
std::string TabsDLL::newTab(int tab_id, std::string page) {
    TabNode* new_node = new TabNode(tab_id, page);
    insertSorted(new_node);
    return page;
}

// updating an existing tab by pushing a new page and increasing the page count
std::string TabsDLL::update(int tab_id, std::string page) {
    TabNode* node = findNode(tab_id);
    if (node == nullptr) {
        return "";
    }
    node->page_stack.push(page);
    node->count_of_open_pages++;
    repositionNode(node);
    return page;
}

// Navigating back in a tab: removes the top page
void TabsDLL::backTab(int tab_id) {
    TabNode* node = findNode(tab_id);
    if (node == nullptr) {
        cout << "Error: Tab " << tab_id << " not found." << endl;
        return;
    }
    cout << "Removing from tab with ID: " << tab_id << endl;
    string removedPage;
    bool popped = node->page_stack.pop(removedPage);
    if (popped) {
        node->count_of_open_pages--;
        if (node->count_of_open_pages == 0) {
            cout << "Removed page: " << removedPage << ". Stack is now empty. Deleting tab." << endl;
            removeNode(node);
            delete node;
        } else {
            cout << "Removed page: " << removedPage << ". Remaining number of pages: " << node->count_of_open_pages << endl;
            repositionNode(node);
        }
    }
}

// closing a specific tab and removes all its pages
void TabsDLL::closeTab(int tab_id) {
    TabNode* node = findNode(tab_id);
    if (node == nullptr) {
        cout << "Error: Tab " << tab_id << " not found." << endl;
        return;
    }
    cout << "Closing tab " << tab_id << " and removing all pages:" << endl;
    string removedPage;
    // Pop all pages until the stack is empty.
    while (!(node->page_stack.isEmpty())) {
        bool popped = node->page_stack.pop(removedPage);
        if (popped) {
            cout << "Removed page: " << removedPage << endl;
        }
    }
    removeNode(node);
    delete node;
}

// displaying all tabs in both forward (head to tail) and backward order
void TabsDLL::display() {
    cout << "Displaying tabs from head to tail:" << endl;
    TabNode* current = head;
    while (current != nullptr) {
        cout << "Tab " << current->tab_id << " has " << current->count_of_open_pages << " pages open." << endl;
        current = current->next;
    }
    cout << "Displaying tabs from tail to head:" << endl;
    current = tail;
    while (current != nullptr) {
        cout << "Tab " << current->tab_id << " has " << current->count_of_open_pages << " pages open." << endl;
        current = current->prev;
    }
}

// closing all tabs, removing their pages one by one.
void TabsDLL::quitAndDisplay() {
    cout << "Closing all tabs:" << endl;
    // Always remove the head until the list is empty.
    while (head != nullptr) {
        TabNode* node = head;
        cout << "Closing tab " << node->tab_id << " and removing all pages:" << endl;
        string removedPage;
        while (!(node->page_stack.isEmpty())) {
            bool popped = node->page_stack.pop(removedPage);
            if (popped) {
                cout << "Removed page: " << removedPage << endl;
            }
        }
        removeNode(node);
        delete node;
    }
}
