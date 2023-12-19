#ifndef PRICELIST_HPP
#define PRICELIST_HPP

#include "ds.hpp"
#include "pricelevel.hpp"

class PriceList
{
    std::map<price_t, PriceLevel*> price_list;

    public:

    PriceList() = default;
    ~PriceList()
    {
        for (auto& price_level : price_list)
        {
            delete price_level.second;
        }
    }

    PriceLevel* operator[] (const price_t& price)
    {
        return price_list[price];
    }

    void AddUpdate(Order* order)
    {
        // update price level itself
        price_t price = order->get_price();
        if (price_list.find(price) == price_list.end())
        {
            price_list[price] = new PriceLevel(price);
        }
        // then push order into queue
        price_list[price]->PushOrder(order);
    }

    void WithdrawUpdate(Order* order)
    {
        // std::cout << "WithdrawUpdate" << std::endl;
        price_t price = order->get_price();
        if (price_list.find(price) == price_list.end())
        {
            std::cout << "Price level not found" << std::endl;
            return;
        }
        price_list[price]->WithdrawOrder(order);
        if (price_list[price]->get_qty() == 0)
        {
            delete price_list[price];
            price_list.erase(price);
        }
    }

    void PrintAllLevels()
    {
        std::cout << "Printing all price levels" << std::endl;
        std::map<price_t, PriceLevel*>::iterator it;
        for (it = price_list.begin(); it != price_list.end(); ++it)
        {
            std::cout << *(it->second) << std::endl;
        }
        std::cout << price_list.size() << " price level(s) in total" << std::endl;
    }
};

#endif // PRICELIST_HPP