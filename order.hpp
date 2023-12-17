#ifndef ORDER_HPP
#define ORDER_HPP

#include "ds.hpp"

class Order
{
    oid_t oid;
    price_t price;
    qty_t qty;
    OrderType type;

public:
    Order(oid_t oid, price_t price, qty_t qty, OrderType type)
        : oid(oid), price(price), qty(qty), type(type)
    {
    }

    bool operator<(const Order &rhs) const
    {
        if (type == OrderType::BUY)
        {
            return price < rhs.price;
        }
        else
        {
            return price > rhs.price;
        }
    }

};

#endif // ORDER_HPP