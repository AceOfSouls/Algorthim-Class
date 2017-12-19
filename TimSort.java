//Sergio Fernandes
//12/6/2017
//IT 485-005
//
//This file is the TimSort class

public class TimSort 
{	
	int count;
	private static final int RUN = 64;
	
	public TimSort()
	{
		count = 0;
	}
	
	// checks array from left to right
	private void insertionSort(String arr[], int left, int right)
	{
		for(int i = left + 1; i <= right; i++)
		{
			String temp = arr[i];
			int j = i - 1;
			while(Integer.parseInt(temp) < Integer.parseInt(arr[j]) && j > left)
			{
				arr[j+1] = arr[j];
				j--;
			}
			arr[j+1] = temp;
		}
	}
	
	private void merge(String temp[], String arr[], int left, int mid, int right)
	{
		int i = left;
		int j = mid + 1;
		int k = left;
		while(i <= mid && j <= right)
		{
			if(Integer.parseInt(arr[j]) > Integer.parseInt(arr[i]))
			{
				temp[k++] = arr[i++];
			}
			else
			{
				temp[k++] = arr[j++];
			}
		}
		
		while(i <= mid)
		{
			temp[k++] = arr[i++];
		}
	}
	
	
	public String[] sort(String[] data)
	{
		resetCount();
		String[] output = data;
		//get the values of the strings and the index and put it into a pair
		
		//Uses insertion sort for small arrays
		if(data.length <= RUN)
		{
			for(int i = 0; i < data.length; i += RUN)
			{
				insertionSort(output, i, Math.min((i+31),(data.length - 1)));
				count++;
			}
			return output;
		}
		// Here it starts implementing merge sort like feature
		// starting from the size value of what RUN is it will merge
		// to form size 64, 128, 256 ... 
		for(int size = 1; size < data.length; size = (2*size))
		{
			for(int left = 0; left < data.length - size; left += (2*size))
			{
				int mid = left + size - 1;
				int right = Math.min((left + (2*size) - 1), (data.length - 1));
				
				merge(output , data, left, mid, right);
				count++;
			}
		}
		return output;
	}

	public int getCount()
	{
		return count;
	}
	
	private void resetCount()
	{
		count = 0;
	}
}


/*int len1 = (mid - (left + 1));
		int len2 = (right - mid);
		
		Pair[] L = new Pair[len1];//Left
		Pair[] R = new Pair[len2];//Right
		
		for(int i = 0; i < len1; i++)
		{
			L[i] = arr[left + i];
		}
		for(int i = 0; i < len2; i++)
		{
			R[i] = arr[mid + 1 + i]; 
		}
		
		int i = 0;
		int j = 0;
		int k = 1;
		//Compare the values
		while(i < len1 && j < len2)
		{
			if(L[i].getValue() <= R[j].getValue())
			{
				arr[k] = L[i];
				i++;
			}
			else
			{
				arr[k] = R[j];
				j++;
			}
			k++;
		}
		
		//Fill in the rest of the left side
		while (i < len1)
		{
			arr[k] = L[i];
			k++;
			i++;
		}
		
		//Fill in the rest of the right side
		while (j < len2)
		{
			arr[k] = R[j];
			k++;
			j++;
		}*/