#pragma once

#include <string>

using std::string;

class Human {
protected:
    string name_;
    string surname_;

public:
    Human() = default;
    Human(string name, string surname) : name_(name), surname_(surname) {}
    Human(const Human&) = default;
    Human(Human&&) noexcept = default;
    Human& operator=(const Human&) = default;
    Human& operator=(Human&&) noexcept = default;
    virtual ~Human() = 0;

    inline const string& name() const { return name_; }
    inline const string& surname() const { return surname_; }

    inline void setName(string name) { name_ = name; }
    inline void setSurname(string surname) { surname_ = surname; }
};

inline Human::~Human() = default;
