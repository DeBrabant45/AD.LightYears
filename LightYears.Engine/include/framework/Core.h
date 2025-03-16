#pragma once	

#include <stdio.h>
#include <memory>
#include <map>
#include <unordered_map>
#include <unordered_set>

namespace LightYear
{
template<typename T>
using Unique = std::unique_ptr<T>;

template<typename T>
using Shared = std::shared_ptr<T>;

template<typename T>
using Weak = std::weak_ptr<T>;

template<typename T>
using List = std::vector<T>;

template<typename KeyType, typename ValueType, typename Pr = std::less<KeyType>>
using Map = std::map<KeyType, ValueType, Pr>;

template<typename KeyType, typename ValueType, typename Hasher = std::hash<KeyType>>
using Dictionary = std::unordered_map<KeyType, ValueType, Hasher>;

template<typename T>
using Set = std::unordered_set<T>;

#define LOG(M, ...) printf(M "\n", ##__VA_ARGS__)
}