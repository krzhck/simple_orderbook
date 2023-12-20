#include "order.hpp"
#include "pricelevel.hpp"
#include "pricelist.hpp"
class Orderbook
{
    PriceList price_list;
    std::unordered_map<oid_t, Order*> orders;

public:
    Orderbook() = default;

    ~Orderbook()
    {
        for (auto& order: orders)
        {
            delete order.second;
        } 
    }

    void AddOrder(oid_t oid, price_t price, qty_t qty, OrderType type)
    {
        Order* order = new Order(oid, price, qty, type);
        orders[oid] = order;
        price_list.AddUpdate(order);
    }

    void WithdrawOrder(oid_t oid)
    {   
        if (orders.find(oid) == orders.end())
        {
            std::cout << "Order " << oid << " not found" << std::endl;
            return;
        }

        price_list.WithdrawUpdate(orders[oid]);
        delete orders[oid];
        orders.erase(oid);
    }

    void PrintAllOrders()
    {
        std::cout << "Printing all orders:" << std::endl;
        for (auto it = orders.begin(); it != orders.end(); ++it)
        {
            std::cout << *(it->second) << std::endl;
        }
        std::cout << orders.size() << " order(s) in total" << std::endl;
    }

    void PrintSingleOrder(oid_t oid)
    {
        std::cout << "Printing single order:" << std::endl;
        if (orders.find(oid) == orders.end())
        {
            std::cout << "Order " << oid << " not found" << std::endl;
            return;
        }
        std::cout << *(orders[oid]) << std::endl;
    }

    void PrintAllPriceLevels()
    {
        price_list.PrintAllLevels();
    }
    
    void Match(oid_t oid)
    {
        // DOING
        std::cout << "Matching order " << oid << std::endl;
        if (orders.find(oid) == orders.end())
        {
            std::cout << "Order " << oid << " not found" << std::endl;
            return;
        }

        Order* order = orders[oid];
    }
    
    

};