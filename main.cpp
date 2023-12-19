#include "orderbook.hpp"

int main()
{
    Orderbook* book = new Orderbook();



    book->AddOrder(1, 100, 10, OrderType::BUY);
    book->AddOrder(2, 100, 10, OrderType::BUY);
    book->AddOrder(3, 100, 10, OrderType::BUY);
    book->AddOrder(4, 100, 10, OrderType::BUY);











    delete book;
    return 0;
}