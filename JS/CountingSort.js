`use strict`;

/**
 * Incremental sorting by using counting and no comparisons.
 * 
 * Θ(k + n) space usage.
 * Worst:   k + n.
 * Avg/exp: k + n.
 * Best:    k + n.
 * 
 * @param {Array} arr
 *        The array to sort.
 * @param {Number} kNumbers
 *        arr is [0...kNumbers]. kNumbers = max(arr) + 1 because 0 is accounted for.
 */
function countingSort(arr, kNumbers) {
    let sorted = new Array(arr.length);
    let counted = new Array(kNumbers);
    
    /* Set all the empty elements to number 0 */
    for(let i = 0; i < counted.length; i++) {
        counted[i] = 0;
    }

    /* Count the array */
    for(let i = 0; i < arr.length; i++) {
        counted[arr[i]]++;
    }

    /* Accumulate the counted array */
    for(let i = 1; i < counted.length; i++) {
        counted[i] = counted[i] + counted[i - 1];
    }

    /* Create the sorted array */
    for(let i = arr.length - 1; i >= 0; i--) {
        sorted[counted[arr[i]] - 1] = arr[i];
        counted[arr[i]]--;
    }
    
    return sorted;
}