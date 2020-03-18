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
 * @param {Function} cmp
 *        the compare function used on element element and key. returns are -1, 0, 1
 * @return {Number}
 *         the index of the key. If not found then -1.
 */
function binarySearch(arr, key, cmp) {
    function search(left = 0, right = arr.length - 1) {
        /*
         * Check if the the search range is still correct.
         * Does not work with current implementation
         * If not then the item is not in the array
         */
        // if(arr[left] > key || arr[right] < key || left > right) {
        //     return -1;
        // }

        let mid = Math.floor((left + right) / 2.0);
        
        let cmpRes = cmp(arr[mid], key);
        
        if(cmpRes === 0) {
            return mid;
        }
        else if(cmpRes === -1) {
            return search(left, mid - 1);
        }
        else if(cmpRes === 1) {
            return search(mid + 1, right);
        }
    }
    return search();
}