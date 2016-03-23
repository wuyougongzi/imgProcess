//作者：Winsir
//时间：2016/3/20
//说明：排序算法基于快速排序

template <class T>
void winsort(T *array, size_t p, size_t q)
{
    if(p <= q)
    {
        winpartion(array, p, q);
    }
}

/*
排序所有的函数都是基于 < 符号的比较
自定义的数据结构重载 < 操作符即可
*/
template<class T>
bool operator < (T t1, T t2)
{
    return t1 < t2;
}

template <class T>
void winpartion(T *array, int r, int q)
{
    if(r < q)
    {
        T temp = array[r];
        int i = r;
        int j = q;
        while(i < j)
        {
            while(i < j && temp < array[j])
                --j;

            if(i < j)
            {
                winswap(array[i], array[j]);
                i++;
            }

            while(i < j && array[i] < temp)
                ++i;

            if(i < j)
            {
                winswap(array[i], array[j]);
                j--;
            }
        }
        winpartion(array, r, i - 1);
        winpartion(array, i + 1, q);
    }
}
  
template <class T>
void winswap(T &a1, T &a2)
{
    T tmp = a1;
    a1 = a2;
    a2 = tmp;
}
