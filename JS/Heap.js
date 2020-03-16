`use strict`;

/**
 * A complete binary tree data structure.
 * 
 * For all nodes i > 0 the parent is greater.
 */
class MaxHeap {

    /**
     * initializes this heap with a inner array and builds it.
     * 
     * @class
     *        constructs a MaxHeap.
     * @param {Array} arr
     *        The initial inner array of the max heap.
     */
    constructor(arr) {
        this._arr = arr;

        if(this.length > 0) {
            this.buildMaxHeap();
        }
    }

    /**
     * @return the length of the inner array.
     */
    get length() {
        return this._arr.length;
    }

    /**
     * Sorts the inner array. 
     * 
     * After this call it is guranteed that the inner array is not only a max heap.
     * But the sequence of the elements are also in sorted order.
     * 
     * In place with Θ(1) space usage.
     * Worst:   n * log(n).
     * Avg/exp: n * log(n).
     * Best:    n * log(n).
     * 
     * The space is in place. Because when an element is removed another element is added in the sorted array.
     * Because of this it is constant.
     * 
     */
    sort() {
        /* 
         * Assumes it meets the criteria of a max heap.
         * Because of this we don't need to build the max heap.
         * Otherwise: buildMaxHeap();
         */

         let sorted = [];
         /*
          * heapify from the bottom up. To ensure an ascending order of the inner array.
          */
         for(let i = this.length; i >= 1; i--) {
             /* Place the highest element (first element) from the heap to the end of the sorted array */
            sorted.push(this._arr.shift());
            /* Ensure that the maxHeap properties are true after the removal of the root */
            this.maxHeapify(0);
         }
         this._arr = sorted;
    }

    /**
     * Builds the maxHeap by going from the bottom up and maxHeapify.
     * 
     * Runs Θ(n), not O(n lg n).
     */
    buildMaxHeap() {
        /* 
         * We can split the length by 2 because
         * the leafs always accounts for half the elements in the binary tree.
         */
        for(let i = Math.floor(this.length / 2); i >= 0; i--) {
            this.maxHeapify(i);
        }
    }

    /**
     * float down the elements in the maxHeap does not meet the criterias starting from ith element.
     * Also known as float down.
     * 
     * This does not ensure that the heap is a maxHeap. Use buildMaxHeap for that.
     * Runs O(lg n).
     * 
     * @param {Number} i
     *        The index to start the heapifying.
     */
    maxHeapify(i) {
        let l = this.leftChild(i);
        let r = this.rightChild(i);
        let largest = i;

        /* Checks if t is in the array and if it is larger than the element at largest (index) */
        const checkIfLargest = (t) => t >= 0 & t < this.length && this.get(t) > this.get(largest);

        /* Check if any of the children are larger */
        if(checkIfLargest(l)) {
            largest = l;
        }
        if(checkIfLargest(r)) {
            largest = r;
        }

        /* If a child was found to be larger. Then swap them move down the tree */
        if(largest != i) {
            this._swapElements(i, largest);
            this.maxHeapify(largest);
        }
    }

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
    _swapElements(i, j) {
        let temp = this.get(i);
        this._arr[i] = this.get(j);
        this._arr[j] = temp;
    }

    /**
     * Adds an element to the heap.
     * 
     * Pushes the new element to the inner array and makes it float up.
     * Average: O(1) but worst is O(lg n).
     * 
     * @param {Number} e
     *        The element to add.
     */
    add(e) {
        let i = this._arr.push(e) - 1;

        /* 
         * Swap element with parent if the parent is greater.
         * Recursively continue until the parent is smaller than 0.
         * Arrow function is used because of access to "this."
         */
        const floatUp = (j = i) => {
            let parent = this.parent(j);
            if(parent >= 0 && e > this.get(parent)) {
                this._swapElements(j, parent);
                floatUp(parent);
            }
        }
        
        floatUp();
    }

    /**
     * Removes and returns the root element.
     * 
     * Runs O(lg n).
     * 
     * @return the root element.
     */
    remove() {
        /* Swap the greatest element (root) with one of the smallest */
        this._swapElements(0, this.length - 1);
        /* Use .pop becuase after the swap the root is the end element */
        let root = this._arr.pop();
        /* Since the current root is now a previously leaf we can just maxHeapify by the root. */
        this.maxHeapify(0);
        return root;
    }

    /**
     * retrieves the element in the inner array at i.
     * 
     * @param {Number} i
     *        The element index of the inner array.
     * @return the element at i.
     */
    get(i) {
        return this._arr[i];
    }

    /**
     * @param {Number} i
     *        The index to get the parent for.
     * @return The parent index in the inner array. if the parent is outside then it is negative.
     */
    parent(i) {
        return Math.floor((i - 1) / 2.0);
    }

    /**
     * @param {Number} i
     *        The index to get the left child for.
     * @return The left child index in the inner array.
     */
    leftChild(i) {
        return (i << 1) + 1;
    }

    /**
     * @param {Number} i
     *        The index to get the right child for.
     * @return The right child index in the inner array.
     */
    rightChild(i) {
        return (i << 1) + 2;
    }

    /**
     * @return The string representation of the inner array.
     */
    toString() {
        return this._arr.toString();
    }
}