#include <reent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include <cerrno>
#include <csignal>
#include <cstddef>
// #include <cstring>

extern int __io_putchar(int ch) __attribute__((weak));
extern int __io_getchar(void) __attribute__((weak));

extern "C" _ssize_t _write_r(_reent *reent, int fd, const void *buf, size_t nbytes)
{
  (void)reent;
  (void)fd;
  int i;
  char *b = (char *)buf;
  for (i = 0; i < (int)nbytes; i++)
    {
      if (*(b + i) == '\n')
        {
          __io_putchar('\r');
        }
      __io_putchar(*(b + i));
    }
  return (nbytes);
}

extern "C" _ssize_t _write(int fd, char *buf, size_t nbytes)
{
  (void)fd;
  (void)buf;
  int i;
  for (i = 0; i < (int)nbytes; i++)
    {
      __io_putchar(*buf++);
    }
  return (nbytes);
}

extern "C" int _close_r(_reent *reent, int fildes)
{
  (void)fildes;
  reent->_errno = ENOSYS;
  return -1;
}

extern "C" int _execve_r(_reent *reent, const char *name, char *const *argv,
                         char *const *env)
{
  (void)name;
  (void)argv;
  (void)env;
  reent->_errno = ENOSYS;
  return -1;
}

extern "C" int _fork_r(_reent *reent)
{
  reent->_errno = ENOSYS;
  return -1;
}

extern "C" int _fstat_r(_reent *reent, int fildes, struct stat *st)
{
  (void)fildes;
  (void)st;
  reent->_errno = ENOSYS;
  return -1;
}

extern "C" int _getpid_r(_reent *reent)
{
  reent->_errno = ENOSYS;
  return -1;
}

extern "C" int _gettimeofday(_reent *reent, timeval *ptimeval, void *ptimezone)
{
  (void)ptimeval;
  (void)ptimezone;
  reent->_errno = ENOSYS;
  return -1;
}

extern "C" int _isatty_r(_reent *reent, int file)
{
  (void)file;
  reent->_errno = ENOSYS;
  return 0;
}

extern "C" int _kill_r(_reent *reent, int pid, int sig)
{
  (void)pid;
  (void)sig;
  reent->_errno = ENOSYS;
  return -1;
}

extern "C" int _link_r(_reent *reent, const char *existing, const char *now)
{
  (void)existing;
  (void)now;
  reent->_errno = ENOSYS;
  return -1;
}

extern "C" _off_t _lseek_r(_reent *reent, int file, _off_t ptr, int dir)
{
  (void)file;
  (void)ptr;
  (void)dir;
  reent->_errno = ENOSYS;
  return -1;
}

extern "C" int _open_r(_reent *reent, const char *file, int flags, int mode)
{
  (void)file;
  (void)flags;
  (void)mode;
  reent->_errno = ENOSYS;
  return -1;
}

extern "C" _ssize_t _read_r(_reent *reent, int file, void *ptr, size_t len)
{
  (void)file;
  (void)ptr;
  (void)len;
  reent->_errno = ENOSYS;
  return -1;
}

extern "C" int _readlink_r(_reent *reent, const char *path, char *buf, size_t bufsize)
{
  (void)path;
  (void)buf;
  (void)bufsize;
  reent->_errno = ENOSYS;
  return -1;
}

extern "C" int _stat_r(_reent *reent, const char *path, struct stat *buf)
{
  (void)path;
  (void)buf;
  reent->_errno = EIO;
  return -1;
}

extern "C" int _unlink_r(_reent *reent, const char *path)
{
  (void)path;
  reent->_errno = EIO;
  return (-1);
}

extern "C" void _exit(int rc)
{
  _kill_r(_REENT, rc, -1);
  while (1) {}
}

extern "C" void __attribute__((__noreturn__)) __stack_chk_fail(void)
{
  char msg[] = "*** stack smashing detected ***: terminated\n";
  write(2, msg, strlen(msg));
  raise(SIGABRT);
  _exit(127);
}
