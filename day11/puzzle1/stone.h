#include <string>
#include <utility>

#pragma once

struct Stone {
    private:
        //Attributes
        int value;
        Stone* next;

        /**
         * Returns true if value == 0 and false otherwise.
         */
        bool rule1() {
            return value == 0;
        };

        /**
         * Returns true if value contains an even number of digits and false otherwise.
         */
        bool rule2() {
            std::string str = std::to_string(value);
            return ((str.size() % 2) == 0);
        };

        /**
         * Returns a pair object whose first element is an int made from the first half of digits of this Stone's value and
         * whose second element is an int made from the second half digits of this Stone's value with leading 0's removed.
         */
        std::pair<int, int> splitValue() {
            std::string str = std::to_string(value);
            std::string front = "";
            std::string back = "";
            int index = 0;
            while(index < (str.size() / 2)) {
                front += str.at(index);
                index++;
            }
            while(index < str.size()) {
                bool leadDigit = false;
                if((str.at(index) - '0' > 0) || leadDigit) {
                    back += str.at(index);
                    leadDigit = true;
                }
                index++;
            }
            return std::pair<int, int>(std::stoi(front), std::stoi(back));
        };
    
    public:
        Stone(int _value) {
            value = _value;
            next = nullptr;
        };

        Stone(int _value, Stone* _next) {
            value = _value;
            next = _next;
        };

        ~Stone() {
            delete next;
        };

        /**
         * Applies the appropriate rule to this stone.
         * Returns true if the Stone splits and false otherwise.
         */
        bool blink() {
            if(rule1()) {
                value = 1;
                return false;
            } else if(rule2()) {
                std::pair<int, int> newValues = splitValue();
                next = new Stone(newValues.second, next);
                value = newValues.first;
                return true;
            } else {
                value = (value * 2024);
                return false;
            }
        };

        /**
         * Return the Stone to which this stone is pointing.
         */
        Stone* getNext() {
            return next;
        };

        /**
         * Returns the value engraved on this stone.
         */
        int getValue() {
            return value;
        }

        /**
         * Updates the Stone to which this Stone is pointing.
         */
        void updateNext(Stone* stn) {
            next = stn;
        };
};