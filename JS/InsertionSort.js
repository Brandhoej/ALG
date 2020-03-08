'use strict';

/**
 * Sorts an array using the insertion sort algorithm.
 * 
 * In place with Θ(1) space usage.
 * Worst case:   Θ(n^2).
 * Avg/exp case: Θ(n^2).
 * 
 * @param {Array} arr
 *        A sequence of n numbers stored in an array
 */
function insertionSort(arr) {
    /* Index of sorted sub array */
    for(let j = 1; j < arr.length; j++) {
        let key = arr[j];
        let i = j - 1;
        /* 
         * Ensure the maintenance condition: From 0 to j the array is in sorted order.
         * This is done by moving the key down until it reaches an ith element which is greater.
         */
        while(i >= 0 && arr[i] > key) {
            arr[i + 1] = arr[i];
            i--;
        }
        arr[i + 1] = key;
    }
}