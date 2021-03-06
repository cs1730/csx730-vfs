#ifndef CSX730_VFS_H
#define CSX730_VFS_H

#include <sys/types.h>
#include <stdbool.h>
#include "csx730_meta.h"

typedef int fd_t;

/**
 * Initializes the file system using the given disk image.
 *
 * @param disk_image path to disk image
 * @param size       number of blocks to support
 * @return @c true if the file system is successfully initialized;
 *         @c false otherwise
 */
bool csx730_vfs_init(const char * disk_image, size_t size);

/**
 * Creates a file or directory in the VFS at the path specified
 * by @c path. This operation should be unsuccessful if the
 * file already exists.
 *
 * @param path path to file in the VFS
 * @param dir  whether or not to create a directory
 * @return @c true if the file is successfully created;
 *         @c false otherwise
 */
bool csx730_creat(const char ** path, bool dir);

/**
 * Opens a file or directory in the VFS at the path specified
 * by @c path. The @c fd_t that is returned should be compatible
 * with the other functions in this API. This operation should
 * be unsuccessful if the file does not exist.
 *
 * @param path path to file in the VFS
 * @return an @c fd_t if the file is successfully opened;
 *         @c -1 otherwise
 */
fd_t csx730_open(const char ** path);

/**
 * Deletes a file or directory in the VFS at the path specified
 * by @p path. This operation should be unsuccessful if the
 * file does not exist.
 *
 * @param path path to file in the VFS
 * @return @c true if the file is successfully deleted;
 *         @c false otherwise
 */
bool csx730_unlink(const char ** path);

/**
 * Gets the inode information for this file and stores it in
 * the structure pointed to by @p inode. This operation should
 * be unsuccessful if the file does not exist.
 *
 * @param path  path to file in the VFS
 * @param inode destination structure
 * @return @c true if the inode info is successfully retrieved;
 *         @c false otherwise
 */
bool csx730_stat(const char ** path, inode_t * inode);

/**
 * Gets the inode information for this file and stores it in
 * the structure pointed to by @p inode. This operation should
 * be unsuccessful if the file referred to by @p fd is not
 * open.
 *
 * @param fd  file descriptor returned from @c csx730_open
 * @param inode destination structure
 * @return @c true if the inode info is successfully retrieved;
 *         @c false otherwise
 */
bool csx730_fstat(fd_t fd, inode_t * inode);

/**
 * Closes the file referred to by @p fd. This operation should
 * be unsuccessful if the file referred to by @p fd is not
 * open.
 *
 * @param fd  file descriptor returned from @c csx730_open
 * @return @c true if the file is successfully closed;
 *         @c false otherwise
 */
bool csx730_close(fd_t fd);

/**
 * Moves the read / write offset for the file referred to by @p fd
 * to the offset specified by @p offset. This is similar to a call
 * to @c lseek(2) with @c SEEK_SET. This operation should be 
 * unsuccessful if the file referred to by @p fd is not open.
 *
 * @param fd     file descriptor returned from @c csx730_open
 * @param offset offset to seek to
 * @return @c true if the read / write offset is successfully moved;
 *         @c false otherwise
 */
bool csx730_seek(fd_t fd, size_t offset);

/**
 * Reads @p len bytes of data from the buffer pointed to by @p buf
 * from the file referred to by @p fd. This function is generally
 * expected to behave in much the same way as @c read(2). This 
 * operation should be unsuccessful if the file referred to by @p fd 
 * is not open.
 *
 * @param fd  file descriptor returned from @c csx730_open
 * @param buf data buffer
 * @param len the number of bytes to write
 * @return on success, the number of bytes read;
 *         @c -1 otherwise
 */
ssize_t csx730_read(fd_t fd, void * buf, size_t len);

/**
 * Writes @p len bytes of data from the buffer pointed to by @p buf
 * into the file referred to by @p fd. This function is generally
 * expected to behave in much the same way as @c write(2).
 * This operation should be unsuccessful if the file referred to 
 * by @p fd is not open.
 *
 * @param fd  file descriptor returned from @c csx730_open
 * @param buf data buffer
 * @param len the number of bytes to write
 * @return on success, the number of bytes written;
 *         @c -1 otherwise
 */
ssize_t csx730_write(fd_t fd, void * buf, size_t len);

/**
 * Gets the inode information for the next file in a
 * directory and stores it in the structure pointed to
 * by @p inode. This operation should be unsuccessful 
 * if the file referred to by @p fd is not open.
 *
 * <p>
 * This implementation is not the most efficient as it
 * requires each file in a directory to be atleast 
 * temporarily opened in order to traverse the directory.
 *
 * @param fd  file descriptor returned from @c csx730_open
 * @param inode destination structure
 * @return @c true if the inode info is successfully retrieved;
 *         @c false otherwise
 */
bool csx730_stat_next(fd_t fd, inode_t * inode);

/**
 * Gets the inode information for the first file in a
 * directory and stores it in the structure pointed to
 * by @p inode.
 *
 * <p>
 * This implementation is not the most efficient as it
 * requires a directory to be atleast temporarily opened 
 * in order to traverse its list of children.
 *
 * @param fd  file descriptor returned from @c csx730_open
 * @param inode destination structure
 * @return @c true if the inode info is successfully retrieved;
 *         @c false otherwise
 */
bool csx730_stat_child(fd_t fd, inode_t * buf);

/**
 * Prints the block I/O summary statistics to standard output
 * according to the format specified in the project description.
 */
void csx730_pstats();

#endif // CSX730_VFS_H
