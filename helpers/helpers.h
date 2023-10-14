#ifndef HELPERS_H
#define HELPERS_H
#include<iostream>

char int_to_string(int i);
void sysexit();
std::string charToString(char c);
bool isInteger(std::string s);
void replace(std::string &str, const std::string &search, const std::string &replace);
bool contains(const std::string& s, const std::string& x);

# endif //HELPERS_H