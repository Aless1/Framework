#ifndef __TOOLS_CIRBUFFER__
#define __TOOLS_CIRBUFFER__

namespace Tools {
class CirBuffer {
public:
    CirBuffer(int size) : _size(size), _index_write(0), _index_read(0) {
        _buff = new char[_size];
    }

    ~CirBuffer() {
        delete[] _buff;
    }

public:
    bool Write(const char * data, int len) {
        int buff_len = getBufferLen();
        if(buff_len < len) {
            return false;
        }

        if(_size - _index_write  < len) {
            memcpy(_buff + _index_write, data, len);   
        } else {
            memcpy(_buff + _index_write, data, _size - _index_write);
            memcpy(_buff, data + _size - _index_write, len - _size + _index_write);
        }
        return true;
    }

    void Read(char * data, int & len) {
        len = getBufferLen();
        if(_size - _index_read  < len) {
            memcpy(data, _buff, len);
        } else {
            memcpy(data, _buff, _size - _index_read);
            memcpy(data + _size - _index_read, _buff, len - _size + _index_read);
        }
    }

    bool Out(int len) {
        int buff_len = getBufferLen();
        if(buff_len < len) {
            return false;
        }
        
        _index_read = (_index_read + len) % _size;
        return true;
    }

private:
    int getBufferLen() {
        if(_index_write >= _index_read) {
            return _index_write - _index_read;      
        } else {
            return _size + _index_write - _index_read;
        }
    }

private:
    char * _buff;
    int _size;
    int _index_write;
    int _index_read;
};

}
#endif // __TOOLS_CIRBUFFER__