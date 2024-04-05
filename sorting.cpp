#include<iostream>
#include<fstream>

class Sorting { // sorting class implementing all 3 kinds of sorting methods as static function
public:
    /*-----------------------insertion sort------------------------*/

    static void insertion_sort(int* unsorted, int size) {
        for (int i = 1; i < size; ++i) {
            int key = unsorted[i]; // select an element from unsorted portion
            int j = i - 1;
            while (j >= 0 && unsorted[j] > key) { //iterate sorted part until find the smaller one compare to the key
                unsorted[j + 1] = unsorted[j];
                --j;
            }
            unsorted[j + 1] = key; // put the key in the right position of sorted portion
        }
    }

    /*-----------------------merge sort------------------------*/

    static void merge(int* unsorted, int left, int mid, int right) { // merge function to sort & merge
        
        int n1 = mid - left + 1;
        int n2 = right - mid;

        int* leftarr = new int[n1];
        int* rightarr = new int[n2]; // temp arrays to store halved parts

        for (int i = 0; i < n1; ++i) {
            leftarr[i] = unsorted[left + i];
        }
        for (int j = 0; j < n2; ++j) {
            rightarr[j] = unsorted[mid + 1 + j];
        }

        int i = 0, j = 0, k = left; // Initial index of left, right temp arr and merged

        while (i < n1 && j < n2) { // compare elements of two temp arrays 
            if (leftarr[i] <= rightarr[j]) { // if left temp element is smaller
                unsorted[k] = leftarr[i]; // put it into the merged
                ++i;
            }
            else { // if right temp element is smaller
                unsorted[k] = rightarr[j]; //put it into the merged too
                ++j;
            }
            ++k;
        }

        while (i < n1) { // copy the remaining part of left array if there's any
            unsorted[k] = leftarr[i];
            ++i;
            ++k;
        }

        while (j < n2) { // // copy the remaining part of right array if there's any
            unsorted[k] = rightarr[j];
            ++j;
            ++k;
        }

        delete[] leftarr;
        delete[] rightarr;
    }

    static void mergesort(int* unsorted, int left, int right) { // call itself to do the divide recursively

        if (left < right) { // check the input is right
            int mid = (right + left) / 2;
            mergesort(unsorted, left, mid);
            mergesort(unsorted, mid + 1, right); // recursive calls for division

            merge(unsorted, left, mid, right); // sort & merge
        }
    }

    static void merge_sort(int* unsorted, int size) {
        mergesort(unsorted, 0, size - 1);
    }

    /*-----------------------combined sort (insertion & merge) ------------------------*/

    static void insertion_sort(int* unsorted, int left, int right) { // overloaded insertion sort for setting the range of subarrays
        for (int i = left; i <= right; i++) {
            int key = unsorted[i];
            int j = i - 1;
            while (j >= left && unsorted[j] > key) {
                unsorted[j + 1] = unsorted[j];
                j -= 1;
            }
            unsorted[j + 1] = key;
        }
    }

    static void combinedsort(int* unsorted, int left, int right, int threshold) { // use revised insertion algorithm for sorting small subarrays.
        if (left < right) {
            if (right - left + 1 <= threshold) { // if the total counts of numbers in subarrays are smaller than the threshold, use insertion sort method
                insertion_sort(unsorted, left, right);
            }
            else {
                int mid = (right + left) / 2;

                combinedsort(unsorted, left, mid, threshold);
                combinedsort(unsorted, mid + 1, right, threshold); // do the normal merge sort algorithm for bigger parts (splitting)

                merge(unsorted, left, mid, right); 
            }
        }
    }

    static void combined_sort(int* unsorted, int size) {
        combinedsort(unsorted, 0, size - 1, 10); // setting the threshold as 10
    }

};

int main(int argc, char* argv[]) { // execute in CLI with "compiledname", "inputfile", "outputfile"

    /*----------check number of arguments -------------------------------------------------*/

    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return 1;
    }

    /*------------------------check input file opened--------------------------------------*/

    std::ifstream input_file(argv[1]);

    if (!input_file.is_open()) {
        std::cerr << "Error opening input file: " << argv[1] << std::endl;
        return 1;
    }

    /*------------------------------get data from input.txt---------------------------*/

    int input_size;
    input_file >> input_size; // get the number of input (first line)

    int* input_array = new int[input_size]; // array for storing unsorted numbers

    for (int i = 0; i < input_size; ++i) { // get the unsorted numbers (second line)
        input_file >> input_array[i];
    }

    input_file.close();

    /*-------------copy the input value for each method --------------*/

    int* insertion_input = new int[input_size];
    int* merge_input = new int[input_size];
    int* combined_input = new int[input_size];

    for (int i = 0; i < input_size; ++i) {
        insertion_input[i] = input_array[i];
        merge_input[i] = input_array[i];
        combined_input[i] = input_array[i];
    }

    /*------------------------------- sort -----------------------------------------*/

    Sorting::insertion_sort(insertion_input, input_size);
    Sorting::merge_sort(merge_input, input_size);
    Sorting::combined_sort(combined_input, input_size);

    /*---------------make the output.txt and check ------------------*/

    std::ofstream output_file(argv[2]);

    if (!output_file.is_open()) {
        std::cerr << "Error opening output file." << std::endl;
        return 1;
    }

    /*--------------------print insertion sort values --------------------------------*/

    for (int i = 0; i < input_size - 1; ++i)
        output_file << insertion_input[i] << " ";
    output_file << insertion_input[input_size - 1] << std::endl;

    /*--------------------print merge sort values --------------------------------*/

    for (int i = 0; i < input_size - 1; ++i)
        output_file << merge_input[i] << " ";
    output_file << merge_input[input_size - 1] << std::endl;

    /*--------------------print combinded sort values --------------------------------*/

    for (int i = 0; i < input_size - 1; ++i)
        output_file << combined_input[i] << " ";
    output_file << combined_input[input_size - 1];

    /*------------------- free allocated memory & close output file ---------------------*/

    delete[] input_array;
    delete[] insertion_input;
    delete[] merge_input;
    delete[] combined_input;

    output_file.close();

    return 0;
}
