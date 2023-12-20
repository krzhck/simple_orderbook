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

    qty_t get_type_qty(OrderType type) const
    {
        return (type == OrderType::BUY) ? buy_qty : sell_qty;
    }

    void QtyUpdate(Order* order, qty_t d)
    {
        if (order->get_type() == OrderType::BUY)
        {
            buy_qty += d;
        }
        else
        {
            sell_qty += d;
        }
        qty += d;
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
        std::cout << "WithdrawOrder[" << order->get_oid() << "]: q = " << qty << std::endl;
    }

    void PopOrder(OrderType type)
    {   
        if (this->get_type_qty(type) == 0)
        {
            return;
        }

        std::queue<Order*> &q = (type == OrderType::BUY) ? buy_orders : sell_orders;
        if (q.front() == nullptr)
        {   
            q.pop();
            return;
        }
        while (q.front() == nullptr || q.front()->get_qty() == 0)
        {
            q.pop();
        }
        auto del = q.front()->get_qty();
        q.pop();
        qty -= del;
        if (type == OrderType::BUY)
        {
            buy_qty -= del;
        }
        else
        {
            sell_qty -= del;
        }
    }

    Order* FirstOrder(OrderType type)
    {
        return (type == OrderType::BUY) ? buy_orders.front() : sell_orders.front();
    }

    friend std::ostream& operator<< (std::ostream& os, const PriceLevel& level)
    {
        os << "Price: " << level.price << ", Quantity: " << level.qty;
        return os;
    }
};

#endif // PRICELEVEL_HPP