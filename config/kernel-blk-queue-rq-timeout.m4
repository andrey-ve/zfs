dnl #
dnl # 2.6.XX API change
dnl # Put a comment describing the use of blk_queue_rq_timeout()
dnl #
AC_DEFUN([ZFS_AC_KERNEL_BLK_QUEUE_RQ_TIMEOUT], [
	AC_MSG_CHECKING([whether blk_queue_rq_timeout() is available])
	tmp_flags="$EXTRA_KCFLAGS"
	EXTRA_KCFLAGS="-Wno-unused-but-set-variable"
	ZFS_LINUX_TRY_COMPILE([
		#include <linux/blkdev.h>
	],[
		struct request_queue *q = NULL;
		blk_queue_rq_timeout(q, 0);
	],[
		AC_MSG_RESULT(yes)
		AC_DEFINE(HAVE_BLK_QUEUE_RQ_TIMEOUT, 1,
		          [blk_queue_rq_timeout() is available])
	],[
		AC_MSG_RESULT(no)
	])

	AC_MSG_CHECKING([whether blk_queue_rq_timeout() is GPL-only])
	ZFS_LINUX_TRY_COMPILE([
		#include <linux/module.h>
		#include <linux/blkdev.h>

		MODULE_LICENSE("CDDL");
	],[
		struct request_queue *q = NULL;
		blk_queue_rq_timeout(q, 0);
	],[
		AC_MSG_RESULT(no)
	],[
		AC_MSG_RESULT(yes)
		AC_DEFINE(HAVE_BLK_QUEUE_RQ_TIMEOUT_GPL_ONLY, 1,
		          [blk_queue_rq_timeout() is GPL-only])
	])
	EXTRA_KCFLAGS="$tmp_flags"
])
