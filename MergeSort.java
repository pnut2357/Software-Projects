/***************************************************************************************************
 * CLASS: MergeSort (MergeSort.java)
 *
 * DESCRIPTION
 * MergeSort Class sorts an array-list in ascending or descending order by using the merge sort 
 * algorithm. Instead of copying the unsorted list as pieces of sublists, the class uses the 
 * indices of the original unsorted list for division. 
 * 
 * COURSE AND PROJECT INFO
 * CSE205 Object Oriented Programming and Data Structure, 2019 Spring
 * Project Number: project 03
 *
 * AUTHOR
 * @author Jaehyuk Choi, jchoi154, jchoi154@asu.edu
 **************************************************************************************************/
import java.util.ArrayList;

/**
 * This class sorts an {@code ArrayList<E>} list using the merge sort algorithm. It
 * implements the algorithm recursively and uses list indices to for sublists. This avoids having
 * to copy elements from a list being sorted into left and right sublists within mergeSort(). With
 * this implementation, the only new list which we have to create is the list in merge() which is
 * formed by copying elements from the two sublists being merged.
 *
 * @author Jae H. Choi
 */
public class MergeSort<E extends Comparable<? super E>> 
{	
    /**
     * Pass as the second argument to sort() to sort the list into ascending order.
     */
	public final int ASCENDING = 0;

    /**
     * Pass as the second argument to sort() to sort the list into descending order.
     */
	public final int DESCENDING = 1;

    /**
     * Stores the sort order parameter pOrder to sort().
     */
	private int mOrder;
	
    /**
     * CONSTRUCTOR MERGESORT
     * This default ctor does nothing.
     */
	public MergeSort()
	{
		// empty constructor. 
	}
        
    /**
     * METHOD SORT
     * Called to sort an {@code ArrayList<E>} list into ascending order. Usage:
     *
     * <pre>{@code
     * // Declare a MergeSort<Integer> object named 'sorter' which will sort an ArrayList<Integer>
     * // list.
     * MergeSort<Integer> sorter = new MergeSort<>();
     *
     * // Call the sort() method on sorter to sort the list.
     * sorter.sort(myArrayListOfIntegers);
     * }</pre>
     *
     * Does not return a value, but upon return from this method, pList will be sorted into
     * descending order.
     *
     * @param pList The {@code ArrayList<E>} list being sorted.
     * @param pOrder Either ASCENDING or DESCENDING to specify the sort order.
     */
	public void sort (ArrayList<E> pList, int pOrder)
	{
		// stores the what order the user wants. 
		mOrder = pOrder;
		// calls the method mergeSort() from index 0 to index pList.size()-1
		mergeSort(pList, 0, pList.size()-1);
	}
        
    /**
     * METHOD ARRAYLISTREPLACE
     * pSrcList is an {@code ArrayList<E>} list which contains pSrcList.size() elements which are going to
     * replace the elements in pDstList starting at index pFromIdx of pDstList.
     *
     * @param pDstList The destination list where the elements are going to be replaced.
     * @param pFromIdx The index within pDstList where the elements will start being replaced.
     * @param pSrcList The list containing the objects which will replace those in pDstList.
     */
	private void arrayListReplace (ArrayList<E> pDstList, int pFromIdx, ArrayList<E> pSrcList)
	{
		// replaces the part of a destination list with a source list at the index of the destination list. 
		for (int idx=0; idx < pSrcList.size(); ++idx)
			pDstList.set(pFromIdx+idx,pSrcList.get(idx));
	}
	
    /**
     * METHOD MERGESORT
     * This is the primary recursive mergeSort() method.
     *
     * pList is the entire list. pFromIdx and pToEnd are the indices of a sublist of pList which
     * will be sorted. For example, supposed pList is { 9 8 7 6 5 4 3 2 1 }, pFromIdx is 3, and
     * pToIdx is 7. This method will sort the elements of pList at indices 3, 4, 5, 6, 7. Upon
     * return from this method, those elements within pList will be sorted, although the other
     * elements in pList will remain untouched.
     *
     * @param pList The {@code ArrayList<E>} list which will is being sorted.
     * @param pFromIdx The index of the first element of the sublist being sorted.
     * @param pToIdx The index of the last element of the sublist being sorted.
     */
	private void mergeSort (ArrayList<E> pList, int pFromIdx, int pToIdx)
	{
		// sets up the subList = pFromIdx - pToIdx + 1
		int listSize = pToIdx - pFromIdx + 1;
		if (listSize < 2) return;
		
		// divides the pList into two sublists.
		int midIdx = pFromIdx + listSize/2,
			lBegIdx = pFromIdx,
			lEndIdx = midIdx - 1,
			rBegIdx = lEndIdx + 1,
			rEndIdx = pToIdx;
		
		// Recursive call for left sublist. 
		mergeSort(pList, lBegIdx, lEndIdx);
		// Recursive call for right sublist.
		mergeSort(pList, rBegIdx, rEndIdx);
		
		// calls the method arrayListReplace() to replace the unsorted list with sorted list by merge().
		arrayListReplace(pList, pFromIdx, merge(pList, lBegIdx, lEndIdx, rBegIdx, rEndIdx));
	}
	
    /**
     * METHOD MERGE
     * This method merges two sublists of pList. The left sublist consists of those elements at
     * indices pLBegIdx..pLEndIdx. The right sublist consists of the elements at pRBegIdx..pREndIdx.
     *
     * @param pList The entire list which is being merge sorted.
     * @param pLBegIdx The index of the first element of the left sublist being merged.
     * @param pLEndIdx The index of the last element of the left sublist being merged.
     * @param pRBegIdx The index of the first element of the right sublist being merged.
     * @param pREndIdx The index of the last element of the right sublist being merged.
     *
     * @return A new {@code ArrayList<E>} list which consists of the elements in the left and right
     * sublists. This list is sorted into ascending order.
     */
    private ArrayList<E> merge (ArrayList<E> pList, int pLBegIdx, int pLEndIdx, int pRBegIdx, int pREndIdx) 
    {
    	// creates mergedList as an arraylist.
        ArrayList<E> mergedList = new ArrayList<>();
        
        // sets up lIdx starts from pLBegIdx and rIdx starts from pRBegIdx.
        int lIdx = pLBegIdx, 
        	rIdx = pRBegIdx;
        
        while (lIdx <= pLEndIdx && rIdx <= pREndIdx) 
        {
        	// Ascending order
        	boolean copyFromLeft = (pList.get(lIdx)).compareTo(pList.get(rIdx)) <= 0;
        	
        	// Descending order
        	if (mOrder == DESCENDING)
        	{
        		copyFromLeft = (pList.get(lIdx)).compareTo(pList.get(rIdx)) > 0;
        	}
        	
        	// depending on the list's order, each element is added in order. 
            if (copyFromLeft) {
                mergedList.add(pList.get(lIdx++));
            } else {
                mergedList.add(pList.get(rIdx++));
            }
        }
        // in the case that lIdx is left to be sorted.
        if (lIdx <= pLEndIdx) 
        {
            while (lIdx <= pLEndIdx) 
            {
                mergedList.add(pList.get(lIdx++));
            }
        } 
        else // in the case that rIdx is left to be sorted.
        {
            while (rIdx <= pREndIdx) 
            {
                mergedList.add(pList.get(rIdx++));
            }
        }
        
        return mergedList;
    }
    
}
