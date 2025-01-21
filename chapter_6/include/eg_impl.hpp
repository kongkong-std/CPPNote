#ifndef EG_IMPL_HPP_
#define EG_IMPL_HPP_

// header
#include "main.hpp"

// classes
/*
 * book class initial
 */
class Book
{
public:
    std::string author, title, publisher, format;
    double price;
    int year_publish;
};

/*
 * book class 1
 */
class Book1
{
public:
    std::string author, title, publisher, format;
    double price;
    void SetYearPublish(int);
    int GetYearPublish() const;

private:
    int year_publish;
};

// function prototype
/*
 * book class
 */
void eg6_1(void);

#endif