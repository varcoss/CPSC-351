#include <iostream>
#include <vector>
#include <thread>

// Function to increment array elements
void increment_array_elements(std::vector<int>& array, int start, int end) {
    for (int i = start; i < end; ++i) {
        array[i] += 1;
        std::cout << "Thread: " << pthread_self() << ", Incremented array[" << i << "] = " << array[i] << std::endl; //modify array name as you have in your program. pthread_self() will print out ID of the thread.
    }
}

int main() {
    // Define the array
    std::vector<int> my_array = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Divide the array into two halves
    int midpoint = my_array.size() / 2;

    // Create two threads for processing each half of the array
    std::thread thread1(increment_array_elements, std::ref(my_array), 0, midpoint);
    std::thread thread2(increment_array_elements, std::ref(my_array), midpoint, my_array.size());

    // Start the threads and wait for them to finish
    thread1.join();
    thread2.join();

    // Print the modified array
    std::cout << "Modified array with multi-threading: ";
    for (const auto& element : my_array) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    return 0;
}
