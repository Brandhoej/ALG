'use strict';

/**
 * Divide and conquer approach to sorting an array in ascending order.
 * 
 * The array is split in half recursively until they are trivial.
 * Then they are sorted by moving up the tree.
 * 
 * Θ(n) space usage.
 * Worst:   n * log(n).
 * Avg/exp: n * log(n).
 * Best:    n * log(n).
 * 
 * @param {Array} arr
 *        The array to sort.
 */
function mergeSort(arr) {
    /**
     * Marges the subarray spanning [left, right].
     * 
     * @param {Number} left
     *        The start index of the first sub array.
     * @param {Number} mid
     *        The end index the first sub array. mid + 1 is start index of the second subarray.
     * @param {Number} right
     *        The end index of the second subarray.
     */
    function merge(left, mid, right) {
        /* 
         * The sort recursive step for the left half includes the middle.
         * Because of this the length is + 1.
         */
        let leftSubArr  = arr.slice(left, mid + 1);
        let rightSubArr = arr.slice(mid + 1, right + 1);

        let leftIndex  = 0;
        let rightIndex = 0;
        
        /**
         * Merge the elements to the array.
         */
        for(let k = left; k <= right; k++) {
            if(rightIndex == rightSubArr.length || 
               leftIndex < leftSubArr.length && leftSubArr[leftIndex] <= rightSubArr[rightIndex]) {
                arr[k] = leftSubArr[leftIndex++];
            }
            else {
                arr[k] = rightSubArr[rightIndex++];
            }
        }
    }
    
    /**
     * The function used for the recursive calls.
     * 
     * Sorts a subarray delimited in arr by left and right (indices).
     * 
     * @param {Number} [left=0]
     *        The start index of the subarray in arr.
     * @param {Number} [right=arr.length - 1]
     *        The end index of the subarray in arr.
     */
    function sort(left = 0, right = arr.length - 1) {
        if(left < right) {
            let mid = Math.floor((left + right) / 2.0);
            sort(left, mid);
            sort(mid + 1, right);
            merge(left, mid, right);
        }
    }

    /* Calls the sort function which handles the recursion of Merge Sort */
    sort();
}