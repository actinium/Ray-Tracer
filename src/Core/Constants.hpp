#pragma once

#include <limits>
#include <thread>

constexpr double EPSILON = 0.00000001;

static_assert(std::numeric_limits<double>::is_iec559, "IEEE 754 required");
constexpr double INF = std::numeric_limits<double>::infinity();
constexpr double NEG_INF = -std::numeric_limits<double>::infinity();

constexpr double PI = 3.14159265358979323846;

constexpr int MAX_RECURSION = 5;

const unsigned MAX_THREADS = std::thread::hardware_concurrency();
