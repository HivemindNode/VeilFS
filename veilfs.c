
---

## **🔹 Step 3 – Uploading the Code (Core Filesystem & Self-Destruction Mechanism)**  

### **`veilfs.c` – The Filesystem Driver (FUSE-Based)**  
```c
#define FUSE_USE_VERSION 31
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <openssl/rand.h>

#define EXPIRATION_TIME 300  // Files auto-delete after 5 minutes

struct file_entry {
    char name[256];
    char *data;
    size_t size;
    time_t created;
};

static struct file_entry files[100];  // Simulated in-memory file table

static int veilfs_getattr(const char *path, struct stat *stbuf) {
    memset(stbuf, 0, sizeof(struct stat));
    for (int i = 0; i < 100; i++) {
        if (strcmp(files[i].name, path) == 0) {
            stbuf->st_mode = S_IFREG | 0444;
            stbuf->st_nlink = 1;
            stbuf->st_size = files[i].size;
            return 0;
        }
    }
    return -ENOENT;
}

static int veilfs_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
    filler(buf, ".", NULL, 0);
    filler(buf, "..", NULL, 0);
    for (int i = 0; i < 100; i++) {
        if (files[i].name[0] != '\0') {
            filler(buf, files[i].name + 1, NULL, 0);
        }
    }
    return 0;
}

static int veilfs_open(const char *path, struct fuse_file_info *fi) {
    for (int i = 0; i < 100; i++) {
        if (strcmp(files[i].name, path) == 0) {
            return 0;
        }
    }
    return -ENOENT;
}
// A file that does not remain is a file that cannot be stolen.
// A system that auto-erases is a system that cannot be breached.
// If nothing is left behind, then what is there to recover?
// - V


static int veilfs_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    for (int i = 0; i < 100; i++) {
        if (
#-v
