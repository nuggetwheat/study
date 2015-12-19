#ifndef quiz_foo_hpp
#define quiz_foo_hpp

#include <initializer_list>

#include "quiz.hpp"

namespace study {

  const std::initializer_list<Item> foo {
   { "Describe the superblock methods.",
       R"(
<b>alloc_inode</b>(sb)
  Allocates pace for an inode object, including the space required for
  filesystem-specific data.

<b>destroy_inode</b>(inode)
  Destroys an inode object, including the filesystem-specific data.

<b>read_inode</b>(inode)
  Fills the fields of the inode object passed as the parameter with the data on
  disk; the i_no field of the inode object identifies the specific filesystem
  inode on the disk to be read

<b>dirty_inode</b>(inode)
  Invoked when the inode is marked as modified (dirty).  Used by filesystems
  such as FeiserFS and Ext3 to update the filesystem journal on disk.

<b>write_inode</b>(inode, flag)
  Updates a filesystem inode wiht the contents of the inode object passed as the
  parameter; the i_ino field of the inode object identifies the specific
  filesystem inode on the disk to be read.

<b>put_inode</b>(inode)
  Invoked when the inode is released -- its reference counter is decreased -- to
  perform filesystem-specific operations.

<b>drop_inode</b>(inode)
  Invoked when the inode is about to be destroyed -- that is, when the last user
  releases the inode; filesystems that implement this method usually make use of
  generic_drop_inode().  This function removes every reference to the inode from
  the VFS data structures and, if the inode no longer appears in any directory,
  invokes the delete_inode() superblock method to delete the inode from the
  filesystem.

<b>delete_inode</b>(inode)
  Invoked when the inode must be destroyed.  Deletes the VFS inode in memory and
  the file data and metadata on disk.

<b>put_super</b>(super)
  Releases the superblock object passed as the parameter (because the
  corresponding filesystem is unmounted).

<b>write_super</b>(super)
  Updates a flesystem superblock with the contents of the object indicated.

<b>sync_fs</b>(sb, wait)
  Invoked when flushing the filesystem to update filesystem-specific data
  structures on disk (used by journaling filesystems).

<b>write_super_lockfs</b>(super)
  Blocks changes to the filesystem and updates the superblock with the contents
  of the object indicated.  This method is invoked when the filesystem is
  frozen, for instance by the Logical Volume Manager (LVM) driver.

<b>unlockfs</b>(super)
  Undoes the block of filesystem updates achieved by the write_super_lockfs()
  superblock method.

<b>statfs</b>(super, buf)
  Returns statistics on a filesystem by filling the buf buffer.

<b>remount_fs</b>(super, flags, data)
  Remounts the filesystem with new options (invoked when a mount option must be
  changed).

<b>clear_inode</b>(inode)
  Invoked when a disk inode is being destroyed to perform filesystem-specific
  operations.

<b>unmount_begin</b>(super)
  Aborts a mount operation because the corresponding unmount operation has been
  started (used only by network filesystems).

<b>show_options</b>(seq_file, vfsmount)
  Used to display filesystem-specific options.

<b>quota_read</b>(super, type, data, size, offset)
  Used by the quota system to read data from the file that specifies the limits
  for this filesystem.

<b>quota_write</b>(super, type, data, size, offset)
  Used by the quota system to write data into the file that specifies the limits
  for this filesystem.
)"}
  };

}

#endif // quiz_foo_hpp
