#pragma once

#include <iostream>
#include <string_view>
#include <deque>
#include <map>
using namespace std;

class Translator {
public:
    Translator() = default;

    void Add(string_view source, string_view target) {
        if (language1.count(source)) {
            slova.push_back(string(target));
            language1[source] = slova.back();
        }
        else{
            slova.push_back(string(source));
            slova.push_back(string(target));  
            //cout << *(slova.end() - 2) << " " << slova.back() << endl;
            language1[*(slova.end() - 2)] = slova.back();
            language2[slova.back()] = *(slova.end() - 2);
        }

    }
    string_view TranslateForward(string_view source) const {
        if (language1.count(source)) {
            return language1.at(source);
        }
        return"";
    }
    string_view TranslateBackward(string_view target) const {
        if (language2.count(target)) {
            return language2.at(target);
        }
        return"";
    }

private:
    deque<string> slova;
    map<string_view, string_view> language1;
    map<string_view, string_view> language2;

};
///////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "my_assert.h"
#include <string>
#include <cassert>

using namespace std;
void TestSimple() {
    Translator translator;
    translator.Add(string("okno"s), string("window"s));
    translator.Add(string("stol"s), string("table"s));

    assert(translator.TranslateForward("okno"s) == "window"s);
    assert(translator.TranslateBackward("table"s) == "stol"s);
    assert(translator.TranslateForward("table"s) == ""s);
    translator.Add(string("okno"s), string("winda"s));
    assert(translator.TranslateForward("okno"s) != "window"s);
}

int main() {
    TestSimple();
}
