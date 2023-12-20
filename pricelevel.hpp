#ifndef PRICELEVEL_HPP
#define PRICELEVEL_HPP

#include "ds.hpp"
class PriceLevel
{
    const price_t price;
	qty_t qty;
    qty_t buy_qty;
    qty_t sell_qty;

    std::queue<Order*> buy_orders;
    std::queue<Order*> sell_orders;

public:
    PriceLevel() = delete;
    PriceLevel(price_t price) : price(price), qty(0), buy_qty(0), sell_qty(0) {}
    ~PriceLevel() = default;

    price_t get_price() const
    {
        return price;
    }

    qty_t get_qty() const
    {
        return qty;
    }

    qty_t get_buy_qty() const
    {
        return buy_qty;
    }

    qty_t get_sell_qty() const
    {
        return sell_qty;
    }

    void PushOrder(Order* order)
    {
        if (order == nullptr)
        {
            return;
        }
        auto q = order->get_qty();
        if (order->get_type() == OrderType::BUY)
        {
            buy_orders.push(order);
            buy_qty += q;
        }
        else
        {
            sell_orders.push(order);
            sell_qty += q;
        }
        qty += q;
    }

    void WithdrawOrder(Order* order)
    {
        if (order == nullptr)
        {
            return;
        }
        auto q = order->get_qty();
        if (order->get_type() == OrderType::BUY)
        {
            buy_qty -= q;
        }
        else
        {
            sell_qty -= q;
        }
        qty -= q;
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