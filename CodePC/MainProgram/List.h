#pragma once
#include <iterator> // For std::forward_iterator_tag
#include <cstddef>  // For std::ptrdiff_t

template <typename T>
class List final
{
private:
	size_t length = 0;
	unsigned int capacity = 0;

public:
	T* arr = nullptr;

	//add object to List
	void Add(T value)
	{
		//check if need to expand
		if (length >= capacity)
		{
			capacity = (capacity == 0) ? capacity = 4 : capacity *= 2;

			T* oldArray = arr;
			arr = new T[capacity];

			//copy value to new array
			for (unsigned int i = 0; i < length; i++)
				arr[i] = oldArray[i];

			delete[] oldArray;
			arr[length] = value;
			length++;
		}
		else
		{
			arr[length] = value;
			length++;
		}
	}
	//insert object at index
	void Insert(T value, unsigned int atIndex)
	{
		//check if need to expand
		if (length >= capacity)
		{
			capacity = (capacity == 0) ? capacity += 1 : capacity *= 2;

			T* oldArray = arr;
			arr = new T[capacity];

			//copy value to new array
			for (unsigned int i = 0; i < length; i++)
			{
				if (i == atIndex)
				{
					arr[i] = value;
					for (unsigned int k = i; k < length; k++)
					{
						arr[k + 1] = oldArray[k];
					}
					break;
				}
				else
				{
					arr[i] = oldArray[i];
				}
			}

			delete[] oldArray;
			length++;
		}
		else
		{
			arr[length] = value;
			length++;
		}
	}
	//swap array element
	void Swap(unsigned int fromIndex, unsigned int toIndex)
	{
		T temp = arr[fromIndex];
		arr[fromIndex] = arr[toIndex];
		arr[toIndex] = temp;
	}

	//get object by index
	T Get(unsigned int index)
	{
		return arr[index];
	}
	// operator[], use as arr[index]
	T& operator[](const unsigned int index) const
	{
		return *(arr + index);
	}

	//set object at index
	void Set(T value, unsigned int index)
	{
		if (index < length && index >= 0)
			arr[index] = value;
	}

	//return -1 if not found
	unsigned int GetIndex(T value)
	{
		for (unsigned int i = 0; i < length; i++)
			if (value == arr[i])
				return i;
		return -1;
	}

	//resize array size/length
	void ReSize(unsigned int newSize)
	{
		if (capacity < newSize)
		{
			//expand array
			capacity = newSize;
			length = newSize;

			T* oldArray = arr;
			arr = new T[capacity];

			//copy value to new array
			for (unsigned int i = 0; i < length; i++)
				arr[i] = oldArray[i];

			//delete old array
			delete[] oldArray;
		}
		else
		{
			length = newSize;
		}
	}
	//resize array capacity
	void ReSizeCapacity(unsigned int newSize)
	{
		if (length > newSize)
			length = newSize;

		capacity = newSize;

		T* oldArray = arr;
		arr = new T[capacity];

		//copy value to new array
		for (unsigned int i = 0; i < length; i++)
			arr[i] = oldArray[i];

		delete[] oldArray;
	}

	//delete/destroy object from List
	void Delete(T value)
	{
		for (unsigned int i = 0; i < length; i++)
		{
			//found object
			if (arr[i] == value)
			{
				length--;
				//check array count is bigger than 0
				if (length > 0)
				{
					//push up rest array index by 1
					for (unsigned int k = i; k < length; k++)
						arr[k] = arr[k + 1];
				}
				return;
			}
		}
	}
	//delete/destroy index from List
	void DeleteAt(unsigned int index)
	{
		//index cant be negative value
		if (index >= 0)
		{
			length--;
			//check array count is bigger than 0
			if (length > 0)
			{
				//push up rest array index by 1
				for (unsigned int i = 0; i < length; i++)
					arr[i] = arr[i + 1];
			}
		}
	}

	//get length/size/number/count of List
	unsigned int Length()
	{
		return length;
	}
	//get capacity of List
	unsigned int Capacity()
	{
		return capacity;
	}

	//get the array pointer, please dont modify the array
	T* GetArray()
	{
		return arr;
	}

	//clear array cap and size to zero
	void Clear()
	{
		length = 0;
		if (capacity > 0)
			delete[] arr;
		capacity = 0;
	}

	//invert list, first to last, last to first
	void Invert()
	{
		if (length >= 2)
		{
			for (unsigned int i = 0; i < length - 1 - i; i++)
			{
				Swap(i, length - 1 - i);
			}
		}

	}

	//default constructor
	List()
	{

	}
	//copy constructor
	List(const List& org) 
	{ 
		length = org.length;
		capacity = org.capacity;
		arr = new T[capacity];

		//copy value to new array
		for (unsigned int i = 0; i < length; i++)
			arr[i] = org.arr[i];

	}
	//destructor
	~List()
	{
		Clear();
	}
};