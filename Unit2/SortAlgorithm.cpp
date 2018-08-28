#include <stdio.h>
#include <map>
#include <string>
#include <functional>
#include <xrefwrap>

template<typename T>
void swap(T& a, T&b)
{
    T temp = a;
    a = b;
    b = temp;
}

//冒泡
/*
    两两比较，大的后移，一次循环之后最后一位最大
*/
void bubbleSort(int arr[], int nLen)
{
    for (int i = 0; i < nLen; ++i)
    {
        bool bExchange = false; //优化，若一次循环没有任何改变，即当前有序。
        for (int j = 0; j < nLen - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
                bExchange = true;
            }
        }
        if (!bExchange)
        {
            return;
        }
    }
}

//选择
/*
    选择最大的元素，将其与最后一个元素交换
*/
void selectSort(int arr[], int nLen)
{
    for (int i = 0; i < nLen; ++i)
    {
        int nMax = 0;
        for (int j = 1; j < nLen -i; ++j)
        {
            if (arr[j] > arr[nMax])
            {
                nMax = j;
            }
        }
        swap(arr[nMax], arr[nLen - i -1]);
    }
}

//插入
/*
    将元素往前面有序区间插入，起始有序区间为arr[0]
    最理想情况为数组初始即为有序，插入排序速度即为O(n)
*/
void insertSort(int arr[], int nLen)
{
    for (int i = 1; i < nLen; ++i)
    {
        int j = i;
        while (j > 0)
        {
            if (arr[j] < arr[j - 1])
            {
                swap(arr[j], arr[j - 1]);
                --j;
            }
            else
                break;
        }
    }
}

//希尔
/*
    希尔是插入排序的优化，希尔通过一个步距将数组分组，分别对每一组进行插入排序
    然后缩小步距，再对每一组进行插入排序，最终步距为1，插入排序完成即为有序数组
    这样数组快速的成为有序，最后一次插入排序速度非常快
*/
void shellSort(int arr[], int nLen)
{
    int gap = nLen / 2;//初始步距
    for (; gap > 0; gap /=2)    //步距每次递减一半，下面是插入排序
    {
        for (int i = gap; i < nLen; ++i)
        {
            int j = i;
            while (j >= gap)
            {
                if (arr[j] < arr[j - gap])
                {
                    swap(arr[j], arr[j - gap]);
                    j -= gap;
                }
                else
                    break;
            }
        }
    }
}

//归并
/*
    归并是通过分治法将数组分为若干个有序数组，对两个有序数组合并为一个有序数组
    因此归并要将数组划分为一个元素，然后不停地合并
*/
void mergeArr(int arr[], int nL, int nM, int nR)
{
    int nLen = nR - nL + 1;
    int *temp = new int[nLen];
    int i = nL, j = nM + 1, n = 0;
    while (i <= nM && j <= nR)
    {
        temp[n++] = arr[i] > arr[j] ? arr[j++] : arr[i++];
    }
    while (i <= nM)
    {
        temp[n++] = arr[i++];
    }
    while (j <= nR)
    {
        temp[n++] = arr[j++];
    }
    for (n = 0; n < nLen; ++n)
    {
        arr[nL++] = temp[n];
    }
    delete [] temp;
}

//递归归并
void mergeSort1(int arr[], int nL, int nR)
{
    if (nL == nR)   //此时数组就剩一个元素，为有序数组
    {
        return;
    }
    int nM = (nL + nR) / 2;
    mergeSort1(arr, nL, nM);
    mergeSort1(arr, nM + 1, nR);
    mergeArr(arr, nL, nM, nR);
}

//非递归归并
void mergeSort2(int arr[], int nLen)
{
    for (int i = 1; i < nLen; i *= 2)
    {
        int nL = 0;
        while (nL + i < nLen)
        {
            int nM = nL + i - 1;
            int nR = nM + i > nLen ? nLen - 1 : nM + i;
            mergeArr(arr, nL, nM, nR);
            nL = nR + 1;
        }
    }
}

//堆排
/*
    根据完全二叉树的特性，将堆顶元素与最后一个元素互换，即将最大或最小元素放在最后
    调整堆后再次循环
*/
void adjustHeap(int arr[], int nIndex, int nLen)
{
    int i = 2 * nIndex;//left child
    while (i < nLen)
    {
        if (i + 1 < nLen && arr[i+1] > arr[i])
        {
            ++i;
        }

        if (arr[nIndex] < arr[i])
        {
            swap(arr[nIndex], arr[i]);
            nIndex = i;
            i = 2 * i;
        }
        else
            break;
    }
}

void makeHeap(int arr[], int nLen)
{
    for (int i = nLen / 2; i >= 0; --i)
    {
        adjustHeap(arr, i, nLen);
    }
}

void heapSort(int arr[], int nLen)
{
    makeHeap(arr, nLen);
    for (int i = 1; i < nLen; ++i)
    {
        swap(arr[0], arr[nLen - i]);
        adjustHeap(arr, 0, nLen - i);
    }
}

//快排
/*
    冒泡的优化，找一个基准值，将比这个大的放在基准值后面，
    小的放在基准值前面，然后对前后两组再找基准值，循环至组大小为1
*/
void quickSort(int arr[], int nL, int nR)
{
    if (nL >= nR)
    {
        return;
    }

    int key = nL;
    int i = nL, j = nR;
    while (i != j)
    {
        while (j > i)
        {
            if (arr[j] < arr[key])
            {
                swap(arr[j], arr[key]);
                key = j;
                break;
            }
            --j;
        }

        while (i < j)
        {
            if (arr[i] > arr[key])
            {
                swap(arr[i], arr[key]);
                key = i;
                break;
            }
            ++i;
        }
    }

    quickSort(arr, nL, i - 1);
    quickSort(arr, i + 1, nR);
}

int main()
{
    int nLength = 10;
    int a[] = { 2, 7, 4, 6, 3, 8, 0, 9, 1, 5, 12, 19, 17, 11 };
    heapSort(a, 14);
    for (auto i : a)
    {
        printf("%d\n", i);
    }
    system("pause");
    return 0;
}