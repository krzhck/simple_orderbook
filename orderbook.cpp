#include "order.hpp"

class Orderbook
{
    std::priority_queue<Order> buy_orders;
    std::priority_queue<Order> sell_orders;
    std::unordered_map<oid_t, Order> orders;

public:
    Orderbook() = default;

    void AddOrder(oid_t oid, price_t price, qty_t qty, OrderType type)
    {

    }

    void DeleteOrder(oid_t oid)
    {
    }

    void GetBuyPriceLevels(std::vector<PriceLevel> &levels, int max_levels) const
    {
    }

    void GetSellPriceLevels(std::vector<PriceLevel> &levels, int max_levels) const
    {
    }
};