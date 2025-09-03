#include <vector>
#include "stone.h"

#pragma once

struct StoneList {
    private:
        Stone* head;
        int size;
    
    public:
        StoneList() {
            head = nullptr;
            size = 0;
        };

        ~StoneList() {
            delete head;
        };

        bool append(Stone* stn) {
            if(size <= 0) {
                head = stn;
                size++;
                return true;
            } else {
                Stone* next = head->getNext();
                while(next != nullptr) {
                    next = next->getNext();
                }
                next->updateNext(stn);
                size++;
                return true;
            }
            return false;
        };

        void blink() {
            Stone* stn = head;
            while(stn != nullptr) {
                if(stn->blink()) {
                    size++;
                    stn = stn->getNext()->getNext();
                } else {
                    stn = stn->getNext();
                }
            }
        };

        int getSize() {
            return size;
        };

        std::vector<int>* toArray() {
            std::vector<int>* values = new std::vector<int>();
            Stone* curr = head;
            while(curr != nullptr) {
                values->push_back(curr->getValue());
                curr = curr->getNext();
            }
            return values;
        };
};