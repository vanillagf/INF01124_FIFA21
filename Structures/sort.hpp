#pragma once

#include "../Headers/head.hpp"

namespace sort{
    inline auto lomuto(vector<pair<long, float>>& arr, int low, int high){
        auto pivot = arr[high];
        int i = (low-1);

        for(int j = low; j <= high-1; ++j){
            if(arr[j].second >= pivot.second){
                ++i;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i+1], arr[high]);
        return (i+1);
    }

    inline auto hoare(vector<pair<long, float>>& arr, int low, int high){
        auto pivot = arr[low];
        int i = low, j = high;

        while(i < j){
            while(arr[j].second < pivot.second && i < j)
                --j;
            arr[i] = arr[j];
            while(arr[i].second >= pivot.second && i < j)
                ++i;
            arr[j] = arr[i];
        }
        arr[j] = pivot;
        return i;
    }

    inline auto median(vector<pair<long, float>>& arr, int low, int high){
        int mid = (low+high)/2;
        if(arr[mid].second > arr[low].second)
            swap(arr[mid], arr[low]);
        if(arr[high].second > arr[low].second)
            swap(arr[high], arr[low]);
        if(arr[mid].second > arr[high].second)
            swap(arr[mid], arr[high]);
        return sort::hoare(arr, low, high);
    }

    inline void quicksort(vector<pair<long, float>>& arr, int begin, int end){
        if(begin < end){
            auto q = sort::median(arr, begin, end);
            sort::quicksort(arr, begin, q-1);
            sort::quicksort(arr, q+1, end);
        }
    }

    inline void sort(vector<pair<long, float>>& arr, int begin, int end){
            sort::quicksort(arr, begin, end);
        }
}