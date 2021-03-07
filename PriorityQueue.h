#ifndef __PRIORITY_QUEUE_H__
#define __PRIORITY_QUEUE_H__

#define true 1
#define false 0

struct Heap
{
    int numOfData;
    int heapArr[];
};

struct PQueue
{
    Heap heap;
};

// int compare function
int DataPriorityComp(int d1; int d2)
{
    return d2 - d1;
}

void HeapInit(Heap heap)
{
    heap.numOfData = 0;
    heap.heapArr = array(-1);
}

int HIsEmpty(Heap heap)
{
    if (heap.numOfData == 0)
    {
        return true;
    }
    return false;
}

int GetParentIDX(const int idx)
{
    return idx / 2;
}

int GetLChildIDX(const int idx)
{
    return idx * 2;
}

int GetRChildIDX(const int idx)
{
    return GetLChildIDX(idx) + 1;
}

int GetHiPriChildIDX(Heap heap; const int idx)
{
    if (GetLChildIDX(idx) > heap.numOfData)
    {
        return 0;
    }
    else if (GetLChildIDX(idx) == heap.numOfData)
    {
        return GetLChildIDX(idx);
    }
    else
    {
        if (DataPriorityComp(heap.heapArr[GetLChildIDX(idx)], heap.heapArr[GetRChildIDX(idx)]) < 0)
        {
            return GetRChildIDX(idx);
        }
        return GetLChildIDX(idx);
    }
}

void HInsert(Heap heap; int data)
{
    int idx = heap.numOfData + 1;

    while (idx != 1)
    {
        if (DataPriorityComp(data, heap.heapArr[GetParentIDX(idx)]) > 0)
        {
            heap.heapArr[idx] = heap.heapArr[GetParentIDX(idx)];
            idx = GetParentIDX(idx);
        }
        else
        {
            break;
        }
    }

    heap.numOfData++;
    resize(heap.heapArr, heap.numOfData + 1);
    heap.heapArr[idx] = data;
}

int HDelete(Heap heap)
{
    int retData = heap.heapArr[1];
    int lastElem = heap.heapArr[heap.numOfData];
    int parentIdx = 1;
    int childIdx;

    while (childIdx = GetHiPriChildIDX(heap, parentIdx))
    {
        if (DataPriorityComp(lastElem, heap.heapArr[childIdx]) >= 0)
        {
            break;
        }
        heap.heapArr[parentIdx] = heap.heapArr[childIdx];
        parentIdx = childIdx;
    }

    heap.heapArr[parentIdx] = lastElem;
    heap.numOfData--;
    resize(heap.heapArr, heap.numOfData + 1);
    return retData;
}

// PriorityQueue Wrapping
void PQueueInit(PQueue pq)
{
    HeapInit(pq.heap);
}

int PQIsEmpty(PQueue pq)
{
    return HIsEmpty(pq.heap);
}

void PEnqueue(PQueue pq; int data)
{
    HInsert(pq.heap, data);
}

int PDequeue(PQueue pq)
{
    return HDelete(pq.heap);
}

#endif