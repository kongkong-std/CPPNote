#include "../include/eg_impl.hpp"

void Book1::SetYearPublish(int year)
{
    year_publish = year;
}

int Book1::GetYearPublish(void) const
{
    return year_publish;
}

void eg6_1(void)
{
    Book my_book;

    my_book.author = "Lewis Carroll";
    my_book.title = "Alice's adventures in Wonderland";
    my_book.publisher = "Macmillan";
    my_book.format = "hardback";
    my_book.price = 12.34;
    my_book.year_publish = 1865;

    std::cout << "Information of the book:\n";
    std::cout << "title: " << my_book.title << '\n';
    std::cout << "author: " << my_book.author << '\n';
    std::cout << "publisher: " << my_book.publisher << '\n';
    std::cout << "format: " << my_book.format << '\n';
    std::cout << "publish year: " << my_book.year_publish << '\n';
    std::cout << "price: " << my_book.price << '\n';
    std::cout << '\n';

    Book1 my_book1;
    my_book1.author = my_book.author;
    my_book1.title = my_book.title;
    my_book1.publisher = my_book.publisher;
    my_book1.format = my_book.format;
    my_book1.price = my_book.price;

    int year = 0;
    std::cout << "input publish year of book1: ";
    std::cin >> year;
    my_book1.SetYearPublish(year);

    std::cout << "Information of the book1:\n";
    std::cout << "title: " << my_book1.title << '\n';
    std::cout << "author: " << my_book1.author << '\n';
    std::cout << "publisher: " << my_book1.publisher << '\n';
    std::cout << "format: " << my_book1.format << '\n';
    std::cout << "publish year: " << my_book1.GetYearPublish() << '\n';
    std::cout << "price: " << my_book1.price << '\n';
    std::cout << '\n';
}
