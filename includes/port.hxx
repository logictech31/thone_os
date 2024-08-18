#pragma once
#include "types.hxx"

class Port {
protected:
    u16 port_num;
    Port(u16 port_num);
    ~Port();
};

class Port_8bit: public Port {
public:
    Port_8bit(u16 port_num);
    ~Port_8bit();
    virtual void Write(u8 data);
    virtual u8 Read();
};

class Port_8bit_Slow: public Port_8bit {
public:
    Port_8bit_Slow(u16 port_num);
    ~Port_8bit_Slow();
    virtual void Write(u8 data);
};

class Port_16bit: public Port {
public:
    Port_16bit(u16 port_num);
    ~Port_16bit();
    virtual void Write(u16 data);
    virtual u16 Read();
};

class Port_32bit: public Port {
public:
    Port_32bit(u32 port_num);
    ~Port_32bit();
    virtual void Write(u32 data);
    virtual u32 Read();
};
