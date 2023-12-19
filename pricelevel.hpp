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

    price_t get_price() const
    {
        return price;
    }

    qty_t get_qty() const
    {
        return qty;
    }

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

    void WithdrawOrder(Order* order)
    {
        qty -= order->get_qty();
    }

    Order* PopOrder(OrderType type)
    {   
        // TODO: maybe pop later
        std::queue<Order*> &q = (type == OrderType::BUY) ? buy_orders : sell_orders;
        Order* order = q.front();
        while (order != nullptr && !q.empty())
        {   
            if (q.front()->get_qty() > 0)
            {
                continue;
            }
            q.pop();
            order = q.front();
        }
        return order;
    }

    friend std::ostream& operator<< (std::ostream& os, const PriceLevel& level)
    {
        os << "Price: " << level.price << ", Quantity: " << level.qty;
        return os;
    }
};

#endif // PRICELEVEL_HPP