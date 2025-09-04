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
                Stone* curr = head;
                while(curr->getNext() != nullptr) {
                    curr = curr->getNext();
                }
                curr->updateNext(stn);
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

        std::vector<uint16_t>* toArray() {
            std::vector<uint16_t>* values = new std::vector<uint16_t>();
            Stone* curr = head;
            while(curr != nullptr) {
                values->push_back(curr->getValue());
                curr = curr->getNext();
            }
            return values;
        };
};