#include <vector>
#include <limits>
#include <cmath>
#include <algorithm>
#include <utility>

class RadixHeap {
public:
    RadixHeap(long long nC) : K(static_cast<int>(std::ceil(std::log2(nC))), buckets(K + 1), range(K + 1), distances(nC, std::numeric_limits<long long>::max()), nC(nC)) {}

    void insert(int node, long long distance) {
        int bucketIndex = getBucketIndex(distance);
        buckets[bucketIndex].push_back(node);
        distances[node] = distance;
    }

    int findMin() {
        int k = 0;
        while (buckets[k].empty()) {
            ++k;
        }

        if (range[k].second - range[k].first > 1) {
            redistribute(k);
            k = 0;
        }

        return buckets[k].front();
    }

    void deleteMin() {
        int k = 0;
        while (buckets[k].empty()) {
            ++k;
        }

        if (range[k].second - range[k].first > 1) {
            redistribute(k);
            k = 0;
        }

        buckets[k].erase(buckets[k].begin());
    }

    void decreaseKey(int node, long long newDistance) {
        int oldBucketIndex = getBucketIndex(distances[node]);
        auto& bucket = buckets[oldBucketIndex];
        bucket.erase(std::remove(bucket.begin(), bucket.end(), node), bucket.end());

        insert(node, newDistance);
    }

    bool empty() const {
        for (const auto& bucket : buckets) {
            if (!bucket.empty()) {
                return false;
            }
        }
        return true;
    }

private:
    int getBucketIndex(long long distance) const {
        if (distance == 0) {
            return 0;
        } else if (distance == 1) {
            return 1;
        } else {
            return static_cast<int>(std::log2(distance)) + 1;
        }
    }

    void redistribute(int k) {
        long long minDistance = std::numeric_limits<long long>::max();
        for (int node : buckets[k]) {
            if (distances[node] < minDistance) {
                minDistance = distances[node];
            }
        }

        range[0].first = minDistance;
        range[0].second = minDistance;
        for (int i = 1; i <= k; ++i) {
            range[i].first = range[i - 1].second + 1;
            range[i].second = std::min(range[i].first + (1LL << i) - 1, nC - 1);
        }

        std::vector<int> temp = std::move(buckets[k]);
        buckets[k].clear();

        for (int node : temp) {
            int newBucketIndex = getBucketIndex(distances[node]);
            buckets[newBucketIndex].push_back(node);
        }
    }

    const int K;
    long long nC;
    std::vector<std::vector<int>> buckets;
    std::vector<std::pair<long long, long long>> range;
    std::vector<long long> distances;
};
