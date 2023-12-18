#include "order.hpp"
#include "pricelevel.hpp"
#include "pricelist.hpp"
class Orderbook
{
    PriceList price_list;
    std::unordered_map<oid_t, Order> orders;

    PriceLevel GetBetterPriceLevel(Order &order) const
    {
    }



public:
    Orderbook() = default;

    void AddOrder(oid_t oid, price_t price, qty_t qty, OrderType type)
    {
        Order order(oid, price, qty, type);
        orders[oid] = order;
        if (type == OrderType::BUY)
        {
            
        }
        else
        {
            
        }
    }

    void WithdrawOrder(oid_t oid)
    {
        
    }

    void GetBuyPriceLevels(std::vector<PriceLevel> &levels, int max_levels) const
    {

    }

    void GetSellPriceLevels(std::vector<PriceLevel> &levels, int max_levels) const
    {
    }

    void Match(oid_t oid)
    {
        if (orders.find(oid) == orders.end())
        {
            std::cout << "Order " << oid << " not found" << std::endl;
            return;
        }
        Order order = orders[oid];
        if (order.get_type() == OrderType::BUY)
        {
            // Match with sell orders 

            while (!sellOrders.empty() && newOrder.quantity > 0 && newOrder.price >= sellOrders.top().price) {
                // Process buy order with available sell orders
                Order topSell = sellOrders.top();
                sellOrders.pop();
                int quantityToTrade = std::min(newOrder.quantity, topSell.quantity);
                newOrder.quantity -= quantityToTrade;
                topSell.quantity -= quantityToTrade;

                if (topSell.quantity > 0) {
                    sellOrders.push(topSell);
                }

                std::cout << "Traded: " << quantityToTrade << " at price " << topSell.price << std::endl;
            }
            if (newOrder.quantity > 0) {
                buyOrders.push(newOrder);
            }
        }
        else
        {
            // Match with buy orders
        }
    }

    ~Orderbook() = default;
};