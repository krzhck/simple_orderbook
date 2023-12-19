#ifndef DS_HPP
#define DS_HPP

#include <iostream>
#include <vector>
#include <cstdint>
#include <queue>
#include <map>
#include <string>
#include <unordered_map>
#include "order.hpp"

using oid_t = int64_t;
using price_t = double;
using qty_t = int64_t;

enum OrderType
{
    BUY = 0,
    SELL = 1
};

#endif // DS_HPP