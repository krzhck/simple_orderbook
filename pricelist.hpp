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
        price_t price = order->get_price();
        if (price_list.find(price) == price_list.end())
        {
            price_list[price] = new PriceLevel(price);
        }
        price_list[price]->PushOrder(order);
    }

    void WithdrawUpdate(Order* order)
    {
        // TODO
    }

    PriceLevel& FindBetter()
    {
        // TODO
    }
};

#endif // PRICELIST_HPP