#ifndef PRICELIST_HPP
#define PRICELIST_HPP

#include "ds.hpp"
#include "pricelevel.hpp"

class PriceList
{
    std::map<price_t, PriceLevel*> price_levels;

    public:

    PriceList() = default;
    ~PriceList()
    {
        for (auto& price_level : price_levels)
        {
            delete price_level.second;
        }
    }

    PriceLevel* operator[] (const price_t& price)
    {
        return price_levels[price];
    }

    PriceLevel* BetterPrice(Order* order)
    {
        auto it = price_levels.find(order->get_price());
        if (it == price_levels.end())
        {
            return nullptr;
        }

        if (order->get_type() == OrderType::BUY)
        {
            // buy find lower
            while (it != price_levels.begin())
            {
                if (it->second->get_sell_qty() > 0)
                {
                    return it->second;
                }
                it--;
            }
            if (it->second->get_sell_qty() > 0)
            {
                return it->second;
            }
        }

        else
        {
            // sell find higher
            while (it != price_levels.end())
            {
                if (it->second->get_buy_qty() > 0)
                {
                    return it->second;
                }
                it++;
            }
        }
        return nullptr;
    }

    void AddUpdate(Order* order)
    {
        // update price level itself
        price_t price = order->get_price();
        if (price_levels.find(price) == price_levels.end())
        {
            price_levels[price] = new PriceLevel(price);
        }
        // then push order into queue
        price_levels[price]->PushOrder(order);
    }

    void WithdrawUpdate(Order* order)
    {
        price_t price = order->get_price();
        if (price_levels.find(price) == price_levels.end())
        {
            std::cout << "Price level not found" << std::endl;
            return;
        }

        price_levels[price]->WithdrawOrder(order);
        if (price_levels[price]->get_qty() <= 0)
        {
            delete price_levels[price];
            price_levels.erase(price);
        }
    }

    void PrintAllLevels()
    {
        std::cout << "Printing all price levels" << std::endl;
        std::map<price_t, PriceLevel*>::iterator it;
        for (it = price_levels.begin(); it != price_levels.end(); ++it)
        {
            std::cout << *(it->second) << std::endl;
        }
        std::cout << price_levels.size() << " price level(s) in total" << std::endl;
    }
};

#endif // PRICELIST_HPP