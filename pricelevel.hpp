#ifndef PRICELEVEL_HPP
#define PRICELEVEL_HPP

#include "ds.hpp"



class PriceLevel
{
    const price_t price;
	qty_t qty;

    std::priority_queue<Order> buy_orders;
    std::priority_queue<Order> sell_orders;

public:
    PriceLevel() = delete;
    PriceLevel(price_t price) : price(price), qty(0) {}
    // ~PriceLevel() = default;
};

#endif // PRICELEVEL_HPP