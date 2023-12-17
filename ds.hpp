#ifndef DS_HPP
#define DS_HPP

#include <iostream>
#include <vector>
#include <cstdint>
#include <queue>
#include <unordered_map>
#include "order.hpp"

using oid_t = int64_t;
using price_t = double;
using qty_t = int64_t;

enum class OrderType
{
    BUY = 0,
    SELL
};

struct PriceLevel
{
	const price_t price;
	qty_t qty;
};

#endif // DS_HPP