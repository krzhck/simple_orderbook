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
        : oid(oid), price(price), qty(qty), type(type) {}
    
    ~Order() = default;

    bool operator==(const Order &rhs) const
    {
        return oid == rhs.get_oid();
    }

    bool operator!=(const Order &rhs) const
    {
        return !(*this == rhs);
    }

    bool IsBetterThan(const Order &rhs) const
    {
        if (type == OrderType::BUY)
        {
            return price > rhs.get_price();
        }
        else
        {
            return price < rhs.get_price();
        }
    }

    oid_t get_oid() const
    {
        return oid;
    }

    price_t get_price() const
    {
        return price;
    }

    qty_t get_qty() const
    {
        return qty;
    }

    OrderType get_type() const
    {
        return type;
    }

    void print() const
    {
        std::cout << "oid: " << oid << ", price: " << price << ", qty: " << qty << ", type: " << (type == OrderType::BUY ? "BUY" : "SELL") << std::endl;
    }
};

#endif // ORDER_HPP