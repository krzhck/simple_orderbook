#ifndef PRICELEVEL_HPP
#define PRICELEVEL_HPP

#include "ds.hpp"
class PriceLevel
{
    const price_t price;
	qty_t qty;

    std::queue<Order*> buy_orders;
    std::queue<Order*> sell_orders;

public:
    PriceLevel() = delete;
    PriceLevel(price_t price) : price(price), qty(0) {}
    ~PriceLevel() = default;

    void PushOrder(Order* order)
    {
        if (order->get_type() == OrderType::BUY)
        {
            buy_orders.push(order);
        }
        else
        {
            sell_orders.push(order);
        }
        qty += order->get_qty();
    }
};

#endif // PRICELEVEL_HPP