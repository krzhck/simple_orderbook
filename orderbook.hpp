#include "order.hpp"
#include "pricelevel.hpp"
#include "pricelist.hpp"
class Orderbook
{
    PriceList* price_list;
    std::unordered_map<oid_t, Order*> orders;

public:
    Orderbook() 
    {
        if (price_list == nullptr)
        {
            price_list = new PriceList();
        }
    }

    ~Orderbook()
    {
        delete price_list;
        for (auto& order: orders)
        {
            delete order.second;
        }
    }

    void AddOrder(oid_t oid, price_t price, qty_t qty, OrderType type)
    {
        if (orders.find(oid) != orders.end())
        {
            std::cout << "Order " << oid << " already exists" << std::endl;
            return;
        }

        Order* order = new Order(oid, price, qty, type);
        orders[oid] = order;
        price_list->AddUpdate(order);
    }

    void WithdrawOrder(oid_t oid)
    {   
        if (orders.find(oid) == orders.end())
        {
            std::cout << "WithdrawOrder() Order " << oid << " not found" << std::endl;
            return;
        }

        price_list->WithdrawUpdate(orders[oid]);
        delete orders[oid];
        orders.erase(oid);
        std::cout << "Order " << oid << " withdrawn" << std::endl;
    }

    void PrintAllOrders()
    {
        std::cout << "All orders:" << std::endl;
        for (auto it = orders.begin(); it != orders.end(); ++it)
        {
            std::cout << *(it->second) << std::endl;
        }
        std::cout << orders.size() << " order(s) in total" << std::endl;
    }

    void PrintSingleOrder(oid_t oid)
    {
        std::cout << "Single order:" << std::endl;
        if (orders.find(oid) == orders.end())
        {
            std::cout << "Order " << oid << " not found" << std::endl;
            return;
        }
        std::cout << *(orders[oid]) << std::endl;
    }

    void PrintAllPriceLevels()
    {
        price_list->PrintAllLevels();
    }
    
    void Match(oid_t oid)
    {
        std::cout << "Matching order " << oid << std::endl;
        if (orders.find(oid) == orders.end())
        {
            std::cout << "Match() Order " << oid << " not found" << std::endl;
            return;
        }

        Order* order = orders[oid];
        PriceLevel* price = (*price_list)[order->get_price()];
        OrderType type = order->get_type();

        std::cout << "Order: " << *order << std::endl;
        
        PriceLevel* b_price = nullptr;
        Order* opp_order = nullptr;

        while (order->get_qty() > 0)
        {
            b_price = price_list->BetterPrice(order);
            if (b_price == nullptr)
            {
                std::cout << "No better price." << std::endl;
                return;
            }
            std::cout << "Better Price: " << *b_price << std::endl;
            
            // dequeue
            while (b_price->get_qty(!type) > 0)
            {
                if (order->get_qty() == 0) break;

                opp_order = b_price->FirstOrder(!type);
                if (opp_order == nullptr) continue;
                
                // trade
                std::cout << "Opposite order: " << *opp_order << std::endl;
                auto qty = order->get_qty();
                auto opp_qty = opp_order->get_qty();

                if (qty >= opp_qty)
                {
                    // need pop
                    order->set_qty(qty - opp_qty);
                    price->QtyUpdate(order, -opp_qty);
                    
                    b_price->PopOrder(!type);
                    opp_order->set_qty(0);
                    WithdrawOrder(opp_order->get_oid());
                }
                else
                {
                    // no need pop
                    order->set_qty(0);
                    price->QtyUpdate(order, -qty);

                    opp_order->set_qty(opp_qty - qty);
                    b_price->QtyUpdate(opp_order, -qty);
                }
            }
        }
        if (order->get_qty() <= 0)
            WithdrawOrder(oid);
    }
};