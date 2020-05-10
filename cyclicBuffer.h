#include <vector>
#include <memory>

template <typename T>
class cyclicBuffer
{

private:
    std::unique_ptr<std::vector<T>> buffer;
    typename std::vector<T>::iterator gettingPos;
    typename std::vector<T>::iterator addingPos;

    unsigned int elementCount;

public:
    // Default constructor sith size of buffer
    cyclicBuffer(int size = 1)
    {
        if (size > 0)
        {
            buffer = std::make_unique<std::vector<T>>(size);
            gettingPos = buffer->begin();
            addingPos = buffer->begin();
        }
        else
            throw std::length_error("Invalid size");
    }
    // Add new element
    void push(T newElement)
    {

        if (elementCount < buffer->size())
        {
            ++elementCount;
        }
        else
            throw std::length_error("Buffer is full"); /* this else statement is optional for when the buffer can not overwrite unread data when full and can be omitted if it can */

        if (addingPos == buffer->end())
            addingPos = buffer->begin();
        *(addingPos++) = newElement;
    }
    // Pop last element
    T pop()
    {
        if (elementCount > 0)
        {
            --elementCount;
        }
        else
            throw std::length_error("Buffer is empty");
        if (gettingPos == buffer->end())
            gettingPos = buffer->begin();
        return *(gettingPos++);
    }
    // Get number of elements available in buffer
    int getCurrentSize() const { return elementCount; }
    // Get buffer max size
    int getCapacity() const { return buffer->size(); }
    // Clear buffer
    void clear()
    {
        addingPos = buffer->begin();
        gettingPos = buffer->begin();
        elementCount = 0;
    }
};
