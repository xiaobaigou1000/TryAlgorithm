#include "foolsort.h"
#include "space_complexity.h"

int main()
{
    // calculateSpaceComplexity(50000, 5000, 60, 1, "pre", FoolSort::inplace_AVLSort<size_t>);
    // calculateSpaceComplexity(500000, 50000, 60, 1, "avl_sc", FoolSort::inplace_AVLSort<size_t>);
    // calculateSpaceComplexity(500000, 50000, 60, 1, "quick_sc", FoolSort::inplace_quickSort<size_t>);
    calculateSpaceComplexity(500000, 50000, 60, 1, "merge_sc", FoolSort::inplace_mergeSort<size_t>);
}
