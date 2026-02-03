#ifndef BOOK_H
#define BOOK_H


struct page{
    uchar content[VGA_HEIGHT][VGA_WIDTH];
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


struct book* init_book(u32 num_pg);

#endif