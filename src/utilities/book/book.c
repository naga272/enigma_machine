#include "utilities/idt/body_int/master/keyboard_layer.h"
#include "utilities/memory/heap/malloc.h"
#include "utilities/video/video.h"
#include "utilities/book/book.h"


extern KB_FLAGS f_t;


O3 static inline void __page__del__(struct page* self)
{
    kfree(self);
}


O3 static inline void __book_rm_page(struct book* self, u32 off_page)
{
    self->pg[off_page]->__del__(self->pg[off_page]);
    self->total_pg--;
    self->change_pg(self, self->idx_last_pg);
}


O3 static inline void try_switch_pg_to_left(struct book* self)
{
    if (!f_t.change_page_shell_left)
        return;
    
    if (self->idx_pg == 0)
        return;
} 


O3 static inline struct page* init_page()
{
    struct page* init = (struct page*) kmalloc(sizeof(struct page));

    init->cursor_x_pos = 0;
    init->cursor_y_pos = 0;
    init->__del__ = __page__del__;

    return init;
}


O3 static inline void create_new_page(struct book* self)
{
    // void* krealloc(void* old_ptr, size_t old_size, size_t new_size);
    self->pg = krealloc(
        self->pg,
        sizeof(struct page*) * self->total_pg,
        sizeof(struct page*) * self->total_pg + 1
    );

    self->pg[self->total_pg] = init_page();
    self->total_pg++;
}


O3 static inline void try_switch_pg_to_right(struct book* self)
{
    if (!f_t.change_page_shell_right)
        return;

    if (self->idx_pg == self->total_pg - 1)
        self->add_page(self);

    self->idx_last_pg = self->idx_pg;
    self->idx_pg++;
} 


O3 static inline void __book_change_page(struct book* self, u32 off_page)
{
    self->pg[off_page]->cursor_x_pos = terminal_col;
    self->pg[off_page]->cursor_y_pos = terminal_row;

    terminal_row = 0;
    terminal_col = 1;

    try_switch_pg_to_left(self);
    try_switch_pg_to_right(self);
}


O3 static inline void __book_del_book(struct book* self)
{
    for (u32 counter = 0; counter < self->total_pg; counter++)
        self->pg[counter]->__del__(self->pg[counter]);

    kfree(self->pg);
    kfree(self);
}


struct book* init_book(u32 num_pg)
{
    struct book* init = (struct book*) kmalloc(sizeof(struct book));
    init->total_pg = num_pg;
    init->idx_last_pg = 0;
    init->idx_pg = 0;

    init->change_pg = __book_change_page;
    init->rm_page = __book_rm_page;
    init->add_page = create_new_page;
    init->__del__ = __book_del_book;

    init->pg = kmalloc(sizeof(struct page*) * init->total_pg);

    for (u32 counter = 0; counter < num_pg; counter++)
        init->pg[counter] = init_page();

    return init;
}
