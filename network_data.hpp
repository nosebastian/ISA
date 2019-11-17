#ifndef __NETWORK_DATA_HPP

#define __NETWORK_DATA_HPP

#include <cstddef>
#include <ostream>

/**
 * Iterface used for classes which can be converted 
 * into network data.
 */
class network_data
{
private:
    /* data */
public:
    /**
     * Method used to encode class into bytes in network byte order
     * @param buffer Pointer to buffer allocated for data
     * @param max_size Maximum size of data, which should be writen to buffer
     * @return Size of data written to buffer. If max_size is too small -1 is returned.
     */
    virtual int encode(uint8_t * buffer, std::size_t max_size) = 0;
    /**
     * Method used for updating class properties from data in network byte order stored in buffer
     * @param buffer_start Pointer to start of buffered packet
     * @param buffer Pointer to buffer of network data
     * @param size Size of buffered data
     * @return size of data read from buffer. If enetered size of buffered data is too small to update all necesary parameters -1 is returned.
     */
    virtual int decode(const uint8_t *buffer_start, const uint8_t * buffer, std::size_t size) = 0;
    network_data();
    ~network_data();
};

#endif