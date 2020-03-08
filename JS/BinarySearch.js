'use strict';

/**
 * Uses the binary search to look for a key element in the array.
 * 
 * In place with Θ(1) space usage.
 * Worst:   lg n.
 * Avg/exp: lg n.
 * Best:    1.
 * 
 * @param {Array} arr
 *        A sorted array of numbers.
 * @param {Number} key
 *        The key element value to search for
 * @return {Number}
 *         the index of the key. If not found then -1.
 */
function binarySearch(arr, key) {
    function search(left = 0, right = arr.length - 1) {
        /*
         * Check if the the search range is still correct. 
         * If not then the item is not in the array
         */
        if(arr[left] > key || arr[right] < key || left > right) {
            return -1;
        }

        let mid = Math.floor((left + right) / 2.0);

        if(arr[mid] == key) {
            return mid;
        }
        else if(arr[mid] > key) {
            return search(left, mid - 1);
        }
        else if(arr[mid] < key) {
            return search(mid + 1, right);
        }
    }
    return search();
}