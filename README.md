# SetWorkingSet
A command line program to set the working set of a process.

Usage:

```
SetWorkingSet PID [MinSize MaxSize]

  PID = decimal value of the process ID you want to alter.
  MinSize MaxSize = values passed to the SetProcessWorkingSetSize API.
  If omitted they are passed to the API as -1 to remove as many pages as possible.

e.g. SetWorkingSet A_Pid__Number__Here 204800 1413120
```

See the documentation for the [SetProcessWorkingSetSize](https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-setprocessworkingsetsize) function for more information.