#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Binary Search
int binarySearch(const vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// Binary Search used in Exponential Search
int binarySearchRange(const vector<int>& arr, int left, int right, int target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// Exponential Search
int exponentialSearch(const vector<int>& arr, int target) {
    if (arr[0] == target) return 0;
    int i = 1;
    while (i < arr.size() && arr[i] <= target) i *= 2;
    return binarySearchRange(arr, i / 2, min(i, (int)arr.size() - 1), target);
}

// Quick Sort
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high], i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int p = partition(arr, low, high);
        quickSort(arr, low, p - 1);
        quickSort(arr, p + 1, high);
    }
}

// Merge Sort
void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> L(arr.begin() + left, arr.begin() + mid + 1);
    vector<int> R(arr.begin() + mid + 1, arr.begin() + right + 1);
    int i = 0, j = 0, k = left;
    while (i < L.size() && j < R.size())
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < L.size()) arr[k++] = L[i++];
    while (j < R.size()) arr[k++] = R[j++];
}
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Display first 10 elements
void displaySample(const vector<int>& arr) {
    for (int i = 0; i < min(10, (int)arr.size()); ++i)
        cout << arr[i] << " ";
    cout << (arr.size() > 10 ? "... (showing first 10)" : "") << "\n";
}

int main() {
    int choice, N, target;
    vector<int> original;

    srand(time(0));
    cout << "==== DSA Assignment Console Program ====\n";

    cout << "Enter number of elements to generate: ";
    cin >> N;

    original.resize(N);
    for (int i = 0; i < N; ++i)
        original[i] = rand() % 1000;

    cout << "Generated Array: ";
    displaySample(original);

    do {
        cout << "\nChoose Operation:\n";
        cout << "1. Binary Search\n";
        cout << "2. Exponential Search\n";
        cout << "3. Quick Sort\n";
        cout << "4. Merge Sort\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                vector<int> arr = original;
                sort(arr.begin(), arr.end());
                cout << "Sorted Array for Binary Search: ";
                displaySample(arr);
                cout << "Enter number to search: ";
                cin >> target;
                auto start = high_resolution_clock::now();
                int index = binarySearch(arr, target);
                auto stop = high_resolution_clock::now();
                cout << (index != -1 ? "Element found at index: " + to_string(index) : "Element not found") << "\n";
                cout << "Time taken: " << duration_cast<nanoseconds>(stop - start).count() << " nanoseconds\n";
                break;
            }

            case 2: {
                vector<int> arr = original;
                sort(arr.begin(), arr.end());
                cout << "Sorted Array for Exponential Search: ";
                displaySample(arr);
                cout << "Enter number to search: ";
                cin >> target;
                auto start = high_resolution_clock::now();
                int index = exponentialSearch(arr, target);
                auto stop = high_resolution_clock::now();
                cout << (index != -1 ? "Element found at index: " + to_string(index) : "Element not found") << "\n";
                cout << "Time taken: " << duration_cast<nanoseconds>(stop - start).count() << " nanoseconds\n";
                break;
            }

            case 3: {
                vector<int> arr = original;
                auto start = high_resolution_clock::now();
                quickSort(arr, 0, arr.size() - 1);
                auto stop = high_resolution_clock::now();
                cout << "Quick Sorted Array: ";
                displaySample(arr);
                cout << "Time taken: " << duration_cast<microseconds>(stop - start).count() << " microseconds\n";
                break;
            }

            case 4: {
                vector<int> arr = original;
                auto start = high_resolution_clock::now();
                mergeSort(arr, 0, arr.size() - 1);
                auto stop = high_resolution_clock::now();
                cout << "Merge Sorted Array: ";
                displaySample(arr);
                cout << "Time taken: " << duration_cast<microseconds>(stop - start).count() << " microseconds\n";
                break;
            }

            case 0:
                cout << "Exiting program. Good luck!\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
