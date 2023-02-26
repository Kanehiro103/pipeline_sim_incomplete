#ifndef _READ_H_
#define _READ_H_

#include "register.h"

#define BUFFER_SIZE 256

//16進表記の命令が書かれたファイルを受け取り、メモリに書き込む
int read_(reg_set*, char*);

#endif