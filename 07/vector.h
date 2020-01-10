#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
#include <iterator>


template <class T>
class Allocator
{
    public:
        T* allocate(size_t size)
        {
            return static_cast<T*>(operator new(size * sizeof(T)));
        }
        void deallocate(T* data, size_t size)
        {
            operator delete(data, size*sizeof(T));
        }

        template<class... Args>
        void construct(T* data, Args&&... args)
        {
            new(data) T(std::forward<Args>(args)...);
        }
        void destroy(T* data)
        {
            data->~T();
        }
};

template <class T>
class Iterator: public std::iterator<std::random_access_iterator_tag, T>
{
    private:
        T* data;
    public:
        Iterator(T* data_) :
        data(data_)
        {}
        Iterator(const Iterator& it):
        data(it.data)
        {}

        bool operator ==(const Iterator<T>& equal) const 
        {
            return data == equal.data;
        }
        bool operator !=(const Iterator<T>& not_equal) const
        {
            return data != not_equal.data;
        }
        bool operator >(const Iterator<T>& it) const
        {
            return (data > it.data);
        }
        bool operator <(const Iterator<T>& it) const
        {
            return data < it.data;
        }
        bool operator >=(const Iterator<T>& it) const
        {
            return data >= it.data;
        }
        bool operator <=(const Iterator<T>& it) const
        {
            return data <= it.data;
        }
        T& operator[](size_t i)
        {
            return data[i];
        }
        const T& operator[](size_t i) const 
        {
            return data[i];
        }

        Iterator operator+(size_t size)
        {
            Iterator tmp(this->data + size);
            return tmp;
        }
        Iterator& operator+=(size_t size)
        {
            this->data += size;
            return *this;
        }
        Iterator operator-(size_t size)
        {
            Iterator tmp(this->data + size);
            return tmp;
        }
        Iterator& operator-=(size_t size)
        {
            this->data -= size;
            return *this;
        }
        
        const T& operator*()const 
        {
            return *data;
        }
        
        T& operator*()
        {
            return *data;
        }
        Iterator& operator++()
        {
            data++;
            return *this;
        }
        Iterator operator++(int)
        {
            Iterator tmp(*this);
            data++;
            return tmp;
        }
        Iterator& operator--()
        {
            data--;
            return *this;
        }
        Iterator operator--(int)
        {
            Iterator tmp(*this);
            data--;
            return tmp;
        }
        const T* operator ->()const 
        {
            return data;
        }
        T* operator->()
        {
            return data;
        }
};

template <class T>
class Vector
{
    private:
        Allocator<T> allocator;
        T* data;
        size_t cur_size;
        size_t size;
        T* ptr;
    public:
        explicit Vector(size_t size_ = 0): 
            ptr(allocator.allocate(size_)), 
            cur_size(size_), 
            size(size_)
        {
            for(size_t i = 0; i < cur_size; i++)
                allocator.construct(ptr + i);
        }

        ~Vector()
        {
            while(cur_size > 0)
            {
                allocator.destroy(ptr + cur_size);
                cur_size--;
            }
            allocator.deallocate(ptr, size);
        }

        Iterator<T> begin() const 
        {
            return Iterator<T>(ptr);
        }

        Iterator<T> end() const
        {
            return Iterator<T>(ptr + cur_size);
        }

        std::reverse_iterator<Iterator<T>> rbegin()
        {
            return std::reverse_iterator<Iterator<T>>(end());
        }
        
        std::reverse_iterator<Iterator<T>> rend()
        {
            return std::reverse_iterator<Iterator<T>>(begin());
        }

        T& operator[](size_t ind)
        {
            return ptr[ind];
        }

        const T& operator[](size_t ind)const
        {
            return ptr[ind];
        }

        void pop_back()
        {
            cur_size--;
            allocator.destroy(ptr + cur_size);
        }

        void add(size_t cap)
        {
            if(cap <= cur_size)
                return ;
            
            T* tmp = allocator.allocate(cap);
            
            for(int i = 0; i < cur_size; i++)
            {
                allocator.construct(tmp + i, ptr[i]);
                allocator.destroy(ptr + i);
            }
            allocator.deallocate(ptr, size);
            ptr = tmp;
            size = cap;
        }

        void push_back(const T& val)
        {
            if(cur_size >= size)
                add(2*size + 1);
            allocator.construct(ptr + cur_size, val);
            cur_size++;
        }

        void resize(size_t n)
        {
            if(n < cur_size)
            {
                for(T* p = ptr + n; ptr != ptr + size; p++)
                    allocator.destroy(p);
            }
            cur_size = n;
            return ;

            if(n >= size)
                this->add(n);
            
            for(T* p = ptr + cur_size; p != ptr + n; p++)
                allocator.construct(p);
            
            cur_size = n;
            return ;
        }

        size_t size_()const
        {
            return cur_size;
        }

        size_t capacity_()const 
        {
            return size;
        }

        bool empty() const 
        {
            return cur_size == 0;
        }

        void clear()
        {
            while(cur_size > 0)
            {
                allocator.destroy(data + cur_size);
                cur_size--;
            }
        }
};
#endif