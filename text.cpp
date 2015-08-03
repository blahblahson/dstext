#include <nds.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "text.h"

int dsprintf(PRINTINFO *info, int x, int y, const char *format, ...)
{
#ifdef TEXT_CLIP
    if(x < 0 || y < 0 || x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT ||
            x + info->w > SCREEN_WIDTH || y + info->h > SCREEN_HEIGHT)
        return -1;
#endif
    int ret;
    va_list ap;
    char *str = NULL;
    unsigned int i;
    int pos, ypos;

    va_start(ap, format);
#ifdef TEXT_CLIP
    ret = vsnprintf(str, (SCREEN_HEIGHT-x)/info->w, format, ap);
#else
    ret = vsprintf(str, format, ap);
#endif
    va_end(ap);

    for(i = 0; i < strlen(str); i++) {
        pos = x + i*info->w;
        for(ypos = y; ypos < y+info->h; y++)
            memcpy(info->dest + (ypos * SCREEN_WIDTH + pos), info->src + ypos-y
                    * info->w + info->chartable[str[i]], info->w);
    }

    return ret;
}

// guaranteed no-clipping (even with TEXT_CLIP defined)
int dsprintf_noclip(PRINTINFO *info, int x, int y, const char *format, ...)
{
    int ret;
    va_list ap;
    char *str = NULL;
    unsigned int i;
    int pos, ypos;

    va_start(ap, format);
    ret = vsprintf(str, format, ap);
    va_end(ap);

    for(i = 0; i < strlen(str); i++) {
        pos = x + i*info->w;
        for(ypos = y; ypos < y+info->h; y++)
            memcpy(info->dest + (ypos * SCREEN_WIDTH + pos), info->src + ypos-y
                    * info->w + info->chartable[str[i]], info->w);
    }

    return ret;
}
