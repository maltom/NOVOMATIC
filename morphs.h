#include <vector>
#include <array>
#include <algorithm>

std::array<int, 4> pickMorphs(const std::vector<float> &weights)
{
    int n = 4;
    struct morph
    {
        float value;
        int index;
        bool operator>(morph a)
        {
            return (this->value > a.value);
        }
    };
    if (weights.size() < n)
        return {-1, -1, -1, -1};

    std::array<morph, 4> heap;
    for (int i = 0; i < heap.size(); ++i)
    {
        heap[i].value = weights[i];
        heap[i].index = i;
    }
    std::make_heap(heap.begin(), heap.end(),std::greater<>{});

    for(int i = 4; i<weights.size();++i)
    {
        if(weights[i]>heap[0].value)
        {
            heap[0].value = weights[i];
            heap[0].index = i;
            std::make_heap(heap.begin(), heap.end(),std::greater<>{});
        }
    }
    std::array<int, 4> result;
    for (int i = 0; i < n; ++i)
        result[i] = heap[i].index;
    return result;
}