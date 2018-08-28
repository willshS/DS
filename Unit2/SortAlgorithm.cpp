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

//ð��
/*
    �����Ƚϣ���ĺ��ƣ�һ��ѭ��֮�����һλ���
*/
void bubbleSort(int arr[], int nLen)
{
    for (int i = 0; i < nLen; ++i)
    {
        bool bExchange = false; //�Ż�����һ��ѭ��û���κθı䣬����ǰ����
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

//ѡ��
/*
    ѡ������Ԫ�أ����������һ��Ԫ�ؽ���
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

//����
/*
    ��Ԫ����ǰ������������룬��ʼ��������Ϊarr[0]
    ���������Ϊ�����ʼ��Ϊ���򣬲��������ٶȼ�ΪO(n)
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

//ϣ��
/*
    ϣ���ǲ���������Ż���ϣ��ͨ��һ�����ཫ������飬�ֱ��ÿһ����в�������
    Ȼ����С���࣬�ٶ�ÿһ����в����������ղ���Ϊ1������������ɼ�Ϊ��������
    ����������ٵĳ�Ϊ�������һ�β��������ٶȷǳ���
*/
void shellSort(int arr[], int nLen)
{
    int gap = nLen / 2;//��ʼ����
    for (; gap > 0; gap /=2)    //����ÿ�εݼ�һ�룬�����ǲ�������
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

//�鲢
/*
    �鲢��ͨ�����η��������Ϊ���ɸ��������飬��������������ϲ�Ϊһ����������
    ��˹鲢Ҫ�����黮��Ϊһ��Ԫ�أ�Ȼ��ͣ�غϲ�
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

//�ݹ�鲢
void mergeSort1(int arr[], int nL, int nR)
{
    if (nL == nR)   //��ʱ�����ʣһ��Ԫ�أ�Ϊ��������
    {
        return;
    }
    int nM = (nL + nR) / 2;
    mergeSort1(arr, nL, nM);
    mergeSort1(arr, nM + 1, nR);
    mergeArr(arr, nL, nM, nR);
}

//�ǵݹ�鲢
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

//����
/*
    ������ȫ�����������ԣ����Ѷ�Ԫ�������һ��Ԫ�ػ���������������СԪ�ط������
    �����Ѻ��ٴ�ѭ��
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

//����
/*
    ð�ݵ��Ż�����һ����׼ֵ�����������ķ��ڻ�׼ֵ���棬
    С�ķ��ڻ�׼ֵǰ�棬Ȼ���ǰ���������һ�׼ֵ��ѭ�������СΪ1
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