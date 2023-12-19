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
        for (auto it = orders.begin(); it != orders.end(); ++it)
        {
            delete it->second;
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
        price_list.WithdrawUpdate(orders[oid]);
        orders.erase(oid);
    }

    void PrintAllOrders()
    {
        std::cout << "Printing all orders" << std::endl;
        for (auto it = orders.begin(); it != orders.end(); ++it)
        {
            //std::cout << it->second->get_oid() << " " << it->second->get_price() << " " << it->second->get_qty() << " " << it->second->get_type() << std::endl;
            //it->second->print();
            std::cout << *(it->second) << std::endl;
        }
    }

    void PrintAllPriceLevels()
    {
        price_list.PrintAllLevels();
    }

    /*
    void Match(oid_t oid)
    {
        if (orders.find(oid) == orders.end())
        {
            std::cout << "Order " << oid << " not found" << std::endl;
            return;
        }
        Order order = orders[oid];
        if (order.get_type() == OrderType::BUY)
        {
            // Match with sell orders 

            while (!sellOrders.empty() && newOrder.quantity > 0 && newOrder.price >= sellOrders.top().price) {
                // Process buy order with available sell orders
                Order topSell = sellOrders.top();
                sellOrders.pop();
                int quantityToTrade = std::min(newOrder.quantity, topSell.quantity);
                newOrder.quantity -= quantityToTrade;
                topSell.quantity -= quantityToTrade;

                if (topSell.quantity > 0) {
                    sellOrders.push(topSell);
                }

                std::cout << "Traded: " << quantityToTrade << " at price " << topSell.price << std::endl;
            }
            if (newOrder.quantity > 0) {
                buyOrders.push(newOrder);
            }
        }
        else
        {
            // Match with buy orders
        }
    }
    */
    

};