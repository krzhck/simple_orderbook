#ifndef PRICELIST_HPP
#define PRICELIST_HPP

#include "ds.hpp"
#include "pricelevel.hpp"

class PriceList
{
    std::map<price_t, PriceLevel> price_list;

    public:

    PriceList() = default;
    PriceList(const PriceList& other) = default;
    PriceList(PriceList&& other) = default;

    PriceLevel& operator[] (const price_t& price)
    {
        return price_list[price];
    }

    void insert(const price_t& price)
    {

        price_list.insert(std::make_pair(price, PriceLevel(price)));
    }

    PriceLevel& FindBetter()
    {
        // TODO
    }
};

#endif // PRICELIST_HPP