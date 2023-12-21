#include "orderbook.hpp"

using namespace std;
int main()
{
    Orderbook* book = new Orderbook();



    book->AddOrder(1, 100, 10, OrderType::BUY);
    book->AddOrder(2, 200, 10, OrderType::BUY);
    book->AddOrder(3, 300, 10, OrderType::BUY);
    book->AddOrder(4, 400, 10, OrderType::BUY);
    book->AddOrder(5, 100, 10, OrderType::SELL);
    book->AddOrder(6, 200, 10, OrderType::SELL);
    book->AddOrder(7, 300, 10, OrderType::SELL);
    book->AddOrder(8, 400, 10, OrderType::SELL);

    book->AddOrder(10, 1000, 250, OrderType::BUY);

    book->AddOrder(11, 10, 10, OrderType::SELL);

    book->PrintAllOrders();
    book->PrintAllPriceLevels();
    
    //book->PrintSingleOrder(5);

    book->WithdrawOrder(1);
    //book->WithdrawOrder(3);

    //book->PrintAllOrders();

    book->Match(10);
    book->Match(11);

    book->PrintAllOrders();
    book->PrintAllPriceLevels();

    delete book;
    return 0;
}