/*
 *
 */

#include <iostream>
#include <vector>
#include "ListNode.h"
#include "profiler.h"

#define STD_LIMIT 10000

using namespace std;

Profiler profiler;

// Main topic
class Merge {
    // fun to verify when all lists are empty
    static bool stop(vector<ListNode *> &lists);

    // fun to find the minimum value based on min heap
    static int min_index(vector<int> arr, vector<bool> util);

public:
    // fun to merge k linked lists
    static ListNode *KLists(vector<ListNode *> &lists, Operation opComp, Operation opAttr);
};

bool Merge::stop(vector<ListNode *> &lists) {
    for (auto &list: lists) {
        if (!list->empty())
            return true;
    }
    return false;
}

int Merge::min_index(vector<int> arr, vector<bool> util) {
    int index = 0;
    while (util[index])
        index++;
    int val = arr[index];
    int ret_index = index;
    for (int i = index + 1; i < arr.size(); ++i) {
        if (util[i])
            continue;
        if (arr[i] < val) {
            val = arr[i];
            ret_index = i;
        }
    }
    return ret_index;
}

ListNode *Merge::KLists(vector<ListNode *> &lists, Operation opComp, Operation opAttr) {
    auto *result = new ListNode;
    vector<int> first_el_arr;
    vector<bool> util;
    while (stop(lists)) {
        for (auto &list: lists) {
            opComp.count();
            opAttr.count(2);
            if (!list->empty()) {
                first_el_arr.push_back(list->head()->get_key());
                util.push_back(false);
            } else {
                first_el_arr.push_back(0);
                util.push_back(true);
            }
        }
        opAttr.count();
        int min_index = Merge::min_index(first_el_arr, util);
        opAttr.count();
        result->push(lists[min_index]->head()->get_key());
        opAttr.count();
        lists[min_index]->pop();
        first_el_arr.clear();
        util.clear();
    }
    return result;
}

// fun to generate a sorted linked list
ListNode *generate(int length, int max_sum_limit, int max_element) {
    auto *list = new ListNode();
    int arr[length];
    FillRandomArray(arr, length, 1, max_element, false, 1);
    int cont = 0;
    for (int i: arr) {
        cont += i;
        list->push(i);
        if (cont >= max_sum_limit)
            break;
    }
    return list;
}

// fun to generate k sorted linked lists, based on: -an array of limits for each
//                                                  -sum of all elements limit
//                                                  -max element value (min element is set on 1)
vector<ListNode *> generate_k_lists(const int *limits, int k, int max_sum_limit, int max_element) {
    auto *result = new vector<ListNode *>;
    for (int i = 0; i < k; i++) {
        result->push_back(generate(limits[i], max_sum_limit, max_element));
    }
    return *result;
}

void demo() {
    int limits[] = {7, 5, 10, 6, 9};

    Operation opComp = profiler.createOperation("demo_comp", 5);
    Operation opAttr = profiler.createOperation("demo_attr", 5);

    vector<ListNode *> lists = generate_k_lists(limits, 5, 10000, 500);

    for (int i = 0; i < lists.size(); ++i) {
        cout << "List " << i + 1 << ":\n";
        lists[i]->print_list();
        cout << "\n";
    }

    cout << "Result:\n";
    auto *result = Merge::KLists(lists, opComp, opAttr);
    result->print_list();

    if (result->test_sorted())
        cout << "- sorted -";
    else
        cout << "- NOT sorted -";
}

// first task (lab)
void perf_1() {
    int k1 = 5;
    int limits1[k1];
    for (int i = 100; i < 10000; i += 100) {
        Operation opComp_k1 = profiler.createOperation("comp_k1", i);
        Operation opAttr_k1 = profiler.createOperation("attr_k1", i);
        for (int j = 0; j < k1; ++j) {
            limits1[j] = i;
        }
        auto lists1 = generate_k_lists(limits1, k1, STD_LIMIT, STD_LIMIT);
        Merge::KLists(lists1, opComp_k1, opAttr_k1);
    }

    int k2 = 10;
    int limits2[k2];
    for (int i = 100; i <= 10000; i += 100) {
        Operation opComp_k2 = profiler.createOperation("comp_k2", i);
        Operation opAttr_k2 = profiler.createOperation("attr_k2", i);
        for (int j = 0; j < k2; ++j) {
            limits2[j] = i;
        }
        auto lists2 = generate_k_lists(limits2, k2, STD_LIMIT, STD_LIMIT);
        Merge::KLists(lists2, opComp_k2, opAttr_k2);
    }

    int k3 = 100;
    int limits3[k3];
    for (int i = 100; i <= 10000; i += 100) {
        Operation opComp_k3 = profiler.createOperation("comp_k3", i);
        Operation opAttr_k3 = profiler.createOperation("attr_k3", i);
        for (int j = 0; j < k3; ++j) {
            limits3[j] = i;
        }
        auto lists3 = generate_k_lists(limits3, k3, STD_LIMIT, STD_LIMIT);
        Merge::KLists(lists3, opComp_k3, opAttr_k3);
    }

    profiler.addSeries("total_k1", "comp_k1", "attr_k1");
    profiler.addSeries("total_k2", "comp_k2", "attr_k2");
    profiler.addSeries("total_k3", "comp_k3", "attr_k3");

    profiler.createGroup("PARTIAL (k1 - k2)", "total_k1", "total_k2");
    profiler.createGroup("TOTAL (k1 - k2 - k3)", "total_k1", "total_k2", "total_k3");

    profiler.reset();
}

// second task (lab)
void perf_2() {
    for (int k = 10; k <= 500; k += 10) {
        Operation opComp_k = profiler.createOperation("comp_k", k);
        Operation opAttr_k = profiler.createOperation("attr_k", k);
        int limits[k];
        for (int i = 0; i < k; i++) {
            limits[i] = STD_LIMIT;
        }
        auto lists = generate_k_lists(limits, k, STD_LIMIT, STD_LIMIT);
        Merge::KLists(lists, opComp_k, opAttr_k);
    }
    profiler.addSeries("total_k", "comp_k", "attr_k");

    profiler.reset();
}

int main() {
//    demo();
//    perf_1();
//    perf_2();
    return 0;
}
