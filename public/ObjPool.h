#ifndef __TOOL_OBJPOOL__
#define __TOOL_OBJPOOL__

namespace Tools {

struct chunk {
    void * data;
    chunk * next;
};

template <typename T>
class ObjPool{
public:
    ObjPool(int chunk_size) : _chunk_size(chunk_size), chunks(NULL) {
        if(chunk_size < 0) {
            std::err << "ObjPool err" << endl;
            return;
        }    
        allocate_chunk();
    }
    ~ObjPool() {}

    T& acquire_object();
    void release_object(T& obj); 

private:
    void allocate_chunk();

private:
    int _chunk_size;
    chunk * chunks;
};

}

#define OBJECT_POOL(class, size) new ObjPool<class>(size)
#endif // __TOOL_OBJPOOL__
