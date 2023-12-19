#include "orderbook.hpp"

using namespace std;
int main()
{
    Orderbook* book = new Orderbook();



    book->AddOrder(1, 100, 10, OrderType::BUY);
    book->AddOrder(2, 100, 10, OrderType::BUY);
    book->AddOrder(3, 200, 10, OrderType::BUY);
    book->AddOrder(4, 100, 10, OrderType::SELL);

    book->PrintAllOrders();

    //book->PrintSingleOrder(5);

    book->WithdrawOrder(1);
    book->WithdrawOrder(3);

    book->PrintAllOrders();
    
    book->PrintAllPriceLevels();


    delete book;
    return 0;
}