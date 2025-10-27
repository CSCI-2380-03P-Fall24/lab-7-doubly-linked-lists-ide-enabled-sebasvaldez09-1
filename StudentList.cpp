// StudentList.cpp
#include "StudentList.h"
#include <iostream>
using namespace std;

// Define a constructor to initialize the list. The list starts with no Students
StudentList::StudentList() {
    head = nullptr;
    tail = nullptr;
    numStudents = 0;
}

// return the number of students currently in the list
int StudentList::listSize() {
    return numStudents;
}

// add a Node with a student to the front (head) of the list.
void StudentList::addFront(Student s) {
    Node* newNode = new Node(s, head, nullptr);
    if (head != nullptr) head->prev = newNode;
    head = newNode;
    if (tail == nullptr) tail = newNode;
    numStudents++;
}

// add a Node with a student to the back (tail) of the list.
void StudentList::addBack(Student s) {
    Node* newNode = new Node(s, nullptr, tail);
    if (tail != nullptr) tail->next = newNode;
    tail = newNode;
    if (head == nullptr) head = newNode;
    numStudents++;
}

// Print out the names of each student in the list.
void StudentList::printList() {
    Node* cur = head;
    while (cur != nullptr) {
        cout << cur->data.name << endl;
        cur = cur->next;
    }
}

// Remove the Node with the student at the front (head) of the list
// should not fail if list is empty! Print an error message if this occurs
void StudentList::popFront() {
    if (head == nullptr) {
        cout << "List is empty!" << endl;
        return;
    }
    Node* del = head;
    head = head->next;
    if (head != nullptr) head->prev = nullptr;
    else tail = nullptr; // list became empty
    delete del;
    numStudents--;
}

// Remove the Node with the student at the back (tail) of the list
// should not fail if list is empty! Print an error message if this occurs
void StudentList::popBack() {
    if (tail == nullptr) {
        cout << "List is empty!" << endl;
        return;
    }
    Node* del = tail;
    tail = tail->prev;
    if (tail != nullptr) tail->next = nullptr;
    else head = nullptr; // list became empty
    delete del;
    numStudents--;
}

// insert a student at the position "index" (head is index 0).
// if index is outside of current list range, print a message and insert at back
void StudentList::insertStudent(Student s, int index) {
    if (index <= 0) {
        addFront(s);
        return;
    }
    if (index >= numStudents) {
        cout << "Index out of range. Inserting at back." << endl;
        addBack(s);
        return;
    }

    // walk to the node currently at 'index'
    Node* cur = head;
    for (int i = 0; i < index; ++i) cur = cur->next;

    Node* n = new Node(s, cur, cur->prev);
    if (cur->prev) cur->prev->next = n;
    cur->prev = n;
    if (cur == head) head = n; // (this won't actually happen because index>0)
    numStudents++;
}

// find the student with the given id number and return them
// if no student matches, print a message and return a dummy student
Student StudentList::retrieveStudent(int idnumber) {
    Node* cur = head;
    while (cur != nullptr) {
        if (cur->data.id == idnumber) return cur->data;
        cur = cur->next;
    }
    cout << "Student not found!" << endl;
    return Student(); // defaults: "nobody", -1, 0.0
}

// Remove a Node with a student from the list with a given id number
// If no student matches, print a message and do nothing
void StudentList::removeStudentById(int idnumber) {
    Node* cur = head;
    while (cur != nullptr) {
        if (cur->data.id == idnumber) {
            if (cur->prev) cur->prev->next = cur->next;
            else head = cur->next;

            if (cur->next) cur->next->prev = cur->prev;
            else tail = cur->prev;

            delete cur;
            numStudents--;
            return;
        }
        cur = cur->next;
    }
    cout << "Student not found!" << endl;
}

// Change the GPA of the student with given id number to newGPA
void StudentList::updateGPA(int idnumber, float newGPA) {
    Node* cur = head;
    while (cur != nullptr) {
        if (cur->data.id == idnumber) {
            cur->data.GPA = newGPA; // NOTE: capital GPA per student.t
            return;
        }
        cur = cur->next;
    }
    cout << "Student not found!" << endl;
}

// Add all students from otherlist to this list.
// otherlist should be empty after this operation.
void StudentList::mergeList(StudentList &otherlist) {
    if (otherlist.head == nullptr) return; // nothing to merge

    if (head == nullptr) {
        head = otherlist.head;
        tail = otherlist.tail;
    } else {
        tail->next = otherlist.head;
        otherlist.head->prev = tail;
        tail = otherlist.tail;
    }
    numStudents += otherlist.numStudents;

    // empty otherlist
    otherlist.head = nullptr;
    otherlist.tail = nullptr;
    otherlist.numStudents = 0;
}

// create a StudentList of students whose GPA is at least minGPA.
// Return this list. Do not modify the original list.
StudentList StudentList::honorRoll(float minGPA) {
    StudentList honors;
    Node* cur = head;
    while (cur != nullptr) {
        if (cur->data.GPA >= minGPA) honors.addBack(cur->data);
        cur = cur->next;
    }
    return honors;
}

// remove all students whose GPA is below a given threshold.
void StudentList::removeBelowGPA(float threshold) {
    Node* cur = head;
    while (cur != nullptr) {
        Node* next = cur->next;
        if (cur->data.GPA < threshold) {
            if (cur->prev) cur->prev->next = cur->next;
            else head = cur->next;
            if (cur->next) cur->next->prev = cur->prev;
            else tail = cur->prev;
            delete cur;
            numStudents--;
        }
        cur = next;
    }
}
