#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

#include "euclidean_clustering.h"

namespace
{
std::vector<int> sorted(std::vector<int> values)
{
    std::sort(values.begin(), values.end());
    return values;
}
}

int main()
{
    KdTree3D tree;
    const std::vector<KdTree3D::Point> points = {
        {{0.0f, 0.0f, 0.0f}},
        {{0.5f, 0.5f, 0.5f}},
        {{0.8f, 0.8f, 0.0f}},
        {{0.0f, 0.0f, 1.0f}},
        {{-0.5f, -0.5f, -0.5f}},
        {{5.0f, 5.0f, 5.0f}},
        {{5.4f, 5.0f, 5.0f}}
    };

    for (std::size_t index = 0; index < points.size(); ++index)
    {
        tree.insert(points[index], static_cast<int>(index));
    }

    assert(sorted(tree.search({{0.0f, 0.0f, 0.0f}}, 1.0f)) ==
           std::vector<int>({0, 1, 3, 4}));
    assert(tree.search({{10.0f, 10.0f, 10.0f}}, 0.5f).empty());

    std::vector<std::vector<int>> clusters =
        euclideanCluster3D(points, tree, 1.25f);
    for (std::vector<int>& cluster : clusters)
    {
        std::sort(cluster.begin(), cluster.end());
    }
    std::sort(clusters.begin(), clusters.end());

    assert(clusters.size() == 2);
    assert(clusters[0] == std::vector<int>({0, 1, 2, 3, 4}));
    assert(clusters[1] == std::vector<int>({5, 6}));

    std::cout << "KD-tree and Euclidean clustering tests passed" << std::endl;
    return 0;
}
