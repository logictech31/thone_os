#pragma once
#include "types.hxx"

class Port {
protected:
    uint16_t port_num;
    Port(uint16_t port_num);
    ~Port();
};

class Port_8bit: public Port {
public:
    Port_8bit(uint16_t port_num);
    ~Port_8bit();
    virtual void Write(uint8_t data);
    virtual uint8_t Read();
};

class Port_8bit_Slow: public Port_8bit {
public:
    Port_8bit_Slow(uint16_t port_num);
    ~Port_8bit_Slow();
    virtual void Write(uint8_t data);
};

class Port_16bit: public Port {
public:
    Port_16bit(uint16_t port_num);
    ~Port_16bit();
    virtual void Write(uint16_t data);
    virtual uint16_t Read();
};

class Port_32bit: public Port {
public:
    Port_32bit(uint32_t port_num);
    ~Port_32bit();
    virtual void Write(uint32_t data);
    virtual uint32_t Read();
};

