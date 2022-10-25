#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <avr/io.h>

template<const uint8_t buffer_size>
class Buffer
{
    static constexpr const uint8_t byte_index = buffer_size;

    uint8_t byte[buffer_size];
    bool buffer_empty;

    public:
    
    Buffer(){ Buffer<buffer_size>::flush();}

    void set_byte_index(uint8_t index){byte_index = index;}
    uint8_t get_byte_index(void)const{return byte_index;}

    bool is_empty(void)const{return buffer_empty;}
    void set_empty(void){buffer_empty = true;}
    void set_not_empty(void){buffer_empty = false;}

    uint8_t get_byte(uint8_t index) const {return byte[index];}
    uint8_t get_byte(void) const {return byte[byte_index];}

    void set_byte(uint8_t b, uint8_t ind)
    {
        byte[ind] = b;
        Buffer<buffer_size>::set_buffer_not_empty();
    }

    void set_byte(uint8_t b)
    {
        byte[byte_index] = b;
        Buffer<buffer_size>::set_buffer_not_empty();
    }

    void flush(void)
    {
        for (uint8_t i = 0; i < buffer_size; i++)
        {
            byte[i] = 0;
        }

        buffer_empty = true;
    }

};

#endif //BUFFER_HPP