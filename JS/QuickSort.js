`use strict`;

/**
 * Divide and conquer approach to sorting an array in ascending order.
 * 
 * partition the array until the sorting is trivial.
 * 
 * In place with Θ(1) space usage.
 * Worst:   n^2.
 * Avg/exp: n * log(n).
 * Best:    n * log(n).
 * 
 * @param {Array} arr
 *        The array to sort.
 */
function quickSort(arr) {
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
        /**
         * Swaps two elements in the inner array.
         * 
         * Uses the space of a element to hold a temp value.
         * 
         * @param {Number} i
         *        The element (index) to swap.
         * @param {Number} j
         *        The element (index) to swap.
         */
        function swap(i, j) {
            let temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }

        /**
         * Partitions a subarray of arr.
         * 
         * @param {Number} left
         *        The start index of the sub array.
         * @param {Number} right
         *        The end index of the subarray.
         */
        function partition(left, right) {
            let pivot = arr[right];
            let i = left;
            /* Move through the sub array and create the partition */
            for(let j = left; j <= right - 1; j++) {
                if(arr[j] <= pivot) {
                    /* Move it down to the "smaller than" partition */
                    swap(i, j);
                    i++;
                }
            }
            /* Move the pivot element to the middle */
            swap(i, right);
            return i;
        }

        if(left < right) {
            let q = partition(left, right);
            sort(left, q - 1);
            sort(q + 1, right);
        }
    }

    sort();
}