#include <vector>
#include <queue>
#include <limits>
#include <list>
#include <array>
#include <iostream>

class RadixHeap {
public:
    RadixHeap() : size_(0), last_(0), buckets_(num_buckets), buckets_min_(num_buckets, std::numeric_limits<long long>::max()) {}
    void insert(long long node, long long distance);
    long long findMin();
    void deleteMin();
    bool empty() const;
private:
    long long size_;
    long long last_;
    long long num_buckets = std::numeric_limits<long long>::digits + 1;
    std::vector<std::vector<std::pair<long long, long long>>> buckets_;
    std::vector<long long> buckets_min_;

    long long find_bucket(long long x, long long last) const {
        if (x == last) {
            return 0;
        } else {
            return 64 - __builtin_clzll(x ^ last);
        }
    }

    void pull() {
        if (size_ > 0) {
            if (!buckets_[0].empty()) {
                return;
            } else {
                long long i;
                for (i = 1; buckets_[i].empty(); i++);

                last_ = buckets_min_[i];

                for (const auto& [distance, node] : buckets_[i]) {
                    long long new_bucket_index = find_bucket(distance, last_);
                    buckets_[new_bucket_index].emplace_back(distance, node);
                    buckets_min_[new_bucket_index] = std::min(buckets_min_[new_bucket_index], distance);
                }
                buckets_[i].clear();
                buckets_min_[i] = std::numeric_limits<long long>::max();
            }
        }
    }
};

void RadixHeap::insert(long long node, long long distance) {
        if (last_ <= distance) {
            size_++;
            long long bucket_index = find_bucket(distance, last_);
            buckets_[bucket_index].emplace_back(distance, node);
            buckets_min_[bucket_index] = std::min(buckets_min_[bucket_index], distance);
        }
    }

long long RadixHeap::findMin() {
    pull();
    return buckets_[0].back().second;
}

void RadixHeap::deleteMin() {
    pull();
    buckets_[0].pop_back();
    size_--;
}

bool RadixHeap::empty() const {
    return size_ == 0;
}