#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef uint8_t u8;
typedef int8_t i8;

typedef uint16_t u16;
typedef int16_t i16;

typedef uint32_t u32;
typedef int32_t i32;

typedef unsigned char uchar;
typedef unsigned short ushort;


#define VGA_WIDTH   80
#define VGA_HEIGHT  100

#ifndef O3
#define O3 __attribute__((optimize("O3")))
#endif


struct page{
    char content[VGA_HEIGHT][VGA_WIDTH];
    u16 cursor_x_pos;
    u16 cursor_y_pos;
    void (*__del__)(struct page*);
};


struct book{
    struct page** pg;
    u32 total_pg;
    u32 idx_last_pg;
    u32 idx_pg;
    void (*change_pg)   (struct book*, u32 off_page);
    void (*rm_page)     (struct book*, u32 off_page);
    void (*add_page)    (struct book*);
    void (*__del__)     (struct book*);
};


O3 static inline void __page__del__(struct page* self)
{
    free(self);
}


O3 static inline void __book_add_page(struct book* self)
{   

}


O3 static inline void __book_rm_page(struct book* self, u32 off_page)
{
    self->pg[off_page]->__del__(self->pg[off_page]);
    self->total_pg--;
    self->change_pg(self, self->idx_last_pg);
}


O3 static inline void __book_change_page(struct book* self, u32 off_page)
{

}


O3 static inline void __book_del_book(struct book* self)
{
    for (u32 counter = 0; counter < self->total_pg; counter++)
        self->pg[counter]->__del__(self->pg[counter]);

    free(self->pg);
    free(self);
}


O3 static inline struct page* init_page()
{
    struct page* init = (struct page*) malloc(sizeof(struct page));

    init->cursor_x_pos = 0;
    init->cursor_y_pos = 0;
    init->__del__ = __page__del__;

    return init;
}


struct book* init_book(u32 num_pg)
{
    struct book* init = (struct book*) malloc(sizeof(struct book));
    init->total_pg = num_pg;
    init->idx_last_pg = 0;
    init->idx_pg = 0;

    init->change_pg = __book_change_page;
    init->rm_page = __book_rm_page;
    init->add_page = __book_add_page;
    init->__del__ = __book_del_book;

    init->pg = malloc(sizeof(struct page*) * init->total_pg);

    for (u32 counter = 0; counter < num_pg; counter++)
        init->pg[counter] = init_page();

    return init;
}


int main(int argc, char** argv, char** envp)
{
    struct book* b = init_book(16);

    b->__del__(b);
    return EXIT_SUCCESS;
}
