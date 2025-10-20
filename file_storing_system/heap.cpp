#include "Heap.h"
#include "File.h"
#include <iostream>

Heap::Heap(bool by_version) : modification_time(by_version) {}

bool Heap::compare(File* a, File* b) const {

    if (modification_time) return (a->last_modified >= b->last_modified);
    
    else return (a->total_versions >= b->total_versions);
}

void Heap::heapify_up(int idx, HashMap<File*, int>& file_loc_modification_time, 
    HashMap<File*, int>& file_loc_most_versions) {
    
    while (idx > 0) {
        int parent = (idx - 1) / 2;
    
        if (compare(heap[idx], heap[parent])) {
    
            if (modification_time) {
                int tmp = file_loc_modification_time[heap[idx]];
                file_loc_modification_time[heap[idx]] = file_loc_modification_time[heap[parent]];
                file_loc_modification_time[heap[parent]] = tmp;
            } else {
                int tmp = file_loc_most_versions[heap[idx]];
                file_loc_most_versions[heap[idx]] = file_loc_most_versions[heap[parent]];
                file_loc_most_versions[heap[parent]] = tmp;
            }
    
            std::swap(heap[idx], heap[parent]);
            idx = parent;
    
        } else break;
    }
    return;
}

void Heap::heapify_down(int idx, HashMap<File*, int>& file_loc_modification_time,
    HashMap<File*, int>& file_loc_most_versions) {
    
    int left = 2 * idx + 1, right = 2 * idx + 2, largest = idx;

    if (left < heap.size() && compare(heap[left], heap[largest])) largest = left;

    if (right < heap.size() && compare(heap[right], heap[largest])) largest = right;

    if (largest != idx) {

        if (modification_time) {
            int tmp = file_loc_modification_time[heap[idx]];
            file_loc_modification_time[heap[idx]] = file_loc_modification_time[heap[largest]];
            file_loc_modification_time[heap[largest]] = tmp;
        } else {
            int tmp = file_loc_most_versions[heap[idx]];
            file_loc_most_versions[heap[idx]] = file_loc_most_versions[heap[largest]];
            file_loc_most_versions[heap[largest]] = tmp;
        }

        std::swap(heap[idx], heap[largest]);
        heapify_down(largest, file_loc_modification_time, file_loc_most_versions);
    }
    return;
}

File* Heap::top() {
    if (heap.empty()) return nullptr;
    return heap[0];
}

void Heap::add(File* file, HashMap<File*, int>& file_loc_modification_time,
    HashMap<File*, int>& file_loc_most_versions) {

    heap.push_back(file);

    if (modification_time) file_loc_modification_time[file] = heap.size() - 1;
    else file_loc_most_versions[file] = heap.size() - 1;

    heapify_up(heap.size() - 1, file_loc_modification_time, file_loc_most_versions);
}

void Heap::remove(int idx,
    HashMap<File*, int>& file_loc_modification_time,
    HashMap<File*, int>& file_loc_most_versions) {

    int last = heap.size() - 1;

    if (idx < 0 || idx > last) return;
    File* removed = heap[idx];

    if (idx != last) {
        std::swap(heap[idx], heap[last]);
        heap.pop_back();

        if (modification_time) file_loc_modification_time.erase(removed);
        else file_loc_most_versions.erase(removed);

        if (modification_time) file_loc_modification_time[heap[idx]] = idx;
        else file_loc_most_versions[heap[idx]] = idx;

        heapify_up(idx, file_loc_modification_time, file_loc_most_versions);
        heapify_down(idx, file_loc_modification_time, file_loc_most_versions);
        
    } else {
        heap.pop_back();

        if (modification_time) file_loc_modification_time.erase(removed);
        else file_loc_most_versions.erase(removed);
    }
}

File* Heap::operator[](int idx) {   
    return heap[idx];
}

int Heap::size() const { return heap.size(); }
