#ifndef ORDER_HPP
#define ORDER_HPP

#include "ds.hpp"

class Order
{
    const oid_t oid;
    price_t price;
    qty_t qty;
    const OrderType type;

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

    void set_qty(qty_t qty)
    {
        this->qty = qty;
    }

    void print() const
    {
        std::cout << "oid: " << oid << ", price: " << price << ", qty: " << qty << ", type: " << (type == OrderType::BUY ? "BUY" : "SELL") << std::endl;
    }

    friend std::ostream &operator<<(std::ostream &os, const Order &order)
    {
        os << "oid: " << order.oid << ", price: " << order.price << ", qty: " << order.qty << ", type: " << (order.type == OrderType::BUY ? "BUY" : "SELL");
        return os;
    }
};

#endif // ORDER_HPP