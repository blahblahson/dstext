#ifndef _TEXT_H_
#define _TEXT_H_

// right now this only works with monospace text

// undefine this to remove clipping, or use dsprintf_noclip
#define TEXT_CLIP

#ifndef u16
typedef unsigned short int u16;
#endif

// predefined generic character table
extern int text_generic_ctable[];

struct PRINTINFO {
    int w, h;
    u16 *dest;
    u16 *src;
    int chartable[128];
};

int dsprintf(PRINTINFO *, int, int, const char *, ...);
int dsprintf_noclip(PRINTINFO *, int, int, const char *, ...);

#endif /* _TEXT_H_ */
