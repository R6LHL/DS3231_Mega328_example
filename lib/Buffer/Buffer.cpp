//#include "buffer.hpp"
/*
template<const uint8_t buffer_size>
Buffer::Buffer(){flush();}
*/
/*
template<const uint8_t buffer_size>
void Buffer<buffer_size>::set_byte_index(uint8_t index)
{
    byte_index = index;
}
*/
/*
template<const uint8_t buffer_size>
uint8_t Buffer<buffer_size>::get_byte_index(void)const
{
    return byte_index;
}
*/
/*
template<const uint8_t buffer_size>
bool Buffer<buffer_size>::is_empty(void)const
{
    return buffer_empty;
}
*/
/*
template<const uint8_t buffer_size>
void Buffer<buffer_size>::set_empty(void)
{
    buffer_empty = true;
}
*/
/*
template<const uint8_t buffer_size>
void Buffer<buffer_size>::set_not_empty(void)
{
    buffer_empty = false;
}
*/
/*
template<const uint8_t buffer_size>
uint8_t Buffer<buffer_size>::get_byte(uint8_t index)const
{
    return byte[index];
}
*/
/*
template<const uint8_t buffer_size>
uint8_t Buffer<buffer_size>::get_byte(void)const
{
    return byte[byte_index];
}
*/
/*
template<const uint8_t buffer_size>
void Buffer<buffer_size>::set_byte(uint8_t b, uint8_t ind)
{
    byte[ind] = b;
    Buffer<buffer_size>::set_buffer_not_empty();
}
*/
/*
template<const uint8_t buffer_size>
void Buffer<buffer_size>::set_byte(uint8_t byte)
{
    byte[byte_index] = byte;
    set_buffer_not_empty();
}
*/
/*
template<const uint8_t buffer_size>
void Buffer<buffer_size>::flush()
{
    for (uint8_t i = 0; i < buffer_size; i++)
    {
        byte[i] = 0;
    }

    buffer_empty = true;
}
*/