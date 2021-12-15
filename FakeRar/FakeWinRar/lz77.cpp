#include "lz77.h"
/*lz77.c*/
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>

#include "bit.h"
#include "compress.h"

/*compare_win 确定前向缓冲区中与滑动窗口中匹配的最长短语*/
static int compare_win(const unsigned char *window, const unsigned char *buffer,
                       int *offset, unsigned char *next)
{
    int match,longest,i,j,k;

    /*初始化偏移量*/
    *offset = 0;

    /*如果没有找到匹配，准备在前向缓冲区中返回0和下一个字符*/
    longest = 0;
    *next = buffer[0];

    /*在前向缓冲区和滑动窗口中寻找最佳匹配*/
    for(k=0; k<LZ77_WINDOW_SIZE; k++)
    {
        i = k;
        j = 0;
        match = 0;

        /*确定滑动窗口中k个偏移量匹配的符号数*/
        while(i<LZ77_WINDOW_SIZE && j<LZ77_BUFFER_SIZE - 1)
        {
            if(window[i] != buffer[j])
                break;

            match++;
            i++;
            j++;
        }

        /*跟踪最佳匹配的偏移、长度和下一个符号*/
        if(match > longest)
        {
            *offset = k;
            longest = match;
            *next = buffer[j];
        }
    }
    return longest;
}

/*lz77_compress  使用lz77算法压缩数据*/
int lz77_compress(const unsigned char *original,unsigned char **compressed,int size)
{
    unsigned char     window[LZ77_WINDOW_SIZE],
                      buffer[LZ77_BUFFER_SIZE],
                      *comp,
                      *temp,
                      next;
    int               offset,
                      length,
                      remaining,
                      hsize,
                      ipos,
                      opos,
                      tpos,
                      i;
    /*使指向压缩数据的指针暂时无效*/
    *compressed = NULL;

    /*写入头部信息*/
    hsize = sizeof(int);
    if((comp = (unsigned char *)malloc(hsize)) == NULL)
        return -1;
    memcpy(comp,&size,sizeof(int));

    /*初始化滑动窗口和前向缓冲区(用0填充)*/
    memset(window, 0 , LZ77_WINDOW_SIZE);
    memset(buffer, 0 , LZ77_BUFFER_SIZE);

    /*加载前向缓冲区*/
    ipos = 0;

    for(i=0; i<LZ77_BUFFER_SIZE && ipos < size; i++)
    {
        buffer[i] = original[ipos];
        ipos++;
    }

    /*压缩数据*/
    opos = hsize * 8;
    remaining = size;

    while(remaining > 0)
    {
        if((length = compare_win(window,buffer,&offset,&next)) != 0)
        {
            /*编码短语标记*/
            token = 0x00000001 << (LZ77_PHRASE_BITS - 1);

            /*设置在滑动窗口找到匹配的偏移量*/
            token = token | (offset << (LZ77_PHRASE_BITS - LZ77_TYPE_BITS - LZ77_WINOFF_BITS));

            /*设置匹配串的长度*/
            token = token | (length << (LZ77_PHRASE_BITS - LZ77_TYPE_BITS - LZ77_WINOFF_BITS - LZ77_BUFLEN_BITS));

            /*设置前向缓冲区中匹配串后面紧邻的字符*/
            token = token | next;

            /*设置标记的位数*/
            tbits = LZ77_PHRASE_BITS;
        }
        else
        {
            /*编码一个字符标记*/
            token = 0x00000000;

            /*设置未匹配的字符*/
            token = token | next;

            /*设置标记的位数*/
            tbits = LZ77_SYMBOL_BITS;
        }

        /*确定标记是大端格式*/
        token = htonl(token);

        /*将标记写入压缩缓冲区*/
        for(i=0; i<tbits; i++)
        {
            if(opos % 8 == 0)
            {
                /*为压缩缓冲区分配临时空间*/
                if((temp = (unsigned char *)realloc(comp,(opos / 8) + 1)) == NULL)
                {
                    free(comp);
                    return -1;
                }
                comp = temp;
            }

            tpos = (sizeof(unsigned long ) * 8) - tbits + i;
            bit_set(comp,opos,bit_get((unsigned char *)&token,tpos));
            opos++;
        }
        /*调整短语长度*/
        length++;

        /*从前向缓冲区中拷贝数据到滑动窗口中*/
        memmove(&window[0],&window[length],LZ77_WINDOW_SIZE - length);
        memmove(&window[LZ77_WINDOW_SIZE - length],&buffer[0],length);
        memmove(&buffer[0],&buffer[length],LZ77_BUFFER_SIZE - length);
        /*向前向缓冲区中读取更多数据*/
        for(i = LZ77_BUFFER_SIZE - length; i<LZ77_BUFFER_SIZE && ipos <size; i++)
        {
            buffer[i] = original[ipos];
            ipos++;
        }

        /*调整剩余未匹配的长度*/
        remaining = remaining - length;
    }
    /*指向压缩数据缓冲区*/
    *compressed = comp;
    /*返回压缩数据中的字节数*/
    return ((opos - 1) / 8) + 1;
}

/*lz77_uncompress  解压缩由lz77_compress压缩的数据*/
int lz77_uncompress(const unsigned char *compressed,unsigned char **original)
{
    unsigned char window[LZ77_WINDOW_SIZE],
                  buffer[LZ77_BUFFER_SIZE]
                  *orig,
                  *temp,
                  next;
    int           offset,
                  length,
                  remaining,
                  hsize,
                  size,
                  ipos,
                  opos,
                  tpos,
                  state,
                  i;
    /*使指向原始数据的指针暂时无效*/
    *original = orig = NULL;

    /*获取头部信息*/
    hsize = sizeof(int);
    memcpy(&size,compressed,sizeof(int));

    /*初始化滑动窗口和前向缓冲区*/
    memset(window, 0, LZ77_WINDOW_SIZE);
    memset(buffer, 0, LZ77_BUFFER_SIZE);

    /*解压缩数据*/
    ipos = hsize * 8;
    opos = 0;
    remaining = size;

    while(remaining > 0)
    {
        /*获取压缩数据中的下一位*/
        state = bit_get(compressed,ipos);
        ipos++;

        if(state == 1)
        {
            /*处理的是短语标记*/
            memset(&offset, 0, sizeof(int));

            for(i=0; i<LZ77_WINOFF_BITS; i++)
            {
                tpos = (sizeof(int)*8) - LZ77_WINOFF_BITS + i;
                bit_set((unsigned char *)&offset, tpos, bit_get(compressed,ipos));
                ipos++;
            }

            memset(&length, 0, sizeof(int));
            for(i=0; i<LZ77_BUFLEN_BITS; i++)
            {
                tpos = (sizeof(int)*8) - LZ77_BUFLEN_BITS + i;
                bit_set((unsigned char *)&length, tpos, bit_get(compressed,ipos));
                ipos++;
            }

            next = 0x00;
            for(i=0; i<LZ77_NEXT_BITS; i++)
            {
                tpos = (sizeof(unsigned char)*8) - LZ77_NEXT_BITS + i;
                bit_set((unsigned char *)&next, tpos, bit_get(compressed,ipos));
                ipos++;
            }

            /*确保偏移和长度对系统有正确的字节排序*/
            offset = ntohl(offset);
            length = ntohl(length);

            /*将短语从滑动窗口写入原始数据缓冲区*/
            i=0;
            if(opos>0)
            {
                if((temp = (unsigned char *)realloc(orig,opos+length+1)) == NULL)
                {
                    free(orig);
                    return 1;
                }
                orig = temp;
            }
            else
            {
                if((orig = (unsigned char *)malloc(length+1)) == NULL)
                    return -1;
            }

            while(i<length && remaining>0)
            {
                orig[opos] = window[offset + i];
                opos++;
                /*在前向缓冲区中记录每个符号，直到准备更新滑动窗口*/
                buffer[i] = window[offset + i];
                i++;

                /*调整剩余符号总数*/
                remaining --;
            }

            /*将不匹配的符号写入原始数据缓冲区*/
            if(remaining > 0)
            {
                orig[opos] = next;
                opos++;

                /*仍需在前向缓冲区中记录此符号*/
                buffer[i] = next;

                /*调整剩余字符总数*/
                remaining--;
            }
            /*调整短语长度*/
            length++;
        }
        else
        {
            /*处理的是字符标记*/
            next = 0x00;
            for(i=0; i<LZ77_NEXT_BITS; i++)
            {
                tpos = (sizeof(unsigned char)*8) - LZ77_NEXT_BITS + i;
                bit_get((unsigned char *)&next, tpos,bit_get(compressed,ipos));
                ipos++;
            }

            /*将字符写入原始数据缓冲区*/
            if(opos > 0)
            {
                if((temp = (unsigned char*)realloc(orig,opos+1)) == NULL)
                {
                    free(orig);
                    return -1;
                }
                orig = temp;
            }
            else
            {
                if((orig = (unsigned char *)malloc(1)) == NULL)
                return -1;
            }
            orig[opos] = next;
            opos++;

            /*在前向缓冲区中记录当前字符*/
            if(remaining > 0)
                buffer[0] = next;
            /*调整剩余数量*/
            remaining--;

            /*设置短语长度为1*/
            length = 1;
        }
        /*复制前向缓冲中的数据到滑动窗口*/
        memmove(&window[0], &window[length],LZ7_WINDOW_BITS - length);
        memmove(&window[LZ77_WINDOW_SIZE - length], &buffer[0], length);
    }
    /*指向原始数据缓冲区*/
    *original = orig;

    /*返回解压缩的原始数据中的字节数*/
    return  opos;
}
