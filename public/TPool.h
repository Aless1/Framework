#ifndef __LIB_TPOOL__
#define __LIB_TPOOL__

namespace Lib {
template <typename T, int chunks_count = 1, int chunks_size = 64>
class TPool {

struct ChunkList;
struct Chunk {
    char buff[sizeof(T)];
    ChunkList * parent;
    Chunk * prev;
    Chunk * next;
};

struct ChunkList {
    Chunk chunks[chunks_size];
    int used;
    ChunkList * prev;
    ChunkList * next;  
};

public:
    TPool() : _head(NULL), _head_list(NULL), _chunk_list_count(0) {
        alloc_chunklist(chunks_count);
    }
    
    ~TPool() {
        while(_head_list) {
            ChunkList * temp = _head_list;
            _head_list = _head_list->next;
            delete temp;
        } 
    }

public:
    T * Create() {
        if(!_head) {
            alloc_chunklist(1);
        }
        T * t = new (_head->buff)T();
        remove_chunk(_head);
        chunk->parent->used++;
        return t;
    }
    
    template<typename... Args>
    T * Create(Args... args) {
        if(!_head) {
            alloc_chunklist(1);
        }
        T * t = new (_head->buff)T(args...);
        remove_chunk(_head);
        chunk->parent->used++;
        return t;
    }

    void Recover(T * t) {
        t->~T();
        Chunk * chunk = (Chunk *)t;
        if(chunk->parent->used == 1 && _chunk_list_count > chunks_count) {
            free_chunks(chunk->parent);
        } else {
            append_chunk(chunk);
            chunk->parent->used--;
        }
    } 

private:
    void alloc_chunklist(int count) {
        for(int i = 0; i < count; i++) {
            ChunkList * chunklist = new ChunkList();
            arrage_chunklist(chunklist);
            chunklist->prev = NULL;
            chunklist->next = _head_list;
            if(_head_list) {
                _head_list->prev = chunklist;
            }
            _head_list = chunklist;
        }
        _chunk_list_count += count;
    }

    void arrage_chunks(ChunkList * chunklist) {
        chunklist->used = 0;
        for(int i = 0; i < chunks_size; i++) {
            chunklist->chunks[i]->parent = chunklist;
            chunklist->chunks[i]->next =  _head;
            append_chunk(chunklist->chunks[i]);
        }
    }

    void free_chunks(ChunkList * chunklist) {
        for(int i = 0; i < chunks_size; i++) {
            remove_chunk(chunklist->chunks[i]);
        }

        if(chunklist == _head_list) {
            _head_list = _head_list->next;
        }
        _chunk_list_count--;
        delete chunklist;          
    }

    void append_chunk(Chunk * chunk) {
        chunk->prev = NULL:
        chunk->next = _head;
        if(_head) {
            _head->prev = chunk;
        }
    }

    void remove_chunk(Chunk * chunk) {
        if(chunk->next) {
            chunk->next->prev = chunk->prev;
        }

        if(chunk->prev) {
            chunk->prev->next = chunk->next;
        }
    }

private:
    Chunk * _head;
    ChunkList * _head_list;
    int _chunk_list_count;
}

#define CREATE_FROM_POOL(pool, ...) pool.Create(__AV_ARGS__)

#endif // __LIB_TPOOL__`_
