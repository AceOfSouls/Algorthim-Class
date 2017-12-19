//Sergio Fernandes
//12/6/2017
//IT 485-005
//
//This File is used to test out Timsort and to see how it can sort a multitude of Socal Security Numbers.
//It uses 3 different test case arrays, one already sorted, one randomly sorted and one reverse order.
import java.util.Random;
import java.util.Arrays;

public class TTest
{
	public static void main(String[] args)
	{
		String[] sortedArray = new String[10000];
		String[] unsortedArray = new String[10000];
		String[] reverseArray = new String[10000];
		Random rng = new Random();
		
		for(int i = 0; i < sortedArray.length; i++)
		{
			if(i<10)
			{
				sortedArray[i] = "00000000" + i;
			}
			else if(i<100)
			{
				sortedArray[i] = "0000000" + i;
			}
			else if(i < 1000)
			{
				sortedArray[i] = "000000" + i;
			}
			else if(i<10000)
			{
				sortedArray[i] = "00000" + i;
			}
			else if(i<100000)
			{
				sortedArray[i] = "0000" + i;
			}
			else if(i<1000000)
			{
				sortedArray[i] = "000" + i;
			}
			else if(i<10000000)
			{
				sortedArray[i] = "00" + i;
			}
			else if(i<100000000)
			{
				sortedArray[i] = "0" + i;
			}
			else
			{
				sortedArray[i] = "" + i;
			}
		}
		
		for(int i = 0; i < unsortedArray.length; i++)
		{
			unsortedArray[i] = "" + rng.nextInt(10) + rng.nextInt(10) + rng.nextInt(10) + rng.nextInt(10) + 
					rng.nextInt(10) + rng.nextInt(10) + rng.nextInt(10) + rng.nextInt(10) + rng.nextInt(10);
		}
		
		int count = 999999999;
		for(int i = 0; i < reverseArray.length; i++)
		{
			if(count<10)
			{
				reverseArray[i] = "00000000" + count;
			}
			else if(count<100)
			{
				reverseArray[i] = "0000000" + count;
			}
			else if(count < 1000)
			{
				reverseArray[i] = "000000" + count;
			}
			else if(count<10000)
			{
				reverseArray[i] = "00000" + count;
			}
			else if(count<100000)
			{
				reverseArray[i] = "0000" + count;
			}
			else if(count<1000000)
			{
				reverseArray[i] = "000" + count;
			}
			else if(count<10000000)
			{
				reverseArray[i] = "00" + count;
			}
			else if(count<100000000)
			{
				reverseArray[i] = "0" + count;
			}
			else if(count < 0)
			{
				count = 999999999;
			}
			else
			{
				reverseArray[i] = "" + count;
			}
			count--;
		}
		
		
		//First lets print a couple of the array values from each to compare the end results
		System.out.println();
		System.out.print("Sorted array pattern: ");
		for(int i = 0; i < 5; i++)
		{
			System.out.print(sortedArray[i] + " -> ");
		}
		System.out.print(sortedArray[6] + "... etc.");
		System.out.println();
		System.out.println("----------------------------------------------------------------------------------------------------------------------------------");
		System.out.println();
		
		System.out.print("Randomly sorted array pattern: ");
		for(int i = 0; i < 5; i++)
		{
			System.out.print(unsortedArray[i] + " -> ");
		}
		System.out.print(unsortedArray[6] + "... etc.");
		System.out.println();
		System.out.println();
		System.out.println("This array will cannot have 2 of the same values since social security numbers do not repeat.");
		System.out.println("----------------------------------------------------------------------------------------------------------------------------------");
		System.out.println();
		
		System.out.print("Reverse sorted array pattern: ");
		for(int i = 0; i < 5; i++)
		{
			System.out.print(reverseArray[i] + " -> ");
		}
		System.out.print(reverseArray[6] + "... etc.");
		System.out.println();
		System.out.println("----------------------------------------------------------------------------------------------------------------------------------");
		System.out.println();
		
		
		
		//Now lets see it sorted using timsort as well as the count

		TimSort sort1 = new TimSort();
		TimSort sort2 = new TimSort();
		TimSort sort3 = new TimSort();
		
		System.out.print("Sorted array after Sorting: ");
		sortedArray = sort1.sort(sortedArray);
		for(int i = 0; i < 20; i++)
		{
			System.out.print(sortedArray[i] + " ");
		}
		System.out.println();
		System.out.println("----------------------------------------------------------------------------------------------------------------------------------");
		System.out.println();
		System.out.println("The ammount of times it had traversed is: " + sort1.getCount());
		System.out.println();

		System.out.print("Unsorted array after Sorting: ");
		unsortedArray = sort2.sort(unsortedArray);
		for(int i = 0; i < 20; i++)
		{
			System.out.print(unsortedArray[i] + " ");
		}
		System.out.println();
		System.out.println("----------------------------------------------------------------------------------------------------------------------------------");
		System.out.println();
		System.out.println("The ammount of times it had traversed is: " + sort2.getCount());
		System.out.println();
		
		System.out.print("Reversed array after Sorting: ");
		reverseArray = sort3.sort(reverseArray);
		for(int i = 0; i < 20; i++)
		{
			System.out.print(reverseArray[i] + " ");
		}
		System.out.println();
		System.out.println("----------------------------------------------------------------------------------------------------------------------------------");
		System.out.println();
		System.out.println("The ammount of times it had traversed is: " + sort3.getCount());
		System.out.println();
	}
}